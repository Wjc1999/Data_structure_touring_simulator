#ifndef SRC_TRAVELLER
#define SRC_TRAVELLER
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdint>

#include "user_type.h"
#include "path.h"
#include "time_format.h"
#include "city_graph.h"

const int kMaxInt = INT32_MAX; // 0x7fffffff
class Traveller                // 旅行者
{
public:
  Traveller() = default;
  // 显示旅客id
  const std::string &ShowID() const
  {
    std::cout << id_ << std::endl;
    return id_;
  };
  // 显示旅客路径
  void ShowPath() const { touring_path_.Show(); };
  // 为旅客获取一条路径**关键算法**
  Path get_path(const CityGraph &graph, const std::vector<City_id> &plan, Strategy s);
  // 设置旅行路径
  void set_path(Path path);

private:
  std::string id_ = "";                       // 旅客id
  TravellerState state_ = STAY;               // 旅客当前状态
  Time new_journey_;                          // 旅客下一次空闲的时间
  Strategy strategy_ = LEAST_MONEY;           // 旅行策略
  std::vector<City_id> travelling_plan_;      // 旅行计划 <起点>, <中继点>... , <终点>
  Path touring_path_;                         // 旅行路径
  std::vector<PathNode>::iterator next_city_; // 路径中的下一个城市
  Path get_path_LM(const CityGraph &graph, const std::vector<City_id> &plan);
};

Path Traveller::get_path(const CityGraph &graph, const std::vector<City_id> &plan, Strategy s)
{
  if (plan.size() < 2)
    throw plan.size();
  if (s == LEAST_MONEY)
    return get_path_LM(graph, plan);
}

Path Traveller::get_path_LM(const CityGraph &graph, const std::vector<City_id> &plan)
{
  City_id destination; // 终点
  City_id origin;                    // 起点
  Path path;
  for(int cnt=plan.size()-1;cnt>0;cnt--){
    destination = plan[cnt];
    origin = plan[cnt-1];
    int price[kCityNum];                         
    int preway[kCityNum][2];
    bool is_count[kCityNum];
    std::vector<int> find_min_price;

    for (int j = 0; j < kCityNum; j++)//对数据进行初始化
    {
      if (j == origin)
        continue;
      for (int k = 0; k < graph.Getsize(origin, j); k++)
        find_min_price.push_back(graph.GetRoute(origin, j, k).price);

      if (!find_min_price.empty())
      {
        std::vector<int>::iterator min = min_element(find_min_price.begin(), find_min_price.end());
        price[j] = *min;
        preway[j][0] = origin;
        preway[j][1] = distance(find_min_price.begin(), min);
        find_min_price.clear();
      }
      else
      {
        price[j] = kMaxInt;
        preway[j][0] = -1;
        preway[j][1] = -1;
      }
    }

    price[origin] = kMaxInt;
    preway[origin][0] = -1;
    preway[origin][1] = -1;
    is_count[origin] = true;

    while (!is_count[destination])
    {
      int temp = kMaxInt;
      int city_temp = origin;

      for (int i = 0; i < kCityNum; i++)   //找到最小值
      {
        if (!is_count[i] && price[i] < temp)
        {
          temp = price[i];
          city_temp = i;
        }
      }

      is_count[city_temp] = true;
      if (city_temp = destination)
        break;

      for (int j = 0; j < kCityNum; j++)  //更新
      {
        if (is_count[j])
          continue;
        for (int k = 0; k < graph.Getsize(city_temp, j); k++)
          find_min_price.push_back(graph.GetRoute(city_temp, j, k).price);
        if (!find_min_price.empty())
        {
          std::vector<int>::iterator min = min_element(find_min_price.begin(), find_min_price.end());
          int newprice = *min + price[city_temp];
          if (newprice < price[j])
          {
            price[j] = newprice;
            preway[j][0] = city_temp;
            preway[j][1] = distance(find_min_price.begin(), min);
          }
          find_min_price.clear();
        }
      }
    }
    for(int traceback = destination;traceback!=origin;traceback = preway[traceback][0]){
      path.Append(graph, preway[traceback][0], traceback, preway[traceback][1]);
    }
  }
  path.Reverse();
  path.Show();
}
#endif // SRC_TRAVELLER