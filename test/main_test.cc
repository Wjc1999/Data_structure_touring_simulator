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
#include "../src/save_at_exit.h"


int main()
{
    IDMap id_map;
    CityGraph city_graph;
    Traveller traveller;
    Path path;
    std::vector<City_id> plan;
    Strategy strategy;
    Time limit_time;
    Time init_time;

    ClearScreen();
    int account_name_line = Welcome(traveller);
    ClearScreen();
    
    traveller.LoadData(account_name_line, city_graph);
    setTravellerPtr(&traveller);
    setSignalHandlers();
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
            strategy = InputStrategy(init_time, limit_time);

            path = traveller.SchedulePath(city_graph, strategy, init_time, limit_time);

            // path.Show();
            PrintPath(city_graph, id_map, path);
            if (PathConfirm())
                traveller.set_path(path);
            ClearScreen();
            break;
        case INQUIRE_STATE:
            std::cout << "用户名: " <<traveller.get_ID() << std::endl;
            PrintTravellerInfo(city_graph, id_map, traveller.get_init_time(), traveller);
            break;
        case INQUIRE_PATH:
            //PrintPath(city_graph, id_map, path, 0);
            PrintRoutes(city_graph, id_map);
            break;
        case SIMULATE:
            traveller.InitState(city_graph);
            InitializeSimulator(traveller.get_init_time());
            Simulate(traveller, city_graph, id_map);
            break;
        case EXIT:
            std::exit(0);
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