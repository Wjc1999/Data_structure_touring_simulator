
#ifndef TEST_GET_PATH
#define TEST_GET_PATH
#define TEST_TIME
#include "../src/traveller.h"
using namespace std;

int call_counter_time = 0;
int call_counter_money = 0;
int depth_counter = 0;

int main(){
    CityGraph graph;
    Traveller me;
    vector<City_id> plan{1, 30};
    // plan.push_back(12);
    // plan.push_back(4);
    // plan.push_back(23);
    // plan.push_back(14);
    // plan.push_back(8);
    // plan.push_back(29);
    // plan.push_back(1);
    // plan.push_back(16);
    // plan.push_back(22);
    // plan.push_back(3);
    // plan.push_back(0);
    // 
    // plan.push_back(2);
    // plan.push_back(5);
    // plan.push_back(6);
    // 
    // plan.push_back(13);
    // plan.push_back(27);
    auto path = me.GetPath(graph, plan, LEAST_MONEY);
    path.FixTotalTime(graph);
    path.Show();
    cout << path.GetTotalPrice() << '\t' << endl;
    path.GetTotalTime().print() << endl;
    cout << call_counter_money << endl;
    cout << depth_counter << endl;

    path = me.GetPath(graph, plan, LEAST_TIME);
    path.FixTotalTime(graph);
    path.Show();
    cout << path.GetTotalPrice() << '\t' << endl;
    path.GetTotalTime().print() << endl;
    cout << call_counter_time << endl;
    cout << depth_counter << endl;
    return 0;
}

#endif // TEST_GET_PATH