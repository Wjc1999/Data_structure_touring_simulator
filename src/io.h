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

inline void Welcome();
inline void Menu(const IDMap &im);
inline void Request(const IDMap &im);
inline void Status();
inline void Mapsearch();
inline int Namecheck(string s);


inline void Welcome() //欢迎界面
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
            cout<<"请输入你想注册的账号："<<endl;
            string name;
            cin>>name;
            cout<<"你获得了一个账号！"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            break;
        }
        else if(sorl=='l'||sorl=='L')
        {
            cout<<"请输入你的id："<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            break;
        }
        else
        {
            cout<<"请重新输入：";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
}

inline void Menu(const IDMap &im) //功能菜单
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
            Request(im);
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
        else
        {
            cout<<"请重新输入：";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
}

inline void Request(const IDMap &im) //预定行程
{
    cout << "当前支持的城市有：" << endl;
    for(int i=0;i<kCityNum;i++)
    {
        cout<<i+1<<":"<<im.GetCityStr(i)<<endl;
    }
    cout << "请输入您的当前城市：" << endl;
    //read();//读取数据
    cout << "请输入您的目的城市：" << endl;
    //read();
    cout << "请输入您希望经过的城市(没有可填无)：" << endl;
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
}
#endif //SRC_IO