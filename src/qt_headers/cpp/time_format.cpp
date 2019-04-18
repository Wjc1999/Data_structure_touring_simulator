#include "headers/time_format.h"

inline Time Time::time_diff(const Time &t) const
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

inline Time &Time::add_time(const Time &t)
{
  return add_time(t.hour_, t.day_);
}

inline Time &Time::add_time(const int hour, const int day /* = 0 */)
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

inline int Time::hour_diff(const Time &t) const
{
  Time temp = time_diff(t);
  return temp.hour_ + temp.day_ * 24;
}

inline Time &Time::minus_time(const Time &t)
{
  return add_time(-t.hour_, -t.day_);
}

inline Time &Time::minus_time(const int hour, const int day)
{
  return add_time(-hour, -day);
}

inline void RouteShow(const Time &leave, const Time &arrive)
{
  std::cout << leave.GetHour() << ":00" << "\t\t"
            << arrive.GetHour() << ":00";
  if (arrive.GetDay())
    std::cout << "+" << arrive.GetDay() << "\t\t";
  else
    std::cout << "\t\t";
}

inline int Time::to_hour() const
{
    return day_ * 24 + hour_;
}

inline int Time::GetDay() const
{
    return day_;
}

inline int Time::GetHour() const
{
    return hour_;
}

inline void Time::Reset()
{
    hour_ = 0;
    day_ = 0;
}

inline int Time::GetLength() const
{
    return hour_ + day_ * 24;
}

inline void Time::set_hour(int hour)
{
    hour_ = hour;
}

