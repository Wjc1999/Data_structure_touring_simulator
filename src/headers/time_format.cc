#ifndef SRC_TIME_CC
#define SRC_TIME_CC

#include <iostream>

#include "time_format.h"

Time Time::time_diff(const Time &t) const
{
  int temp_hour = hour_ - t.hour_, temp_day = day_ - t.day_;
  if (temp_hour < 0)
  {
    --temp_day;
    temp_hour += 24;
  }
  Time res(temp_day + 1, temp_hour);
  return res;
}

Time &Time::add_time(const Time &t)
{
  return add_time(t.hour_, t.day_);
}

Time &Time::add_time(const int hour, const int day /* = 0 */)
{
  day_ += day;
  hour_ += hour;
  int d = hour_ / 24;
  if (d)
  {
    hour_ -= 24 * d;
    day_ += d;
  }
  return *this;
}

int Time::hour_diff(const Time &t) const
{
  Time temp = time_diff(t);
  return temp.hour_ + temp.day_ * 24;
}

Time &Time::minus_time(const Time &t)
{
  return add_time(-t.hour_, -t.day_);
}

Time &Time::minus_time(const int hour, const int day)
{
  return add_time(-hour, -day);
}

void RouteShow(const Time &leave, const Time &arrive)
{
  std::cout << leave.GetHour() << ":00" << "\t\t"
            << arrive.GetHour() << ":00";
  if (arrive.GetDay())
    std::cout << "+" << arrive.GetDay() << "\t\t";
  else
    std::cout << "\t\t";
}

#endif //SRC_TIME_CC
