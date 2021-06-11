#include "mywindow.h"
#include "ui_mywindow.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <QColorDialog>
#include <iostream>

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui -> setupUi(this);

    szer = ui -> frame -> width();
    wys = ui -> frame -> height();
    poczX = ui -> frame -> x();
    poczY = ui -> frame -> y();

    img = new QImage(szer, wys, QImage::Format_RGB32);
    txt = new QImage(":/tekstura2.png");

    connect(ui -> translacjaX, SIGNAL(valueChanged(int)), this, SLOT(akcja())); // zmiany na suwakach
    connect(ui -> translacjaY, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> translacjaZ, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> skalowanieX, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> skalowanieY, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> skalowanieZ, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> rotacjaX, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> rotacjaY, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> rotacjaZ, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> pochylenieX, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> pochylenieY, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> pochylenieZ, SIGNAL(valueChanged(int)), this, SLOT(akcja()));

    connect(ui -> transX, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> transY, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> transZ, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> skalX, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> skalY, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> skalZ, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> rotX, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> rotY, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    connect(ui -> rotZ, SIGNAL(valueChanged(int)), this, SLOT(akcja()));
    //mozliwosc drugiej bryly
    akcja();
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_quit_clicked()
{
    qApp -> quit();
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX, poczY, *img);
}

void MyWindow::on_reset_clicked() //ustawianie wszystkich wartosci na poczatkowe
{
    img -> fill(QColor(Qt::white).rgb());
    ui -> translacjaX -> setValue(0);
    ui -> translacjaY -> setValue(0);
    ui -> translacjaZ -> setValue(0);
    ui -> skalowanieX -> setValue(100);
    ui -> skalowanieY -> setValue(100);
    ui -> skalowanieZ -> setValue(90);
    ui -> rotacjaX -> setValue(0);
    ui -> rotacjaY -> setValue(0);
    ui -> rotacjaZ -> setValue(0);
    ui -> pochylenieX ->setValue(0);
    ui -> pochylenieY ->setValue(0);
    ui -> pochylenieZ ->setValue(0);

    ui -> transX -> setValue(-200);
    ui -> transY -> setValue(-200);
    ui -> transZ -> setValue(-200);
    ui -> skalX ->setValue(110);
    ui -> skalY ->setValue(100);
    ui -> skalZ ->setValue(90);

    akcja();
}

bool MyWindow::czyWidoczna(int a1, int a2, int b1, int b2, int c1, int c2){
    return (((a1-b1)*(c2-b2)) - ((c1-b1)*(a2-b2))) < 0;
}

double MyWindow::interpolacja(int x, int y, double dx){
    return (1-dx)*x+dx*y;
}

bool MyWindow::isInTriangle(point p1, point p2, point p3, point a) //obie metody wziete z zad10
{
    int xp = a.x;
    int yp = a.y;

    int x1 = p1.x;
    int y1 = p1.y;
    int x2 = p2.x;
    int y2 = p2.y;
    int x3 = p3.x;
    int y3 = p3.y;

    x2 -= x1; y2 -= y1;
    x3 -= x1; y3 -= y1;
    xp -= x1; yp -= y1;
    double d = x2*y3 - x3*y2;
    double w1 = xp*(y2 - y3) + yp*(x3 - x2) + x2*y3 - x3*y2;
    double w2 = xp*y3 - yp*x3;
    double w3 = yp*x2 - xp*y2;
    return checkRange(w1, 0, d) && checkRange(w2, 0, d) && checkRange(w3, 0, d);
}

bool MyWindow::checkRange(double val, double min, double max)
{
    return val >= min && val <= max;
}

