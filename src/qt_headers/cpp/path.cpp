
#include "headers/path.h"


void Path::Remove(const CityGraph &graph)
{
  if (len_ == 1)
  {
    cities_.pop_back();
    start_city_ = 0;
    end_city_ = 0;
    len_ = 0;
    total_price_ = 0;
    total_timecost_.Reset();
  }
  if (!len_)
    return;

  else
  {
    len_--;
    end_city_ = cities_.at(len_ - 1).current_city;
    int i = cities_.at(len_).former_city;
    int j = cities_.at(len_).current_city;
    int k = cities_.at(len_).kth_way;
    total_price_ -= graph.GetRoute(i, j, k).price;
    int fi = cities_.at(len_ - 1).former_city;
    int fj = cities_.at(len_ - 1).current_city;
    int fk = cities_.at(len_ - 1).kth_way;
    Time temp = graph.GetRoute(i, j, k).end_time.time_diff(graph.GetRoute(fi, fj, fk).end_time);
    total_timecost_.minus_time(temp);
    cities_.pop_back();
  }
}

void Path::Append(const CityGraph &graph, City_id i, City_id j, int k, int back)
{ //用ijk给每一种方式编号，通过ijk获得所有数据。
  //std::cout << i << '\t' << j << '\t' << k << std::endl;
  PathNode temp = {i, j, k};
  if (!(len_++))
    end_city_ = j;
  start_city_ = i;
  if (back)
    cities_.push_back(temp);
  else
    cities_.push_front(temp);
  total_price_ += graph.GetRoute(i, j, k).price;
  // total_timecost_.add_time(graph.GetRoute(i, j, k).end_time.time_diff(graph.GetRoute(i, j, k).start_time));  // 只计算路途上的时间,不计等候时间
}

void Path::Append(const CityGraph &graph, City_id i, City_id j, int k, Time total_time)
{
  PathNode temp = {i, j, k};
  if (!(len_++))
    end_city_ = j;
  start_city_ = i;
  cities_.push_front(temp);
  total_price_ += graph.GetRoute(i, j, k).price;
  // assert(graph.GetRoute(i, j, k).end_time.time_diff(wait_time).GetDay() >= 0);
  // Time diff = graph.GetRoute(i, j, k).end_time.time_diff(wait_time);
  // if (diff.GetDay() < 0)
  //   diff.add_time(24);
  // assert(diff.GetDay() >= 0);
  // total_timecost_.add_time(diff);
  // total_timecost_ = total_time;
}

Path &Path::Append(const Path &path)
{
  len_ += path.len_;
  end_city_ = path.end_city_;
  total_price_ += path.total_price_;
  // PathNode end = cities_.back();
  // PathNode path_start = path.cities_.front();
  // Time diff = graph.GetRoute(end.former_city, end.current_city, end.kth_way).end_time.time_diff(graph.GetRoute(end.former_city, end.current_city, end.kth_way).start_time);
  // if (diff.GetDay() < 0)
  //     diff.add_time(0, 1);
  // total_timecost_.add_time(path.total_timecost_); // 只计算路途上的时间,不计等候时间
  for (const auto &node : path.cities_)
    cities_.push_back(node);
  return *this;
}

void Path::FixTotalTime(const CityGraph &graph, const Time &start_time)
{
  Time now = start_time;
  total_timecost_ = Time();
  for (const auto &node : cities_)
  {
    Time temp_now(1, now.GetHour());
    Route r = graph.GetRoute(node.former_city, node.current_city, node.kth_way);
    int wait_hour = r.start_time.hour_diff(temp_now);
    int route_hour = r.end_time.hour_diff(r.start_time);
    wait_hour += ((wait_hour < 0) ? 24 : 0);
    total_timecost_.add_time(wait_hour + route_hour);
    now.add_time(wait_hour + route_hour);
  }
}

inline void Path::Reverse()
{
  reverse(cities_.begin(), cities_.end());
  Fix();
}

inline void Path::Fix()
{
  if (len_)
  {
    start_city_ = cities_[0].former_city;
    end_city_ = cities_[cities_.size() - 1].current_city;
  }
}

void Path::Show() const
{
  for (auto path_node : cities_)
    std::cout << path_node.former_city << '\t'
              << path_node.current_city << '\t'
              << path_node.kth_way << std::endl;
}

inline int Path::GetLen() const
{
    return len_;
}

inline int Path::GetTotalPrice() const
{
    return total_price_;
}

inline const Time &Path::GetTotalTime() const
{
    return total_timecost_;
}

inline std::deque<PathNode>::const_iterator Path::cbegin() const
{
    return cities_.cbegin();
}

inline std::deque<PathNode>::const_iterator Path::cend() const
{
    return cities_.cend();
}

inline const PathNode &Path::GetNode(int k) const
{
    return cities_.at(k);
}

