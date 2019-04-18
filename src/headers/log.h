#ifndef SRC_LOG_H
#define SRC_LOG_H

#include <string>
#include <iostream>
#include <fstream>

enum ErrorCode
{
    /*待补充*/
};

/* class Log
 * 用于建立日志文件,对程序的操作进行记录.
 * 日志文件格式: [系统时间] ([程序内系统时间]) [日志信息]
 */
class Log
{
public:
  Log(); // 根据给定的文件路径打开日志文件
  ~Log(); // 程序结束时记录程序的运行状况

  // 提供错误行为的日志
  bool ErrorLog(ErrorCode err_code);

  // 记录用户操作
  bool OperationLog(/*待补充*/);

  // 记录各部件加载情况
  bool LoadingSuccessLog(/*待补充*/);

  // 记录程序的运行结果
  bool ResultLog(/*待补充*/);

  //  for debug
  const std::string &get_log_path() const { return log_path_; }

private:
  std::ofstream log_stream_; // 供写入的日志文件流
  std::string log_path_;
  std::string GetCurrentTimestamp() const;
  std::string GetCurrentTime() const;

  //  向日志文件中写入log_str
  bool WriteLog(const std::string &log_str);
};

#endif // SRC_LOG_H
