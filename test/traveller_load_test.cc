#ifndef TEST_TRAVELLER_LOAD
#define TEST_TRAVELLER_LOAD

#include <vector>
#include <iostream>
#include <string>

#include "../src/path.h"
#include "../src/io.h"
#include "../src/traveller.h"

int main()
{
    CityGraph graph;
    Traveller t;
    std::string name;
    ShowNameList();
    int cnt;
    do
    {
        std::cin >> name;
        cnt = AccountCheck(name);
    } while (cnt == -1);

    if (t.LoadData(cnt, graph))
    {
        std::cout << "success!" << std::endl;
        t.ShowID();
        t.ShowPlan();
        t.ShowPath();
    }

    else
        std::cout << "干!" << std::endl;
    return 0;
}
#endif // TEST_TRAVELLER_LOAD