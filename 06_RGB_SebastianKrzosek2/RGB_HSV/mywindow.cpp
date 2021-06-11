#include "mywindow.h"
#include <math.h>
#include "ui_mywindow.h"


MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{

    ui->setupUi(this);

    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    img = new QImage(szer,wys,QImage::Format_RGB32);

}

MyWindow::~MyWindow()
{
    delete ui;
}


void MyWindow::on_exitButton_clicked()
{
    qApp->quit();
}


void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.drawImage(poczX,poczY,*img);
}


void MyWindow::on_cleanButton_clicked()
{
    czysc();
    update();
}


void MyWindow::on_draw1Button_clicked()
{
    rysuj1();
    update();
}

void MyWindow::on_draw2Button_clicked()
{
    rysuj2();
    update();
}

void MyWindow::czysc()
{
    unsigned char *ptr;

    ptr = img->bits();

    int i,j;

    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
}

void MyWindow::rysuj1()
{
        unsigned char *ptr;
        ptr = img->bits();
        int szer = img->width();
        int wys = img->height();

        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                    if(ui->redRadio->isChecked()){
                        ptr[szer*4*i + 4*j]= i/2; // Skladowa BLUE
                        ptr[szer*4*i + 4*j + 1] = j/2; // Skladowa GREEN
                        ptr[szer*4*i + 4*j + 2] = ui->colorSliderRgb->value(); // Skladowa RED
                    }else{
                        if(ui->blueRadio->isChecked()){
                            ptr[szer*4*i + 4*j]= ui->colorSliderRgb->value(); // Skladowa BLUE
                            ptr[szer*4*i + 4*j + 1] = j/2; // Skladowa GREEN
                            ptr[szer*4*i + 4*j + 2] =  i/2;// Skladowa RED
                        }else{
                            ptr[szer*4*i + 4*j]= j/2;  // Skladowa BLUE
                            ptr[szer*4*i + 4*j + 1] = ui->colorSliderRgb->value(); // Skladowa GREEN
                            ptr[szer*4*i + 4*j + 2] =  i/2;// Skladowa RED
                        }
                    }
                }
        }
}

void MyWindow::on_colorSliderRgb_valueChanged(){
    rysuj1();
    update();
}

void MyWindow::on_colorSliderH_valueChanged(){
    rysuj2();
    update();
}

void MyWindow::on_colorSliderS_valueChanged(){
    rysuj2();
    update();
}

void MyWindow::on_colorSliderV_valueChanged(){
    rysuj2();
    update();
}

color MyWindow::hsvToRgb(float fH, float fS, float fV){
    float fR, fG, fB;
    float fC = fV * fS;
    float fHPrime = fmod(fH/60.0,6);
    float fX = fC * (1 -fabs(fmod(fHPrime,2) - 1));
    float fM = fV - fC;
      //qDebug()<<fH<<"  "<<fHPrime;
    if(0 <= fHPrime && fHPrime < 1) {
      fR = fC;
      fG = fX;
      fB = 0;
    } else if(1<= fHPrime && fHPrime < 2) {
      fR = fX;
      fG = fC;
      fB = 0;
    } else if(2 <= fHPrime && fHPrime <3) {
      fR = 0;
      fG = fC;
      fB = fX;
    } else if(3 <= fHPrime && fHPrime< 4) {
      fR = 0;
      fG = fX;
      fB = fC;
    } else if(4 <= fHPrime && fHPrime < 5) {
      fR = fX;
      fG = 0;
      fB = fC;
    } else if(5 <= fHPrime && fHPrime <6) {
      fR = fC;
      fG = 0;
      fB = fX;
    } else {
      fR = 0;
      fG = 0;
      fB = 0;
    }
    fR+=fM;
    fG+=fM;
    fB+=fM;
    fR*=255;
    fG*=255;
    fB*=255;

    color a;
    a.fR = fR;
    a.fG = fG;
    a.fB = fB;

    return a;
}

void MyWindow::rysuj2()
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();

    float fH, fS, fV;

    fH = ui->colorSliderH->value();
    fS = (ui->colorSliderS->value())/100.0;
    fV = (ui->colorSliderV->value())/100.0;


        color tempColor;
        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                        tempColor = hsvToRgb(fH, (i/600.0*fS), j/720.0*fV);
                        ptr[szer*4*i + 4*j]= tempColor.fB;
                        ptr[szer*4*i + 4*j + 1] = tempColor.fG;
                        ptr[szer*4*i + 4*j + 2] = tempColor.fR;
                }
        }
        update();
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    x -= poczX;
    y -= poczY;

    int kolor = 0;
    unsigned char *ptr;
    ptr = img->bits();

    if(event->button() == Qt::LeftButton)
    {
        kolor = 0;

    }
    else
    {
        kolor = 255;
    }

    if ((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
    {

        ptr[szer*4*y + 4*x] = kolor;
        ptr[szer*4*y + 4*x + 1] = kolor;
        ptr[szer*4*y + 4*x + 2] = kolor;
    }

    update();

}


