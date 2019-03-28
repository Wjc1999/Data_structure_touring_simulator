#ifndef SRC_TRAVELLER
#define SRC_TRAVELLER

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdint>
#include <random>
#include <fstream>
#include <sstream>
#include <initializer_list>

#include "user_type.h"
#include "path.h"
#include "time_format.h"
#include "city_graph.h"

const int kMaxInt = INT32_MAX; // 0x7fffffff
#ifdef TEST_GET_PATH
extern int call_counter_time;
extern int call_counter_money;
extern int depth_counter;
#endif // TEST_GET_PATH
const std::string save_path = "../data/traveller_data.txt";
const std::string name_path = "../data/namelist.txt";

struct DFSLeastMoneyParWarp
{
  int temp_price;
  int path_price;
  bool *isMeet;
  int current;
  int depth;
  int min_price;
};

struct DFSLeastTimeParWarp
{
  Time t;
  City_id current;
  bool *isMeet;
  int depth;
  std::vector<City_id> temp;
};

class Traveller // 旅行者
{
public:
  Traveller() = default;
  Traveller(std::string id);
  // 显示旅客id
  const std::string &ShowID() const
  {
    std::cout << id_ << std::endl;
    return id_;
  };
  // 显示旅客路径
  void ShowPath() const { touring_path_.Show(); }
  // 为旅客获取一条路径**关键算法**
  Path GetPath(const CityGraph &graph, const std::vector<City_id> &plan, Strategy s, Time t = Time(), Time limit_time = Time());
  Path GetPath(const CityGraph &graph, Strategy s, Time t = Time(), Time limit_time = Time())
  {
    return GetPath(graph, travelling_plan_, s, t, limit_time);
  }

  // 设置旅行路径
  //void set_path(Path path);
  bool SaveData();
  bool LoadData(int cnt, const CityGraph &graph);
  void set_plan(const std::vector<City_id> &plan) { travelling_plan_ = plan; }
  void set_plan(std::initializer_list<City_id> il) { travelling_plan_ = std::vector<City_id>(il); }
  void append_plan(City_id city) { travelling_plan_.push_back(city); }
  void UpdateState(const CityGraph &graph, Time now);

private:
  std::string id_ = "";                  // 旅客id
  TravellerState state_ = STAY;          // 旅客当前状态
  Strategy strategy_ = LEAST_MONEY;      // 旅行策略
  std::vector<City_id> travelling_plan_; // 旅行计划 <起点>, <中继点>... , <终点>
  Path touring_path_;                    // 旅行路径
  int next_city_hour_left_ = 0;          // 到下一个城市的剩余多少小时
  int position_pathnode_ = -2;           // 当前在第k个pathnode上, -2代表没有出行计划，-1代表有出行计划但没到出发时间
  //std::vector<PathNode>::iterator next_city_; // 路径中的下一个城市
  Time init_time_; // 最开始时的时间
  Path GetPathLeastMoney(const CityGraph &graph, const std::vector<City_id> &plan);
  Path GetPathLeastTime(const CityGraph &graph, const std::vector<City_id> &plan, Time now);
  void DFSLeastTime(const CityGraph &graph, const std::vector<City_id> &plan, Path &path, Path &temp_path, DFSLeastTimeParWarp &par_warp);
  void DFSLeastMoney(const std::vector<std::vector<int>> &price_matrix, std::vector<int> &path, std::vector<int> &temp_path, DFSLeastMoneyParWarp &par_warp);
};

Traveller::Traveller(std::string id)
{
  id_ = id;
}

void Traveller::DFSLeastMoney(const std::vector<std::vector<int>> &price_matrix, std::vector<int> &path, std::vector<int> &temp_path, DFSLeastMoneyParWarp &par_warp)
{
#ifdef TEST_GET_PATH
  call_counter_money++;
#endif                                             // TEST_GET_PATH
  if (par_warp.current == price_matrix.size() - 1) // 到达终点时判断递归深度(路径长度)是否符合要求
  {
    if (par_warp.depth == price_matrix.size() - 1) // 路径长度是否符合要求
    {
      path = temp_path;
      par_warp.path_price = par_warp.temp_price;
#ifdef TEST_GET_PATH
      depth_counter++;
      std::cout << par_warp.path_price << std::endl;
#endif // TEST_GET_PATH
    }
    else
      return;
  }

  std::vector<int> path_save;
  int current_save = par_warp.current;

  for (int i = 0; i != price_matrix.size(); ++i)
  {
    if (i == par_warp.current || par_warp.isMeet[i])
      continue;
    else
    {
      par_warp.isMeet[i] = true;
      path_save = temp_path;
      par_warp.temp_price += price_matrix[par_warp.current][i];
      if (par_warp.temp_price <= par_warp.path_price && (price_matrix.size() - 2 - par_warp.depth) * par_warp.min_price <= par_warp.path_price - par_warp.temp_price)
      {
        temp_path.push_back(i);
        par_warp.depth++, par_warp.current = i; // 进入更深层的递归时保存当前的状态
        DFSLeastMoney(price_matrix, path, temp_path, par_warp);
        par_warp.depth--, par_warp.current = current_save; // 还原状态
      }
      par_warp.temp_price -= price_matrix[par_warp.current][i]; // 还原状态
      par_warp.isMeet[i] = false;
      temp_path = path_save;
    }
  }
}

