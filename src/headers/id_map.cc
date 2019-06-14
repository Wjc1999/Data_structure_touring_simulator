﻿#ifndef SRC_IDMAP_CC
#define SRC_IDMAP_CC

#pragma execution_character_set("utf-8")

#include <fstream>
#include <map>
#include <string>

#include "id_map.h"
#include "user_type.h"
#include "log.h"

const std::string IDMap::paths_[3]= {
        // 文件路径
        "..//data//city_id.txt",            // city_id_path
        "..//data//train_seat_type_id.txt", // train_seat_type_path
        "..//data//transport_type_id.txt"   // trans_id_path_
};

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
            return;
        }
    }
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