void MyWindow::akcja()
{
    int translationX, translationY, translationZ,
            translation2X, translation2Y, translation2Z,
            halfImgX = szer / 2, halfImgY = wys / 2,
            dlugosc;
    double pochylX, pochylY, pochylZ,
            scaleX, scaleY, scaleZ,
            scale2X, scale2Y, scale2Z,
            pomX, pomY, pomZ,
            rotateOX, rotateOY, rotateOZ,
            rotX, rotY, rotZ;
    bool x,y,z;
    dlugosc = 100;

    translationX = ui -> translacjaX -> value(); //czytanie wszystkich wartosci z suwakow i guzikow
    translationY = ui -> translacjaY -> value();
    translationZ = ui -> translacjaZ -> value();
    scaleX = (ui -> skalowanieX -> value())/100.0;
    scaleY = (ui -> skalowanieY -> value())/100.0;
    scaleZ = (ui -> skalowanieZ -> value())/100.0;
    rotateOX =ui -> rotacjaX -> value()/10000.0-1;
    rotateOY = ui -> rotacjaY -> value()/10000.0-1;
    rotateOZ = ui -> rotacjaZ -> value()/10000.0-1;
    pochylX = ui -> pochylenieX ->value();
    pochylY = ui -> pochylenieY ->value();
    pochylZ = ui -> pochylenieZ ->value();
    x = ui->x->isChecked(); //boole sprawdzajace wzg ktorej osi bedziemy pochylac
    y = ui->y->isChecked();
    z = ui->z->isChecked();

    translation2X = ui -> transX -> value();
    translation2Y = ui -> transY -> value();
    translation2Z = ui -> transZ -> value();
    scale2X = ui-> skalX -> value()/100.0 ;
    scale2Y = ui-> skalY -> value()/100.0 ;
    scale2Z = ui-> skalZ -> value()/100.0 ;
    rotX = ui -> rotX->value()/10000.0-1;
    rotY = ui -> rotY->value()/10000.0-1;
    rotZ = ui -> rotZ->value()/10000.0-1;

    img -> fill(color.rgb()); //kolor tla

    //przod glownej
    dodajPunkt(halfImgX - (dlugosc / 2), halfImgY - (dlugosc / 2), 0); //lewy gorny
    dodajPunkt(halfImgX + (dlugosc / 2), halfImgY - (dlugosc / 2), 0); //prawy gorny
    dodajPunkt(halfImgX + (dlugosc / 2), halfImgY + (dlugosc / 2), 0); //prawy dolny
    dodajPunkt(halfImgX - (dlugosc / 2), halfImgY + (dlugosc / 2), 0); //lewy dolny

    //tył glownej
    dodajPunkt(halfImgX - (dlugosc / 2), halfImgY - (dlugosc / 2), 1.0 * dlugosc); //lewy gorny
    dodajPunkt(halfImgX + (dlugosc / 2), halfImgY - (dlugosc / 2), 1.0 * dlugosc); //prawy gorny
    dodajPunkt(halfImgX + (dlugosc / 2), halfImgY + (dlugosc / 2), 1.0 * dlugosc); //prawy downy
    dodajPunkt(halfImgX - (dlugosc / 2), halfImgY + (dlugosc / 2), 1.0 * dlugosc); //lewy dolny

    //przod drugiej
    dodajPunkt2((halfImgX/12.0) - (dlugosc / 6), (halfImgY/12.0) - (dlugosc /6), 0 ); //lewy gorny
    dodajPunkt2((halfImgX/12.0) + (dlugosc / 6), (halfImgY/12.0) - (dlugosc /6), 0 ); //prawy gorny
    dodajPunkt2((halfImgX/12.0) + (dlugosc / 6), (halfImgY/12.0) + (dlugosc /6), 0 ); //prawy dolny
    dodajPunkt2((halfImgX/12.0) - (dlugosc / 6), (halfImgY/12.0) + (dlugosc /6), 0 ); //lewy dolny

    //tyl drugiej
    dodajPunkt2((halfImgX/12.0) - (dlugosc / 6), (halfImgY/12.0) - (dlugosc /6), 0.3 * dlugosc); //lewy gorny
    dodajPunkt2((halfImgX/12.0) + (dlugosc / 6), (halfImgY/12.0) - (dlugosc /6), 0.3 * dlugosc); //prawy gorny
    dodajPunkt2((halfImgX/12.0) + (dlugosc / 6), (halfImgY/12.0) + (dlugosc /6), 0.3 * dlugosc); //prawy dolny
    dodajPunkt2((halfImgX/12.0) - (dlugosc / 6), (halfImgY/12.0) + (dlugosc /6), 0.3 * dlugosc); //lewy dolny


    for (unsigned int i = 0; i <= sciany.size() - 1; i++)
    {
        sciany[i].x = sciany[i].x - halfImgX; //wysrodkowanie (modeluje jedynie polozenie bryly)
        sciany[i].y = sciany[i].y - halfImgY;

        if (rotateOX != 0) //obracanie na osi OX
        {
            pomY = ((sciany[i].y * cos(rotateOX)) - (sciany[i].z * sin(rotateOX)));
            pomZ = ((sciany[i].y * sin(rotateOX)) + (sciany[i].z * cos(rotateOX)));
            sciany[i].y = pomY;
            sciany[i].z = pomZ;
        }
        if (rotateOY != 0) //OY
        {
            pomX = ((sciany[i].x * cos(rotateOY)) + (sciany[i].z * sin(rotateOY)));
            pomZ = (((-1 * sciany[i].x) * sin(rotateOY)) + (sciany[i].z * cos(rotateOY)));
            sciany[i].x = pomX;
            sciany[i].z = pomZ;
        }
        if (rotateOZ != 0) //OZ
        {
            pomX = ((sciany[i].x * cos(rotateOZ)) - (sciany[i].y * sin(rotateOZ)));
            pomY = ((sciany[i].x * sin(rotateOZ)) + (sciany[i].y * cos(rotateOZ)));
            sciany[i].x = pomX;
            sciany[i].y = pomY;
        }
        if(rotX != 0){ //obracanie drugiej bryly na tych samych zasadach
            pomY = ((sciany2[i].y * cos(rotX)) - (sciany2[i].z * sin(rotX)));
            pomZ = ((sciany2[i].y * sin(rotX)) + (sciany2[i].z * cos(rotX)));
            sciany2[i].y = pomY;
            sciany2[i].z = pomZ;
        }
        if(rotY != 0){
            pomX = ((sciany2[i].x * cos(rotY)) + (sciany2[i].z * sin(rotY)));
            pomZ = (((-1 * sciany2[i].x) * sin(rotY)) + (sciany2[i].z * cos(rotY)));
            sciany2[i].x = pomX;
            sciany2[i].z = pomZ;
        }
        if(rotZ != 0){
            pomX = ((sciany2[i].x * cos(rotZ)) - (sciany2[i].y * sin(rotZ)));
            pomY = ((sciany2[i].x * sin(rotZ)) + (sciany2[i].y * cos(rotZ)));
            sciany2[i].x = pomX;
            sciany2[i].y = pomY;

        }

        if((pochylY != 0 || pochylZ !=0) && x == true) //pochylenie x
        {
             pomY = sciany[i].y + (sciany[i].z * (double)pochylY/100.0);
             pomZ = sciany[i].z + (sciany[i].z * (double)pochylZ/100.0);
             sciany[i].y = (double)pomY;
             sciany[i].z = (double)pomZ;
        }
        if((pochylX != 0 || pochylZ !=0) && y == true) //y
        {
             pomX = sciany[i].x + (sciany[i].z * (double)pochylX/100.0);
             pomZ = sciany[i].z + (sciany[i].z * (double)pochylZ/100.0);
             sciany[i].x = (double)pomX;
             sciany[i].z = (double)pomZ;
        }
        if((pochylX != 0 || pochylY !=0) && z == true) //z
        {
             pomX = sciany[i].x + (sciany[i].z * (double)pochylX/100.0);
             pomY = sciany[i].y + (sciany[i].z * (double)pochylY/100.0);
             sciany[i].x = (double)pomX;
             sciany[i].y = (double)pomY;
        }

        sciany[i].x = (sciany[i].x * scaleX) + halfImgX + translationX; //skalowanie
        sciany[i].y = (sciany[i].y * scaleY) + halfImgY + translationY; //i translacja
        sciany[i].z = (sciany[i].z * scaleZ) + translationZ;

        sciany2[i].x = (sciany2[i].x * scale2X) + halfImgX + translation2X;
        sciany2[i].y = (sciany2[i].y * scale2Y) + halfImgY + translation2Y;
        sciany2[i].z = (sciany2[i].z * scale2Z) + translation2Z;

        //zamiana z 3d na 2d
        sciany[i].x = (sciany[i].x / ((sciany[i].z / 1000.0) + 1.0));
        sciany[i].y = (sciany[i].y / ((sciany[i].z / 1000.0) + 1.0));

        sciany2[i].x = (sciany2[i].x / ((sciany2[i].z / 1000.0) + 0.8));
        sciany2[i].y = (sciany2[i].y / ((sciany2[i].z / 1000.0) + 0.8));
    }

    point src[4]; //do tekstury (wspolrzedne)
    src[0].x = 0;
    src[0].y = 0 ;
    src[1].x = 400;
    src[1].y = 0;
    src[2].x = 0;
    src[2].y = 400;
    src[3].x = 400;
    src[3].y = 400;

    if(widocznaSciana)
    {
        if(czyWidoczna(sciany[4].x, sciany[4].y, sciany[0].x, sciany[0].y, sciany[3].x, sciany[3].y))//lewa sciana
        {
         if(teksturowanie){
               teksturuj(sciany[4],sciany[0],sciany[7],src[0],src[1],src[2],img,txt);
               teksturuj(sciany[3],sciany[7],sciany[0],src[3],src[2],src[1],img,txt);
            }
            rysujLinie(sciany[0].x, sciany[0].y, sciany[4].x, sciany[4].y, R, G, B);
            rysujLinie(sciany[0].x, sciany[0].y, sciany[3].x, sciany[3].y, R, G, B);
            rysujLinie(sciany[7].x, sciany[7].y, sciany[3].x, sciany[3].y, R, G, B);
            rysujLinie(sciany[7].x, sciany[7].y, sciany[4].x, sciany[4].y, R, G, B);

        }
        if(czyWidoczna(sciany[0].x, sciany[0].y, sciany[4].x, sciany[4].y, sciany[1].x, sciany[1].y)) //gora
        {
         if(teksturowanie){
               teksturuj(sciany[4],sciany[5],sciany[0],src[0],src[1],src[2],img,txt);
               teksturuj(sciany[1],sciany[0],sciany[5],src[3],src[2],src[1],img,txt);
            }
            rysujLinie(sciany[0].x, sciany[0].y, sciany[4].x, sciany[4].y, R, G, B);
            rysujLinie(sciany[0].x, sciany[0].y, sciany[1].x, sciany[1].y, R, G, B);
            rysujLinie(sciany[1].x, sciany[1].y, sciany[5].x, sciany[5].y, R, G, B);
            rysujLinie(sciany[4].x, sciany[4].y, sciany[5].x, sciany[5].y, R, G, B);
        }
        if(czyWidoczna(sciany[0].x, sciany[0].y, sciany[1].x, sciany[1].y, sciany[3].x, sciany[3].y)) //przod
        {
         if(teksturowanie){
                teksturuj(sciany[0],sciany[1],sciany[3],src[0],src[1],src[2],img,txt);
                teksturuj(sciany[2],sciany[3],sciany[1],src[3],src[2],src[1],img,txt);
            }
            rysujLinie(sciany[0].x, sciany[0].y, sciany[1].x, sciany[1].y, R, G, B);
            rysujLinie(sciany[0].x, sciany[0].y, sciany[3].x, sciany[3].y, R, G, B);
            rysujLinie(sciany[2].x, sciany[2].y, sciany[3].x, sciany[3].y, R, G, B);
            rysujLinie(sciany[2].x, sciany[2].y, sciany[1].x, sciany[1].y, R, G, B);
        }
        if(czyWidoczna(sciany[1].x, sciany[1].y, sciany[5].x, sciany[5].y, sciany[6].x, sciany[6].y)) //prawa
        {
         if(teksturowanie){
               teksturuj(sciany[1],sciany[5],sciany[2],src[0],src[1],src[2],img,txt);
               teksturuj(sciany[6],sciany[2],sciany[5],src[3],src[2],src[1],img,txt);
            }
            rysujLinie(sciany[1].x, sciany[1].y, sciany[2].x, sciany[2].y, R, G, B);
            rysujLinie(sciany[1].x, sciany[1].y, sciany[5].x, sciany[5].y, R, G, B);
            rysujLinie(sciany[6].x, sciany[6].y, sciany[2].x, sciany[2].y, R, G, B);
            rysujLinie(sciany[6].x, sciany[6].y, sciany[5].x, sciany[5].y, R, G, B);
        }
        if(czyWidoczna(sciany[3].x, sciany[3].y, sciany[2].x, sciany[2].y, sciany[7].x, sciany[7].y)) // dol
        {
         if(teksturowanie){
                teksturuj(sciany[3],sciany[2],sciany[7],src[0],src[1],src[2],img,txt);
                teksturuj(sciany[6],sciany[7],sciany[2],src[3],src[2],src[1],img,txt);
            }
            rysujLinie(sciany[3].x, sciany[3].y, sciany[2].x, sciany[2].y, R, G, B);
            rysujLinie(sciany[3].x, sciany[3].y, sciany[7].x, sciany[7].y, R, G, B);
            rysujLinie(sciany[6].x, sciany[6].y, sciany[2].x, sciany[2].y, R, G, B);
            rysujLinie(sciany[6].x, sciany[6].y, sciany[7].x, sciany[7].y, R, G, B);
        }
        if(czyWidoczna(sciany[4].x, sciany[4].y, sciany[7].x, sciany[7].y, sciany[5].x, sciany[5].y)) //tyl
        {
         if(teksturowanie){
                teksturuj(sciany[7],sciany[6],sciany[4],src[0],src[1],src[2],img,txt);
                teksturuj(sciany[5],sciany[4],sciany[6],src[3],src[2],src[1],img,txt);
            }
            rysujLinie(sciany[4].x, sciany[4].y, sciany[7].x, sciany[7].y, R, G, B);
            rysujLinie(sciany[4].x, sciany[4].y, sciany[5].x, sciany[5].y, R, G, B);
            rysujLinie(sciany[6].x, sciany[6].y, sciany[5].x, sciany[5].y, R, G, B);
            rysujLinie(sciany[6].x, sciany[6].y, sciany[7].x, sciany[7].y, R, G, B);
        }
    }else
    {
    //dolna ściana
    rysujLinie(sciany[2].x, sciany[2].y, sciany[3].x, sciany[3].y, R, G, B);
    rysujLinie(sciany[2].x, sciany[2].y, sciany[6].x, sciany[6].y, R, G, B);
    rysujLinie(sciany[3].x, sciany[3].y, sciany[7].x, sciany[7].y, R, G, B);
    rysujLinie(sciany[6].x, sciany[6].y, sciany[7].x, sciany[7].y, R, G, B);

    //górna ściana
    rysujLinie(sciany[0].x, sciany[0].y, sciany[1].x, sciany[1].y, R, G, B);
    rysujLinie(sciany[0].x, sciany[0].y, sciany[4].x, sciany[4].y, R, G, B);
    rysujLinie(sciany[4].x, sciany[4].y, sciany[5].x, sciany[5].y, R, G, B);
    rysujLinie(sciany[5].x, sciany[5].y, sciany[1].x, sciany[1].y, R, G, B);

    //ściany boczne
    rysujLinie(sciany[0].x, sciany[0].y, sciany[3].x, sciany[3].y, R, G, B);
    rysujLinie(sciany[1].x, sciany[1].y, sciany[2].x, sciany[2].y, R, G, B);
    rysujLinie(sciany[4].x, sciany[4].y, sciany[7].x, sciany[7].y, R, G, B);
    rysujLinie(sciany[5].x, sciany[5].y, sciany[6].x, sciany[6].y, R, G, B);
}

    if(drugaBryla){
        rysujLinie(sciany2[2].x, sciany2[2].y, sciany2[3].x, sciany2[3].y, R, G, B);
        rysujLinie(sciany2[2].x, sciany2[2].y, sciany2[6].x, sciany2[6].y, R, G, B);
        rysujLinie(sciany2[3].x, sciany2[3].y, sciany2[7].x, sciany2[7].y, R, G, B);
        rysujLinie(sciany2[6].x, sciany2[6].y, sciany2[7].x, sciany2[7].y, R, G, B);

        //górna ściana
        rysujLinie(sciany2[0].x, sciany2[0].y, sciany2[1].x, sciany2[1].y, R, G, B);
        rysujLinie(sciany2[0].x, sciany2[0].y, sciany2[4].x, sciany2[4].y, R, G, B);
        rysujLinie(sciany2[4].x, sciany2[4].y, sciany2[5].x, sciany2[5].y, R, G, B);
        rysujLinie(sciany2[5].x, sciany2[5].y, sciany2[1].x, sciany2[1].y, R, G, B);

        //ściany boczne
        rysujLinie(sciany2[0].x, sciany2[0].y, sciany2[3].x, sciany2[3].y, R, G, B);
        rysujLinie(sciany2[1].x, sciany2[1].y, sciany2[2].x, sciany2[2].y, R, G, B);
        rysujLinie(sciany2[4].x, sciany2[4].y, sciany2[7].x, sciany2[7].y, R, G, B);
        rysujLinie(sciany2[5].x, sciany2[5].y, sciany2[6].x, sciany2[6].y, R, G, B);
    }

    sciany.clear();
    sciany2.clear();
    update(); 
}

