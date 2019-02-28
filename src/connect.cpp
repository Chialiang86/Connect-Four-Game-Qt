#include "connect.h"

connect_line::connect_line(int fromx,int fromy,int tox,int toy,QWidget *parent): QWidget(parent)
{
    qw=parent;
    fx=fromx;
    fy=fromy;
    tx=tox;
    ty=toy;
}

void connect_line::paintEvent(QPaintEvent *){
    QPen d;
    QPainter painter(this);
    d.setColor(QColor(100,255,100));
    d.setWidth(10);
    d.setStyle(Qt::SolidLine);
    painter.setPen(d);
    painter.drawLine(fx,fy,tx,ty);
    raise();
    update();

}
