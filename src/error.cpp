#include "error.h"
error::error(bool full,QWidget *parent) : QWidget(parent)
{
   setWindowTitle("- ERROR -");
   s=new QFrame(parent);
   resize(250,150);

   //QPixmap fitpixmap_userIcon=pixmap_userIcon.scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//
   background=new QLabel(this);
   bg.load("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/background.png");
   //bg.scaled(250,150,Qt::IgnoreAspectRatio);
   background->setGeometry(0,0,250,150);
   background->setAlignment(Qt::AlignCenter);
   background->setPixmap(bg.scaled(250,150,Qt::IgnoreAspectRatio));
   background->show();

   label=new QLabel(this);
   if(full){
       label->setText("The col is FULL!!");
   }
   else {
       label->setText("The checkerboard is EMPTY!!");
   }

   label->setGeometry(10,20,230,30);
   label->setAlignment(Qt::AlignCenter);
   label->setFont(QFont("Courier",14));

   QPalette o;
   ok=new QPushButton(this);
   ok->setGeometry(70,60,110,40);
   ok->setText("- OK -");
   ok->setFont(QFont("Courier",16));
   o=ok->palette();
   o.setColor(QPalette::Button, QColor(225,225,225));
   o.setColor(QPalette::ButtonText, QColor(255,0,0));
   ok->setAutoFillBackground(true);
   ok->setPalette(o);
   ok->update();
   connect(ok,&QPushButton::clicked,this,&error::quit);
}

void error::quit()
{
   delete this;
}
