#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <mymap.h>
#include <QTime>
#include <QTimer>
#include <QObject>
#include <QLCDNumber>
#include <QMessageBox>

class Simulator : public QObject
{
    Q_OBJECT

public:
    explicit Simulator(QObject *parent = nullptr);
    void initialize(QLCDNumber* lcd1, QLCDNumber* lcd2, MyMap* map, CityGraph *cg, Traveller *t);
    void start();
    void stop();
    void continuing();
    void reset();

private:
    QLCDNumber* day_LCD_;
    QLCDNumber* hour_LCD_;
    MyMap* map_;
    QTimer timer_;
    bool is_start_ = false;
    int display_day_;
    int display_hour_;
    int display_interval_ = 100;

public slots:
    void onTimerOut();
};

#endif // SIMULATOR_H
