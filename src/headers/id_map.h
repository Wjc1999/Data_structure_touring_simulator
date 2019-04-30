#ifndef SRC_IDMAP_H
#define SRC_IDMAP_H

#pragma execution_character_set("utf-8")

#include <fstream>
#include <map>
#include <string>

#include "user_type.h"

/* class IDMap
 * 储存各类序号及其对应的字符串,供输出使用
 */
class IDMap
{
public:
  IDMap();

  // 给序号获得城市名
  const std::string &GetCityStr(City_id id) const { return GetStr(id, city_map_); }
  // 给序号获得火车座位等级名
  const std::string &GetTrainSeatTypeStr(Train_id id) const { return GetStr(id, train_map_); }
  // 给序号获得交通方式
  const std::string &GetTransStr(Trans_id id) const { return GetStr(id, trans_map_); }

#define TEST_IDMAP
#ifdef TEST_IDMAP
  std::map<int, std::string>::size_type GetCityMapSize()  const { return city_map_.size();  }
  std::map<int, std::string>::size_type GetTrainMapSize() const { return train_map_.size(); }
  std::map<int, std::string>::size_type GetTransMapSize() const { return trans_map_.size(); }
#endif // TEST_IDMAP

private:
  std::map<City_id, City_str> city_map_;
  std::map<Train_id, Train_str> train_map_;
  std::map<Trans_id, Trans_str> trans_map_;
  bool LoadID(std::ifstream &id_file, std::map<int, std::string> &map); //从给定的文件中加载ID
  const std::string &GetStr(int id, const std::map<int, std::string> &map) const { return map.at(id);}
  const std::string paths_[3] = {
      // 文件路径
      "..//data//city_id.txt",            // city_id_path
      "..//data//train_seat_type_id.txt", // train_seat_type_path
      "..//data//transport_type_id.txt"   // trans_id_path_
  };
};
#endif // SRC_IDMAP_H
