#ifndef ERROW_H
#define ERROW_H
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>

class error : public QWidget
{
public:
    int col_num=-1;
    error(bool,QWidget *parent=nullptr);

   public slots:
    void quit();

private:
    QFrame *s;
    QLabel *label,*background;
    QPixmap bg;
    QPushButton *ok;
};

#endif // ERROW_H
