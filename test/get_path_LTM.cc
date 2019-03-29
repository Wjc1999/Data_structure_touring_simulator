#include "../src/traveller.h"
#include "../src/city_graph.h"
#include "../src/id_map.h"
int main()
{
    CityGraph graph;
    IDMap idmap;
    Traveller t("test");
    std::vector<int> plan;
    plan.push_back(29);
    plan.push_back(27);
    plan.push_back(16);
    Time now(1, 7);
    Time limit(1, 23);
    Path path = t.GetPath(graph, plan, LIMIT_TIME, now, limit);
}