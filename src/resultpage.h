#ifndef RESULTPAGE_H
#define RESULTPAGE_H

#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QWidget>

class resultpage : public QWidget
{
    Q_OBJECT

public:
    resultpage(bool,int,int,QWidget *parent);
    QPushButton *ok,*mainMenu;
public slots:
    void toClose();


private:
    QString score_text,result_text;
    QPixmap bg;
    QPalette opal,mpal;
    QLabel *background,*score,*result;
};

#endif // RESULTPAGE_H
