

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
  Path get_path(const vector<city_id> &plan, stragety s);

private:
  istream LoadCityGraph(istream, mode);         // 加载文件
  vector<Route> city[city_number][city_number]; // citynumber表示城市（节点）的数量
};
