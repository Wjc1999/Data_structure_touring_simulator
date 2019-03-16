#ifndef SRC_PATH
#define SRC_PATH

#include <iostream>
#include <vector>

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
  Path();
  // 添加一个PathNode到路径尾端,并且更改总价与总时间、长度
  void append(const CityGraph &graph, City_id former_city, City_id current_city, int k); //通过ijk添加一个节点
  //打印这条路径
  void Show() const;
  //获取路径长度
  int GetLen() const { return len_; };
  //获取路径总价
  int GetTotalPrice() const { return total_price_; };
  //获取总时间
  const Time &GetTotalTime() const { return total_timecost_; };

#ifdef TEST_PATH
#include <cassert>
  bool ValidatePath() const // 验证path是否合法
  {
    std::assert(cities_.size() == len_ && len_ > 0);
    City_id temp = cities_.at(0).current_city;
    for (int i = 1; i < len_; ++i)
      if (cities_.at(i).former_city != temp)
        return false;
    return true;
  }
#endif

private:
  std::vector<PathNode> cities_; //储存节点
  int start_city_ = 0;           //记录出发城市
  int end_city_ = 0;             //记录到达城市
  int len_ = 0;                  //路径长度
  int total_price_ = 0;          //总价
  Time total_timecost_;          //总时间
};

inline void Path::append(const CityGraph &graph, City_id i, City_id j, int k)
{ //用ijk给每一种方式编号，通过ijk获得所有数据。
  PathNode temp = {i, j, k};
  cities_.push_back(temp);
  if (!len_)
    start_city_ = i; //设置起始点
  end_city_ = j;     //记录终点
  len_++;
  total_price_ += graph.GetRoute(i, j, k).price;
  total_timecost_.add_time(graph.GetRoute(i, j, k).end_time.time_diff(graph.GetRoute(i, j, k).start_time));
}

void Path::Show() const
{
  for (auto path_node : cities_)
    std::cout << path_node.former_city << ' ' << path_node.current_city << ' ' << path_node.kth_way << std::endl;
}
#endif // SRC_PATH