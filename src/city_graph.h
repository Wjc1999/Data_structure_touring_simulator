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
