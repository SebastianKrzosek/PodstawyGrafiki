#include "mainwindow.h"
#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <QStack>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img= new QImage(500,500,QImage::Format_RGB32);
    img1[0]=new QImage(":/zdj1.jpg");
    img1[1]=new QImage(":/zdj2.jpg");
    img1[2]=new QImage(":/zdj3.jpg");
    img1[3]=new QImage(":/zdj4.jpg");
    for(int i=0;i<4;i++)
    {
        pokazZdjecie[i]=1;
    }
    for(int i=0;i<4;i++)
    {
        krycie[i]=100;
    }
    for(int i=0;i<4;i++)
    {
        tryb[i]=0;
    }

    ui->comboBox->addItem("zwykly",1);
    ui->comboBox->addItem("Multiply",2);
    ui->comboBox->addItem("Darken",3);
    ui->comboBox->addItem("Lighten",4);
    ui->comboBox->addItem("Diff",5);

    ui->comboBox_2->addItem("zwykly",1);
    ui->comboBox_2->addItem("Multiply",2);
    ui->comboBox_2->addItem("Darken",3);
    ui->comboBox_2->addItem("Lighten",4);
    ui->comboBox_2->addItem("Diff",5);

    ui->comboBox_3->addItem("zwykly",1);
    ui->comboBox_3->addItem("Multiply",2);
    ui->comboBox_3->addItem("Darken",3);
    ui->comboBox_3->addItem("Lighten",4);
    ui->comboBox_3->addItem("Diff",5);

    ui->comboBox_4->addItem("zwykly",1);
    ui->comboBox_4->addItem("Multiply",2);
    ui->comboBox_4->addItem("Darken",3);
    ui->comboBox_4->addItem("Lighten",4);
    ui->comboBox_4->addItem("Diff",5);


    narysuj();
    update();
}
void MainWindow::paintEvent(QPaintEvent* event){

    QPainter p(this);
    p.drawImage(50,50,*img);
}
MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::narysuj()
{

    unsigned char *wsk;
     unsigned char *wsk2;
     for(int i=0;i<500;i++)
     {
         wsk =img->scanLine(i);

         for(int j=0;j<500;j++)
         {
             wsk[4*j]=255;
              wsk[4*j+1]=255;
               wsk[4*j+2]=255;
         }
     }

     for(int k=0;k<4;k++)
     {
      if(pokazZdjecie[k]!=0)
      {
        for(int i=0;i<500;i++)
        {
            wsk =img->scanLine(i);
            wsk2 =img1[k]->scanLine(i);
            for(int j=0;j<500;j++)
            {

                double alfa=(double)krycie[k]/(double)100;
                double alfaRev=(double)1.0 - alfa;
                int r1=wsk2[4*j];//kolory nowego zdjecia
                int g1=wsk2[4*j+1];
                int b1=wsk2[4*j+2];
                int r2=wsk[4*j];//kolory dotychczasowego wyswietlanego
                int g2=wsk[4*j+1];
                int b2=wsk[4*j+2];
                if(tryb[k]==0) {}
                else if(tryb[k]==2)
                {
                    r1=darken(r1,r2);
                    g1=darken(g1,g2);
                    b1=darken(b1,b2);
                }
                else if(tryb[k]==3)
                {
                    r1=lighten(r1,r2);
                    g1=lighten(g1,g2);
                    b1=lighten(b1,b2);
                }
                else if(tryb[k]==1)
                {
                    r1=multiply(r1,r2);
                    g1=multiply(g1,g2);
                    b1=multiply(b1,b2);
                }
                else if(tryb[k]==4)
                {
                    r1=diff(r1,r2);
                    g1=diff(g1,g2);
                    b1=diff(b1,b2);
                }

                wsk[4*j]=alfa*r1+alfaRev*wsk[4*j];
                wsk[4*j+1]=alfa*g1+alfaRev*wsk[4*j+1];
                wsk[4*j+2]=alfa*b1+alfaRev*wsk[4*j+2];
                }
            }
        }
    }

      update();
}

int MainWindow::multiply(int s1 ,int b1){
    return (s1*b1)>>8;
}

int MainWindow::diff(int s1 ,int b1){
    return abs(b1-s1);

}

int MainWindow::darken(int c1, int c2){
    if(c1<c2) return c1;
    else return c2;
}

int MainWindow::lighten(int c1, int c2){
    if(c1>c2) return c1;
    else return c2;
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    pokazZdjecie[0]=arg1;
    narysuj();
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    pokazZdjecie[1]=arg1;
    narysuj();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    pokazZdjecie[2]=arg1;
    narysuj();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    pokazZdjecie[3]=arg1;
    narysuj();
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    krycie[0]=value;
    narysuj();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    krycie[1]=value;
    narysuj();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    krycie[2]=value;
    narysuj();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    krycie[3]=value;
    narysuj();
}

void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
   tryb[0]=index;
   narysuj();
}

void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    tryb[1]=index;
    narysuj();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    tryb[2]=index;
    narysuj();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    tryb[3]=index;
    narysuj();
}
