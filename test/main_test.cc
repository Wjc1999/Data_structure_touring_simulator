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

int main()
{
    IDMap id_map;
    CityGraph city_graph;
    Traveller traveller;
    Path path;
    // Welcome();
    int opcode = Menu(id_map, traveller);
    switch (opcode)
    {
    case 1:
        path = traveller.GetPath(city_graph, LEAST_MONEY);
        path.Show();
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
    return 0;
}
/*
1
2 3 4 2 2 3 4 5 6 2 3 5 6 4 2 1 35 2 q
9
*/
#endif // TEST_MAIN