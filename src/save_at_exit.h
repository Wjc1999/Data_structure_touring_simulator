#ifndef SAVE_AT_EXIT
#define SAVE_AT_EXIT

#include <cstdlib>
#include <csignal>
#include <string>
#include <iostream>

#include "io.h"
#include "traveller.h"

static Traveller *p_traveller = nullptr;
static bool saved = false;

void setTravellerPtr(Traveller *traveller)
{
    p_traveller = traveller;
}

void SaveDataOnExit()
{
    if (!saved && p_traveller != nullptr && (*p_traveller).get_position() != -2)
    {
        std::cout << "saving..." << "\t";
        if ((*p_traveller).SaveData())
        {
            saved = true;
            std::cout << "success." << std::endl;
        }
        else
            std::cout << "failed." << std::endl;
    }
}

void SaveDataOnExit(int sig)
{
    std::cout << "Receiving signal " << sig << std::endl;
    SaveDataOnExit();
    std::exit(EXIT_FAILURE);
}

void setSignalHandlers()
{
    std::signal(SIGABRT, SaveDataOnExit);
    std::signal(SIGINT, SaveDataOnExit);
    std::signal(SIGTERM, SaveDataOnExit);
    std::atexit(SaveDataOnExit);
}

#endif // SAVE_AT_EXIT
