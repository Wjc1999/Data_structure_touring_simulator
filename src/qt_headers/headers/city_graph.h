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

  int get_city_num() const;

  //打印ijk的存储数据
  void Show(City_id former_city, City_id current_city, int k) const;

  //获得存储在ijk的Route
  const Route &GetRoute(City_id former_city, City_id current_city, int k) const;
  
  //获得city[i][j]的大小
  int Getsize(City_id i, City_id j) const;

private:
  bool LoadCityGraph(const std::string &name, int type); // 加载文件
  std::vector <Route> city_[kCityNum][kCityNum];
};
#endif //SRC_CG
