#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "DataModels.h"
#include "DynamicArray.h"
#include "CSVParser.h"
#include "HashTable.h"

struct HaloSystem {
    DynamicArray<User> users;
    DynamicArray<Device> devices;
    DynamicArray<App> apps;
    DynamicArray<Resource> resources;
    DynamicArray<LogEntry> logs;

    HashTable userMap;
    HashTable deviceMap;
    HashTable appMap;
    HashTable resourceMap;
};
void initSystem(HaloSystem& sys);
int getOrCreateUserIndex(HaloSystem& sys, const std::string& id);
int getOrCreateDeviceIndex(HaloSystem& sys, const std::string& id);
int getOrCreateAppIndex(HaloSystem& sys, const std::string& id);
int getOrCreateResourceIndex(HaloSystem& sys, const std::string& id);
void loadDataFromCSV(HaloSystem& sys, const std::string& filename);
void freeSystemMemory(HaloSystem& sys);
