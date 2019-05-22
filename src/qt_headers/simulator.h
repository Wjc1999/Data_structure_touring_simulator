#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <myclock.h>
#include <mymap.h>
#include <QTime>
#include <QTimer>
#include <QObject>

class Simulator : public QObject
{
    Q_OBJECT

public:
    explicit Simulator(QObject *parent = nullptr);
    void initialize(MyClock* clock, MyMap* map);
    void start();

private:
    MyClock* clock_;
    MyMap* map_;
    QTimer timer;

public slots:
    void onTimerOut();
};

#endif // SIMULATOR_H
