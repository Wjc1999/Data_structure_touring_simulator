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

    void initialize(QLCDNumber *lcd1, QLCDNumber *lcd2, MyMap *map, CityGraph *cg, Traveller *t);
    void ready_for_simulate();
    void set_flush_rate(int simulate_onehour_s_, int display_interval_ms_);
    void start();
    void stop();
    void continuing();
    void reset();

private:
    QLCDNumber *day_LCD_;
    QLCDNumber *hour_LCD_;
    MyMap *map_;
    QTimer timer_;

    bool is_start_ = false;
    bool is_finished = false;
    int display_day_;
    int display_hour_;
    int simulate_onehour_s_ = 1;   //模拟中1小时对应多少秒，可更改
    int display_interval_ms_ = 20; //间隔多少刷新，可更改
    int flush_per_hour_ = 50;      //1小时中刷新多少次，simulate_onehour_s_/display_interval_ms_;

    int flush_count_ = 0; //当前刷新了几次
    int current_pathnode_ = 0;
    int hour_left_;
    TravellerState current_states_;

public slots:
    void onTimerOut();
};

#endif // SIMULATOR_H
