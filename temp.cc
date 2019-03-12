#include <vector>
#include <iostream>
#include <string>
#include <map>
using namespace std;

using city_id = int;
using city_str = string;
// time_format.h
class Time // 表示时间
{
  public:
    Time(int time);
    int GetDay();
    int GetHour();
    Time get
  private:
    int day;
    int hour;
};

// path.h
struct PathNode // 路径节点
{
    city_id city;
    Time arrive_time;
    transport_id transport_type;
};
class Path // 路径
{
  public:
    Path &path_append(city_id);

  private:
    vector<PathNode> cities_;
    int total_price_;
    Time time_cost_;
};

// city_graph.h

struct Route
{
    vector<Time> start_time;
    vector<Time> end_time;
    int price;
};
class CityGraph // 城市图
{
  public:
    Path get_path(const vector<city_id> &plan, stragety s);

  private:
    istream LoadCityGraph(istream, mode); // 加载文件
    Route city[city_number][city_number];        // citynumber表示城市（节点）的数量
};

// traveller.h
class Traveller // 旅行者
{
  public:
    // 待定
  private:
    stragety stragety;
    vector<city_id> travelling_plan;  // 旅行计划
    Path touring_path;                // 旅行路径
    vector<Path>::iterator next_city; // 路径中的下一个城市
};
// id_map.h
enum mode
{
    CITY,
    TRAIN
};
class IDMap
{
  public:
    // 待定
  private:
    istream LoadCityID(istream file, mode m);  // 加载文件
    istream LoadTrainID(istream file, mode m); // 加载文件
    map<city_id, city_str> city_map;
    map<train_id, trian_str> train_map;
}；

// log.h
class log
{
    public:
      
    private:
      ostream log_file;
    
};