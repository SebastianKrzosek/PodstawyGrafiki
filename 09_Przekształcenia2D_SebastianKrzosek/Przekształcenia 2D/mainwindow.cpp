#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    width = ui -> frame -> width();
    height = ui -> frame -> height();

    img = new QImage(width, height, QImage::Format_RGB32);
    clear();
    pingwin = new QImage(":/pingwin.jpg");
    imageSize = pingwin -> width();
    reset();
    poruszanie[0][2] = 100;
    poruszanie[1][2] = 50;
    generateImage();

}
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(0, 0, *img);

}
void MainWindow::reset()
{
    matrixReset(poruszanie);
    matrixReset(obracanie);
    matrixReset(skalowanie);
    matrixReset(pochylanie);
    matrixReset(wynik);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateImage()
{
    unsigned char * ptr;
    unsigned char * ptr2;

    ptr = img->bits();
    ptr2 = pingwin ->bits();

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            colorPixel(ptr, j, i, 255);
        }
    }
    matrixReset(wynik);

    odwrocenie(obracanie);
    odwrocenie(skalowanie);
    odwrocenie(pochylanie);

    matrixMultiplication(poruszanie, wynik);
    matrixMultiplication(obracanie, wynik);
    matrixMultiplication(skalowanie, wynik);
    matrixMultiplication(pochylanie, wynik);

    odwrocenie(obracanie);
    odwrocenie(skalowanie);
    odwrocenie(pochylanie);
    int przesuniecieX = (height / 2) + poruszanie[0][2] * 2;
    int przesuniecieY = (width / 2) + poruszanie[1][2];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int x = floor((i - przesuniecieX) * wynik[0][0] + (j - przesuniecieY) * wynik[0][1] + 225);
            int y = floor((i - przesuniecieX) * wynik[1][0] + (j - przesuniecieY) * wynik[1][1] + 225);

            if(x >= 0 && x < imageSize && y >= 0 && y < imageSize)
            {
                ptr[width * 4 * i + 4 * j] = ptr2[imageSize * 4 * x + 4 * y];
                ptr[width * 4 * i + 4 * j + 1] = ptr2[imageSize * 4 * x + 4 * y  + 1];
                ptr[width * 4 * i + 4 * j + 2] = ptr2[imageSize * 4 * x + 4 * y  + 2];
            }
        }
    }

    update();
}

//Wszystkie operacje to macierze przekształneń we współrzędnych jednorodnych
// x'   1 0 tx   x
// y' = 0 1 0  * y
// 1    0 0 1    1
void MainWindow::on_moveXSlider_valueChanged(int value)
{
    poruszanie[0][2] = value;

    generateImage();
}
// x'   1 0 0     x
// y' = 0 1 ty  * y
// 1    0 0 1     1
void MainWindow::on_MoveYSlider_valueChanged(int value)
{
    poruszanie[1][2] = value;

    generateImage();
}
// x'   cos -sin 0    x
// y' = sin cos    *  y
// 1    0    0   1    1
void MainWindow::on_SpinSlider_valueChanged(int value)
{
    double radian = (value * M_PI) / 180;
    obracanie[0][0] = qCos(radian);
    obracanie[0][1] = -qSin(radian);
    obracanie[1][0] = qSin(radian);
    obracanie[1][1] = qCos(radian);

    generateImage();
}
// x'   sx 0 0    x
// y' = 0 sy 0  * y
// 1    0 0  1    1
void MainWindow::on_ScaleSlider_valueChanged(int value)
{
    skalowanie[0][0] = (double)value / 100;
    skalowanie[1][1] = (double)value / 100;
    generateImage();
}
// x'   1 shx  0    x
// y' = 0  1   0 *  y
// 1    0  0   1    1
void MainWindow::on_TiltXSlider_valueChanged(int value)
{
    pochylanie[0][1] = (double)value / 100;

    generateImage();
}
// x'   1    0   0    x
// y' = shy  1   0 *  y
// 1    0    0   1    1
void MainWindow::on_TiltYSlider_valueChanged(int value)
{
    pochylanie[1][0] = (double)value / 100;

    generateImage();
}
//Mnożenie macierzy
void MainWindow::matrixMultiplication(double tab1[3][3], double tab2[3][3])
{
    double tmp;
    double newTab[3][3];
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            tmp = 0;
            for(int k = 0; k < 3; k++)
            {
                tmp += tab1[k][j] * tab2[i][k];
            }
            newTab[i][j] = tmp;
        }
    }
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            tab2[i][j] = newTab[i][j];
        }
    }
}

void MainWindow::matrixReset(double matrix[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            matrix[i][j] = 0;
        }
        matrix[i][i] = 1;
    }
}

void MainWindow::odwrocenie(double M[3][3])
{
    //Wyznacznik macierzy 3x3
    double det = M[0][0]*M[1][1]*M[2][2] + M[1][0]*M[2][1]*M[0][2] + M[2][0]*M[0][1]*M[1][2]
                - (M[0][0]*M[2][1]*M[1][2]) - (M[2][1]*M[1][1]*M[0][2]) - (M[1][0]*M[0][1]*M[2][2]);
        if(det != 0)
        {
            det = 1 / det;
            double T[3][3];
            //Macierz dopełnień
            T[0][0] = det * (M[1][1]*M[2][2] - (M[1][2]*M[2][1]));
            T[0][1] = det * (M[0][2]*M[2][1] - (M[0][1]*M[2][2]));
            T[0][2] = det * (M[0][1]*M[1][2] - (M[0][2]*M[1][1]));

            T[1][0] = det * (M[1][2]*M[2][0] - (M[1][0]*M[2][2]));
            T[1][1] = det * (M[0][0]*M[2][2] - (M[0][2]*M[2][0]));
            T[1][2] = det * (M[0][2]*M[1][0] - (M[0][0]*M[1][2]));

            T[2][0] = det * (M[1][0]*M[2][1] - (M[1][1]*M[2][0]));
            T[2][1] = det * (M[0][1]*M[2][0] - (M[0][0]*M[2][1]));
            T[2][2] = det * (M[0][0]*M[1][1] - (M[0][1]*M[1][0]));

            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                    M[i][j] = T[i][j];
            }
        }
}

void MainWindow::clear()
{
    ptr = img->bits();

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            colorPixel(ptr, j, i, 0);
        }
    }
    update();
}

void MainWindow::colorPixel(unsigned char *ptr, int x, int y, int color) {
    if(width - x > 0 && width + x > width && height - y > 0 && height + y > height) {
        ptr[width * 4 * y + 4 * x] = color;
        ptr[width * 4 * y + 4 * x + 1] = color;
        ptr[width * 4 * y + 4 * x + 2] = color;
    }
}

void MainWindow::on_exitButton_clicked()
{
    qApp->quit();
}