void Traveller::DFSLeastTime(const CityGraph &graph, const std::vector<City_id> &plan, Path &path, Path &temp_path, DFSLeastTimeParWarp &par_warp)
{
#ifdef TEST_GET_PATH
  call_counter_time++;
#endif // TEST_GET_PATH
  if (par_warp.current == plan.size() - 1)
  {
    if (par_warp.depth == plan.size() - 1)
    {
      path = temp_path;
#ifdef TEST_GET_PATH
      depth_counter++;
      std::cout << path.GetTotalTime().to_hour() << std::endl;
#endif // TEST_GET_PATH
    }
    else
      return;
  }

  int temp_current = par_warp.current;
  Time temp_time;
  Time time_save = par_warp.t;
  Path path_save;

  for (int i = 0; i < plan.size(); ++i)
  {
    if (i == par_warp.current || par_warp.isMeet[i])
      continue;
    else
    {
      par_warp.temp[0] = plan[par_warp.current], par_warp.temp[1] = plan[i];
      temp_time = init_time_;
      path_save = temp_path;
      par_warp.isMeet[i] = true;
      temp_path.Append(GetPathLeastTime(graph, par_warp.temp, par_warp.t));
      temp_path.FixTotalTime(graph, init_time_);
      if (temp_path.GetTotalTime().to_hour() < path.GetTotalTime().to_hour() && plan.size() - 1 - par_warp.depth < path.GetTotalTime().to_hour() - temp_path.GetTotalTime().to_hour())
      {
        par_warp.current = i, par_warp.depth++, par_warp.t = temp_time.add_time(temp_path.GetTotalTime());
        DFSLeastTime(graph, plan, path, temp_path, par_warp);
        par_warp.current = temp_current, par_warp.depth--, par_warp.t = time_save;
      }
      par_warp.isMeet[i] = false;
      temp_path = path_save;
    }
  }
}

