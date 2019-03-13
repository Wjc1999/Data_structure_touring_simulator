#ifndef SRC_IDMAP
#define SRC_IDMAP

#include <iostream>
#include <map>
#include <string>

#include "user_type.h"
/* class IDMap
 * 储存各类序号及其对应的字符串,供输出使用
 */
class IDMap
{
public:
  /* 
     */
  IDMap() = default;
  ~IDMap(); // 是否需要析构函数?
  /* 给序号获得城市名
    */
  std::string GetCityStr(City_id id) const;
  /* 给序号获得火车座位等级名
    */
  std::string GetTrainSeatTypeStr(Train_id id) const;
  /* 给序号获得交通方式
   */
  std::string GetTransStr(Trans_id id) const;

private:
  std::istream &LoadCityID(std::istream &city_id_file);           // 加载城市与序号的对应文件
  std::istream &LoadTrainSeatTypeID(std::istream &train_id_file); // 加载火车等级与序号的对应文件
  std::istream &LoadTransportID(std::istream &trans_id_file);     // 从文件中加载交通方式对应的序号
  std::map<City_id, City_str> city_map_;
  std::map<Train_id, Train_str> train_map_;
  std::map<Trans_id, Trans_str> trans_map_;
  const std::string train_seat_type_file_path_ = "", city_file_path_ = "", trans_id_file_path_ = ""; // 文件路径
};

#endif // SRC_IDMAP
