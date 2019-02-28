#ifndef IMAGE_H
#define IMAGE_H
#include <QWidget>
#include <QLabel>

class image : public QWidget
{
    Q_OBJECT
public:
    image(QWidget *parent=nullptr);
    QLabel *l;
};

#endif // IMAGE_H
