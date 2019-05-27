#ifndef SRC_LOG_H
#define SRC_LOG_H

#pragma execution_character_set("utf-8")

#include <string>
#include <iostream>
#include <fstream>

/* namespace Log
 * 用于建立日志文件,对程序的操作进行记录.
 * 日志文件格式: [系统时间] ([程序内系统时间]) [日志信息]
 */
namespace Log
{
bool LogWrite(const std::string &log_str);

const std::string &get_log_path();

bool CloseLog();
}; // namespace Log

#endif // SRC_LOG_H
