#ifndef SRC_PATH
#define SRC_PATH
#include <vector>
#include "time_format.h"
#include "user_type.h"

class PathNode // 路径节点
{
public:
  PathNode(City_id city, bool start, const Time &depart, const Time &arrive, int price, Trans_id transport_type);

  City_id city_;  //节点城市名
  bool is_start_; //规定true为路径的“起点”，false为“其它点”，
  /*以下相当于一种交通方法的信息
    */
  Time depart_time_;         //从前一个城市离开时的时间
  Time arrive_time_;         //到达该城市时间
  int price_;                //来此地的花费
  Trans_id transport_type_;  //乘坐来的方法
  Train_id train_seat_type_; //如果搭乘火车,记录席别
};

class Path // 路径
{
public:
  /*添加一个PathNode到路径尾端,并且更改总价与总时间
    */
  Path() = default;
  Path &path_append(City_id city, bool start, const Time &depart, const Time &arrive, int price, Trans_id transport_type);
  /*获取路径长度
   */
  std::vector<PathNode>::size_type GetLen() const;

  int GetTotalPrice() const;
  Time GetTotalTime() const;

private:
  std::vector<PathNode> cities_; //储存节点
  int total_price_;              //总价
  Time total_timecost_;          //总时间
};
#endif // SRC_PATH