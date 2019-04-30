#ifndef SRC_LOG_CC
#define SRC_LOG_CC

#pragma execution_character_set("utf-8")

#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include <map>
#include <chrono>
#include <ctime> // 用于获取实际时间
#include <cctype>

#include "log.h"

static bool InitLog();
static std::string GetCurrentTimestamp();
static std::string GetCurrentTime();

static bool is_inited = false;
static std::ofstream log_stream; // 供写入的日志文件流
static std::string log_path;
static const std::string log_doc("../data/"); // log文件的文件目录
static const std::string log_ext(".log");

// 去除字符串内所有非数字字符, 返回一个去除之后的字符串
static std::string RemoveAllPunct(const std::string &time_str)
{
  std::string res;
  for (auto c : time_str)
    if (isdigit(c))
      res += c;
  return res;
}

std::string GetCurrentTimestamp()
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

std::string GetCurrentTime()
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


bool InitLog()
{
  log_path = log_doc + GetCurrentTimestamp() + log_ext;
  log_stream.open(log_path);
  return log_stream.is_open();
}

bool Log::LogWrite(const std::string &log_str)
{
  if (!is_inited)
  {
    bool is_init_success = InitLog();
	if (is_init_success)
		is_inited = true;
  }
  if (log_stream)
  {
    log_stream << GetCurrentTime() << "  " << log_str << std::endl;
    return true;
  }
  else
  {
    return false;
  }
};

const std::string &Log::get_log_path()
{
  return log_path;
}

bool Log::CloseLog()
{
  log_stream.close();
  return !log_stream.is_open();
}

#endif // SRC_LOG_CC