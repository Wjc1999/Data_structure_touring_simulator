#ifndef TEST_MAIN
#define TEST_MAIN

#include <iostream>

#include "../src/io.h"
#include "../src/id_map.h"
#include "../src/city_graph.h"
#include "../src/traveller.h"
#include "../src/time_format.h"
#include "../src/log.h"
#include "../src/path.h"
#include "../src/simulation.h"

int main()
{
    IDMap id_map;
    CityGraph city_graph;
    Traveller traveller;
    Path path;
    std::vector<City_id> plan;
    Strategy strategy;
    ClearScreen();
    int account_name_line = Welcome();
    ClearScreen();
    traveller.LoadData(account_name_line, city_graph);

    while (1)
    {
        int opcode = Menu(id_map, traveller);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        switch (opcode)
        {
        case SCHEDULE:
            plan = Request(id_map);
            traveller.set_plan(plan);
            // traveller.ShowPlan();
            strategy = InputStrategy();
            // TODO : 指定开始时间

            path = traveller.SchedulePath(city_graph, strategy);

            // path.Show();
            PrintPath(city_graph, id_map, path);
            if (PathConfirm())
                traveller.set_path(path);
            ClearScreen();
            break;
        case INQUIRE_STATE:
            PrintTravellerInfo(city_graph, id_map, traveller.get_init_time(), traveller);
            break;
        case INQUIRE_PATH:
            PrintPath(city_graph, id_map, path, 0);
            break;
        case SIMULATE:
            traveller.InitState(city_graph);
            InitializeSimulator(traveller.get_init_time());
            Simulate(traveller, city_graph, id_map);
            break;
        case EXIT:
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}
/*

*/
#endif // TEST_MAIN