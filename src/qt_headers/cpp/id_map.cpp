#include "headers/id_map.h"

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

inline const std::string &IDMap::GetCityStr(City_id id) const
{
    return GetStr(id, city_map_);
}

inline const std::string &IDMap::GetTrainSeatTypeStr(Train_id id) const
{
    return GetStr(id, train_map_);
}

inline const std::string &IDMap::GetTransStr(Trans_id id) const
{
    return GetStr(id, trans_map_);
}

std::map<int, std::string>::size_type IDMap::GetCityMapSize() const
{
    return city_map_.size();
}

std::map<int, std::string>::size_type IDMap::GetTrainMapSize() const
{
    return train_map_.size();
}

std::map<int, std::string>::size_type IDMap::GetTransMapSize() const
{
    return trans_map_.size();
}

inline bool IDMap::LoadID(std::ifstream &id_file, std::map<int, std::string> &map)
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
