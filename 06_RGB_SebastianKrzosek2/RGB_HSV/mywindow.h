#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>

#include <QPainter>

#include <QImage>

#include <QMouseEvent>

#include <QDebug>

namespace Ui {
    class MyWindow;
}

struct color{
    float fR,fG,fB;
};


class MyWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MyWindow(QWidget *parent = 0);

    ~MyWindow();

private:

    Ui::MyWindow *ui;

    QImage *img;

    int szer;
    int wys;
    int poczX;
    int poczY;

    void czysc();
    void rysuj1();
    void rysuj2();
    color hsvToRgb(float fH, float fS, float fV);

private slots:
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void on_colorSliderRgb_valueChanged();
    void on_colorSliderH_valueChanged();
    void on_colorSliderS_valueChanged();
    void on_colorSliderV_valueChanged();
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

};

#endif // MYWINDOW_H
