#ifndef SRC_TRAVELLER
#define SRC_TRAVELLER
#include <vector>
#include <iostream>
#include "path.h"


class Traveller // 旅行者
{
  public:
    using Strategy = int;
    using City_id = int;
    Traveller();

  private:
    Strategy strategy;  // 旅行策略
    std::vector<City_id> travelling_plan;  // 旅行计划
    Path touring_path;                // 旅行路径
    std::vector<Path>::iterator next_city; // 路径中的下一个城市
};

#endif // SRC_TRAVELLER