#ifndef SRC_IO
#define SRC_IO
#include <iostream>
using namespace std;
inline void Welcome() //欢迎界面
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
}

inline void Menu() //功能菜单
{
    cout << "输入对应数字获取功能：" << endl;
    cout << "1、预定行程" << endl;
    cout << "2、状态查询" << endl;
    cout << "3、路线查询" << endl;
    cout << "……" << endl;
    cout << "" << endl;
}

inline void Request() //预定行程
{
    cout << "当前支持的城市有：" << endl;
    //printcity();//打印城市列表
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
#endif //SRC_IO