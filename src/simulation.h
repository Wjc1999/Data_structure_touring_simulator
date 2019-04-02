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
    static std::chrono::time_point<std::chrono::system_clock> start_time;
    static std::chrono::time_point<std::chrono::system_clock> end_time;
    if (count % 2)
    {
        end_time = std::chrono::system_clock::now();
        count++;
        return end_time - start_time;
    }
    else
    {

        start_time = std::chrono::system_clock::now();
        count++;
        return start_time - start_time;
    }
}

// 接受一个值,根据值的奇偶来返回时间间隔,当count为奇数时返回该次调用与上次count为偶数时调用的时间间隔
std::chrono::duration<double, std::milli> Timer(int count)
{
    static std::chrono::time_point<std::chrono::system_clock> start_time;
    static std::chrono::time_point<std::chrono::system_clock> end_time;
    if (count % 2)
    {
        end_time = std::chrono::system_clock::now();
        return end_time - start_time;
    }
    else
    {
        start_time = std::chrono::system_clock::now();
        return start_time - start_time;
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
    int count = 0;
    while (traveller.get_position() != -1)
    {
        //char click;
        Timer(count++);

        ClearScreen();

        std::cout << "当前时间 : " << current_time.GetDay() << " 日 " << current_time.GetHour() << "时" << std::endl;
        //PrintPath(city_graph, id_map, traveller.get_path(), traveller.get_position());
        PrintTravellerInfo(city_graph, id_map, current_time, traveller);
        traveller.UpdateState(city_graph, current_time);
        current_time.add_time(1);
        auto duration = Timer(count++);
        // std::cout << duration.count();
        Sleep(duration.count());
        // std::cin >> click;
    }

    ClearScreen();
    std::cout << "当前时间 : " << current_time.GetDay() << " 日 " << current_time.GetHour() << "时" << std::endl;
    PrintPath(city_graph, id_map, traveller.get_path(), traveller.get_path().GetLen());
}

#endif // SRC_SIMULATE