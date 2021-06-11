#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent* event);
    void rysujpiksel(int x, int y,int r, int g,int b);
    int darken(int c1, int c2);
    int lighten(int c1, int c2);
    int multiply(int s1, int b1);
    int diff(int s1, int b1);
private slots:
    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
     QImage *img;
     QImage *img1[4];

     int pokazZdjecie[4];
     int krycie[4];
     int tryb[4];
     void narysuj();

};

#endif // MAINWINDOW_H
