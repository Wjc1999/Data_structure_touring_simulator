#ifndef TEST_IDMAP
#define TEST_IDMAP

#include "../src/id_map.h"
#include <iostream>

int main()
{
    IDMap test;
    auto city_size = test.GetCityMapSize();
    auto train_size = test.GetTrainMapSize();
    auto trans_size = test.GetTransMapSize();
    for (decltype(city_size) i = 0; i != city_size; ++i)
        std::cout << i << '\t' << test.GetCityStr(i) << std::endl;

    for (decltype(train_size) i = 0; i != train_size; ++i)
        std::cout << i << '\t' << test.GetTrainSeatTypeStr(i) << std::endl;

    for (decltype(trans_size) i = 0; i != trans_size; ++i)
        std::cout << i << '\t' << test.GetTransStr(i) << std::endl;

    return 0;
}

#endif // TEST_IDMAP