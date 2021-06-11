#include "mywindow.h"
#include "ui_mywindow.h"
#include <iostream>
#include <cmath>
#include <vector>

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
    ptr = img -> bits();

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
    ui -> translacjaX -> setValue(0);
    ui -> translacjaY -> setValue(0);
    ui -> translacjaZ -> setValue(0);
    ui -> skalowanieX -> setValue(100);
    ui -> skalowanieY -> setValue(100);
    ui -> skalowanieZ -> setValue(100);
    ui -> rotacjaX -> setValue(0);
    ui -> rotacjaY -> setValue(0);
    ui -> rotacjaZ -> setValue(0);
    ui -> pochylenieX ->setValue(0);
    ui -> pochylenieY ->setValue(0);
    ui -> pochylenieZ ->setValue(0);
    update();
}

void MyWindow::akcja()
{
    int translationX, translationY, translationZ,
            halfImgX = szer / 2, halfImgY = wys / 2,
            dlugosc;
    double pochylX, pochylY, pochylZ,
            scaleX, scaleY, scaleZ,
            pomX, pomY, pomZ,
            rotateOX, rotateOY, rotateOZ;
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

    img -> fill(QColor(Qt::white).rgb()); //kolor tla

    //przod
    dodajPunkt(halfImgX - (dlugosc / 2), halfImgY - (dlugosc / 2), 0); //lewy gorny
    dodajPunkt(halfImgX + (dlugosc / 2), halfImgY - (dlugosc / 2), 0); //prawy gorny
    dodajPunkt(halfImgX + (dlugosc / 2), halfImgY + (dlugosc / 2), 0); //prawy dolny
    dodajPunkt(halfImgX - (dlugosc / 2), halfImgY + (dlugosc / 2), 0); //lewy dolny
    //tył
    dodajPunkt(halfImgX - (dlugosc / 2), halfImgY - (dlugosc / 2), 0.7 * dlugosc); //lewy gorny
    dodajPunkt(halfImgX + (dlugosc / 2), halfImgY - (dlugosc / 2), 0.7 * dlugosc); //prawy gorny
    dodajPunkt(halfImgX + (dlugosc / 2), halfImgY + (dlugosc / 2), 0.7 * dlugosc); //prawy downy
    dodajPunkt(halfImgX - (dlugosc / 2), halfImgY + (dlugosc / 2), 0.7 * dlugosc); //lewy dolny

    for (unsigned int i = 0; i <= sciany.size() - 1; i++)
    {
        sciany[i].x = sciany[i].x - halfImgX;
        sciany[i].y = sciany[i].y - halfImgY;

        //wszystkie wzory wziete sa z prezentacji
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
        sciany[i].y = (sciany[i].y * scaleY) + halfImgY + translationY;
        sciany[i].z = (sciany[i].z * scaleZ) + translationZ;

        //3D -> 2D
        sciany[i].x = (sciany[i].x / ((sciany[i].z / 1000.0) + 1.0));
        sciany[i].y = (sciany[i].y / ((sciany[i].z / 1000.0) + 1.0));
    }

    //dolna ściana
    rysujLinie(sciany[2].x, sciany[2].y, sciany[3].x, sciany[3].y);
    rysujLinie(sciany[2].x, sciany[2].y, sciany[6].x, sciany[6].y);
    rysujLinie(sciany[3].x, sciany[3].y, sciany[7].x, sciany[7].y);
    rysujLinie(sciany[6].x, sciany[6].y, sciany[7].x, sciany[7].y);

    //górna ściana
    rysujLinie(sciany[0].x, sciany[0].y, sciany[1].x, sciany[1].y);
    rysujLinie(sciany[0].x, sciany[0].y, sciany[4].x, sciany[4].y);
    rysujLinie(sciany[4].x, sciany[4].y, sciany[5].x, sciany[5].y);
    rysujLinie(sciany[5].x, sciany[5].y, sciany[1].x, sciany[1].y);

    //ściany boczne
    rysujLinie(sciany[0].x, sciany[0].y, sciany[3].x, sciany[3].y);
    rysujLinie(sciany[1].x, sciany[1].y, sciany[2].x, sciany[2].y);
    rysujLinie(sciany[4].x, sciany[4].y, sciany[7].x, sciany[7].y);
    rysujLinie(sciany[5].x, sciany[5].y, sciany[6].x, sciany[6].y);

    sciany.clear();
    update();
}

void MyWindow::dodajPunkt(int x, int y, int z)
{
    sciany.push_back(point());
    sciany[sciany.size() - 1].x = x;
    sciany[sciany.size() - 1].y = y;
    sciany[sciany.size() - 1].z = z;
}

void MyWindow::rysujLinie(double startX, double startY, double endX, double endY)
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
            rysujPiksel(i, y, 0, 0, 0);
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
            rysujPiksel(x, i, 0, 0, 0);
        }
    }
    update();
}

void MyWindow::rysujPiksel(int x, int y, int r, int g, int b)
{
    if ((x >= 0) && (y >= 0) && (x < szer) && (y < wys))
    {
        ptr[szer*4*y + 4*x + 2] = r;
        ptr[szer*4*y + 4*x + 1] = g;
        ptr[szer*4*y + 4*x] = b;
    }
}


