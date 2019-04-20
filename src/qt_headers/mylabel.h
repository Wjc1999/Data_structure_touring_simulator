#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QResizeEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    void setOriginPixmap();
    bool hasOriginPixmap();
protected:
    void mousePressEvent(QMouseEvent *ev);
    void resizeEvent(QResizeEvent *ev);
signals:

public slots:

private:
    QPixmap origin_pixmap;
};

#endif // MYLABEL_H
