#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    window *w=new window;
    QWidget::connect(w,SIGNAL(toClose()),&app,SLOT(quit()));
    w->show();
    return app.exec();
}

//beginPage *b=new beginPage;

//QWidget::connect(b,SIGNAL(done()),w,SLOT(start()));
/*QWidget::connect(b,SIGNAL(pToP()),w,SLOT(noai()));
QWidget::connect(b,SIGNAL(setEasy()),w,SLOT(connectEasy()));
QWidget::connect(b,SIGNAL(setNormal()),w,SLOT(connectNormal()));
QWidget::connect(b,SIGNAL(setHard()),w,SLOT(connectHard()));
QWidget::connect(w->pc->end,SIGNAL(clicked()),w,SLOT(toEnd()));*/
//QWidget::connect(w->pc->end,SIGNAL(clicked()),&app,SLOT(quit()));
/*QCoreApplication::applicationFilePath();
        QString applicationFilePath;
        applicationFilePath = QCoreApplication::applicationFilePath();
        qDebug()<<"applicationFilePath"<<applicationFilePath±;
    QCoreApplication::applicationDirPath();
       QString applicationDirPath;
       applicationDirPath = QCoreApplication::applicationDirPath();
       qDebug()<<"applicationDirPath"<<applicationDirPath;*/
