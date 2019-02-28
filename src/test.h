#ifndef TEST_H
#define TEST_H
#include <QWidget>
#include <QFrame>
#include <QString>
#include <QLabel>
#include <vector>
using namespace std;


class test : public QWidget
{
    Q_OBJECT
public:
    test(QWidget *parent);
    void set(vector<vector<char>>);
    void clear(QString);

private:
    QString *text;
    QFrame *s;
    QLabel *l;


};

#endif // TEST_H
