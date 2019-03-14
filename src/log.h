#ifndef SRC_LOG
#define SRC_LOG
#include <string>
#include <iostream>
#include <ctime> // 用于获取实际时间
/* class Log
 * 用于建立日志文件,对程序的操作进行记录.
 * 日志文件格式: [系统时间] ([程序内系统时间]) [日志信息]
 */
static enum WriteTplt
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
class Log
{
public:
  Log() = default; // 根据给定的文件路径打开日志文件
  ~Log();          // 关闭日志文件
  /*  向日志文件中写入log_str
     */
  void write(const std::string &log_str);
  /* 根据给定的模式串以及补充信息向日志文件中添加日志
     */
  void write(WriteTplt tplt_str, const std::string &supply_str);

private:
  std::ostream log_file_;                // 供写入的日志文件流
  const std::string log_file_path_ = ""; // log文件的文件名
};

#endif // SRC_LOG