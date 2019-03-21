#ifndef SRC_TRAVELLER
#define SRC_TRAVELLER
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdint>
#include <random>

#include "user_type.h"
#include "path.h"
#include "time_format.h"
#include "city_graph.h"

const int kMaxInt = INT32_MAX; // 0x7fffffff
extern int call_counter_T;
extern int call_counter_M;
extern int depth_counter_T;

struct dfs_logic_m
{
  int temp_price;
  int path_price;
  bool *isMeet;
  int current;
  int depth;
  int min_price;
};

struct dfs_logic_t
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
  // 显示旅客id
  const std::string &ShowID() const
  {
    std::cout << id_ << std::endl;
    return id_;
  };
  // 显示旅客路径
  void ShowPath() const { touring_path_.Show(); }
  // 为旅客获取一条路径**关键算法**
  Path get_path(const CityGraph &graph, const std::vector<City_id> &plan, Strategy s, Time t = Time());
  // 设置旅行路径
  void set_path(Path path);

private:
  std::string id_ = "";                       // 旅客id
  TravellerState state_ = STAY;               // 旅客当前状态
  Time new_journey_;                          // 旅客下一次空闲的时间
  Strategy strategy_ = LEAST_MONEY;           // 旅行策略
  std::vector<City_id> travelling_plan_;      // 旅行计划 <起点>, <中继点>... , <终点>
  Path touring_path_;                         // 旅行路径
  std::vector<PathNode>::iterator next_city_; // 路径中的下一个城市
  Time init_time_;                            // 最开始时的时间
  Path get_path_LM(const CityGraph &graph, const std::vector<City_id> &plan);
  Path get_path_LT(const CityGraph &graph, const std::vector<City_id> &plan, Time now);
  void dfs_LT(const CityGraph &graph, const std::vector<City_id> &plan, Path &path, Path &temp_path, dfs_logic_t &tl);
  void dfs(const std::vector<std::vector<int>> &price_matrix, std::vector<int> &path, std::vector<int> &temp_path, dfs_logic_m &dl);
};

void Traveller::dfs(const std::vector<std::vector<int>> &price_matrix, std::vector<int> &path, std::vector<int> &temp_path, dfs_logic_m &dl)
{
  call_counter_M++;
  if (dl.current == price_matrix.size() - 1)
  {
    if (dl.depth == price_matrix.size())
    {
      path = temp_path;
      dl.path_price = dl.temp_price;
    }
    else
      return;
  }
  std::vector<int> save;
  int temp_current = dl.current;
  for (int i = 0; i != price_matrix.size(); ++i)
  {
    if (i == dl.current || dl.isMeet[i])
      continue;
    else
    {
      dl.isMeet[i] = true;
      save = temp_path;
      dl.temp_price += price_matrix[dl.current][i];
      if (dl.temp_price < dl.path_price && (price_matrix.size() - dl.depth) * dl.min_price < dl.path_price - dl.temp_price)
      {
        temp_path.push_back(i);
        dl.depth++, dl.current = i;
        dfs(price_matrix, path, temp_path, dl);
        dl.depth--, dl.current = temp_current;
      }
      dl.temp_price -= price_matrix[dl.current][i];
      dl.isMeet[i] = false;
      temp_path = save;
    }
  }
}

