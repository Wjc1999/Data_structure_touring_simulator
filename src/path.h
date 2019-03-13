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