#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->x();
    int y = ev->y();
    qDebug() << x << y;
}
