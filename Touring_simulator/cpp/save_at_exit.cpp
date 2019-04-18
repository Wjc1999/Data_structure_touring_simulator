
#include "headers/save_at_exit.h"


void setTravellerPtr(Traveller *traveller)
{
    p_traveller = traveller;
}

void SaveDataOnExit()
{
    if (!saved && p_traveller != nullptr /*&& (*p_traveller).get_position() != -2*/)
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
    std::cout << "Receive signal " << sig << std::endl;
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
