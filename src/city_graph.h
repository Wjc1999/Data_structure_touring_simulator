#ifndef SRC_CG
#define SRC_CG

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "user_type.h"
#include "time_format.h"
#include "id_map.h"

const int kCityNum = 31;
static const std::string flightfn = "../data/flight_extract_with_id.txt";
static const std::string trainfn = "../data/train_extract_with_id.txt";
static const std::string carfn = "../data/car_extract_with_id.txt";

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
  CityGraph(); //构造函数
  int get_city_num() const { return kCityNum; };
  //打印ijk的存储数据
  void Show(City_id former_city, City_id current_city, int k) const;                                                 
  //获得存储在ijk的Route
  const Route &GetRoute(City_id former_city, City_id current_city, int k) const { return city_[former_city][current_city].at(k); }; 
  //获得city[i][j]的大小
  int Getsize(City_id i, City_id j) const { return city_[i][j].size(); };                                           

#ifdef TEST_CG

  void print()
  {
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
      {
        if (i != j)
        {
          for (int k = 0; k < city_[i][j].size(); k++)
            Show(i, j, k);
        }
      }
  }
#endif // TEST_CG

private:
  bool LoadCityGraph(const std::string &name, int type); // 加载文件
  std::vector<Route> city_[kCityNum][kCityNum];
};

inline CityGraph::CityGraph()
{
  if (
      LoadCityGraph(flightfn, 2) &&
      LoadCityGraph(trainfn, 1) &&
      LoadCityGraph(carfn, 0))
    std::cout << "Loading succeed!" << std::endl;
  else
    std::cout << "Loading error!" << std::endl;
}

inline bool CityGraph::LoadCityGraph(const std::string &name, int type)
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

inline void CityGraph::Show(City_id former_city, City_id current_city, int k) const
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
#endif //SRC_CG