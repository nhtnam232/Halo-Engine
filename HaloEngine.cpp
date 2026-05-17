#include"HaloEngine.h"


void initSystem(HaloSystem& sys) {
    initArray(sys.logs, 10000);
    initArray(sys.users, 100);
    initArray(sys.devices, 100);
    initArray(sys.apps, 100);
    initArray(sys.resources, 100);


    initHashTable(sys.userMap);
    initHashTable(sys.deviceMap);
    initHashTable(sys.appMap);
    initHashTable(sys.resourceMap);
}
int getOrCreateUserIndex(HaloSystem& sys, const std::string& id) {
	int idx = getIndex(sys.userMap, id);
	if (idx != -1) {
		return idx;
	}
	User newUser;
	newUser.user_id = id;
	addElement(sys.users, newUser);
	int index = sys.users.size - 1;
	insertNode(sys.userMap, id, index);
	return index;
}
int getOrCreateDeviceIndex(HaloSystem& sys, const std::string& id) {
    int idx = getIndex(sys.deviceMap, id);
    if (idx != -1) return idx;

    Device newDevice; newDevice.device_id = id;
    addElement(sys.devices, newDevice);
    int newIdx = sys.devices.size - 1;
    insertNode(sys.deviceMap, id, newIdx);
    return newIdx;
}

int getOrCreateAppIndex(HaloSystem& sys, const std::string& id) {
    int idx = getIndex(sys.appMap, id);
    if (idx != -1) return idx;

    App newApp; newApp.app_id = id;
    addElement(sys.apps, newApp);
    int newIdx = sys.apps.size - 1;
    insertNode(sys.appMap, id, newIdx);
    return newIdx;
}

int getOrCreateResourceIndex(HaloSystem& sys, const std::string& id) {
    int idx = getIndex(sys.resourceMap, id);
    if (idx != -1) return idx;

    Resource newResource; newResource.resource_id = id;
    addElement(sys.resources, newResource);
    int newIdx = sys.resources.size - 1;
    insertNode(sys.resourceMap, id, newIdx);
    return newIdx;
}
void loadDataFromCSV(HaloSystem& sys, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Loi: Khong the mo file " << filename << std::endl;
        return;
    }
    std::string header;
    if (!std::getline(in, header)) {
        return;
    }
    std::string line = "";
    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        std::string fields[7];
        if (splitCSVLine(line, fields) < 7) {
            continue;
        }
        int userIndex = getOrCreateUserIndex(sys, fields[0]);
        int deviceIndex = getOrCreateDeviceIndex(sys, fields[1]);
        int appIndex = getOrCreateAppIndex(sys, fields[2]);
        int resourceIndex = getOrCreateResourceIndex(sys, fields[3]);
        EventType eventType = stringToEventType(fields[4]);
        std::string location = fields[5];
        long long timestamp = 0;
        try {
            if (!fields[6].empty()) {
                timestamp = std::stoll(fields[6]);
            }
        }
        catch (...) {
            timestamp = 0;
        }
        LogEntry entry;
        entry.userIndex = userIndex;
        entry.deviceIndex = deviceIndex;
        entry.appIndex = appIndex;
        entry.resourceIndex = resourceIndex;
        entry.event_type = eventType;
        entry.location = location;
        entry.timestamp = timestamp;

        addElement(sys.logs, entry);
    }
    in.close();
    std::cout << "Hoan tat! Tong cong: " << sys.logs.size << " logs." << std::endl;
}
void freeSystemMemory(HaloSystem& sys) {
    freeArray(sys.users);
    freeArray(sys.devices);
    freeArray(sys.apps);
    freeArray(sys.resources);
    freeArray(sys.logs);
    freeHashTable(sys.userMap);
    freeHashTable(sys.deviceMap);
    freeHashTable(sys.appMap);
    freeHashTable(sys.resourceMap);
}