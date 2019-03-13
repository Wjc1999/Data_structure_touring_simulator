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