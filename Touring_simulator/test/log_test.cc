#ifndef TEST_LOG
#define TEST_LOG

#include <iostream>

#include "../src/log.h"

int main(void)
{
    Log log;
    std::cout << log.get_log_path() << std::endl;
    log.WriteLog("test");
    return 0;
}

#endif // TEST_LOG