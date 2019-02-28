#ifndef PUSHCOL_H
#define PUSHCOL_H
#include <QPushButton>
#include <QWidget>
#include <QPen>
#include <QString>

class pushObject : public QWidget
{
    Q_OBJECT
public:
    pushObject(QWidget *parent=nullptr);
    QPushButton *restart,*end,*column[7],*mainMenu,*undo;

public slots:
    void s_color();

private:
    QWidget *qw;
    int colWidth=70;
    bool first=true;

};

#endif // PUSHCOL_H
