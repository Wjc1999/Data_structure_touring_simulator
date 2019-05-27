#include "simulator.h"

#pragma execution_character_set("utf-8")

Simulator::Simulator(QObject *parent) : QObject(parent)
{
}


void Simulator::initialize(QLCDNumber* lcd1, QLCDNumber* lcd2, MyMap* map, CityGraph *cg, Traveller *t)
{
    day_LCD_ = lcd1;
    hour_LCD_ = lcd2;
    map_ = map;
    map_->initialize(cg, t);
    timer_.setInterval(display_interval_);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(onTimerOut()));

    display_day_ = map->traveller_->get_init_time().GetDay() + 1;
    display_hour_ = map->traveller_->get_init_time().GetHour();
    day_LCD_->display(display_day_);
    hour_LCD_->display(display_hour_);
}

void Simulator::onTimerOut()
{
    hour_LCD_->display((++display_hour_) % 24);
    if (display_hour_ % 24 == 0)
        day_LCD_->display(++display_day_);
    map_->update();
}

void Simulator::start()
{
    if (!is_start_)
    {
        timer_.start();
        is_start_ = true;
    }
}

void Simulator::stop()
{
    if (is_start_)
        timer_.stop();
}

void Simulator::continuing()
{
    if (is_start_)
        timer_.start();
}

void Simulator::reset()
{
    timer_.stop();
    display_day_ = map_->traveller_->get_init_time().GetDay() + 1;
    display_hour_ = map_->traveller_->get_init_time().GetHour();
    day_LCD_->display(display_day_);
    hour_LCD_->display(display_hour_);
    is_start_ = false;
    map_->reset();
}
