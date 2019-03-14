#ifndef SRC_TRAVELLER
#define SRC_TRAVELLER
#include <vector>
#include <iostream>

#include "user_type.h"
#include "path.h"

class Traveller // 旅行者
{
public:
  Traveller();

private:
  Strategy strategy;                     // 旅行策略
  std::vector<City_id> travelling_plan;  // 旅行计划 <起点>, <中继点>... , <终点>
  Path touring_path;                     // 旅行路径
  std::vector<Path>::iterator next_city; // 路径中的下一个城市
};

#endif // SRC_TRAVELLER