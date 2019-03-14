#ifndef SRC_CG
#define SRC_CG

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "user_type.h"
#include "time_format.h"
#include "path.h"
const int City_number = 31;

struct Route
{
  Trans_id transport_type;
  Train_id train_seat_type;
  Time start_time;
  Time end_time;
  int price;
};

class CityGraph // 城市图
{
public:
  CityGraph();
  Path get_path(const std::vector<City_id> &plan, Strategy s, Time limit_time = Time(1, 0));

#ifdef TEST_CG
#include <iostream>
  //测试用
  void print()
  {
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
      {
        if (i != j)
        {
          for (int k = 0; k < city[i][j].size(); k++)
          {
            std::cout << i << ' ' << j << ' ';
            std::cout << city[i][j].at(k).transport_type << ' ' << city[i][j].at(k).price << std::endl;
          }
        }
      }
  }
#endif // TEST_CG

private:
    bool LoadCityGraph(std::string name, int type); // 加载文件
  std::vector<Route> city[City_number][City_number];
};

inline CityGraph::CityGraph()
{
  std::string flightfn = "../data/flight_extract_with_id.txt";
  std::string trainfn = "../data/train_extract_with_id.txt";
  std::string carfn = "../data/car_extract_with_id.txt";
  if (
      LoadCityGraph(flightfn, 2) &&
      LoadCityGraph(trainfn, 1) &&
      LoadCityGraph(carfn, 0))
    std::cout << "Loading succeed!" << std::endl;
  else
    std::cout << "Loading error!" << std::endl;
}

inline bool CityGraph::LoadCityGraph(std::string name, int type)
{
  std::ifstream stream(name);
  if (type != 1)
  {
    if (stream.is_open())
    {
      int data[5];
      while (!stream.eof())
      {
        for (int i = 0; i < 5; i++)
        {
          stream >> data[i];
        }
        //Route temp;
        Route temp = {type, 0, Time(data[2]), Time(data[3]), data[4]};
        //temp.transport_type = type;
        //temp.train_seat_type = ;
        //temp.start_time = Time(data[2]);
        //temp.end_time = Time(data[3]);
        //temp.price = data[4];
        city[data[0]][data[1]].push_back(temp);
      }
      return true;
    }
    return false;
  }
  else
  {
    if (stream.is_open())
    {
      int data[5];
      std::string line;
      while (getline(stream, line))
      {
        std::istringstream ss(line);
        for (int i = 0; i < 7; i++)
        {
          ss >> data[i];
        }
        Route temp = {type, 0, Time(data[2]), Time(data[3]), data[6]};
        city[data[0]][data[1]].push_back(temp);
      }
      return true;
    }
    return false;
  }
}

#endif //SRC_CG