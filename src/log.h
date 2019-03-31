#ifndef SRC_LOG
#define SRC_LOG
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include <map>
#include <chrono>
#include <ctime> // 用于获取实际时间
#include <cctype>
/* class Log
 * 用于建立日志文件,对程序的操作进行记录.
 * 日志文件格式: [系统时间] ([程序内系统时间]) [日志信息]
 */

static const std::string log_doc("../data/"); // log文件的文件目录
static const std::string log_ext(".log");

enum WriteTplt
{
  USER_INPUT,
  ERROR,
  // 待补充
};
static const std::string kTemplateString[] =
    {
        "用户输入了" //  USER_INPUT 后接输入的内容
        "发生错误"   //  ERROR 后接具体错误
                     //待补充
};

// 去除字符串内所有非数字字符, 返回一个去除之后的字符串
static std::string RemoveAllPunct(const std::string &time_str);

class Log
{
public:
  Log(); // 根据给定的文件路径打开日志文件

  //  向日志文件中写入log_str
  void WriteLog(const std::string &log_str);

  // 根据给定的模式串以及补充信息向日志文件中添加日志
  void WriteLog(WriteTplt tplt_str, const std::string &supply_str);

  const std::string &get_log_path() const { return log_path_; }

private:
  std::ofstream log_stream_; // 供写入的日志文件流
  std::string log_path_;
  std::string GetCurrentTimestamp() const;
  std::string GetCurrentTime() const;
};

Log::Log()
{
  log_path_ = log_doc + GetCurrentTimestamp() + log_ext;
  log_stream_.open(log_path_);
  if (!log_stream_)
    throw "日志文件创建失败";
}

void Log::WriteLog(const std::string &log_str)
{
  log_stream_ << GetCurrentTime() << "  " << log_str << std::endl;
}

static std::string RemoveAllPunct(const std::string &time_str)
{
  std::string res;
  for (auto c : time_str)
    if (isdigit(c))
      res += c;
  return res;
}

std::string Log::GetCurrentTimestamp() const
{
  auto current_time = std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now());
  std::string timestamp = std::ctime(&current_time);
  std::stringstream ss(timestamp);

  std::string month_str, day_str, time_str, year_str;
  std::string res;

  ss >> month_str >> month_str;
  ss >> day_str;
  ss >> time_str;
  ss >> year_str;
  time_str = RemoveAllPunct(time_str);

  res = year_str + month_str + day_str + "_" + time_str;
  return res;
}

std::string Log::GetCurrentTime() const
{
  auto current_time = std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now());
  std::string timestamp = std::ctime(&current_time);
  std::stringstream ss(timestamp);

  std::string month_str, day_str, time_str, year_str;
  std::string res;

  ss >> month_str >> month_str;
  ss >> day_str;
  ss >> time_str;
  ss >> year_str;

  return time_str;
}

#endif // SRC_LOG