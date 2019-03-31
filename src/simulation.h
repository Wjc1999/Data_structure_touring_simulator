#ifndef SRC_SIMULATE
#define SRC_SIMULATE

#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "io.h"
#include "traveller.h"
#include "city_graph.h"
#include "user_type.h"
#include "path.h"
#include "log.h"
#include "id_map.h"

static Time current_time;
// 返回每两次调用间的间隔毫秒数
std::chrono::duration<double, std::milli> Timer()
{
    static int count = 0;
    static auto start_time = std::chrono::system_clock::now();
    static auto end_time = std::chrono::system_clock::now();
    if (count++ % 2)
    {
        start_time = std::chrono::system_clock::now();
        return start_time - start_time;
    }
    else
    {
        end_time = std::chrono::system_clock::now();
        return end_time - start_time;
    }
}

void Sleep(int millseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500 - millseconds));
}

void InitializeSimulator(const Time &start_time)
{
    current_time = start_time;
}

void Simulate(Traveller &traveller, const CityGraph &city_graph, const IDMap &id_map)
{
    while (traveller.get_position() != -2)
    {
        //char click;
        Timer();
#ifdef _WIN32
        system("cls");
#elif __linux__
        system("clear");
#endif
        std::cout << "当前时间 : " << current_time.GetDay() << " 日 " << current_time.GetHour() << "时" << std::endl;
        PrintPath(city_graph, id_map, traveller.get_path(), traveller.get_position());
        traveller.UpdateState(city_graph, current_time);
        current_time.add_time(1);
        auto duration = Timer();
        Sleep(duration.count());
        //std::cin >> click;
    }
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    std::cout << "当前时间 : " << current_time.GetDay() << " 日 " << current_time.GetHour() << "时" << std::endl;
    PrintPath(city_graph, id_map, traveller.get_path());
}

#endif // SRC_SIMULATE