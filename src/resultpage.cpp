#include "resultpage.h"

resultpage::resultpage(bool ai,int p1,int p2,QWidget *parent) : QWidget(parent)
{
   setWindowTitle("- GAME RESULT -");
   resize(250,200);

   background=new QLabel(this);
   bg.load("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/background.png");
   background->setGeometry(0,0,250,200);
   background->setAlignment(Qt::AlignCenter);
   background->setPixmap(bg.scaled(250,200,Qt::KeepAspectRatioByExpanding));
   background->show();

   result=new QLabel(this);
   if(ai)
       p1==p2 ? result_text="DRAW!!!" : p1>p2 ? result_text="YOU WIN!!!" : result_text="YOU LOSE!!!";
   else
       p1==p2 ? result_text="DRAW!!!" : p1>p2 ? result_text="PLAYER1 WIN!!!" : result_text="PLAYER2 LOSE!!!";
   result->setGeometry(10,20,230,20);
   result->setText(result_text);
   result->setAlignment(Qt::AlignCenter);
   result->setFont(QFont("Courier",16));
   result->show();

   score=new QLabel(this);
   score_text="%1%2%3";
   score_text=score_text.arg(QString::number(p1)," : ",QString::number(p2));
   score->setGeometry(10,40,230,20);
   score->setText(score_text);
   score->setAlignment(Qt::AlignCenter);
   score->setFont(QFont("Courier",16));
   score->show();

   mainMenu=new QPushButton(this);
   mainMenu->setGeometry(70,80,110,40);
   mainMenu->setText("MAIN MENU");
   mainMenu->setFont(QFont("Courier",14));
   mpal=mainMenu->palette();
   mpal.setColor(QPalette::Button, QColor(225,225,225));
   mpal.setColor(QPalette::ButtonText, QColor(Qt::red));
   mainMenu->setAutoFillBackground(true);
   mainMenu->setPalette(mpal);
   mainMenu->update();

   ok=new QPushButton(this);
   ok->setGeometry(70,140,110,40);
   ok->setText("OK");
   ok->setFont(QFont("Courier",14));
   opal=ok->palette();
   opal.setColor(QPalette::Button,QColor(225,225,225));
   opal.setColor(QPalette::ButtonText,QColor(255,0,0));
   ok->setAutoFillBackground(true);
   ok->setPalette(opal);
   ok->show();

}

void resultpage::toClose()
{
    delete
    this;
}
