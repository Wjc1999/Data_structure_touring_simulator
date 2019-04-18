#ifndef SRC_IO
#define SRC_IO

#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <exception>

#include "traveller.h"
#include "id_map.h"
#include "user_type.h"
#include "path.h"

#if defined(_WIN32) || (defined(__CYGWIN__) && !defined(_WIN32)) || defined(__MINGW32__) || defined(__MINGW64__)
#include <windows.h>
#endif // _WIN32

extern const std::string name_path;
extern const int kCityNum;

//欢迎界面
int Welcome(Traveller &t);

//功能菜单,返回一个操作代码
int Menu(const IDMap &im, Traveller &traveller);

//预定行程
std::vector<City_id> Request(const IDMap &im);

// 打印错误信息
void ErrorMsg(const std::string &err_msg);

// 打印账户列表
bool PrintNameList();

void Status();

// 根据所提供的traveller添加账号
inline bool AddAccount(const Traveller &traveller);
// 根据用户名添加账号
inline bool AddAccount(const std::string &account_name);

void MapSearch();

// 返回账户名称所在的行数,若账户名称不存在则返回-1
int AccountCheck(const std::string &id);

// 提供界面供用户选择是否采用该路线
bool PathConfirm();

// 给出界面让用户选择策略
Strategy InputStrategy(Time &init_time, Time &limit_time);

// 打印用户的信息
void PrintTravellerInfo(const CityGraph &graph, const IDMap &id_map, const Time &now, const Traveller &traveller);

// 打印界面友好的路径
std::ostream &PrintPath(const CityGraph &graph, const IDMap &id_map, const Path &path, std::ostream &os = std::cout);
std::ostream &PrintPath(const CityGraph &graph, const IDMap &id_map, const Path &path, const int index, bool showtotal = false, std::ostream &os = std::cout);

// 改变模拟的速度
double getSimulateSpeed();

// 提供设置选项菜单
eSettings SettingsMenu();

// 设置控制台字体大小
bool SetConsoleFontSize();

// 验证账户名称是否合法
inline bool IsValidName(const std::string &name_str);

// 返回给定字符串中第一个数字,如果没有数字,则返回一个不是数字的字符
char FindFirstDigit(const std::string &op_str);

// 返回给定字符串中第一个字母,如果没有字母,则返回一个不是字母的字符
char FindFirstAlpha(const std::string &op_str);

inline void ClearScreen();

// 输出两个城市的所有路线
void PrintRoutes(const CityGraph &graph, const IDMap &id_map);

// 获得时间
Time InputLimitTime();
Time InputInitTime();

// 判断所给城市是否处于旅行计划中
bool IsInplan(const std::vector<City_id> &plan, City_id city);

//预定行程
//
//
//
//
// TODO: 判断输入是否为数字

// 打印错误信息
// TODO : 同时输出至日志

#endif //SRC_IO
