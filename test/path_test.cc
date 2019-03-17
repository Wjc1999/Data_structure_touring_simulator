#ifndef TEST_PATH
#define TEST_PATH
#define TEST_TIME

#include <iostream>

#include "../src/city_graph.h"
#include "../src/path.h"

int main()
{
    Path test_path;
    CityGraph test_graph;
    for (int i = 1; i != 25; ++i)
        test_path.append(test_graph, i - 1, i, 0);
    test_path.Show();
    std::cout << "长度: " <<test_path.GetLen() << std::endl;
    std::cout << test_path.GetTotalPrice() << "元" <<std::endl;
    test_path.GetTotalTime().print();
    return 0;
}



#endif // TEST_PATH