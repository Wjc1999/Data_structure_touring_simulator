#include "../src/traveller.h"
#include "../src/io.h"
#include "../src/path.h"
#include<vector>

int main()
{
    CityGraph graph;
    IDMap idmap;
    Traveller t("test");
    std::vector<int> plan;
    plan.push_back(30);
    plan.push_back(27);
    plan.push_back(16);
    Time ti;
    Path a = t.GetPath(graph, plan, LEAST_MONEY, ti);
    t.set_path(a);
    t.ShowPath();
    if (t.SaveData())
        std::cout << "success!" << std::endl;
    else
        std::cout << "干!" << std::endl;
    /*Traveller t("test2");
    std::vector<int> plan;
    plan.push_back(30);
    plan.push_back(18);
    plan.push_back(14);
    Time ti;
    Path a = t.GetPath(graph, plan, LEAST_TIME, ti);
    t.set_path(a);
    t.ShowPath();
    if (t.SaveData())
        std::cout << "success!" << std::endl;
    else
        std::cout << "干!" << std::endl;*/
    /*Traveller t("test");
    if(t.LoadData(1,graph))
    {
        std::cout<<"success!"<<std::endl;
        t.ShowPath();
    }
    else std::cout<<"干!"<<std::endl;*/
    return 0;
}