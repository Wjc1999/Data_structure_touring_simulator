class Time // 表示时间
{
  public:
    Time(int time); //
    Time &time_diff(const Time &a); // 获取两个时间的差值
    int GetDay() const;
    int GetHour() const;
  private:
    int day = 0;
    int hour = 0;
};