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