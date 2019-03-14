#ifndef TEST_TIME
#define TEST_TIME

#include <iostream>
#include "../src/time_format.h"

int main()
{
    std::cout << "初始化测试" << std::endl;
    Time test1(11000);
    Time test2(22300);
    Time test3(1, 23);
    Time test4(3, 20);
    Time test5(10900);
    Time test6(10000);
    test1.print();
    test2.print();
    test3.print();
    test4.print();
    test5.print();
    test6.print();

    std::cout << "time_diff test" << std::endl;
    test1.time_diff(test2).print();
    test4.time_diff(test1).print();

    std::cout << "hour_diff test" << std::endl;
    std::cout << test1.hour_diff(test2) << std::endl;
    std::cout << test4.hour_diff(test1) << std::endl;

    std::cout << "add_time test" << std::endl;
    //test6.add_time(test1).print();
    test1.add_time(test2).print();

    return 0;
}

#endif // TEST_TIME