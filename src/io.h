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

#include "id_map.h"
#include "user_type.h"
#include "traveller.h"

extern const std::string name_path;
extern const int kCityNum;
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::string;
using std::vector;

int Welcome();
int Menu(const IDMap &im);
std::vector<City_id> Request(const IDMap &im);
void ErrorMsg(const std::string &err_msg);
inline void Status();
inline void MapSearch();
inline int NameCheck(const string &id);
inline bool PathConfirm(const Path &chosen_path, Time now);

//欢迎界面
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
            string name;
            cin >> name;
            while (NameCheck(name) == -1)
            {
                cout << "该账号已被注册，请重新输入：";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> name;
            }
            cout << "你已注册账号：" << name << endl;
            return -1;
        }
        else if (sorl == 'l' || sorl == 'L')
        {
            cout << "请输入你的账号：";
            string name;
            cin >> name;
            while (NameCheck(name) == -1)
            {
                cout << "输入账号有误，请重新输入：";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> name;
            }
            return NameCheck(name);
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
            plan = Request(im);
            // std::for_each(plan.cbegin(), plan.cend(), [](City_id id) { cout << id << endl; });
            traveller.set_plan(plan);
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
        else if (operate_code ==  INQUIRE_PATH)
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

// 返回id所在的行数,若id不存在则返回-1
inline int NameCheck(const string &id)
{
    std::vector<string> namelist;   // unused parameter
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

inline bool PathConfirm(const Path &chosen_path, Time now)
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

#endif //SRC_IO