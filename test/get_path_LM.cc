
#ifndef TEST_GET_PATH
#define TEST_GET_PATH
#define TEST_TIME
#include "../src/traveller.h"
using namespace std;
int main(){
    CityGraph graph;
    Traveller me;
    vector <City_id> plan;
    plan.push_back(12);
    plan.push_back(1);
    plan.push_back(8);
    plan.push_back(23);
    plan.push_back(22);
    plan.push_back(16);
    plan.push_back(29);
    plan.push_back(14);
    plan.push_back(4);
    plan.push_back(2);
    plan.push_back(19);
    plan.push_back(3);
    plan.push_back(0);
    plan.push_back(13);
    plan.push_back(27);
    auto path = me.get_path(graph, plan, LEAST_MONEY);
    path.FixTotalTime(graph);
    path.Show();
    cout << path.GetTotalPrice() << '\t' << endl;
    path.GetTotalTime().print() << endl;

    path = me.get_path(graph, plan, LEAST_TIME);
    path.FixTotalTime(graph);
    path.Show();
    cout << path.GetTotalPrice() << '\t' << endl;
    path.GetTotalTime().print() << endl;
    return 0;
}

#endif // TEST_GET_PATH