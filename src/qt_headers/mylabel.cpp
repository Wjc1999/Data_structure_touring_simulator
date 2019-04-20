#ifndef SRC_MYLABEL
#define SRC_WYLABEL

#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QResizeEvent>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    this->setScaledContents(false);
    this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

void MyLabel::setOriginPixmap()
{
    if (!hasOriginPixmap())
        origin_pixmap = *pixmap();
}

bool MyLabel::hasOriginPixmap()
{
    return !origin_pixmap.isNull();
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->x();
    int y = ev->y();
    qDebug() << this->size() << endl
             << this->origin_pixmap.size() << endl;

    // qDebug() << x << y;
}

void MyLabel::resizeEvent(QResizeEvent *ev)
{
    this->setPixmap(origin_pixmap.scaled(ev->size().width(),
                                         ev->size().height(),
                                         Qt::KeepAspectRatio,
                                         Qt::FastTransformation));
}
#endif // SRC_MYLABEL
