#ifndef CONNECT_H
#define CONNECT_H
#include <QWidget>
#include <QPainter>

class connect_line : public QWidget
{
    Q_OBJECT
public:
    connect_line(int,int,int,int,QWidget *parent=nullptr);
    private:
    void paintEvent(QPaintEvent *);
    QWidget *qw;
    int fx,fy,tx,ty;
};

#endif // CONNECT_H
