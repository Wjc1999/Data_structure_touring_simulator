#ifndef SRC_SIMULATE
#define SRC_SIMULATE

#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <memory>

#include "io.h"
#include "traveller.h"
#include "city_graph.h"
#include "user_type.h"
#include "path.h"
#include "log.h"
#include "id_map.h"

static Time current_time;
static int sleep_millsecs = 500;

// 返回每两次调用间的间隔毫秒数
std::chrono::duration<double, std::milli> Timer();

// 接受一个值,根据值的奇偶来返回时间间隔,当count为奇数时返回该次调用与上次count为偶数时调用的时间间隔
std::chrono::duration<double, std::milli> Timer(int count);

void setSleepMillsecs(int sleep_ms);

void SleepFor(int millseconds);

void InitializeSimulator(const Time &start_time);

#if defined(_WIN32) || (defined(__CYGWIN__) && !defined(_WIN32)) || defined(__MINGW32__) || defined(__MINGW64__)

static HANDLE InitOutBuf();

void Simulate(Traveller &traveller, const CityGraph &city_graph, const IDMap &id_map);

#else

void Simulate(Traveller &traveller, const CityGraph &city_graph, const IDMap &id_map);
#endif
#endif // SRC_SIMULATE
