#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sourSzer = ui->leftFrame->width(); // nasza lewa ramka
    sourWys = ui->leftFrame->height();// "zrodlo tekstury"
    sourPoczX = ui->leftFrame->x();
    sourPoczY = ui->leftFrame->y();

    destSzer = ui->rightFrame->width(); // prawa ramka,
    destWys = ui->rightFrame->height();// miejsce w ktore przenosimy teksture
    destPoczX = ui->rightFrame->x();
    destPoczY = ui->rightFrame->y();

    textureImg = new QImage(":slonecznik");
    sourceImg = new QImage(sourSzer,sourWys,QImage::Format_ARGB32);
    destinationImg = new QImage(destSzer,destWys,QImage::Format_ARGB32);


    leftTriangle.setleft(true);// oznaczamy sobie nasza lewa ramke

    Point temp;
    temp.x = 50; temp.y = 200;
    leftTriangle.points[0]=temp;  //nakladanie "na sztywno" pkt na lewa ramke
    temp.x = 140; temp.y = 90;
    leftTriangle.points[1]=temp;
    temp.x = 220; temp.y = 190;
    leftTriangle.points[2]=temp;

    laczeniePunktow(leftTriangle);

    rightTriangle.setleft(false); //nakladanie "na sztywno" pkt na prawa ramke
    temp.x = 60; temp.y = 210;
    rightTriangle.points[0]=temp;
    temp.x = 150; temp.y = 80;
    rightTriangle.points[1]=temp;
    temp.x = 210; temp.y = 200;
    rightTriangle.points[2]=temp;

    laczeniePunktow(rightTriangle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(sourPoczX,sourPoczY,*textureImg);
    p.fillRect(sourceImg->rect(), Qt::transparent);
    p.drawImage(sourPoczX,sourPoczY,*sourceImg);
    p.fillRect(destinationImg->rect(), Qt::transparent);
    p.drawImage(destPoczX,destPoczY,*destinationImg);
}

bool MainWindow::isInTriangle(Triangle triangle, Point a){
    int xp = a.x;
    int yp = a.y;

    int x1 = triangle.points[0].x;
    int y1 = triangle.points[0].y;
    int x2 = triangle.points[1].x;
    int y2 = triangle.points[1].y;
    int x3 = triangle.points[2].x;
    int y3 = triangle.points[2].y;

    x2 -= x1; y2 -= y1;
    x3 -= x1; y3 -= y1;
    xp -= x1; yp -= y1;
    double d = x2*y3 - x3*y2;
    double w1 = xp*(y2 - y3) + yp*(x3 - x2) + x2*y3 - x3*y2;
    double w2 = xp*y3 - yp*x3;
    double w3 = yp*x2 - xp*y2;
    return checkRange(w1, 0, d) && checkRange(w2, 0, d) && checkRange(w3, 0, d);
}

bool MainWindow::checkRange(double val, double min, double max) {
  return val >= min && val <= max;
}

void MainWindow::rysujPiksel(int x, int y, int r, int g, int b, bool isLeft){
    unsigned char *ptr;
    if(isLeft){
        ptr = sourceImg->bits();
        if ((x>=0)&&(y>=0)&&(x<sourSzer)&&(y<sourWys))
        {
            ptr[sourSzer*4*y + 4*x] = b;
            ptr[sourSzer*4*y + 4*x+1] = g;
            ptr[sourSzer*4*y + 4*x + 2] = r;
            ptr[sourSzer*4*y + 4*x + 3] = 255;
        }
    }else{
        ptr = destinationImg->bits();
        if ((x>=0)&&(y>=0)&&(x<destSzer)&&(y<destWys))
        {
            ptr[sourSzer*4*y + 4*x] = b;
            ptr[sourSzer*4*y + 4*x+1] = g;
            ptr[sourSzer*4*y + 4*x + 2] = r;
            ptr[sourSzer*4*y + 4*x + 3] = 255;
        }
    }
}

void MainWindow::rysujPunkt(int Ax, int Ay, bool isLeft) //stawianie punkcikow
{
    for(int x=-4; x<3; x++){
        for(int y=-4; y<3; y++){
            rysujPiksel(Ax+x,Ay+y,255,255,0,isLeft);
        }
    }
}

