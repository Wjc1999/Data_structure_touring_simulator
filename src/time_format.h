#ifndef SRC_TIME
#define SRC_TIME
/*  class Time
 *  用于表示时间与处理时间
*/
class Time
{
public:
  // 接受一个形如dhh00的整数,将d作为日期,hh作为小时储存
  explicit Time(int time = 10000) : Time(time / 10000, (time - time / 10000 * 10000) / 100) {}
  Time(int day, int hour) : day_(day - 1), hour_(hour) {}

  // 获取当前时间与给定时间的差值,返回值为差值时间的拷贝(this - t)
  Time time_diff(const Time &t) const;

  // 将当前时间与给定时间相加,返回相加后时间的引用(改变了使用此方法的对象)
  Time &add_time(const Time &t);
  Time &add_time(const int hour, const int day = 0);

  // 将当前时间与给定时间相减,返回相减后时间的引用(改变了使用此方法的对象)
  Time &minus_time(const Time &t);
  Time &minus_time(const int hour, const int day = 0);

  // 获取当前时间与给定时间的差值,返回值为两者相差的小时数(this - t)
  int hour_diff(const Time &) const;

  // 返回当前时间对应的小时数
  int to_hour() const { return day_ * 24 + hour_; }

  int GetDay() const { return day_; }
  int GetHour() const { return hour_; }
  void Reset() { hour_ = 0, day_ = 0; }               //重置
  int GetLength() const { return hour_ + day_ * 24; } //获得总时长
  void set_hour(int hour) { hour_ = hour; }

#ifdef TEST_TIME
#include <iostream>
  std::ostream &print(std::ostream &os = std::cout) const
  {
    os << "日期是: " << GetDay()
       << "\t时间是: " << GetHour();
    return os;
  }
#endif // TEST_TIME

private:
  int day_ = 0; // day_为0表示当天
  int hour_ = 0;
};

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

void RouteShow(const Time &leave, const Time &arrive)
{
  std::cout << leave.GetHour() << ":00" << "\t\t"
            << arrive.GetHour() << ":00";
  if (arrive.GetDay() > 1)
    std::cout << "+" << arrive.GetDay() - 1 << "\t\t";
  else
    std::cout << "\t\t";
}

#endif // SRC_TIME