#ifndef WINNER_H
#define WINNER_H
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QApplication>

class over : public QWidget
{
public:
    over(bool,int,bool,bool,bool,QWidget *parent=nullptr);
    QPushButton *again,*closed;

  public slots:
    void quit_();
signals:

private:
    QString overText;
    QFrame *s;
    QLabel *label,*background;
    QPixmap bg;
};


#endif // WINNER_H
