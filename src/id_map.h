enum mode
{
  //代表是城市
  CITY,
  //代表是火车
  TRAIN
};
class IDMap
{
  public:
    /*给序号获得城市名
    */
    string get_citystr(int city_id);
    /*给序号获得火车座位等级名
    */
    string get_trainstr(int train_id);
  private:
    istream LoadCityID(istream file, mode m);  // 加载城市与序号的对应文件
    istream LoadTrainID(istream file, mode m); // 加载火车等级与序号的对应文件
    map <city_id, city_str> city_map;
    map <train_id, trian_str> train_map;
}；