void MainWindow::rysujOdcinek(int x0, int y0, int x1, int y1, bool isLeft) //metoda do polaczenia pkt (zwykle odcinki)
{
    double a,b;
    int buff;
    rysujPiksel(x0,y0,255,255,255,isLeft);

    if(x1!=x0){
        if(y0!=y1){
            if(abs(x1-x0)>=abs(y1-y0)){
                a = ((y1*1.0)-y0)/(x1-x0);
                b = y1 - a * x1;
                if (x0>x1){
                    buff=x1;
                    x1=x0;
                    x0=buff;
                }
                double y;
                for(int x=x0; x<=x1; ++x){
                    y = (a*x) + b;
                    rysujPiksel(x,(int)floor(y+0.5),255,255,255,isLeft);
                }
            }else{
                a = ((x1*1.0)-x0)/(y1-y0);
                b = x1 - a * y1;
                double x;
                if (y0>y1){
                    buff=y0;
                    y0=y1;
                    y1=buff;
                }
                for(int y=y0; y<=y1; y++){
                    x = (a*y) + b;
                    rysujPiksel((int)floor(x+0.5),y,255,255,255,isLeft);
                }
            }
        }else{
            if (x0>x1){
                buff=x1;
                x1=x0;
                x0=buff;
            }
            for(int x=x0; x<=x1; ++x){
                rysujPiksel(x,y1,255,255,255,isLeft);
            }
        }
    }else{
        if (y0>y1){
            buff=y0;
            y0=y1;
            y1=buff;
        }
        for(int y=y0; y<=y1; y++){
            rysujPiksel(x1,y,255,255,255,isLeft);
        }
    }
    update();
}

void MainWindow::laczeniePunktow(Triangle t){ //zwykle rysowanie odcinkow miedzy pkt
    for(int i=0; i<=2; i++){
        rysujPunkt(t.points[i].x,t.points[i].y, t.isLeft);
    }
    rysujOdcinek(t.points[0].x, t.points[0].y, t.points[1].x, t.points[1].y, t.isLeft);
    rysujOdcinek(t.points[1].x, t.points[1].y, t.points[2].x, t.points[2].y, t.isLeft);
    rysujOdcinek(t.points[0].x, t.points[0].y, t.points[2].x, t.points[2].y, t.isLeft);
}

Point MainWindow::getPointFromLeft(Point a) //przenoszenie pkt ( PREZENTACJA )
{
    double u,v,w;
    int x,y;
    x=a.x;
    y=a.y;

    int xa = rightTriangle.points[0].x;
    int ya = rightTriangle.points[0].y;
    int xb = rightTriangle.points[1].x;
    int yb = rightTriangle.points[1].y;
    int xc = rightTriangle.points[2].x;
    int yc = rightTriangle.points[2].y;

    v = ( (x-xa)*(yc-ya)*(1.0)-(xc-xa)*(y-ya) ) / ( (xb-xa)*(yc-ya)-(xc-xa)*(yb-ya) );
    w = ( (xb-xa)*(y-ya)*(1.0)-(x-xa)*(yb-ya) ) / ( (xb-xa)*(yc-ya)-(xc-xa)*(yb-ya) );
    u = 1 - v - w;

    Point result;
    result.x = u*leftTriangle.points[0].x + v*leftTriangle.points[1].x + w*leftTriangle.points[2].x;
    result.y = u*leftTriangle.points[0].y + v*leftTriangle.points[1].y + w*leftTriangle.points[2].y;

    return result;
}

