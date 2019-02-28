#include "image.h"

image::image(QWidget *parent) : QWidget(parent)
{

    setWindowTitle(tr("按鍵組"));
    resize(500,500);
    QPixmap p("/Users/guojialiang/Desktop/build-CONNECT_FOUR_GMAE-Desktop_Qt_5_12_1_clang_64bit-Debug/down.jpg");

    l = new QLabel(this);
    l->setGeometry(20,20,30,30);        //設定位置大小
    l->setAlignment(Qt::AlignCenter);
    l->setPixmap(p.scaled(60,60,Qt::KeepAspectRatio));
}
