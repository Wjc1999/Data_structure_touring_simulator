#ifndef SRC_PATH
#define SRC_PATH

#include <cassert>

#include <iostream>
#include <deque>
#include <algorithm>

#include "user_type.h"
#include "time_format.h"
#include "city_graph.h"

struct PathNode // 路径节点
{
  City_id former_city;  //前一个城市id，相当于“i”
  City_id current_city; //节点城市名，相当于“j”
  int kth_way;          //第k种方法，相当于“k”

  /*以下相当于一种交通方法的信息(可以省略)
  bool is_start_; //规定true为路径的“起点”，false为“其它点”
  Time depart_time_;         //从前一个城市离开时的时间
  Time arrive_time_;         //到达该城市时间
  int price_;                //来此地的花费
  Trans_id transport_id_;    //乘坐来的方法
  Train_id train_seat_type_; //如果搭乘火车,记录席别
  */
};

class Path // 路径
{
public:
  Path() = default;

  // 添加一个PathNode到路径首个元素之前,并且更改总价与总时间、长度
  void Append(const CityGraph &graph, City_id i, City_id j, int k, int back = 0); //通过ijk添加一个节点
  void Append(const CityGraph &graph, City_id i, City_id j, int k, Time wait_time);
  Path &Append(const Path &path);
  void Remove(const CityGraph &graph);
  // 固定路径的出发与结束点
  void Fix();

  // 根据路径设置总时间
  void FixTotalTime(const CityGraph &graph, const Time &start_time = Time());

  //将cities向量反转
  void Reverse();

  //打印这条路径
  void Show() const;

  //获取路径长度
  int GetLen() const { return len_; }

  //获取路径总价
  int GetTotalPrice() const { return total_price_; }

  //获取总时间
  const Time &GetTotalTime() const { return total_timecost_; }

  // 返回指向路径第首个元素的迭代器
  std::deque<PathNode>::const_iterator cbegin() { return cities_.cbegin(); }

  // 返回指向路径尾后元素的迭代器
  std::deque<PathNode>::const_iterator cend() { return cities_.cend(); }

  //返回节点
  PathNode GetNode(int k) { return cities_.at(k); }

#ifdef TEST_PATH

  bool ValidatePath() const // 验证path是否合法
  {
    assert(cities_.size() == len_ && len_ > 0);
    City_id temp = cities_.at(0).current_city;
    for (int i = 1; i < len_; ++i)
      if (cities_.at(i).former_city != temp)
        return false;
    return true;
  }
#endif

private:
  std::deque<PathNode> cities_; //储存节点
  int start_city_ = 0;          //记录出发城市
  int end_city_ = 0;            //记录到达城市
  int len_ = 0;                 //路径长度
  int total_price_ = 0;         //总价
  Time total_timecost_;         //总时间
};

inline void Path::Remove(const CityGraph &graph)
{
  if (len_ == 1)
  {
    cities_.pop_back();
    start_city_ = 0;
    end_city_ = 0;
    len_ = 0;
    total_price_ = 0;
    total_timecost_.Reset();
  }
  if (!len_)
    return;

  else
  {
    len_--;
    end_city_ = cities_.at(len_ - 1).current_city;
    int i = cities_.at(len_).former_city;
    int j = cities_.at(len_).current_city;
    int k = cities_.at(len_).kth_way;
    total_price_ -= graph.GetRoute(i, j, k).price;
    int fi = cities_.at(len_-1).former_city;
    int fj = cities_.at(len_-1).current_city;
    int fk = cities_.at(len_-1).kth_way;
    Time temp = graph.GetRoute(i, j, k).end_time.time_diff(graph.GetRoute(fi,fj,fk).end_time);
    total_timecost_.minus_time(temp);
    cities_.pop_back();
  }
}

inline void Path::Append(const CityGraph &graph, City_id i, City_id j, int k, int back)
{ //用ijk给每一种方式编号，通过ijk获得所有数据。
  //std::cout << i << '\t' << j << '\t' << k << std::endl;
  PathNode temp = {i, j, k};
  if (!(len_++))
    end_city_ = j;
  start_city_ = i;
  if (back)
    cities_.push_back(temp);
  else
    cities_.push_front(temp);
  total_price_ += graph.GetRoute(i, j, k).price;
  // total_timecost_.add_time(graph.GetRoute(i, j, k).end_time.time_diff(graph.GetRoute(i, j, k).start_time));  // 只计算路途上的时间,不计等候时间
}

inline void Path::Append(const CityGraph &graph, City_id i, City_id j, int k, Time total_time)
{
  PathNode temp = {i, j, k};
  if (!(len_++))
    end_city_ = j;
  start_city_ = i;
  cities_.push_front(temp);
  total_price_ += graph.GetRoute(i, j, k).price;
  // assert(graph.GetRoute(i, j, k).end_time.time_diff(wait_time).GetDay() >= 0);
  // Time diff = graph.GetRoute(i, j, k).end_time.time_diff(wait_time);
  // if (diff.GetDay() < 0)
  //   diff.add_time(24);
  // assert(diff.GetDay() >= 0);
  // total_timecost_.add_time(diff);
  // total_timecost_ = total_time;
}

inline Path &Path::Append(const Path &path)
{
  len_ += path.len_;
  end_city_ = path.end_city_;
  total_price_ += path.total_price_;
  // PathNode end = cities_.back();
  // PathNode path_start = path.cities_.front();
  // Time diff = graph.GetRoute(end.former_city, end.current_city, end.kth_way).end_time.time_diff(graph.GetRoute(end.former_city, end.current_city, end.kth_way).start_time);
  // if (diff.GetDay() < 0)
  //     diff.add_time(0, 1);
  // total_timecost_.add_time(path.total_timecost_); // 只计算路途上的时间,不计等候时间
  for (const auto &node : path.cities_)
    cities_.push_back(node);
  return *this;
}

inline void Path::FixTotalTime(const CityGraph &graph, const Time &start_time)
{
  Time now = start_time;
  total_timecost_ = Time();
  for (const auto &node : cities_)
  {
    Time temp_now(1, now.GetHour());
    Route r = graph.GetRoute(node.former_city, node.current_city, node.kth_way);
    int wait_hour = r.start_time.hour_diff(temp_now);
    int route_hour = r.end_time.hour_diff(r.start_time);
    wait_hour += ((wait_hour < 0) ? 24 : 0);
    total_timecost_.add_time(wait_hour + route_hour);
    now.add_time(wait_hour + route_hour);
  }
}

inline void Path::Reverse()
{
  reverse(cities_.begin(), cities_.end());
  Fix();
}

inline void Path::Fix()
{
  if (len_)
  {
    start_city_ = cities_[0].former_city;
    end_city_ = cities_[cities_.size() - 1].current_city;
  }
}

void Path::Show() const
{
  for (auto path_node : cities_)
    std::cout << path_node.former_city << '\t'
              << path_node.current_city << '\t'
              << path_node.kth_way << std::endl;
}
#endif // SRC_PATH