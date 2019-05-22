#include "simulator.h"

Simulator::Simulator(QObject *parent) : QObject(parent)
{

}


void Simulator::initialize(MyClock* clock, MyMap* map)
{
    clock_ = clock;
    map_ = map;
    timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

void Simulator::onTimerOut()
{
    //获取系统当前时间
    QTime time = QTime::currentTime();
    //设置晶体管控件QLCDNumber上显示的内容
    clock_->display(time.toString("hh:mm:ss"));
}

void Simulator::start()
{
    timer.start();
}
