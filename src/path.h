#ifndef SRC_PATH
#define SRC_PATH

#include <vector>
#include "time_format.h"
#include "user_type.h"
#include "city_graph.h"

struct PathNode // 路径节点
{
  City_id former_city_;   //前一个城市id，相当于“i”
  City_id current_city_;  //节点城市名，相当于“j”
  int kth_way_;           //第k种方法，相当于“k”

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
  /*添加一个PathNode到路径尾端,并且更改总价与总时间、长度
   */
  void append(const CityGraph graph, City_id i, City_id j, int k);//通过ijk添加一个节点
  void Show();//展示一条路径
  //std::vector<PathNode>::size_type GetLen() const;
  int GetLen() const {return len;};                   //获取路径长度
  int GetTotalPrice() const {return total_price_;};   //获取总价
  Time GetTotalTime() const {return total_timecost_;};//获取总时间

private:
  std::vector <PathNode> cities_;//储存节点
  int start_city;                //记录出发城市
  int end_city;                  //记录到达城市
  int len;                       //内容量
  int total_price_;              //总价
  Time total_timecost_;          //总时间
};

void Path::append(const CityGraph graph, City_id i, City_id j, int k){//用ijk给每一种方式编号，通过ijk获得所有数据。
  PathNode temp = {i,j,k};
  cities_.push_back(temp);
  if(!len)start_city = i;//设置起始点
  end_city = j;          //记录终点
  len++;
  total_price_ += graph.Get(i,j,k).price;
  total_timecost_.add_time(graph.Get(i,j,k).start_time.time_diff(graph.Get(i,j,k).end_time));
}

void Path::Show(){
  //输出在屏幕上
}
#endif // SRC_PATH