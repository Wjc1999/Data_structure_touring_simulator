﻿#ifndef SRC_TIME_CC
#define SRC_TIME_CC

#include <iostream>
#include <string>

#include "time_format.h"

Time &Time::add_time(const Time &t)
{
  return add_time(t.hour_, t.day_);
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

std::string RouteShow(const Time &leave, const Time &arrive)
{
  std::string temp;
  temp += std::to_string(leave.GetHour());
  temp += ":00\t\t";
  temp += std::to_string(arrive.GetHour());
  temp += ":00";
  /*std::cout << leave.GetHour() << ":00" << "\t\t"
            << arrive.GetHour() << ":00";*/
  if (arrive.GetDay())
  {
    temp += "+" + std::to_string(arrive.GetDay()) + "\t\t";
    //std::cout << "+" << arrive.GetDay() << "\t\t";
  }

  else
  {
    temp += "\t\t";
    //std::cout << "\t\t";
  }
  return temp;
}

#endif //SRC_TIME_CC
