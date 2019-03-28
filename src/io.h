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

extern const int kCityNum;
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::string;
using std::vector;

void Welcome();
int Menu(const IDMap &im);
std::vector<City_id> Request(const IDMap &im);
void ErrorMsg(const std::string &err_msg);
inline void Status();
inline void Mapsearch();
inline int Namecheck(string s);

void Welcome() //欢迎界面
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
            cout<<"请输入你想注册的账号：";
            string name;
            cin>>name;
            while(Namecheck(name)==-1)
            {
                cout<<"该账号已被注册，请重新输入：";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cin>>name;
            }
            cout<<"你已注册账号："<<name<<endl;
            return;
        }
        else if (sorl == 'l' || sorl == 'L')
        {
            cout<<"请输入你的账号：";
            string name;
            cin>>name;
            while(Namecheck(name)==-1)
            {
                cout<<"输入账号有误，请重新输入：";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cin>>name;
            }
            return;
        }
        else if(sorl=='q'||sorl=='Q')
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

int Menu(const IDMap &im, Traveller &traveller) //功能菜单  返回一个操作代码
{
    cout << "输入对应数字获取功能：" << endl;
    cout << "1、预定行程" << endl;
    cout << "2、状态查询" << endl;
    cout << "3、路线查询" << endl;
    cout << "……" << endl;
    char num;
    std::vector<City_id> plan;
    while (cin >> num)
    {
        if (num == '1')
        {
            cout << "预定行程" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            plan = Request(im);
            std::for_each(plan.cbegin(), plan.cend(), [](City_id id) { cout << id << endl; });
            traveller.set_plan(plan);
            // 输入旅行策略
            return num - '0';
        }
        else if (num == '2')
        {
            cout << "状态查询" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return num - '0';
        }
        else if (num == '3')
        {
            cout << "路线查询" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return num - '0';
        }
        else if(num=='q'||num=='Q')
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

std::vector<City_id> Request(const IDMap &im) //预定行程
// TODO : 判断输入是否为数字
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

    cout << "请输入您的当前城市：" << endl;
    while (1)
    {
        if (!cin.good())
            cin.clear();
        cin >> id;
        if (cin.good())
        {
            temp_id = std::stoi(id);
            if (temp_id < im.GetCityMapSize() + 1 || temp_id < 1)
            {
                res.push_back(std::stoi(id) - 1);
                break;
            }
            else
            {
                ErrorMsg("无效的输入");
            }
        }
    }

    cout << "请输入您希望经过的城市(没有可填无)：" << endl;
    while (1)
    {
        if (!cin.good())
            cin.clear();
        cin >> id;
        if (cin.good())
        {
            if (id == "q")
            {
                if (temp_res.size())
                    break;
                else
                {
                    ErrorMsg("无有效输入");
                    continue;
                }
            }

            temp_id = std::stoi(id);
            if (temp_id > im.GetCityMapSize() || temp_id < 1)
                ErrorMsg("无效的城市");
            else if (temp_id == res.front())
                ErrorMsg("与起点重复");
            else
            {
                temp_res.push_back(temp_id - 1);
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
            temp_id = std::stoi(id);
            if (std::find(res.begin(), res.end(), temp_id) != res.end())
            {
                ErrorMsg("重复的城市");
            }
            else if (temp_id > im.GetCityMapSize() || temp_id < 1)
                ErrorMsg("无效的城市");
            else
            {
                res.push_back(temp_id - 1);
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

void ErrorMsg(const std::string &err_msg)
{
    std::cout << err_msg << std::endl;
}

inline void Mapsearch()
{
    //citygraph.()//关于图的输出
}

inline int Namecheck(string s)
{
    vector<string> namelist;
    std::ifstream stream(namepath);
    if (stream.is_open())
    {
        int cnt = 0;
        string temp;
        while (getline(stream, temp))
        {
            if (temp == s)
            {
                return cnt;
            }
            cnt++;
        }
        return -1;
    }
    return -1;
}
#endif //SRC_IO