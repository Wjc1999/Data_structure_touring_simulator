#ifndef SRC_PATH
#define SRC_PATH
#include"time_format.h"
#include <vector>
using city_id = int;
using transport_id = std::string;

struct PathNode // 路径节点
{
    city_id city;//城市名
    int nodetype;//规定0为“起点”，1为“其它点”，
    /*以下相当于一种交通方法的信息
    */
    Time depart_time;//之前离开的时间
    Time arrive_time;//到达时间
    int price;//来此地的花费
    transport_id transport_type;//乘坐来的方法
};
class Path // 路径
{
  public:
    /*通过一个id添加至路径
    */
    Path &path_append(transport_id);

  private:
    vector <PathNode> cities_;//储存节点
    int total_price_;//总价
    Time total_timecost_;//总时间
};
#endif//SRC_PATH