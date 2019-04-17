#ifndef SRC_IDMAP
#define SRC_IDMAP

// #include <iostream>
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
  const std::string &GetStr(int id, const std::map<int, std::string> &map) const;
  const std::string paths_[3] = {
      // 文件路径
      "..//data//city_id.txt",            // city_id_path
      "..//data//train_seat_type_id.txt", // train_seat_type_path
      "..//data//transport_type_id.txt"   // trans_id_path_
  };
};

IDMap::IDMap()
{
  std::ifstream in_id_file;
  decltype(&city_map_) map_table[3] = // 三个map的类型实际上是一样的
      {
          &city_map_,
          &train_map_,
          &trans_map_
      };
  for (int i = 0; i != 3; ++i)
  {
    in_id_file.open(paths_[i]);
    // std::cout << "in_id_file opened " << i << std::endl;
    if (in_id_file.is_open())
    {
      LoadID(in_id_file, *map_table[i]);
      in_id_file.close();
    }
    else
      in_id_file.clear();
    // error handler
  }
  // std::cout << "Loaded IDs" << std::endl;
}

bool IDMap::LoadID(std::ifstream &id_file, std::map<int, std::string> &map)
{
  int temp_int;
  std::string temp_string;
  while (id_file >> temp_int >> temp_string)
    map[temp_int] = temp_string;
  return id_file.eof();
}

inline const std::string &IDMap::GetStr(int id, const std::map<int, std::string> &map) const
{
  // TODO: error handling
  return map.at(id);  // map为const
}

#endif // SRC_IDMAP