void MyWindow::dodajPunkt(int x, int y, int z)
{
    sciany.push_back(point());
    sciany[sciany.size() - 1].x = x;
    sciany[sciany.size() - 1].y = y;
    sciany[sciany.size() - 1].z = z;
}

void MyWindow::dodajPunkt2(int x, int y, int z)
{
    sciany2.push_back(point());
    sciany2[sciany2.size() - 1].x = x;
    sciany2[sciany2.size() - 1].y = y;
    sciany2[sciany2.size() - 1].z = z;
}

void MyWindow::rysujLinie(double startX, double startY, double endX, double endY, int r, int g, int c)
{
    double a, b, pom;
    int x, y;

    if (abs(startX - endX) >= abs(startY - endY))
    {
        if (startX > endX)
        {
            pom = startX;
            startX = endX;
            endX = pom;
            pom = startY;
            startY = endY;
            endY = pom;
        }

        a = (endY - startY) / (endX - startX);
        b = endY - (a * endX);

        for (int i = startX; i <= endX; i++)
        {
            y = round((a * i) + b);
            rysujPiksel(i, y, r, g, c);
        }
    }
    else
    {
        if (startY > endY)
        {
            pom = startX;
            startX = endX;
            endX = pom;
            pom = startY;
            startY = endY;
            endY = pom;
        }

        a = (endX - startX) / (endY - startY);
        b = endX - (a * endY);

        for (int i = startY; i <= endY; i++)
        {
            x = round((a * i) + b);
            rysujPiksel(x, i, r, g, c);
        }
    }
    update();
}

