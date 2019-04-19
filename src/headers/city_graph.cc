#ifndef SRC_CG_CC
#define SRC_CG_CC

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "city_graph.h"
#include "user_type.h"
#include "time_format.h"
#include "id_map.h"

static const std::string flight_file_path = "../data/flight_extract_with_id.txt";
static const std::string train_file_path = "../data/train_extract_with_id.txt";
static const std::string car_file_path = "../data/car_extract_with_id.txt";

CityGraph::CityGraph()
{
  if (
      LoadCityGraph(flight_file_path, 2) &&
      LoadCityGraph(train_file_path, 1) &&
      LoadCityGraph(car_file_path, 0))
      ;
    //std::cout << "数据读取成功！" << std::endl;
  else
  {
    //std::cout << "数据读取失败！" << std::endl;
    exit(0);
  }
}

bool CityGraph::LoadCityGraph(const std::string &name, int type)
{ //将飞机火车汽车数据加载到程序中
  std::ifstream stream(name);
  if (type != 1)
  { //飞机汽车的数据
    if (stream.is_open())
    {
      int data[5];
      while (!stream.eof())
      {
        for (int i = 0; i < 5; i++)
        {
          stream >> data[i];
        }
        Route temp = {type, 0, Time(data[2]), Time(data[3]), data[4]};
        //temp.transport_type = type;
        //temp.train_seat_type = ;
        //temp.start_time = Time(data[2]);
        //temp.end_time = Time(data[3]);
        //temp.price = data[4];
        city_[data[0]][data[1]].push_back(temp);
      }
      stream.close();
      return true;
    }
    stream.close();
    return false;
  }
  else
  { //火车的数据
    if (stream.is_open())
    {
      int data[7];
      std::string line;
      while (getline(stream, line))
      {
        std::istringstream ss(line);
        for (int i = 0; i < 7; i++)
        {
          ss >> data[i];
        }
        Route temp = {type, 0, Time(data[2]), Time(data[3]), data[6]};
        city_[data[0]][data[1]].push_back(temp);
      }
      stream.close();
      return true;
    }
    stream.close();
    return false;
  }
}

void CityGraph::Show(City_id former_city, City_id current_city, int k) const
{
  if (former_city != current_city)
  {
    std::cout << former_city << ' ' << current_city << ' ' << k << ' '
              << city_[former_city][current_city].at(k).start_time.GetDay() << ' '
              << city_[former_city][current_city].at(k).start_time.GetHour() << ' '
              << city_[former_city][current_city].at(k).end_time.GetDay() << ' '
              << city_[former_city][current_city].at(k).end_time.GetHour() << ' '
              << city_[former_city][current_city].at(k).price << std::endl;
  }
  else
    std::cout << "No data!" << std::endl;
}
#endif // SRC_CG_CC
