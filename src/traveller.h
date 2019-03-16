#ifndef SRC_TRAVELLER
#define SRC_TRAVELLER
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include "user_type.h"
#include "path.h"
#include "time_format.h"
#include "city_graph.h"
const int maxint = 0x7fffffff;
class Traveller // 旅行者
{
public:
  Traveller();
  std::string ShowID();                  // 显示旅客id
  void ShowPath();                       // 显示旅客路径
  Path get_path(CityGraph graph, const std::vector <City_id> &plan, Strategy s);//为旅客获取一条路径**关键算法**

private:
  std::string id;                        // 旅客id
  int state;                             // 旅客当前状态
  Time new_journey;                      // 旅客下一次空闲的时间
  Strategy strategy;                     // 旅行策略
  std::vector<City_id> travelling_plan;  // 旅行计划 <起点>, <中继点>... , <终点>
  Path touring_path;                     // 旅行路径
  std::vector<Path>::iterator next_city; // 路径中的下一个城市
  Path get_path_LM(CityGraph graph, const std::vector <City_id> &plan);
};

std::string Traveller::ShowID(){
  std::cout<<id<<std::endl;
  return id;
}

Path Traveller::get_path(CityGraph graph, const std::vector <City_id> &plan, Strategy s){
  if(plan.size()<2)throw plan.size();
  if(s == LEAST_MONEY)return get_path_LM(graph, plan);
}

Path Traveller::get_path_LM(CityGraph graph, const std::vector <City_id> &plan){
  int destination = plan[plan.size()-1];
  int origin = plan[0];
  Path path;
  int price[City_number];
  int preway[City_number][2];
  bool is_count[City_number];
  std::vector <int> findminprice;
  for(int j=0;j<City_number;j++){
    if(j==origin)continue;
    for(int k=0;k<graph.Getsize(origin,j);k++)findminprice.push_back(graph.Get(origin,j,k).price);
    if(!findminprice.empty()){
      std::vector<int>::iterator min = min_element(findminprice.begin(), findminprice.end());
      price[j] = *min;
      preway[j][0] = origin;
      preway[j][1] = distance(findminprice.begin(),min);
      findminprice.clear();
    }
    else{
      price[j] = maxint;
      preway[j][0] = -1;
      preway[j][1] = -1;
    }
  }
  price[origin] = maxint;
  preway[origin][0] = -1;
  preway[origin][1] = -1;
  is_count[origin] = true;
  while(!is_count[destination]){
    int temp = maxint;
    int city_temp = origin;
    for(int i=0;i<City_number;i++){
      if(!is_count[i]&&price[i]<temp){
        temp = price[i];
        city_temp = i;
      }
    }
    is_count[city_temp] = true;if(city_temp = destination)break;
    for(int j=0;j<City_number;j++){
      if(is_count[j])continue;
      for(int k=0;k<graph.Getsize(city_temp,j);k++)findminprice.push_back(graph.Get(city_temp,j,k).price);
      if(!findminprice.empty()){
        std::vector<int>::iterator min = min_element(findminprice.begin(), findminprice.end());
        int newprice = *min + price[city_temp];
        if(newprice<price[j]){
          price[j] = newprice;
          preway[j][0] = city_temp;
          preway[j][1] = distance(findminprice.begin(),min);
        }
        findminprice.clear();
      }
    }
  }
}
#endif // SRC_TRAVELLER