Path Traveller::GetPath(const CityGraph &graph, const std::vector<City_id> &plan, Strategy s, Time start_time, Time limit_time)
{
  init_time_ = start_time;
  strategy_ = s;
  travelling_plan_ = plan;

  if (plan.size() < 2)
    throw plan.size();
  if (s == LEAST_MONEY)
  {
    std::vector<std::vector<Path>> path_matrix;
    std::vector<std::vector<int>> price_matrix;
    std::vector<int> order_of_path, temp_path;
    int min_price = kMaxInt;
    Path res;
    int path_price = GetPathLeastMoney(graph, plan).GetTotalPrice();

    std::vector<City_id> temp_plan_shuffle = plan;
    int temp_path_price;
    std::random_device rd;
    std::mt19937 g(rd());
    for (int i = 0; i < 100; i++)
    {
      shuffle(temp_plan_shuffle.begin() + 1, temp_plan_shuffle.end() - 1, g);
      temp_path_price = GetPathLeastMoney(graph, temp_plan_shuffle).GetTotalPrice();
      if (temp_path_price < path_price)
        path_price = temp_path_price;
    }

    size_t sz = plan.size();
    bool *isMeet = new bool[sz];
    std::vector<City_id> temp_plan{0, 1};

    for (int i = 0; i != sz; ++i)
    {
      isMeet[i] = false;
      path_matrix.emplace_back();

      for (int j = 0; j != sz; ++j)
      {
        if (i != j && i != sz - 1 && j)
        {
          temp_plan[0] = plan[i], temp_plan[1] = plan[j];
          path_matrix[i].push_back(GetPathLeastMoney(graph, temp_plan));
        }
        else
        {
          path_matrix[i].emplace_back();
        }
      }
    }

    for (int i = 0; i != path_matrix.size(); ++i)
    {
      price_matrix.emplace_back();
      for (int j = 0; j != path_matrix[i].size(); ++j)
      {
        price_matrix[i].push_back(path_matrix[i][j].GetTotalPrice());
        if (price_matrix[i].back() && min_price > price_matrix[i].back())
          min_price = price_matrix[i].back();
      }
    }

    isMeet[0] = true;
    DFSLeastMoneyParWarp par_warp = {0, path_price, isMeet, 0, 0, min_price};
    order_of_path.push_back(0);
    temp_path.push_back(0);
    DFSLeastMoney(price_matrix, order_of_path, temp_path, par_warp);

    for (int i = 1; i != order_of_path.size(); ++i)
      res.Append(path_matrix[order_of_path[i - 1]][order_of_path[i]]);
    res.FixTotalTime(graph, start_time);

    delete isMeet;
    return res;
    // return GetPathLeastMoney(graph, plan);
  }
  else if (s == LEAST_TIME)
  {
    Path res = GetPathLeastTime(graph, plan, start_time);
    res.FixTotalTime(graph, start_time);
    int i = 0;
    auto sz = plan.size();

    if (plan.size() == 2)
      return res;
    else
    {
      bool *isMeet = new bool[sz];
      Path temp_path;
      std::vector<City_id> buf;
      for (i = 1; i != sz; ++i)
        isMeet[i] = false;
      std::vector<City_id> temp{0, 1};
      DFSLeastTimeParWarp par_warp = {start_time, 0, isMeet, 0, temp};
      DFSLeastTime(graph, plan, res, temp_path, par_warp);
      delete isMeet;
    }
    return res;
  }
  else // if (s == LIMIT_TIME)
  {
    // TODO
  }
}

Path Traveller::GetPathLeastMoney(const CityGraph &graph, const std::vector<City_id> &plan)
{
  City_id destination; // 终点
  City_id origin;      // 起点
  Path path;
  std::vector<int> find_min_cost;
  // std::cout << plan[0] << plan[1] << std::endl;
  for (int cnt = plan.size() - 1; cnt > 0; cnt--)
  {
    destination = plan[cnt];
    origin = plan[cnt - 1];
    int cost[kCityNum];      // 记录最小花费
    int preway[kCityNum][2]; // preway[cityA][] = {CityB, transport_index_from_CityB_to_CityA}
    bool is_count[kCityNum] = {false};

    for (int j = 0; j < kCityNum; j++) //对数据进行初始化
    {
      if (j == origin)
        continue;
      for (int k = 0; k < graph.Getsize(origin, j); k++) // 将所有从origin到j的价格push到find_min_cost中
        find_min_cost.push_back(graph.GetRoute(origin, j, k).price);

      if (!find_min_cost.empty()) // 如果可以从origin到j
      {
        std::vector<int>::iterator min = min_element(find_min_cost.begin(), find_min_cost.end());
        cost[j] = *min;
        preway[j][0] = origin;
        preway[j][1] = distance(find_min_cost.begin(), min);
        find_min_cost.clear();
      }
      else // 不可达
      {
        cost[j] = kMaxInt;
        preway[j][0] = -1;
        preway[j][1] = -1;
      }
    }

    cost[origin] = kMaxInt; // 去除origin
    preway[origin][0] = -1;
    preway[origin][1] = -1;
    is_count[origin] = true;

    while (!is_count[destination])
    {
      int temp = kMaxInt;
      int city_temp = origin;

      for (int i = 0; i < kCityNum; i++) //找到最小值
      {
        if (!is_count[i] && cost[i] < temp)
        {
          temp = cost[i];
          city_temp = i;
        }
      }

      is_count[city_temp] = true;
      if (city_temp == destination)
        break;

      for (int j = 0; j < kCityNum; j++) //更新
      {
        if (is_count[j])
          continue;
        for (int k = 0; k < graph.Getsize(city_temp, j); k++)
          find_min_cost.push_back(graph.GetRoute(city_temp, j, k).price);
        if (!find_min_cost.empty())
        {
          std::vector<int>::iterator min = min_element(find_min_cost.begin(), find_min_cost.end());
          int newcost = *min + cost[city_temp];
          if (newcost < cost[j])
          {
            cost[j] = newcost;
            preway[j][0] = city_temp;
            preway[j][1] = distance(find_min_cost.begin(), min);
          }
          find_min_cost.clear();
        }
      }
    }
    for (int traceback = destination; traceback != origin; traceback = preway[traceback][0])
    {
      path.Append(graph, preway[traceback][0], traceback, preway[traceback][1]);
    }
  }
  //path.Reverse();
  //path.Show();
  return path;
}

