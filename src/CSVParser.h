#pragma once
#include <string>
#include <sstream>
#include "DataModels.h"



EventType stringToEventType(const std::string& eventStr);
int splitCSVLine(const std::string& line, std::string fields[7]);
std::string eventTypeToString(int type);
