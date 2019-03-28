#ifndef SRC_IO
#define SRC_IO
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <fstream>
#include "id_map.h"
#include "traveller.h"

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::string;
using std::vector;

const int kCityNum = 31;

inline int Welcome();
inline void Menu(const IDMap &im);
inline void Request(const IDMap &im, Traveller &t);
inline void Status();
inline void Mapsearch();
inline int Namecheck(string s);


inline int Welcome() //欢迎界面
{
    cout<<"|----------------------------------------------|"<<endl;
    cout<<endl;
    cout<<"|                                              |"<<endl;
    cout<<endl;
    cout<<"|                   Welcome!                   |"<<endl;
    cout<<endl;
    cout<<"|                                              |"<<endl;
    cout<<endl;
    cout<<"|----------------------------------------------|"<<endl;
    cout<<endl;
    cout<<"选择注册还是已有账号登陆？"<<endl;
    cout<<"注册：S           登陆：L"<<endl;
    char sorl;
    while(1)
    {
        cin>>sorl;
        if(sorl=='S'||sorl=='s')
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
            return -1;
        }
        else if(sorl=='l'||sorl=='L')
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
            return Namecheck(name);
        }
        else if(sorl=='q'||sorl=='Q')
        {
            exit(0);
        }
        else
        {
            cout<<"请重新输入：";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
}

inline void Menu(const IDMap &im, Traveller &t) //功能菜单
{
    cout << "输入对应数字获取功能：" << endl;
    cout << "1、预定行程" << endl;
    cout << "2、状态查询" << endl;
    cout << "3、路线查询" << endl;
    cout << "……" << endl;
    char num;
    while(1)
    {
        cin>>num;
        if(num=='1')
        {
            cout<<"预定行程"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            Request(im,t);
            break;
        }
        else if(num=='2')
        {
            cout<<"状态查询"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            break;
        }
        else if(num=='3')
        {
            cout<<"路线查询"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            break;
        }
        else if(num=='q'||num=='Q')
        {
            exit(0);
        }
        else
        {
            cout<<"请重新输入：";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
}

inline void Request(const IDMap &im, Traveller &t) //预定行程
{
    cout << "当前支持的城市有：" << endl;
    for(int i=0;i<kCityNum;i++)
    {
        cout<<i<<":"<<im.GetCityStr(i)<<endl;
    }
    cout <<"请输入您的当前城市：(输入数字)";
    int city;
    vector <int> p;
    while(1)
    {
        cin>>city;
        if(city>=0&&city<kCityNum)
        {
            cout<<"你选择的当前城市是："<<im.GetCityStr(city)<<endl;
            p.push_back(city);
            break;
        }
        else if(city==-1)
        {
            exit(0);
        }
        else
        {
            cout<<"输入有误，请重新输入：";
        }
        
    }
    cout << "请输入您希望经过的城市(填一串数字，-1结束)：" << endl;
    while(1)
    {
        cin>>city;
        if(city>=0&&city<kCityNum)
        {
            cout<<im.GetCityStr(city)<<" "<<"以加入计划"<<endl;
            t.Plan_Add(city);
        }
        else if(city<0)
        {
            cout<<"途径城市输入完毕"<<endl;
            break;
        }
        else
        {
            cout<<city<<" "<<"输入有误！"<<endl;
        }
    }
    cout <<"请输入您的目的城市：";
    while(1)
    {
        cin>>city;
        if(city>=0&&city<kCityNum)
        {
            cout<<"你选择的目的城市是："<<im.GetCityStr(city)<<endl;
            t.Plan_Add(city);
        }
        else if(city==-1)
        {
            exit(0);
        }
        else
        {
            cout<<"输入有误，请重新输入：";
        }
    }
    cout<<"请输入你的策略：(M代表最少钱，T代表最少时间，L代表限制时间内最少钱)";
    char s;
    while(1)
    {
        cin>>s;
        if(s=='M'||s=='m')
        {
            t.GetPath(graph,)
        }
        else if(s=='T'||s=='t')
        {
            
        }
        else if(s=='L'||s=='l')
        {

        }
        else if(s=='q'||s=='Q')
        {
            exit(0);//
        }
        else
        {
            cout<<"请重新输入：";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
    //read();
}

inline void Status()
{
    //traveller.();//关于traveller的输出
}

inline void Mapsearch()
{
    //citygraph.()//关于图的输出
}

inline int Namecheck(string s)
{
    vector <string> namelist;
    std::ifstream stream(namepath);
    if(stream.is_open())
    {
        int cnt=0;
        string temp;
        while(getline(stream,temp))
        {
            if(temp==s)
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