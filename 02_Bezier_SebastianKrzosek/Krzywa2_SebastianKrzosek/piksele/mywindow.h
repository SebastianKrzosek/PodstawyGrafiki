#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QPushButton>
#include <vector>

namespace Ui {
    class MyWindow;
}

class MyWindow : public QMainWindow
{
    // Q_OBJECT jest to makro, ktore musi sie znajdowac
    // we wszystkich klasach definiujacych wlasne sygnaly i sloty
    // W naszej klasie nie jest ono potrzebne,
    // ale QtCreator dodaje je automatycznie do kazdej klasy.
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:
    struct punkt{
        int x,y;
    };
    Ui::MyWindow *ui;
    QImage *img;        // Pole przechowujace obrazek
    QImage imgcopy;    //kopia
    int szer;         // Pola przechowujace szerokosc i wysokosc rysunku
    int wys;
    int poczX;       // oraz wspolrzedne jego lewego gornego naroznika
    int poczY;
    double startX, startY, endX, endY; //wspolrzedne klikniecia
    int wybor = 1;          //potrzebne do case'a, aby okreslic co rysujemy
    int ileBokow = 3;      //minimum trojkat
    int ilePunktow = 0;
    int licznik;

    std::vector <int> punktyX; //kontener na wspolrzedne potrzebne do krzywej
    std::vector <int> punktyY;

    // Deklaracje funkcji
    void czysc();
    void rysujPiksel(int x, int y);
    void rysuj();
    void rysujLinie(int x0, int y0, int x1, int y1);
    void rysujOkrag();
    void rysujElipse();
    void rysujWielokat(int n);
    void rysujPunkt(int x, int y); //punkt potrzebny do krzywej
    void rysujKrzywa();


    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void mousePressEvent(QMouseEvent *event); //obslugiwanie myszki
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    void on_cleanButton_clicked();  //czyszczenie
    void on_exitButton_clicked(); //zamkniecie
    void on_RadioButton_clicked(); //odcinek
    void on_radioButton_clicked(); //okrag
    void on_radioButton_2_clicked(); //elipsa
    void on_radioButton_3_clicked(); //wielokat
    void on_radioButton_4_clicked(); //wielokat w elipsie
    void on_spinBox_valueChanged(int arg1); //ile wierzcholkow wielokata
    void on_radioButton_5_clicked(); //krzywa
    void on_radioButton_6_clicked();
};

#endif // MYWINDOW_H
