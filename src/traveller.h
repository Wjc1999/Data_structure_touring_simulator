#ifndef SRC_TRAVELLER
#define SRC_TRAVELLER
#include <vector>
#include <iostream>
#include <string>

#include "user_type.h"
#include "path.h"
#include "time_format.h"

class Traveller // 旅行者
{
public:
  Traveller();
  std::string ShowID();                  // 显示旅客id
  void ShowPath();                       // 显示旅客路径
  Path get_path(const std::vector <City_id> &plan, Strategy s);//为旅客获取一条路径**关键算法**

private:
  std::string id;                        // 旅客id
  int state;                             // 旅客当前状态
  Time new_journey;                      // 旅客下一次空闲的时间
  Strategy strategy;                     // 旅行策略
  std::vector<City_id> travelling_plan;  // 旅行计划 <起点>, <中继点>... , <终点>
  Path touring_path;                     // 旅行路径
  std::vector<Path>::iterator next_city; // 路径中的下一个城市
};

#endif // SRC_TRAVELLER