void Traveller::dfs_LT(const CityGraph &graph, const std::vector<City_id> &plan, Path &path, Path &temp_path, dfs_logic_t &tl)
{
  call_counter_T++;
  if (tl.current == plan.size() - 1)
  {
    if (tl.depth == plan.size() - 1)
    {
      depth_counter_T++;
      path = temp_path;
      std::cout << path.GetTotalTime().to_hour() << std::endl;
    }
    else
      return;
  }
  int temp_current = tl.current;
  Time temp_time;
  Time save_t = tl.t;
  Path save;
  for (int i = 0; i < plan.size(); ++i)
  {
    if (i == tl.current || tl.isMeet[i])
      continue;
    else
    {
      tl.temp[0] = plan[tl.current], tl.temp[1] = plan[i];
      temp_time = init_time_;
      save = temp_path;
      tl.isMeet[i] = true;
      temp_path.Append(get_path_LT(graph, tl.temp, tl.t));
      temp_path.FixTotalTime(graph, init_time_);
      if (temp_path.GetTotalTime().to_hour() < path.GetTotalTime().to_hour() && plan.size() - 1 - tl.depth < path.GetTotalTime().to_hour() - temp_path.GetTotalTime().to_hour())
      {
        tl.current = i, tl.depth++, tl.t = temp_time.add_time(temp_path.GetTotalTime());
        dfs_LT(graph, plan, path, temp_path, tl);
        tl.current = temp_current, tl.depth--, tl.t = save_t;
      }
      tl.isMeet[i] = false;
      temp_path = save;
    }
  }
}

Path Traveller::get_path(const CityGraph &graph, const std::vector<City_id> &plan, Strategy s, Time start_time)
{
  init_time_ = start_time;
  if (plan.size() < 2)
    throw plan.size();
  if (s == LEAST_MONEY)
  {
    std::vector<std::vector<Path>> adj_matrix;
    std::vector<std::vector<int>> price_matrix;
    std::vector<int> path_order, temp_path;
    int min_price = kMaxInt;
    Path path;
    int path_price = get_path_LM(graph, plan).GetTotalPrice();
    size_t s = plan.size();
    bool *isMeet = new bool[s];
    std::vector<City_id> temp_plan{0, 1};
    for (int i = 0; i != s; ++i)
    {
      isMeet[i] = false;
      adj_matrix.emplace_back();
      for (int j = 0; j != s; ++j)
      {
        // std::cout << i << '\t' << j << std::endl;
        if (i != j && i != s - 1 && j)
        {
          temp_plan[0] = plan[i], temp_plan[1] = plan[j];
          adj_matrix[i].push_back(get_path_LM(graph, temp_plan));
        }
        else
        {
          adj_matrix[i].emplace_back();
        }
      }
    }
    for (int i = 0; i != adj_matrix.size(); ++i)
    {
      price_matrix.emplace_back();
      for (int j = 0; j != adj_matrix[i].size(); ++j)
        {
          price_matrix[i].push_back(adj_matrix[i][j].GetTotalPrice());
          if (price_matrix[i].back() && min_price > price_matrix[i].back())
            min_price = price_matrix[i].back();
        }
    }
    isMeet[0] = true;
    dfs_logic_m temp_l = {0, path_price, isMeet, 0, 1, min_price};
    path_order.push_back(0);
    temp_path.push_back(0);
    dfs(price_matrix, path_order, temp_path, temp_l);
    for (int i = 1; i != path_order.size(); ++i)
      path.Append(adj_matrix[path_order[i - 1]][path_order[i]]);
    path.FixTotalTime(graph, start_time);
    delete isMeet;
    return path;
    // return get_path_LM(graph, plan);
  }
  else if (s == LEAST_TIME)
  {
    Path path = get_path_LT(graph, plan, start_time);
    path.FixTotalTime(graph, start_time);
    int i = 0, j = 1, count = 0;
    auto sz = plan.size();
    bool *isMeet = new bool[sz];
    if (plan.size() == 2)
      return path;
    else
    {
      Path temp_path;
      std::vector<City_id> buf;
      for (i = 1; i != sz; ++i)
        isMeet[i] = false;
      std::vector<City_id> temp{0, 1};
      dfs_logic_t tl = {start_time, 0, isMeet, 0, temp};
      dfs_LT(graph, plan, path, temp_path, tl);
      delete isMeet;
    }
    return path;
  }
}

Path Traveller::get_path_LM(const CityGraph &graph, const std::vector<City_id> &plan)
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

Path Traveller::get_path_LT(const CityGraph &graph, const std::vector<City_id> &plan, Time now)
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
#endif // SRC_TRAVELLER