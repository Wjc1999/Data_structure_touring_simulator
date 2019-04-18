#ifndef SRC_TIME
#define SRC_TIME
/*  class Time
 *  用于表示时间与处理时间
*/
#include <iostream>

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
  int to_hour() const;

  int GetDay() const;
  int GetHour() const;
  void Reset();              //重置
  int GetLength() const; //获得总时长
  void set_hour(int hour);

private:
  int day_ = 0; // day_为0表示当天
  int hour_ = 0;
};

void RouteShow(const Time &leave, const Time &arrive);

#endif // SRC_TIME
