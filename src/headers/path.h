#ifndef SRC_PATH_H
#define SRC_PATH_H

#include <deque>

#include "user_type.h"
#include "time_format.h"

class CityGraph;
class Time;

struct PathNode // 路径节点
{
  City_id former_city;  //前一个城市id，相当于“i”
  City_id current_city; //节点城市名，相当于“j”
  int kth_way;          //第k种方法，相当于“k”
};

class Path // 路径
{
public:
  Path() = default;

  // 添加一个PathNode到路径首个元素之前,并且更改总价与总时间、长度
  void Append(const CityGraph &graph, City_id former_city, City_id current_city, int k, int back = 0); //通过ijk添加一个节点
  void Append(const CityGraph &graph, City_id i, City_id j, int k, Time wait_time);
  Path &Append(const Path &path);
  void Remove(const CityGraph &graph);
  // 固定路径的出发与结束点
  void Fix()
  {
    if (len_)
    {
      start_city_ = cities_[0].former_city;
      end_city_ = cities_[cities_.size() - 1].current_city;
    }
  }

  // 根据路径设置总时间
  void FixTotalTime(const CityGraph &graph, const Time &start_time = Time());

  //将cities向量反转
  void Reverse()
  {
    reverse(cities_.begin(), cities_.end());
    Fix();
  }

  //打印这条路径
  void Show() const;

  //获取路径长度
  int GetLen() const { return len_; }

  //获取路径总价
  int GetTotalPrice() const { return total_price_; }

  //获取总时间
  const Time &GetTotalTime() const { return total_timecost_; }

  // 返回指向路径第首个元素的迭代器(危险,必须确保使用时该对象依然存在)
  std::deque<PathNode>::const_iterator cbegin() const { return cities_.cbegin(); }

  // 返回指向路径尾后元素的迭代器(危险,必须确保使用时该对象依然存在)
  std::deque<PathNode>::const_iterator cend() const { return cities_.cend(); }

  //返回节点
  const PathNode &GetNode(int k) const { return cities_.at(k); }

#ifdef TEST_PATH

  bool ValidatePath() const; // 验证path是否合法

#endif

private:
  std::deque<PathNode> cities_; //储存节点
  int start_city_ = 0;          //记录出发城市
  int end_city_ = 0;            //记录到达城市
  int len_ = 0;                 //路径长度
  int total_price_ = 0;         //总价
  Time total_timecost_;         //总时间
};

#endif // SRC_PATH_H
