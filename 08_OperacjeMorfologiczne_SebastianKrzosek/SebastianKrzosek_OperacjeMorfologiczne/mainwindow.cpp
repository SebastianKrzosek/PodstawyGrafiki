#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    width = 500;
    height = 400;
    img = new QImage(width, height, QImage::Format_RGB32);
    img2 = new QImage(width, height, QImage::Format_RGB32);
    img3 = new QImage(width, height, QImage::Format_RGB32);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);
}

void MainWindow::paint(int x,int y, int r, int g, int b){
    unsigned char* ptr;
     ptr = img->bits();

        if (x >= 0 && x < width && y >= 0 && y < height) {
             ptr[width * 4 * y + 4 * x] = b;
             ptr[width * 4 * y + 4 * x + 1] = g;
             ptr[width * 4 * y + 4 * x + 2] = r;
         }
}

bool MainWindow::isWhiteOrBlack(int x, int y){//true = white
    unsigned char* ptr;
     ptr = img2->bits();

        if (x >= 0 && x < width && y >= 0 && y < height) {
            if ( ptr[width * 4 * y + 4 * x]) return true;
             else return false;
         }


}

void MainWindow::translate(){ //zamiana obrazka na bialo-czarny
    unsigned char* ptr;
     ptr = img->bits();

    for (int x =0;x<width;x++){
         for(int y=0;y<height;y++){
            if (    ptr[width * 4 * y + 4 * x]+
                    ptr[width * 4 * y + 4 * x + 1]+
                    ptr[width * 4 * y + 4 * x + 2] >=382 )
            {
                paint(x,y,255,255,255);
            }else{
                paint(x,y,0,0,0);
            }
        }
     }

}

void MainWindow::erosion(){
    bool flag=false;
    for(int x=0; x<width; x++)
    {
        for(int y=0; y<height; y++)
        {
            for(int i=x-(squareSize/2);i<=x+(squareSize/2);i++)
            {
                for(int j=y-(squareSize/2);j<=y+(squareSize/2);j++)
                {
                    if(y!=i && x!=j&&i >= 0 && i < width && j >= 0 && j < height){
                    if(isWhiteOrBlack(i,j)) flag=true;
                    }
                }
            }
            if(flag) {
                paint(x,y,255,255,255);
                flag=false;
            }

        }



}
     *img2 = img -> copy (0,0,width,height);
}

void MainWindow::on_pushButton_clicked()
    {
       erosion();
       update();
    }

void MainWindow::dilation(){
        bool flag=false;
        for(int x=0; x<width; x++)
        {

            for(int y=0; y<height; y++)
            {
                for(int i=x-(squareSize/2);i<=x+(squareSize/2);i++)
                {
                    for(int j=y-(squareSize/2);j<=y+(squareSize/2);j++)
                    {
                        if(y!=i && x!=j&&i >= 0 && i < width && j >= 0 && j < height){
                        if(!isWhiteOrBlack(i,j)) flag=true;
                        }
                    }
                }
                if(flag) {
                    paint(x,y,0,0,0);
                    flag=false;
                }

            }



    }
         *img2 = img -> copy (0,0,width,height);


    }

void MainWindow::on_pushButton_2_clicked()
    {

        dilation();
        update();
    }

void MainWindow::opening(){
       on_pushButton_clicked();
       on_pushButton_2_clicked();
    }

void MainWindow::on_pushButton_3_clicked()
    {
        opening();
    }

void MainWindow::closing(){
        on_pushButton_2_clicked();
        on_pushButton_clicked();

    }

void MainWindow::on_pushButton_4_clicked()
    {
        closing();
    }

void MainWindow::on_pushButton_5_clicked()//ladowanie obrazka
{
        QString filename =  QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::currentPath(),
                "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");
            if( !filename.isNull() )
            {
            }
            img->load(filename);
            *img=img->scaled(width,height,Qt::IgnoreAspectRatio);
            translate();
            *img2=img->copy(0,0,width,height);
            *img3=img->copy(0,0,width,height);
}

void MainWindow::on_pushButton_6_clicked()//reset
{
    *img= img3->copy(0,0,width,height);
    *img2= img3->copy(0,0,width,height);
    update();
}

void MainWindow::on_spinBox_valueChanged(int arg1){
        squareSize=arg1;
}
