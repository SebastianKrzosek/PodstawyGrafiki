#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QImage>
#include <QPainter>
#include <QtMath>
#include <QStack>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void paintEvent(QPaintEvent*);
    void clear();
    void reset();
    void colorPixel(unsigned char *ptr, int x, int y, int color);



    void generateImage();

    void on_moveXSlider_valueChanged(int value);
    void on_MoveYSlider_valueChanged(int value);
    void on_SpinSlider_valueChanged(int value);
    void on_ScaleSlider_valueChanged(int value);
    void on_TiltXSlider_valueChanged(int value);
    void on_TiltYSlider_valueChanged(int value);
    void matrixMultiplication(double tab1[3][3], double tab2[3][3]);
    void matrixReset(double matrix[3][3]);
    void odwrocenie(double M[3][3]);
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;

    unsigned char *ptr;
    unsigned char *ptr2;

    QImage *img;
    QImage *tmpImg;
    QImage *pingwin;
    QVector<QImage*> images;


    int height;
    int width;

    int movement;

    double poruszanie[3][3];
    double obracanie[3][3];
    double skalowanie[3][3];
    double pochylanie[3][3];
    double wynik[3][3];

    int imageSize;

};

#endif // MAINWINDOW_H

