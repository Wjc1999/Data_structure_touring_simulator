#ifndef SRC_USER_TYPE
#define SRC_USER_TYPE
#include <string>
using City_id = int;
using Train_id = int;
using Trans_id = int;
using City_str = std::string;
using Train_str = std::string;
using Trans_str = std::string;
// 旅客旅行策略,默认为最少费用
enum Strategy
{
    LEAST_MONEY,    // 最少费用
    LEAST_TIME,     // 最少时间
    LIMIT_TIME      // 限定时间内最少费用
};
// 旅客所处状态,默认为停留等候
enum TravellerState
{
    STAY,           // 停留等候
    OFF             // 在前往下一个城市的路上
};
#endif // SRC_USER_TYPE