#pragma once

#include<iostream>
#include<string>


enum EventType { LOGIN, LOGOUT, TOKEN_REFRESH, ACCESS, FAILED_LOGIN, OPEN_APP, DOWNLOAD, ADMIN_ACTION };
struct User {
	std::string user_id;
};
struct Device {
	std::string device_id;
};
struct App {
	std::string app_id;
};
struct Resource {
	std::string resource_id;
	int accessCount;
};
struct LogEntry {
	int userIndex;
	int deviceIndex;
	int appIndex;
	int resourceIndex;

	EventType event_type;
	std::string location;
	long long timestamp;
};