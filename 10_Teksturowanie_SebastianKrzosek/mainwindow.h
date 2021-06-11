#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

class Point{
public:
    int x,y;
    Point(){}
    bool isClicked(int x,int y) //pomoc w chwytaniu kwadracikow
    {
        if(abs(this->x-x)<=15 && abs(this->y-y)<=15) return true;
        return false;
    }
};

class DoublePoint{
public:
    double x,y;
    DoublePoint(){}
};

class Triangle{
    public:
        Point points[3];
        bool isLeft;
        void setleft(bool setLeft){
            this->isLeft=setLeft;
        }

        bool isIn(int x, int y){
            x=x+y;
            return false;
        }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Triangle rightTriangle;
    Triangle leftTriangle;

    QImage *sourceImg;
    QImage *destinationImg;
    QImage *textureImg;

    int sourSzer;
    int sourWys;
    int sourPoczX;
    int sourPoczY;

    int destSzer;
    int destWys;
    int destPoczX;
    int destPoczY;

    int clickedY;
    int clickedX;
    int releasedX;
    int releasedY;

    void rysujOdcinek(int x0, int y0, int x1, int y1, bool isLeft);
    void rysujPiksel(int x, int y, int r, int g, int b, bool isLeft);
    void rysujPunkt(int Ax, int Ay, bool isLeft);
    void laczeniePunktow(Triangle t);
    bool isInTriangle(Triangle triangle, Point a);
    bool checkRange(double val, double min, double max);
    Point getPointFromLeft(Point a);
    DoublePoint getDoubledPointFromLeft(Point a);

private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};


#endif // MAINWINDOW_H
