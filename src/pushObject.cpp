#include "pushobject.h"

pushObject::pushObject(QWidget *parent): QWidget(parent)
{
    qw=parent;
    QPalette spal;
    restart=new QPushButton(qw);
    restart->setGeometry(545,20,100,40);
    restart->setText("RESTART");
    restart->setFont(QFont("Courier",14));
    spal=restart->palette();
    spal.setColor(QPalette::Button, QColor(205,205,205));
    spal.setColor(QPalette::ButtonText, QColor(Qt::red));
    restart->setAutoFillBackground(true);
    restart->setPalette(spal);
    restart->update();

    QPalette epal;
    end=new QPushButton(qw);
    end->setGeometry(545,80,100,40);
    end->setText("END");
    end->setFont(QFont("Courier",14));
    epal=restart->palette();
    epal.setColor(QPalette::Button, QColor(205,205,205));
    epal.setColor(QPalette::ButtonText, QColor(Qt::red));
    end->setAutoFillBackground(true);
    end->setPalette(epal);
    end->update();

    QPalette upal;
    undo=new QPushButton(qw);
    undo->setGeometry(545,140,100,40);
    undo->setText("UNDO");
    undo->setFont(QFont("Courier",14));
    upal=undo->palette();
    upal.setColor(QPalette::Button, QColor(205,205,205));
    upal.setColor(QPalette::ButtonText, QColor(Qt::red));
    undo->setAutoFillBackground(true);
    undo->setPalette(upal);
    undo->update();

    QPalette mpal;
    mainMenu=new QPushButton(qw);
    mainMenu->setGeometry(545,200,100,40);
    mainMenu->setText("MAIN MENU");
    mainMenu->setFont(QFont("Courier",14));
    mpal=mainMenu->palette();
    mpal.setColor(QPalette::Button, QColor(205,205,205));
    mpal.setColor(QPalette::ButtonText, QColor(Qt::red));
    mainMenu->setAutoFillBackground(true);
    mainMenu->setPalette(mpal);
    mainMenu->update();


    {//set col button
        QString colName;
        QPalette cpal;
        for(int i=0;i<7;++i){
            column[i] = new QPushButton(qw);
            colName="%1%2";
            colName=colName.arg(QString::number(i+1)," col");
            column[i]->setGeometry(35+i*colWidth,20,60,40);
            column[i]->setText(colName);
            column[i]->setFont(QFont("Courier",12));
            cpal=column[i]->palette();
            cpal.setColor(QPalette::Button, QColor(205,205,205));
            cpal.setColor(QPalette::ButtonText, QColor(Qt::black));
            column[i]->setAutoFillBackground(true);
            column[i]->setPalette(cpal);
            column[i]->update();
        }
    }


}

void pushObject::s_color()
{
    if(first){
        QPalette b;
        b=restart->palette();
        b.setColor(QPalette::Button, QColor(105,105,105));
        b.setColor(QPalette::ButtonText, QColor(Qt::white));
        restart->setText("RESTART");
        restart->setAutoFillBackground(true);
        restart->setPalette(b);
        restart->update();
        first =false;
    }
}
