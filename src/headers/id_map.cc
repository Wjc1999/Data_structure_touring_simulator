#ifndef SRC_IDMAP_CC
#define SRC_IDMAP_CC

#pragma execution_character_set("utf-8")

#include <fstream>
#include <map>
#include <string>

#include "id_map.h"
#include "user_type.h"
#include "log.h"

IDMap::IDMap()
{
  std::ifstream in_id_file;
  decltype(&city_map_) map_table[3] = // 三个map的类型实际上是一样的
      {
          &city_map_,
          &train_map_,
          &trans_map_};
  for (int i = 0; i != 3; ++i)
  {
    in_id_file.open(paths_[i]);
    // std::cout << "in_id_file opened " << i << std::endl;
    if (in_id_file.is_open())
    {
      Log::LogWrite(std::string("加载 ") + paths_[i] + " 中");
      LoadID(in_id_file, *map_table[i]);
      in_id_file.close();
    }
    else
    {
      Log::LogWrite(paths_[i] + " 加载失败");
      in_id_file.clear();
      // error handler
    }
  }
  // std::cout << "Loaded IDs" << std::endl;
}

//从给定的文件中加载ID
bool IDMap::LoadID(std::ifstream &id_file, std::map<int, std::string> &map)
{
  int temp_int;
  std::string temp_string;
  while (id_file >> temp_int >> temp_string)
    map[temp_int] = temp_string;
  return id_file.eof();
}
#endif // SRC_IDMAP_CC
