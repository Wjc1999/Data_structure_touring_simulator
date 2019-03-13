#ifndef SRC_TIME
#define SRC_TIME
/*  class Time
 *  用于表示时间
*/
class Time
{
public:
  /* 接受一个形如dhh00的整数,将d作为日期,hh作为小时储存 
  */
  Time(int time);

  /* 获取当前时间与给定时间的差值,返回值为差值时间的拷贝 
  */
  Time time_diff(const Time &) const;

  /* 获取当前时间与给定时间的差值,返回值为两者相差的小时数
  */
  int hour_diff(const Time &) const;

  int GetDay() const;
  int GetHour() const;

private:
  int day_;
  int hour_;
};

#endif // SRC_TIME