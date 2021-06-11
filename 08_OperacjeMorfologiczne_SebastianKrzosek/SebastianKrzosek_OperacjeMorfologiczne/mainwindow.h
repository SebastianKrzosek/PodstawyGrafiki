#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPainter>
#include <stdio.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QImage *img;
    QImage *img2;
    QImage *img3;


    bool tab[500][400];
    bool tTmp[500][400];
    void paintEvent(QPaintEvent*);
    int width ;
    int height ;
    int squareSize=3;
    void paint (int x,int y,int r,int g, int b);
    void translate (); // x,y return true = white, false = black
    void erosion();
    void dilation();
    void opening();
    void closing();
    bool isWhiteOrBlack(int,int);

};

#endif // MAINWINDOW_H
