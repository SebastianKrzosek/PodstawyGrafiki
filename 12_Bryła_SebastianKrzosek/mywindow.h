#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>

namespace Ui
{
    class MyWindow;
}

class MyWindow : public QMainWindow
{  
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:
    Ui::MyWindow *ui;
    QImage *img;
    QImage *txt;
    QColor color = (Qt::white);

    int szer, wys, poczX, poczY, R=0, G=0, B=0;
    double rot = 10000;
    bool widocznaSciana = false;
    bool teksturowanie = false;
    bool drugaBryla = false;
    struct point {int x; int y; int z;};
    std::vector <point> sciany;
    std::vector <point> sciany2;

    void rysujPiksel(int, int, int, int, int);
    void rysujPikselO(int, int, int, int, int, QImage *obrazek);
    void rysujLinie(double, double, double, double, int, int, int);
    void dodajPunkt(int, int, int);
    void dodajPunkt2(int, int, int);
    void teksturuj(point, point, point,
                   point, point, point,
                   QImage *dest, QImage *src);
    bool czyWidoczna(int, int, int, int, int, int);
    bool isInTriangle(point p1, point p2, point p3, point a);
    bool checkRange(double val, double min, double max);
    double interpolacja(int, int, double);

private slots:
    void on_quit_clicked();
    void paintEvent(QPaintEvent*);
    void on_reset_clicked();
    void on_checkBox_clicked(bool checked);
    void on_Teksturowanie_clicked(bool checked);
    void on_KolorTla_clicked();
    void on_KolorLinii_clicked();
    void on_drugaBryla_clicked(bool checked);
    void akcja();
};

#endif
