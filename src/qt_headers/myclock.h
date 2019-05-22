#ifndef MYCLOCK_H
#define MYCLOCK_H

#include <QLCDNumber>

class MyClock : public QLCDNumber
{
    Q_OBJECT
public:
    explicit MyClock(QWidget *parent = nullptr);
    void initialize();
signals:

public slots:
};

#endif // MYCLOCK_H
