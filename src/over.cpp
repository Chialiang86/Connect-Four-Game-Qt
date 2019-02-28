#include "over.h"
over::over(bool draw,int wi,bool ai,bool d_c,bool d_c_r,QWidget *parent) : QWidget(parent)
{
    setWindowTitle("- WINNER SHOWS UP -");

    s=new QFrame(parent);
    resize(250,200);

    background=new QLabel(this);
    bg.load("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/background.png");
    background->setGeometry(0,0,250,200);
    background->setAlignment(Qt::AlignCenter);
    background->setPixmap(bg.scaled(250,200,Qt::KeepAspectRatioByExpanding));
    background->show();



    if(draw){
        overText="It's a draw!!!";
    }
    else{
        if(!ai){
            overText="%1%2%3";
            overText=overText.arg("player ",QString::number(wi+1)," WINS!!!");
        }
        else if(ai){
            if(d_c_r){
                if(d_c_r==d_c)
                    overText="你被當了!!!";
                else
                    overText="程設PASS!!!";
            }
            else {
                if(d_c_r==d_c)
                    overText="程設PASS!!!";
                else
                    overText="你被當了!!!";
            }
        }
    }
    label=new QLabel(this);
    label->setText(overText);
    label->setGeometry(35,20,180,30);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(QFont("Courier",16));

    QPalette o;
    again=new QPushButton(this);
    again->setGeometry(70,60,110,40);
    again->setText(" CONTINUE ");
    again->setFont(QFont("Courier",14));
    o=again->palette();
    o.setColor(QPalette::Button, QColor(225,225,225));
    o.setColor(QPalette::ButtonText, QColor(255,0,0));
    again->setAutoFillBackground(true);
    again->setPalette(o);
    again->update();

    closed=new QPushButton(this);
    closed->setGeometry(70,120,110,40);
    closed->setText(" END ");
    closed->setFont(QFont("Courier",14));
    o=closed->palette();
    o.setColor(QPalette::Button, QColor(225,225,225));
    o.setColor(QPalette::ButtonText, QColor(255,0,0));
    closed->setAutoFillBackground(true);
    closed->setPalette(o);
    closed->update();

}

void over::quit_()
{
    delete this;
    QCoreApplication::processEvents();
}