Path Traveller::GetPathLeastTime(const CityGraph &graph, const std::vector<City_id> &plan, Time now)
{
  City_id destination; // 终点
  City_id origin;      // 起点
  Path path;
  std::vector<int> find_min_cost;
  Time temp_now;
  std::vector<int>::iterator min;
  for (int cnt = plan.size() - 1; cnt > 0; cnt--)
  {
    destination = plan[cnt];
    origin = plan[cnt - 1];
    int cost[kCityNum];      // 记录最小花费
    int preway[kCityNum][2]; // preway[cityA][] = {CityB, transport_index_from_CityB_to_CityA}
    // Time pretime[kCityNum];
    bool is_count[kCityNum] = {false};

    for (int j = 0; j < kCityNum; j++) //对数据进行初始化
    {
      if (j == origin)
        continue;
      for (int k = 0; k < graph.Getsize(origin, j); k++) // 将所有从origin到j的价格push到find_min_cost中
      {                                                  //*****和LM的区别*****
        const Route &route = graph.GetRoute(origin, j, k);
        temp_now.set_hour(now.GetHour());
        int wait_hour = route.start_time.hour_diff(temp_now); // 计算从当前时间开始需要等待的时间
        if (wait_hour < 0)                                    // 如果发车时间在now之前,想要搭乘这辆车就必须等候到其发车
          wait_hour += 24;
        int route_hour = route.end_time.hour_diff(route.start_time); // 路途上的时间
        find_min_cost.push_back(wait_hour + route_hour);
      }

      if (!find_min_cost.empty()) // 如果可以从origin到j
      {
        min = min_element(find_min_cost.begin(), find_min_cost.end());
        cost[j] = *min;
        preway[j][0] = origin;
        preway[j][1] = distance(find_min_cost.begin(), min);
        // pretime[j] = now;
        find_min_cost.clear();
      }
      else // 不可达
      {
        cost[j] = kMaxInt;
        preway[j][0] = -1;
        preway[j][1] = -1;
      }
    }

    cost[origin] = kMaxInt; // 去除origin
    preway[origin][0] = -1;
    preway[origin][1] = -1;
    is_count[origin] = true;

    while (!is_count[destination])
    {
      int temp = kMaxInt;
      int city_temp = origin;

      for (int i = 0; i < kCityNum; i++) //找到最小值
      {
        if (!is_count[i] && cost[i] < temp)
        {
          temp = cost[i];
          city_temp = i;
        }
      }

      is_count[city_temp] = true;
      if (city_temp == destination)
        break;
      //*****和LM的区别*****
      // Route temp_route = graph.GetRoute(preway[city_temp][0], city_temp, preway[city_temp][1]);
      // now.add_time(cost[city_temp]);   // 此时的时间为之前的时间加上从前一个城市到city_temp的时间(包括等候时间)
      now = graph.GetRoute(preway[city_temp][0], city_temp, preway[city_temp][1]).end_time;
      temp_now.set_hour(now.GetHour()); // 只看到达时间,不看天数
      // now = graph.GetRoute(preway[city_temp][0], city_temp, preway[city_temp][1]).end_time;

      for (int j = 0; j < kCityNum; j++) //更新
      {
        if (is_count[j])
          continue;
        for (int k = 0; k < graph.Getsize(city_temp, j); k++)
        { //*****和LM的区别*****
          const Route &route = graph.GetRoute(city_temp, j, k);
          int wait_hour = route.start_time.hour_diff(temp_now); // 计算从当前时间开始需要等待的时间
          if (wait_hour < 0)                                    // 如果发车时间在now之前,想要搭乘这辆车就必须等候到其发车
            wait_hour += 24;
          int route_hour = route.end_time.hour_diff(route.start_time); // 路途上的时间
          find_min_cost.push_back(wait_hour + route_hour);
        }

        if (!find_min_cost.empty())
        {
          min = min_element(find_min_cost.begin(), find_min_cost.end());
          int newcost = *min + cost[city_temp];
          if (newcost < cost[j])
          {
            cost[j] = newcost;
            preway[j][0] = city_temp;
            preway[j][1] = distance(find_min_cost.begin(), min);
            // pretime[j] = now;
          }
          find_min_cost.clear();
        }
      }
    }
    for (int traceback = destination; traceback != origin; traceback = preway[traceback][0])
    {
      path.Append(graph, preway[traceback][0], traceback, preway[traceback][1]); //pretime[traceback]);
    }
  }
  //path.Reverse();
  //path.Show();
  return path;
}

