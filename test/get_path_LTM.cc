#ifndef TEST_GET_PATH
#define TEST_GET_PATH
#define TEST_TIME

#include <iostream>

#include "../src/traveller.h"
#include "../src/city_graph.h"
#include "../src/id_map.h"

int call_counter_time = 0;
int call_counter_money = 0;
int depth_counter = 0;

using namespace std;
int main()
{
    CityGraph graph;
    IDMap idmap;
    Traveller t("test");
    std::vector<int> plan;
    plan.push_back(12);
    plan.push_back(4);
    plan.push_back(23);
    plan.push_back(14);
    plan.push_back(8);
    plan.push_back(29);
    plan.push_back(1);
    plan.push_back(16);
    plan.push_back(22);
    plan.push_back(3);
    plan.push_back(0);
    plan.push_back(2);
    // plan.push_back(5);
    // plan.push_back(6);
    // plan.push_back(13);
    // plan.push_back(27);
    Time now(1, 7);
    Time limit(5, 23);
    Path path = t.GetPath(graph, plan, LIMIT_TIME, now, limit);
    path.Show();
    cout << path.GetTotalPrice() << '\t' << endl;
    path.GetTotalTime().print() << endl;
    return 0;
}
#endif // TEST_GET_PATH