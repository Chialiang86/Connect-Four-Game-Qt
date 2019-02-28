#include "beginpage.h"

beginPage::beginPage(QWidget *parent): QWidget (parent)
{

    qw=parent;

    th=new QLabel(qw);
    theme.load("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/theme.png");
    th->setGeometry(530,20,120,120);
    th->setAlignment(Qt::AlignCenter);
    th->setPixmap(theme.scaled(120,120,Qt::KeepAspectRatio));
    th->show();

    st=new QLabel(qw);
    st->setGeometry(40,20,400,20);
    st->setText("1. Press the button to start.");
    st->setFont(QFont("Courier",16));
    st->show();

    start=new QPushButton(qw);
    start->setGeometry(40,50,110,40);
    start->setText("START");
    start->setFont(QFont("Courier",14));

    p2c=new QPushButton(qw);
    p2p=new QPushButton(qw);
    last=new QPushButton(qw);
    le=new QLabel(qw);
    mo=new QLabel(qw);
    for(int i=0;i<3;i++){
        level[i]=new QPushButton(qw);
        level[i]->close();
    }
    p2c->close();
    p2p->close();
    last->close();
    le->close();
    mo->close();

    spal=start->palette();
    spal.setColor(QPalette::Button, QColor(255,50,50));
    spal.setColor(QPalette::ButtonText, QColor(Qt::white));
    start->setAutoFillBackground(true);
    start->setPalette(spal);
    start->show();

    connect(start,SIGNAL(clicked()),this,SLOT(chooseMode()));
    connect(p2c,SIGNAL(clicked()),this,SLOT(chooseLevel()));
    connect(p2p,SIGNAL(clicked()),this,SLOT(noLevel()));
    connect(last,SIGNAL(clicked()),this,SLOT(undo()));
    connect(level[0],SIGNAL(clicked()),this,SLOT(e()));
    connect(level[1],SIGNAL(clicked()),this,SLOT(n()));
    connect(level[2],SIGNAL(clicked()),this,SLOT(h()));

}

void beginPage::chooseMode()
{
    if(first){

        mo->setGeometry(40,120,400,20);
        mo->setText("2. Choose what mode to play.");
        mo->setFont(QFont("Courier",16));
        mo->show();

        p2c->setGeometry(40,150,110,40);
        p2c->setText("1 PLAYER");
        p2c->setFont(QFont("Courier",14));
        pcpal=p2c->palette();
        pcpal.setColor(QPalette::Button, QColor(255,50,50));
        pcpal.setColor(QPalette::ButtonText, QColor(Qt::white));
        p2c->setAutoFillBackground(true);
        p2c->setPalette(pcpal);
        p2c->show();


        p2p->setGeometry(180,150,110,40);
        p2p->setText("2 PLAYERS");
        p2p->setFont(QFont("Courier",14));
        pppal=p2p->palette();
        pppal.setColor(QPalette::Button, QColor(255,50,50));
        pppal.setColor(QPalette::ButtonText, QColor(Qt::white));
        p2p->setAutoFillBackground(true);
        p2p->setPalette(pppal);
        p2p->show();

        last->setGeometry(40,470,110,40);
        last->setText("UNDO");
        last->setFont(QFont("Courier",14));
        lapal=last->palette();
        lapal.setColor(QPalette::Button, QColor(255,50,50));
        lapal.setColor(QPalette::ButtonText, QColor(Qt::white));
        last->setAutoFillBackground(true);
        last->setPalette(lapal);
        last->show();


        spal.setColor(QPalette::Button, QColor(155,155,155));
        spal.setColor(QPalette::ButtonText, QColor(Qt::white));
        start->setAutoFillBackground(true);
        start->setPalette(spal);
        start->show();
        first=false;

    }

}