void MyWindow::rysujPiksel(int x, int y, int r, int g, int b)
{
    if ((x >= 0) && (y >= 0) && (x < szer) && (y < wys))
    {
        unsigned char *ptr;
        ptr = img->bits();
        ptr[szer*4*y + 4*x + 2] = r;
        ptr[szer*4*y + 4*x + 1] = g;
        ptr[szer*4*y + 4*x] = b;
    }
}

void MyWindow::rysujPikselO(int x, int y, int r, int g, int b, QImage *obrazek)
{

    if ((x >= 0) && (y >= 0) && (x < szer) && (y < wys))
    {
        unsigned char *ptr;
        ptr = obrazek->bits();
        ptr[szer*4*y + 4*x + 2] = r;
        ptr[szer*4*y + 4*x + 1] = g;
        ptr[szer*4*y + 4*x] = b;
    }
}

void MyWindow::on_checkBox_clicked(bool checked) //box do scian widocznych
{
    widocznaSciana = checked;
    akcja();
}

void MyWindow::on_Teksturowanie_clicked(bool checked) //box do teksturowania
{
    teksturowanie = checked;
    akcja();
}

void MyWindow::teksturuj(point a1, point a2, point a3,
                         point b1, point b2, point b3,
                         QImage *dest, QImage *source)
{
    double xd, yd, u, v, w;
    int xi, yi, r, g, b, pomx, pomy;
    point pom;

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            pom.x = i;
            pom.y = j;
            if(isInTriangle(a1, a2, a3,pom)){ //uvw z prezentacji tez wzory
                v = (double)((i - a1.x) * (a3.y - a1.y) - ((j - a1.y) * (a3.x - a1.x))) /
                        (((a2.x - a1.x) * (a3.y - a1.y)) - ((a2.y - a1.y) * (a3.x - a1.x)));
                w = (double)(((a2.x - a1.x) * (j - a1.y)) - ((i - a1.x) * (a2.y - a1.y))) /
                        (((a2.x - a1.x) * (a3.y - a1.y)) - ((a2.y - a1.y) * (a3.x - a1.x)));
                u = (double)(1.0) - (v + w);

                if(!(v < 0 || v > 1 || u < 0 || u > 1 || w < 0 || w > 1 )){
                    unsigned char *ptr;
                    ptr = source ->bits();

                    xd = u * b1.x + v * b2.x + w * b3.x;
                    yd = u * b1.y + v * b2.y + w * b3.y;

                    xi = static_cast<int>(xd); //rzutowanie
                    yi = static_cast<int>(yd);

                    pomx = xi + 1;
                    pomy = yi + 1;
                    xd -= xi;
                    yd -= yi;

                    r = static_cast<int>(static_cast<int>(interpolacja(static_cast<int>
                        (interpolacja(ptr[500*4*yi + 4*xi + 2],ptr[500*4*pomy + 4*xi + 2],yd)),static_cast<int>
                        (interpolacja(ptr[500*4*yi + 4*pomx + 2],ptr[500*4*pomy + 4*pomx + 2],yd)),xd)));
                    g = static_cast<int>(static_cast<int>(interpolacja(static_cast<int>
                       (interpolacja(ptr[500*4*yi + 4*xi + 1],ptr[500*4*pomy + 4*xi + 1],yd)),static_cast<int>
                       (interpolacja(ptr[500*4*yi + 4*pomx + 1],ptr[500*4*pomy + 4*pomx + 1],yd)),xd)));
                    b = static_cast<int>(static_cast<int>(interpolacja(static_cast<int>
                       (interpolacja(ptr[500*4*yi + 4*xi],ptr[500*4*pomy + 4*xi],yd)),static_cast<int>
                       (interpolacja(ptr[500*4*yi + 4*pomx],ptr[500*4*yi + 4*pomx],yd)),xd)));


                    rysujPikselO(i,j,r,g,b,dest);
                    update();
                }
            }
        }
    }
}

void MyWindow::on_KolorTla_clicked()
{
    color = QColorDialog::getColor(Qt::white,this,"wybierz");
    if (color.isValid())
    {
        akcja();
    }
}

void MyWindow::on_KolorLinii_clicked()
{
    QColor kolor = QColorDialog::getColor(Qt::white,this,"wybierz");
    if (kolor.isValid())
    {
        R = kolor.red();
        G = kolor.green();
        B = kolor.blue();
        akcja();
    }
}

void MyWindow::on_drugaBryla_clicked(bool checked)
{
    drugaBryla = checked;
    akcja();
}
