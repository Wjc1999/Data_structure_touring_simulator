#ifndef SRC_TRAVELLER
#define SRC_TRAVELLER
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdint>

#include "user_type.h"
#include "path.h"
#include "time_format.h"
#include "city_graph.h"

const int kMaxInt = INT32_MAX; // 0x7fffffff
class Traveller                // 旅行者
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
  Path get_path_LM(const CityGraph &graph, const std::vector<City_id> &plan);
  Path get_path_LT(const CityGraph &graph, const std::vector<City_id> &plan, Time now);
};

static void dfs(Path &path, const CityGraph &graph, const std::vector<std::vector<Path>> &adj_matrix, std::vector<Path> &paths, bool *isMeet, int current, int depth)
{
  if (current == adj_matrix.size() - 1)
  {
    if (depth == adj_matrix.size())
      paths.push_back(path);
    else
      return;
  }

  for (int i = 0; i != adj_matrix.size(); ++i)
  {

    if (i == current)
      continue;
    if (!isMeet[i] && adj_matrix[current][i].GetLen())
    {
      isMeet[i] = true;
      Path save = path;
      path.Append(adj_matrix[current][i]);
      dfs(path, graph, adj_matrix, paths, isMeet, i, depth + 1);
      isMeet[i] = false;
      path = save;
    }
  }
}

Path Traveller::get_path(const CityGraph &graph, const std::vector<City_id> &plan, Strategy s, Time t)
{

  if (plan.size() < 2)
    throw plan.size();
  if (s == LEAST_MONEY)
  {
    Path temp;
    std::vector<std::vector<Path>> adj_matrix;
    std::vector<Path> paths;
    size_t s = plan.size();
    bool *isMeet = new bool[s];
    for (int i = 0; i != s; ++i)
    {
      isMeet[i] = false;
      adj_matrix.emplace_back();
      for (int j = 0; j != s; ++j)
      {
        // std::cout << i << '\t' << j << std::endl;
        if (i != j && i != s - 1)
        {
          std::vector<City_id> temp_plan{plan[i], plan[j]};
          adj_matrix[i].push_back(get_path_LM(graph, temp_plan));
        }
        else
        {
          adj_matrix[i].emplace_back();
        }
      }
    }
    isMeet[0] = true;
    dfs(temp, graph, adj_matrix, paths, isMeet, 0, 1);
    temp = paths.front();
    for (auto &path : paths)
    {
      if (temp.GetTotalPrice() > path.GetTotalPrice())
        temp = path;
    }
    delete isMeet;
    return temp;
    // return get_path_LM(graph, plan);
  }
  else // if (s == LEAST_TIME)
    return get_path_LT(graph, plan, t);
}

Path Traveller::get_path_LM(const CityGraph &graph, const std::vector<City_id> &plan)
{
  City_id destination; // 终点
  City_id origin;      // 起点
  Path path;
  // std::cout << plan[0] << plan[1] << std::endl;
  for (int cnt = plan.size() - 1; cnt > 0; cnt--)
  {
    destination = plan[cnt];
    origin = plan[cnt - 1];
    int cost[kCityNum];      // 记录最小花费
    int preway[kCityNum][2]; // preway[cityA][] = {CityB, transport_index_from_CityB_to_CityA}
    bool is_count[kCityNum] = {false};
    std::vector<int>
        find_min_cost;

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
  for (int cnt = plan.size() - 1; cnt > 0; cnt--)
  {
    destination = plan[cnt];
    origin = plan[cnt - 1];
    int cost[kCityNum];      // 记录最小花费
    int preway[kCityNum][2]; // preway[cityA][] = {CityB, transport_index_from_CityB_to_CityA}
    bool is_count[kCityNum];
    std::vector<int> find_min_cost;

    for (int j = 0; j < kCityNum; j++) //对数据进行初始化
    {
      if (j == origin)
        continue;
      for (int k = 0; k < graph.Getsize(origin, j); k++) // 将所有从origin到j的价格push到find_min_cost中
      {                                                  //*****和LM的区别*****
        Route route = graph.GetRoute(origin, j, k);
        find_min_cost.push_back(now.hour_diff(route.start_time) + route.start_time.hour_diff(route.end_time));
      }

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
      //*****和LM的区别*****
      now = graph.GetRoute(preway[city_temp][0], city_temp, preway[city_temp][1]).end_time;

      for (int j = 0; j < kCityNum; j++) //更新
      {
        if (is_count[j])
          continue;
        for (int k = 0; k < graph.Getsize(city_temp, j); k++)
        { //*****和LM的区别*****
          Route route = graph.GetRoute(origin, j, k);
          find_min_cost.push_back(now.hour_diff(route.start_time) + route.start_time.hour_diff(route.end_time));
        }

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
#endif // SRC_TRAVELLER