void beginPage::chooseLevel()
{

    if(mfirst){

        le->setGeometry(40,220,400,20);
        le->setText("3. Choose the level of AI.");
        le->setFont(QFont("Courier",16));
        le->show();

        pcpal=p2c->palette();
        pcpal.setColor(QPalette::Button, QColor(155,155,155));
        pcpal.setColor(QPalette::ButtonText, QColor(Qt::white));
        p2c->setAutoFillBackground(true);
        p2c->setPalette(pcpal);
        p2c->show();
        first=false;

        QString levelName[3]={"EASY","NORMAL","HARD"};

        for(int i=0;i<3;i++){
            level[i]->setGeometry(40+l*i,250,110,40);
            level[i]->setText(levelName[i]);
            level[i]->setFont(QFont("Courier",14));
            lpal[i]=level[i]->palette();
            lpal[i].setColor(QPalette::Button, QColor(250,50,50));
            lpal[i].setColor(QPalette::ButtonText, QColor(Qt::white));
            level[i]->setAutoFillBackground(true);
            level[i]->setPalette(lpal[i]);
            level[i]->update();
            level[i]->show();
            first=false;
        }

        mfirst=false;
        emit pToC();
    }


}

void beginPage::noLevel()
{
    if(mfirst){
        pppal=p2p->palette();
        pppal.setColor(QPalette::Button, QColor(155,155,155));
        pppal.setColor(QPalette::ButtonText, QColor(Qt::white));
        p2p->setAutoFillBackground(true);
        p2p->setPalette(pppal);
        p2p->show();
        mfirst=false;
        //sleep(1);
        emit pToP();
        //this->close();
    }


}

void beginPage::e()
{
    if(lfirst){
        two_people=true;
        l1pal=level[0]->palette();
        l1pal.setColor(QPalette::Button, QColor(155,155,155));
        l1pal.setColor(QPalette::ButtonText, QColor(Qt::white));
        level[0]->setAutoFillBackground(true);
        level[0]->setPalette(l1pal);
        level[0]->show();
        lfirst=false;
        emit setEasy();
        //this->close();
    }

}
void beginPage::n()
{
    if(lfirst){
        two_people=true;
        l2pal=level[1]->palette();
        l2pal.setColor(QPalette::Button, QColor(155,155,155));
        l2pal.setColor(QPalette::ButtonText, QColor(Qt::white));
        level[1]->setAutoFillBackground(true);
        level[1]->setPalette(l2pal);
        level[1]->show();
        lfirst=false;
        emit setNormal();
        //this->close();
    }
}
void beginPage::h()
{
    if(lfirst){
        two_people=true;
        l3pal=level[2]->palette();
        l3pal.setColor(QPalette::Button, QColor(155,155,155));
        l3pal.setColor(QPalette::ButtonText, QColor(Qt::white));
        level[2]->setAutoFillBackground(true);
        level[2]->setPalette(l3pal);
        level[2]->show();
        lfirst=false;
        emit setHard();
        //this->close();
    }
}

void beginPage::setClose()
{
    if(two_people){
        le->close();
        level[0]->close();
        level[1]->close();
        level[2]->close();

    }
    th->close();
    st->close();
    start->close();
    mo->close();
    p2c->close();
    p2p->close();
    last->close();
}


void beginPage::back()
{
    st->show();
    th->show();

    spal=start->palette();
    spal.setColor(QPalette::Button, QColor(255,50,50));
    spal.setColor(QPalette::ButtonText, QColor(Qt::white));
    start->setAutoFillBackground(true);
    start->setPalette(spal);
    start->show();

    first=true;
    mfirst=true;
    lfirst=true;
}

void beginPage::undo()
{

    if(!mfirst){
        pcpal=p2c->palette();
        pcpal.setColor(QPalette::Button, QColor(255,50,50));
        pcpal.setColor(QPalette::ButtonText, QColor(Qt::white));
        p2c->setAutoFillBackground(true);
        p2c->setPalette(pcpal);
        p2c->update();

        pppal=p2p->palette();
        pppal.setColor(QPalette::Button, QColor(255,50,50));
        pppal.setColor(QPalette::ButtonText, QColor(Qt::white));
        p2p->setAutoFillBackground(true);
        p2p->setPalette(pppal);
        p2p->update();

        for(int i=0;i<3;i++){
            level[i]->close();
        }
        le->close();
        mfirst=true;
    }
    else if(!first){
        spal.setColor(QPalette::Button, QColor(255,50,50));
        spal.setColor(QPalette::ButtonText, QColor(Qt::white));
        start->setAutoFillBackground(true);
        start->setPalette(spal);
        start->update();
        p2c->close();
        p2p->close();
        mo->close();
        last->close();
        first=true;
    }


}

