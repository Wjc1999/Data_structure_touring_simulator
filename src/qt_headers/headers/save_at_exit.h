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

void setTravellerPtr(Traveller *traveller);

void SaveDataOnExit();

void SaveDataOnExit(int sig);

void setSignalHandlers();

#endif // SAVE_AT_EXIT
