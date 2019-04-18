#include "headers/log.h"

const std::string &Log::get_log_path() const
{
    return log_path_;
}

Log::Log()
{
  log_path_ = log_doc + GetCurrentTimestamp() + log_ext;
  log_stream_.open(log_path_);
  if (!log_stream_)
    throw "日志文件创建失败";
}

inline bool Log::WriteLog(const std::string &log_str)
{
  if (log_stream_)
  {
    log_stream_ << GetCurrentTime() << "  " << log_str << std::endl;
    return true;
  }
  else
  {
    return false;
  }
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
