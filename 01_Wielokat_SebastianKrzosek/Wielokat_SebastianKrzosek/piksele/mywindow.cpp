#include "mywindow.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include "ui_mywindow.h"

struct punkt{
    int x,y;
};

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    // Wywolujemy funkcje tworzaca elementy GUI
    // Jej definicja znajduje sie w pliku "ui_mywindow.h"
    ui->setupUi(this);

    // Pobieramy wymiary i wspolrzedne lewego gornego naroznika ramki
    // i ustawiamy wartosci odpowiednich pol
    // Uwaga: ramke "rysujFrame" wykorzystujemy tylko do
    // wygodnego ustaiwenia tych wymiarow. Rysunek bedziemy wyswietlac
    // bezposrednio w glownym oknie aplikacji.
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);

}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_exitButton_clicked()
{
    // qApp to globalny wskaznik do obiektu reprezentujacego aplikacje
    // quit() to funkcja (slot) powodujaca zakonczenie aplikacji z kodem 0 (brak bledu)
    qApp->quit();
}

void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);
}

void MyWindow::on_cleanButton_clicked()
{
    // Funkcja czysci (zamalowuje na bialo) obszar rysowania
    // definicja znajduje sie ponizej
    czysc();

    // Funkcja "update()" powoduje ponowne "namalowanie" calego komponentu
    // Wywoluje funkcje "paintEvent"
    update();
}

void MyWindow::czysc()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]= 0; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 0; // Skladowa RED
        }
    }
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    startX = event->x();
    startY = event->y();

    startX -= poczX;
    startY -= poczY;

    imgcopy = img->copy();
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(dynamiczne){
    *img = imgcopy.copy();
    endX = event->x();
    endY = event->y();

    endX -= poczX;
    endY -= poczY;

    rysuj();
    repaint();
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    endX = event->x(); //pobieramy wspolrzedne po puszczeniu klikniecia
    endY = event->y();

    endX -= poczX;
    endY -= poczY;

    rysuj();
    repaint();
}

void MyWindow::rysujPiksel(int x, int y)
    {
    if(!(x<0 || y<0 || x>=szer || y>=wys)){
            unsigned char *ptr;
            ptr = img->bits();
            ptr[szer*4*y + 4*x] = 255;
            ptr[szer*4*y + 4*x + 1] = 255;
            ptr[szer*4*y + 4*x + 2] = 255;
    }
    }

void MyWindow::rysujLinie(int x0, int y0, int x1, int y1){
double a,b,y,x;
int pom;

a = 1.0 * (y1-y0) / (x1 - x0); //wspolczynniki kierunkowe
b = y0 - (1.0 * a * x0);

if(x0 > x1) //w obu warunkach sprawdzamy w ktora strone rysujemy
{
    pom = x0;
    x0 = x1;
    x1 = pom;
}
if(y0>y1){
    pom = y0;
    y0 = y1;
    y1 = pom;
}

if(x0 == x1 && y0 == y1)//jeden piksel
{
    rysujPiksel(x0,y0);
}else if(x0 == x1 && y0 != y1)//linia prosta pionowa
{
    for(int i=y0 ; i<y1 ; i++)
        rysujPiksel(x1,i);
}else if(x0 != x1 && y0 == y1)//linia prosta pozioma
{
    for(int i=x0; i<x1; i++)
    {
        rysujPiksel(i,y0);
    }
}else if(a>-1.0 && a<1.0) //kat mniejszy niz 45
{
    for(int i=x0; i<x1; i++)
    {
        y = a * i + b;
        rysujPiksel(i,round(y));
    }
}
else // kat wiekszy badz rowny 45
{
    for(int i=y0; i<y1; i++)
    {
        x = 1.0*(i - b) / a;
        rysujPiksel(round(x),i);

    }
  }
}

void MyWindow::rysujOkrag(){

    double y;
    double R = sqrt(pow(endX-startX,2)+pow(endY-startY,2));

    for(int x=0 ;x <= R; x++)
    {
        y=sqrt(pow(R,2)-pow(x,2));
        y=round(y);
        rysujPiksel(x+startX,y+startY);       //x,  y
        rysujPiksel(x+startX,-y+startY);      //x, -y
        rysujPiksel(-x+startX,-y+startY);     //-x,-y
        rysujPiksel(-x+startX,y+startY);      //-x, y
        rysujPiksel(y+startX,x+startY);       //y,  x
        rysujPiksel(-y+startX,-x+startY);     //-y,-x
        rysujPiksel(-y+startX,x+startY);      //-y, x
        rysujPiksel(y+startX,-x+startY);      //y, -x
    }
}

void MyWindow::rysujElipse(){

   int x,y;
   int a = abs(startX - endX);
   int b = abs(startY - endY);

   for(double i = 0 ; i<2*M_PI ; i+=0.0001)
   {
       x = round(a*cos(i));
       y = round(b*sin(i));

       rysujPiksel(startX + x, startY + y);
       rysujPiksel(startX + x, startY - y);
       rysujPiksel(startX - x, startY + y);
       rysujPiksel(startX - x, startY - y);
   }
}

void MyWindow::rysujWielokat(int n){

    int x,y,j=0;
    int a = abs(startX - endX);
    int b = abs(startY - endY);
    punkt* lista = new punkt[n]; //tablica, ktora bedzie uzupelniana wierzcholkami

    for(double i = 0 ; i<2*M_PI ; i+=2*M_PI / n) //petla wyznaczajaca wierzcholki naszego wielokata
    {
        x = round(a*cos(i));
        y = round(b*sin(i));

        x+= startX;
        y+= startY;

        lista[j].x = x;
        lista[j].y = y;
        j++;
    }

    for(int i = 0 ; i<n-1 ; i++){ //petla rysujaca odcinki miedzy wierzcholkami wielokata
        rysujLinie(lista[i].x,lista[i].y, lista[i+1].x, lista[i+1].y);
    }
    rysujLinie(lista[n-1].x,lista[n-1].y, lista[0].x, lista[0].y);//ostatnia linia z pkt n do 0
    delete [] lista;
}

void MyWindow::on_RadioButton_clicked() //odcinek
{
    wybor = 1;
}

void MyWindow::on_radioButton_clicked() //okrag
{
    wybor = 2;
}

void MyWindow::rysuj(){

    switch(wybor)
    {
        case 1:
            rysujLinie(startX, startY, endX, endY);
            break;
        case 2:
            rysujOkrag();
            break;
        case 3:
            rysujElipse();
            break;
        case 4:
            rysujWielokat(ileBokow);
            break;
        case 5:
            rysujElipse();
            rysujWielokat(ileBokow);
            break;
        default:;
    }

}

void MyWindow::on_radioButton_2_clicked()
{
    wybor = 3;
}

void MyWindow::on_radioButton_3_clicked()
{
    wybor = 4;
}

void MyWindow::on_radioButton_4_clicked()
{
    wybor = 5;
}

void MyWindow::on_checkBox_stateChanged(int arg1)
{
    if(dynamiczne)
        dynamiczne = false;
    else
        dynamiczne = true;
}

void MyWindow::on_spinBox_valueChanged(int arg1)
{
    ileBokow = arg1;
}
