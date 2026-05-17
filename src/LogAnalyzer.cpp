#include"LogAnalyzer.h"



bool compareLogByTimestamp(const LogEntry& a, const LogEntry& b) {
	return a.timestamp < b.timestamp;
}
bool compareResourceByAccessCount(const Resource& a, const Resource& b) {
	return a.accessCount > b.accessCount;
}
void findLogRangeByTime(const DynamicArray<LogEntry>& logs, long long t1, long long t2, int& startIndex, int& endIndex) {
	startIndex = -1;
	endIndex = -1;

	if (logs.size == 0) return;

	int low = 0, high = logs.size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (logs.data[mid].timestamp >= t1) {
			startIndex = mid;
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	low = 0, high = logs.size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (logs.data[mid].timestamp <= t2) {
			endIndex = mid;
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}

	if (startIndex > endIndex || startIndex == -1 || endIndex == -1) {
		startIndex = -1;
		endIndex = -1;
	}
}


void searchUserJourneyRangeByTime(const HaloSystem& sys, const std::string& userId, long long t1, long long t2) {
	// Kiem tra userID
	int idx = getIndex(sys.userMap, userId);
	if (idx == -1) {
		std::cout << "Nguoi dung khong ton tai!" << std::endl;
		return;
	}

	// Xac dinh khoang thoi gian
	int startIndex, endIndex;
	findLogRangeByTime(sys.logs, t1, t2, startIndex, endIndex);
	if (startIndex == -1 && endIndex == -1) {
		std::cout << "Khong co du lieu log nao trong khoang thoi gian nay!" << std::endl;
		return;
	}

	// Truy xuat
	bool found = false;
	for (int i = startIndex; i <= endIndex; i++) {
		if (sys.logs.data[i].userIndex == idx) {
			if (sys.logs.data[i].event_type == 4) {
				continue;
			}
			found = true;

			const LogEntry& log = sys.logs.data[i];

			// Lay thong tin goc
			std::string deviceId = sys.devices.data[log.deviceIndex].device_id;
			std::string appId = sys.apps.data[log.appIndex].app_id;
			std::string resourceId = sys.resources.data[log.resourceIndex].resource_id;

			std::cout << "[" << log.timestamp << "] User: " << userId << " | "
				<< deviceId << " -> "
				<< appId << " -> "
				<< resourceId
				<< " | Hanh dong: " << eventTypeToString(log.event_type)
				<< " | Vi tri: " << log.location
				<< std::endl;
		}
	}

	if (!found) {
		std::cout << "Nguoi dung khong co hoat dong nao trong khoang thoi gian nay!" << std::endl;
	}
}
void searchResourceJourneyRangeByTime(const HaloSystem& sys, const std::string& resourceId, long long t1, long long t2) {
	int resIdx = getIndex(sys.resourceMap, resourceId);
	if (resIdx == -1) {
		std::cout << "Tai nguyen khong ton tai!" << std::endl;
		return;
	}

	int startIndex, endIndex;
	findLogRangeByTime(sys.logs, t1, t2, startIndex, endIndex);
	if (startIndex == -1 && endIndex == -1) {
		std::cout << "Khong co du lieu log nao trong khoang thoi gian nay!" << std::endl;
		return;
	}

	bool found = false;
	for (int i = startIndex; i <= endIndex; i++) {
		if (sys.logs.data[i].resourceIndex == resIdx) {
			if (sys.logs.data[i].event_type == 4) {
				continue;
			}
			found = true;

			const LogEntry& log = sys.logs.data[i];

			std::string userId = sys.users.data[log.userIndex].user_id;
			std::string deviceId = sys.devices.data[log.deviceIndex].device_id;
			std::string appId = sys.apps.data[log.appIndex].app_id;

			std::string actionStr = eventTypeToString(log.event_type);

			std::cout << "[" << log.timestamp << "] Resource: " << resourceId << " | "
				<< userId << " -> "
				<< deviceId << " -> "
				<< appId
				<< " | Hanh dong: " << actionStr
				<< " | Vi tri: " << log.location
				<< std::endl;
		}
	}

	if (!found) {
		std::cout << "Tai nguyen khong co luot truy cap nao trong khoang thoi gian nay." << std::endl;
	}
}
void top10MostAccessedResources(const HaloSystem& sys, long long t1, long long t2) {
	int startIndex, endIndex;
	findLogRangeByTime(sys.logs, t1, t2, startIndex, endIndex);

	if (startIndex == -1 && endIndex == -1) {
		std::cout << "Khong co hoat dong truy xuat nao trong khoang thoi gian nay!" << std::endl;
		return;
	}

	int numResources = sys.resources.size;
	Resource* tempResources = new Resource[numResources];

	for (int i = 0; i < numResources; i++) {
		tempResources[i].resource_id = sys.resources.data[i].resource_id;
		tempResources[i].accessCount = 0;
	}

	for (int i = startIndex; i <= endIndex; i++) {
		if (sys.logs.data[i].event_type == 4) {
			continue;
		}
		int resIdx = sys.logs.data[i].resourceIndex;
		tempResources[resIdx].accessCount++;
	}

	mySort(tempResources, 0, numResources - 1, compareResourceByAccessCount);

	std::cout << "TOP 10 TAI NGUYEN DUOC TRUY XUAT NHIEU NHAT" << std::endl;
	int limit = (numResources < 10) ? numResources : 10;
	int rank = 1;

	for (int i = 0; i < limit; i++) {
		if (tempResources[i].accessCount > 0) {
			std::cout << rank << ". Resource ID: " << tempResources[i].resource_id
				<< " | So luot truy xuat: " << tempResources[i].accessCount << " lan"
				<< std::endl;
			rank++;
		}
	}

	if (rank == 1) {
		std::cout << "Khong co tai nguyen nao duoc truy cap trong khoang thoi gian nay." << std::endl;
	}

	delete[] tempResources;
}