bool Traveller::SaveData()
{
  std::ofstream out_stream(save_path, std::ofstream::app);
  if (out_stream.is_open())
  {
    out_stream << id_ << std::endl; // 第一行,记录id

    // if (state_ == STAY)
    //   out_stream << "0" << std::endl;
    // else if (state_ == OFF)
    //   out_stream << "1" << std::endl;
    out_stream << state_ << std::endl; // 第二行,记录旅客状态

    // if (strategy_ == LEAST_MONEY)
    //   out_stream << "0" << std::endl;
    // else if (strategy_ == LEAST_TIME)
    //   out_stream << "1" << std::endl;
    // else if (strategy_ == LIMIT_TIME)
    //   out_stream << "2" << std::endl;
    out_stream << strategy_ << std::endl; // 第三行,记录旅行策略

    for (int i = 0; i < travelling_plan_.size(); i++) // 第四行,记录旅行计划
    {
      out_stream << travelling_plan_.at(i) << " ";
    }
    out_stream << std::endl;

    for (auto i = touring_path_.cbegin(); i != touring_path_.cend(); i++) // 第五行,记录旅行路径
    {
      out_stream << (*i).former_city << " " << (*i).current_city << " " << (*i).kth_way << " ";
    }
    out_stream << std::endl;

    out_stream << next_city_hour_left_ << std::endl; //第六行

    out_stream << position_pathnode_ << std::endl; //第七行

    out_stream.close();

    out_stream.open(name_path, std::ofstream::app);
    if (out_stream.is_open())
    {
      out_stream << id_ << std::endl;
      return true;
    }
  }
  return false;
}

bool Traveller::LoadData(int cnt, const CityGraph &graph)
{
  if(cnt == -1)
    return true;
  std::ifstream in_stream(save_path);
  int state_temp;
  int strategy_temp;
  if (in_stream.is_open())
  {
    std::string temp;
    for (int i = 0; i < cnt * 7; i++)
      getline(in_stream, temp); //找位置

    in_stream >> id_; //第一行

    in_stream >> state_temp;    //第二行
    in_stream >> strategy_temp; //第三行

    if (state_temp == 0)
      state_ = STAY;
    else if (state_temp == 1)
      state_ = OFF;
    if (strategy_temp == 0)
      strategy_ = LEAST_MONEY;
    else if (strategy_temp == 1)
      strategy_ = LEAST_TIME;
    else if (strategy_temp == 2)
      strategy_ = LIMIT_TIME;

    getline(in_stream, temp); //第四行
    std::istringstream ss(temp);
    int plantemp;
    while (ss >> plantemp)
    {
      travelling_plan_.push_back(plantemp);
    }

    getline(in_stream, temp); //第五行
    ss.str(temp);
    City_id former_city, current_city, k;
    while (ss >> former_city)
    {
      ss >> current_city;
      ss >> k;
      touring_path_.Append(graph, former_city, current_city, k);
    }
    in_stream >> next_city_hour_left_;
    in_stream >> position_pathnode_;
    return true;
  }
  return false;
}

inline void Traveller::UpdateState(const CityGraph &graph, Time now)
{
  if (state_ == OFF)
  {
    if (next_city_hour_left_ == 1)
    {
      if (position_pathnode_ == touring_path_.GetLen() - 1)
      {
        state_ = STAY;
        position_pathnode_ = -2;
        return;
      }
      else
      {
        position_pathnode_++;
        PathNode node = touring_path_.GetNode(position_pathnode_);
        Route route = graph.GetRoute(node.former_city, node.current_city, node.kth_way);
        next_city_hour_left_ = route.start_time.hour_diff(route.end_time);
      }
    }
    else
      next_city_hour_left_--;
  }
  else
  {

    if (position_pathnode_ == -1)
    {
      /*if(now, init_time_)
      {
        state_=OFF;
        PathNode node = touring_path_.GetNode(0);
        Route route = graph.GetRoute(node.former_city, node.current_city, node.kth_way);
        next_city_hour_left_ = route.start_time.hour_diff(route.end_time);
        position_pathnode_++;
      } 这里做一个时间判断如果到出发时间就更新*/
    }
  }
}
#endif // SRC_TRAVELLER