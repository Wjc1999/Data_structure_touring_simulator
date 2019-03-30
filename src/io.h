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

#include "traveller.h"
#include "id_map.h"
#include "user_type.h"
#include "path.h"

extern const std::string name_path;
extern const int kCityNum;
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::string;
using std::vector;

//欢迎界面
int Welcome();

//功能菜单,返回一个操作代码
int Menu(const IDMap &im, Traveller &traveller);

//预定行程
std::vector<City_id> Request(const IDMap &im);

// 打印错误信息
void ErrorMsg(const std::string &err_msg);

// 打印账户列表
bool ShowNameList();

void Status();

// 根据所提供的traveller添加账号
inline bool AddAccount(const Traveller &traveller) { return traveller.SaveData(); }
// 根据用户名添加账号
bool AddAccount(const std::string &account_name)
{
    std::ofstream fos(name_path, std::ofstream::app);
    if (fos)
    {
        fos << account_name << std::endl;
        return true;
    }
    else
        return false;
}

void MapSearch();

// 返回账户名称所在的行数,若账户名称不存在则返回-1
int AccountCheck(const string &id);

// 提供界面供用户选择是否采用该路线
bool PathConfirm();

// 给出界面让用户选择策略
Strategy InputStrategy();

// 打印用户的信息
void PrintTravellerInfo(const CityGraph &graph, const IDMap &id_map, const Time &now, const Traveller &traveller);

// 打印界面友好的路径
std::ostream &PrintPath(const CityGraph &graph, const IDMap &id_map, const Path &path, std::ostream &os = std::cout);
std::ostream &PrintPath(const CityGraph &graph, const IDMap &id_map, const Path &path, const int index, std::ostream &os = std::cout);

