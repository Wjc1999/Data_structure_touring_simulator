#ifndef SRC_SIMULATE_H
#define SRC_SIMULATE_H

#include <chrono>

class Time;
class Traveller;
class CityGraph;
class IDMap;

// 返回每两次调用间的间隔毫秒数
std::chrono::duration<double, std::milli> Timer();

// 接受一个值,根据值的奇偶来返回时间间隔,当count为奇数时返回该次调用与上次count为偶数时调用的时间间隔
std::chrono::duration<double, std::milli> Timer(int count);

void setSleepMillsecs(int sleep_ms);

void SleepFor(int millseconds);

void InitializeSimulator(const Time &start_time);

void Simulate(Traveller &traveller, const CityGraph &city_graph, const IDMap &id_map);

#endif // SRC_SIMULATE_H
