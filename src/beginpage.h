#ifndef BEGINPAGE_H
#define BEGINPAGE_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <unistd.h>
//#include "mode.h"
//#include "levelpage.h"


class beginPage : public QWidget
{
    Q_OBJECT
public:
    beginPage(QWidget *parent=nullptr);

public slots:
    void chooseMode();
    void chooseLevel();
    void noLevel();
    void setClose();
    void back();
    void undo();
    void e();
    void n();
    void h();
signals:
    void pToP();
    void pToC();
    //void setClose();
    void setEasy();
    void setNormal();
    void setHard();

private:
    QWidget *qw;
    QLabel *st,*mo,*le,*th;
    QPixmap theme;
    QPushButton *start,*p2c,*p2p,*level[3],*last;
    QPalette spal,pcpal,pppal,lpal[3],l1pal,l2pal,l3pal,lapal;
    int l=140;
    bool first=true,mfirst=true,lfirst=true,two_people=false;;

};

#endif // BEGINPAGE_H
/*
void window::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    QPen col; {
        col.setColor(Qt::black);
        col.setWidth(2);
        col.setStyle(Qt::SolidLine);
    }
    QBrush b; {
        b.setColor(QColor(214,255,255));
        b.setStyle(Qt::SolidPattern);
    }

    painter.setBrush(b);
    painter.drawRect(20,120,490,410);


    painter.setPen(col);
    for(int i=0;i<8;++i)
        painter.drawLine(20+i*colWidth,120,20+i*colWidth,530);
    painter.drawLine(20,120,515,120);
    painter.drawLine(20,530,515,530);

    QPen d; {
        d.setColor(Qt::white);
        d.setWidth(1);
        d.setStyle(Qt::SolidLine);
    }
    QBrush disk[2]; {
        disk[0].setColor(QColor(255,100,150));
        disk[0].setStyle(Qt::SolidPattern);
        disk[1].setColor(QColor(100,150,255));
        disk[1].setStyle(Qt::SolidPattern);
    }
    painter.setPen(d);
    painter.setBrush(disk[disk_color]);
    painter.drawEllipse(570,250,40,40);
    for(int i=0;i<7;i++)
        for(int j=0;j<6;j++)
            if(board[j][i].can){
                painter.setBrush(disk[board[j][i].color]);
                painter.drawEllipse(diskxpos[i],diskypos[j],66,66);
            }
    player_text="%1%2%3";
    player_text=player_text.arg("player ",QString::number(++n),"'s turn");
    player->setText(player_text);
    player->setGeometry(535,200,110,20);
    player->setFont(QFont("Courier",12));
    player->setAlignment(Qt::AlignCenter);


    if(!conti)
    {
        QPen d;
        d.setColor(QColor(255,50,50));
        d.setWidth(20);
        d.setStyle(Qt::SolidLine);
        painter.setPen(d);
        painter.drawLine(diskxpos[from.y]+33,diskypos[from.x]+33,diskxpos[to.y]+33,diskypos[to.x]+33);
        update();

    }


}*/
