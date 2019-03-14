#ifndef SRC_USER_TYPE
#define SRC_USER_TYPE
#include <string>
using City_id = int;
using Train_id = int;
using Trans_id = int;
using City_str = std::string;
using Train_str = std::string;
using Trans_str = std::string;
enum Strategy
{
    LEAST_MONEY,    // 最少费用
    LEAST_TIME,     // 最少时间
    LIMIT_TIME      // 限定时间内最少费用
};
#endif // SRC_USER_TYPE