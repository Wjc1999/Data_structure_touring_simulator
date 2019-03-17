#include "../src/traveller.h"
using namespace std;
int main(){
    CityGraph graph;
    Traveller me;
    vector <City_id> plan;
    plan.push_back(16);
    plan.push_back(27);
    plan.push_back(29);
    plan.push_back(0);
    me.get_path(graph, plan, LEAST_MONEY);
    me.get_path(graph, plan, LEAST_TIME).Show();
    return 0;
}