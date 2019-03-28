#include "../src/traveller.h"
#include<vector>
int main()
{
    CityGraph graph;
    IDMap idmap;
    Traveller t("test");
    std::vector <int> plan;
    plan.push_back(30);
    plan.push_back(27);
    plan.push_back(16);
    Time ti;
    t.Confirm(t.GetPath(graph,plan,LEAST_MONEY),ti);
    t.ShowPath();
    if(t.Savedata())std::cout<<"success!"<<std::endl;
    else std::cout<<"干!"<<std::endl;
    /*Traveller t("test");
    if(t.Loaddata(0,graph))
    {
        std::cout<<"success!"<<std::endl;
        t.ShowPath();
    }
    else std::cout<<"干!"<<std::endl;*/
    return 0;
}