int Welcome()
{
    cout << "|----------------------------------------------|" << endl;
    cout << endl;
    cout << "|                                              |" << endl;
    cout << endl;
    cout << "|                   Welcome!                   |" << endl;
    cout << endl;
    cout << "|                                              |" << endl;
    cout << endl;
    cout << "|----------------------------------------------|" << endl;
    cout << endl;
    cout << "选择注册还是已有账号登陆？" << endl;
    cout << "注册：S           登陆：L" << endl;
    char sorl;
    while (1)
    {
        cin >> sorl;
        if (sorl == 'S' || sorl == 's')
        {
            cout << "请输入你想注册的账号：";
            string accout_name;
            cin >> accout_name;
            while (AccountCheck(accout_name) != -1)
            {
                cout << "该账号已被注册，请重新输入：";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> accout_name;
            }
            AddAccount(accout_name);
            cout << "你已注册账号：" << accout_name << endl;
            return -1;
        }
        else if (sorl == 'l' || sorl == 'L')
        {
            cout << "请输入你的账号：";
            string accout_name;
            cin >> accout_name;
            while (AccountCheck(accout_name) == -1)
            {
                cout << "输入账号有误，请重新输入：";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> accout_name;
            }
            return AccountCheck(accout_name);
        }
        else if (sorl == 'q' || sorl == 'Q')
        {
            exit(0);
        }
        else
        {
            cout << "请重新输入：";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

//功能菜单,返回一个操作代码
int Menu(const IDMap &im, Traveller &traveller)
{
    cout << "输入对应数字获取功能：" << endl
         << "1、预定行程" << endl
         << "2、状态查询" << endl
         << "3、路线查询" << endl
         << "4、退出程序" << endl;

    char num;
    std::vector<City_id> plan;
    while (cin >> num)
    {
        int operate_code = num - '0';
        if (operate_code == SCHEDULE)
        {
            cout << "预定行程" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // std::for_each(plan.cbegin(), plan.cend(), [](City_id id) { cout << id << endl; });

            // TODO : 输入旅行策略
            return operate_code;
        }
        else if (operate_code == INQUIRE_STATE)
        {
            cout << "状态查询" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return operate_code;
        }
        else if (operate_code == INQUIRE_PATH)
        {
            cout << "路线查询" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return operate_code;
        }
        else if (operate_code == EXIT)
        {
            return operate_code;
        }
        else
        {
            cout << "请重新输入：";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

//预定行程
// TODO : 判断输入是否为数字
std::vector<City_id> Request(const IDMap &im)
{
    std::vector<City_id> temp_res;
    std::vector<City_id> res;
    std::string id;
    City_id temp_id;

    cout << "当前支持的城市有：" << endl;
    for (int i = 0; i < im.GetCityMapSize(); i++)
    {
        cout << i + 1 << " : " << im.GetCityStr(i) << endl;
    }

    cout << "请输入您的当前城市(输入数字)：";
    while (1)
    {
        if (!cin.good())
            cin.clear();
        cin >> id;
        if (cin.good())
        {
            temp_id = std::stoi(id) - 1;
            if (temp_id < im.GetCityMapSize() && temp_id >= 0)
            {
                cout << "你选择的当前城市是：" << im.GetCityStr(temp_id) << endl;
                res.push_back(temp_id);
                break;
            }
            else
            {
                ErrorMsg("无效的输入");
            }
        }
    }

    cout << "请输入您希望经过的城市(没有可填无)：";
    while (1)
    {
        if (!cin.good())
            cin.clear();
        cin >> id;
        if (cin.good())
        {
            if (id == "q")
            {
                break;
            }

            temp_id = std::stoi(id) - 1;
            if (temp_id >= im.GetCityMapSize() || temp_id < 0)
                ErrorMsg("无效的城市");
            else if (temp_id == res.front())
                ErrorMsg("与起点重复");
            else
            {
                temp_res.push_back(temp_id);
            }
        }
    }
    std::sort(temp_res.begin(), temp_res.end());
    auto unique_end = unique(temp_res.begin(), temp_res.end());
    std::copy(temp_res.begin(), unique_end, std::back_inserter(res));

    cout << "请输入您的目的城市：" << endl;
    while (1)
    {
        if (!cin.good())
            cin.clear();
        cin >> id;
        if (cin.good())
        {
            temp_id = std::stoi(id) - 1;
            if (std::find(res.begin(), res.end(), temp_id) != res.end())
            {
                ErrorMsg("重复的城市");
            }
            else if (temp_id >= im.GetCityMapSize() || temp_id < 0)
                ErrorMsg("无效的城市");
            else
            {
                cout << "你选择的目的城市是：" << im.GetCityStr(temp_id) << endl;
                res.push_back(temp_id);
                break;
            }
        }
    }
    return res;
}

inline void Status()
{
    //traveller.();//关于traveller的输出
}

// 打印错误信息
// TODO : 同时输出至日志
void ErrorMsg(const string &err_msg)
{
    cout << err_msg << endl;
}

inline void MapSearch()
{
    //citygraph.()//关于图的输出
}

// 返回账户名称所在的行数,若账户名称不存在则返回-1
inline int AccountCheck(const string &id)
{
    std::vector<string> namelist; // unused parameter
    std::ifstream in_stream(name_path);
    if (in_stream.is_open())
    {
        int cnt = 0;
        string temp;
        while (getline(in_stream, temp))
        {
            if (temp == id)
            {
                return cnt;
            }
            cnt++;
        }
    }
    return -1;
}

// 打印账户列表
inline bool ShowNameList()
{
    std::string line_buf;
    std::ifstream fis(name_path);
    if (fis)
    {
        while (std::getline(fis, line_buf))
            std::cout << line_buf << std::endl;
        return true;
    }
    else
        return false;
}

inline bool PathConfirm()
{
    char option;
    std::cout << "是否选择该条路线?[Y/N]" << std::endl;
    /*if(now,init_time_)
  {
    state_ = OFF
  }  ***这里做一个当前时间和出发时间的判断*/
    while (1)
    {
        std::cin >> option;
        if (option == 'Y')
            return true;
        else if (option == 'N')
            return false;
        else
        {
            ErrorMsg("无效的输入");
        }
    }
}

inline Strategy InputStrategy()
{
    int strategy;
    std::cout << "输入旅行策略" << std::endl
              << "1. 最少金钱" << std::endl
              << "2. 最少时间" << std::endl
              << "3. 限定时间内最少金钱" << std::endl;
    while (1)
    {
        std::cin >> strategy;
        switch (strategy - 1)
        {
        case 0:
            return LEAST_MONEY;
        case 1:
            return LEAST_TIME;
        case 2:
            return LIMIT_TIME;
        default:
            ErrorMsg("无效的输入");
            break;
        }
    }
}

std::ostream &PrintPath(const CityGraph &graph, const IDMap &id_map, const Path &path, std::ostream &os)
{
    return PrintPath(graph, id_map, path, path.GetLen());
}

std::ostream &PrintPath(const CityGraph &graph, const IDMap &id_map, const Path &path, const int index, std::ostream &os)
{
    std::cout << "为你定制的路线为：" << std::endl;
    std::cout << "始发地" << '\t'
              << "目的地" << '\t'
              << "方式" << '\t'
              << "出发时间" << '\t'
              << "到达时间" << '\t'
              << "价格" << '\t'
              << "完成" << '\t' << std::endl;
    for (int path_node = 0; path_node < index; path_node++)
    {
        int i = path.GetNode(path_node).former_city;
        int j = path.GetNode(path_node).current_city;
        int k = path.GetNode(path_node).kth_way;
        Route route = graph.GetRoute(i, j, k);
        std::cout << id_map.GetCityStr(i) << '\t'
                  << id_map.GetCityStr(j) << '\t'
                  << id_map.GetTransStr(route.transport_type) << '\t';
        RouteShow(route.start_time, route.end_time);
        std::cout << route.price << '\t'
                  << "O" << '\t' << std::endl;
    }

    for (int path_node = index; path_node < path.GetLen(); path_node++)
    {
        int i = path.GetNode(path_node).former_city;
        int j = path.GetNode(path_node).current_city;
        int k = path.GetNode(path_node).kth_way;
        Route route = graph.GetRoute(i, j, k);
        std::cout << id_map.GetCityStr(i) << '\t'
                  << id_map.GetCityStr(j) << '\t'
                  << id_map.GetTransStr(route.transport_type) << '\t';
        RouteShow(route.start_time, route.end_time);
        std::cout << route.price << '\t'
                  << "X" << '\t' << std::endl;
    }
    return os;
}

void PrintTravellerInfo(const CityGraph &graph, const IDMap &id_map, const Time &now, const Traveller &traveller)
{
    auto plan = traveller.get_plan();
    auto path = traveller.get_path();
    auto position = traveller.get_position();

    std::cout << traveller.get_ID() << std::endl;
    if (traveller.get_state() == STAY)
    {
        if (position == -2)
            std::cout << "当前无出行计划" << std::endl;
        else if (position == -1)
        {
            std::cout << std::endl;
            std::cout << "你的始发地是：" << id_map.GetCityStr(plan.front()) << std::endl;
            std::cout << "你的目的地是：" << id_map.GetCityStr(plan.back()) << std::endl;

            if (plan.size() > 2)
            {
                std::cout << "你的途经城市有：";
                for (int i = 1; i < plan.size() - 1; i++)
                {
                    std::cout << id_map.GetCityStr(plan.at(i)) << " ";
                }
                std::cout << std::endl;
            }
            PrintPath(graph, id_map, path, 1);
        }
        else
        {
            PrintPath(graph, id_map, path, position);
            std::cout << "当前在：" << id_map.GetCityStr(path.GetNode(position).former_city) << std::endl;
            std::cout << "离出发还有：" << traveller.get_left_hour() << "h" << std::endl;
        }
    }
    else
    {
        PrintPath(graph, id_map, path, position);
        std::cout << "距目的地" << id_map.GetCityStr(path.GetNode(position).current_city) << "还有：" << traveller.get_left_hour() << "h" << std::endl;
    }
}


#endif //SRC_IO