DoublePoint MainWindow::getDoubledPointFromLeft(Point a){ //przenoszenie pkt typu double (PREZENTACJA)
    double u,v,w;
    int x,y;
    x=a.x;
    y=a.y;

    int xa = rightTriangle.points[0].x;
    int ya = rightTriangle.points[0].y;
    int xb = rightTriangle.points[1].x;
    int yb = rightTriangle.points[1].y;
    int xc = rightTriangle.points[2].x;
    int yc = rightTriangle.points[2].y;

    v = ( (x-xa)*(yc-ya)*(1.0)-(xc-xa)*(y-ya) ) / ( (xb-xa)*(yc-ya)-(xc-xa)*(yb-ya) );
    w = ( (xb-xa)*(y-ya)*(1.0)-(x-xa)*(yb-ya) ) / ( (xb-xa)*(yc-ya)-(xc-xa)*(yb-ya) );
    u = 1 - v - w;

    DoublePoint result;
    result.x = u*leftTriangle.points[0].x + v*leftTriangle.points[1].x + w*leftTriangle.points[2].x;
    result.y = u*leftTriangle.points[0].y + v*leftTriangle.points[1].y + w*leftTriangle.points[2].y;

    return result;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    clickedX = event->x();
    clickedY = event->y();

    if(clickedX>=destPoczX && clickedX<=destPoczX+destSzer && clickedY>=destPoczY && clickedY<=destPoczY+destWys){
        clickedX -= destPoczX;
        clickedY -= destPoczY;

    }else{
        clickedX -= sourPoczX;
        clickedY -= sourPoczY;
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    releasedX = event->x();
    releasedY = event->y();

    //sprawczamy czy nacisnelismy na prawej ramce,
    //jesli tak plus w okolicy jakiegos pkt, to go przesuwamy
    if(releasedX>=destPoczX && releasedX<=destPoczX+destSzer
            && releasedY>=destPoczY && releasedY<=destPoczY+destWys){
        releasedX -= destPoczX;
        releasedY -= destPoczY;
        for(int i=0; i<=2; i++){
            if(rightTriangle.points[i].isClicked(clickedX,clickedY)){
                rightTriangle.points[i].x = releasedX;
                rightTriangle.points[i].y = releasedY;
            }
        }
    }else if((releasedX>=sourPoczX && releasedX<=sourPoczX+sourSzer
              && releasedY>=sourPoczY && releasedY<=sourPoczY+sourWys)) // to samo tylko z lewa ramka
    {
        releasedX -= sourPoczX;
        releasedY -= sourPoczY;
        for(int i=0; i<=2; i++){
            if(leftTriangle.points[i].isClicked(clickedX,clickedY)){
                leftTriangle.points[i].x = releasedX;
                leftTriangle.points[i].y = releasedY;
            }
        }
    }

    sourceImg = new QImage(sourSzer,sourWys,QImage::Format_ARGB32);
    destinationImg = new QImage(destSzer,destWys,QImage::Format_ARGB32);
    laczeniePunktow(leftTriangle);
    laczeniePunktow(rightTriangle);

        for(int i=0; i<destWys; i++)
        {
            for(int j=0; j<destSzer; j++)
            {
                Point tempR;
                DoublePoint tempL;
                tempR.x = j;
                tempR.y = i;
                if(isInTriangle(rightTriangle,tempR)){
                    //d c
                    //a b
                    tempL = getDoubledPointFromLeft(tempR);
                    QColor tempCd = textureImg->pixelColor(floor(tempL.x),floor(tempL.y)); //zwracamy sobie kolory pixeli
                    QColor tempCc = textureImg->pixelColor(floor(tempL.x+1),floor(tempL.y)); //na danych miejscach
                    QColor tempCa = textureImg->pixelColor(floor(tempL.x),floor(tempL.y+1));
                    QColor tempCb = textureImg->pixelColor(floor(tempL.x+1),floor(tempL.y+1));

                    double red,green,blue,a,b;

                    b = floor(tempL.x+1)-tempL.x;
                    a = floor(tempL.y+1)-tempL.y;

                    red = b*((1-a)*tempCa.red()+a*tempCb.red())+(1-b)*((1-a)*tempCc.red()+a*tempCd.red());
                    blue = b*((1-a)*tempCa.blue()+a*tempCb.blue())+(1-b)*((1-a)*tempCc.blue()+a*tempCd.blue());
                    green = b*((1-a)*tempCa.green()+a*tempCb.green())+(1-b)*((1-a)*tempCc.green()+a*tempCd.green());

                    rysujPiksel(tempR.x,tempR.y,(int)red,(int)green,(int)blue,false);
                }
            }
        }
}
