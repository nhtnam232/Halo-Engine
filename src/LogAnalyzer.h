#pragma once
#include"HaloEngine.h"
template <typename T>
void mySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
int hoarePartition(T* arr, int low, int high, bool (*compare)(const T&, const T&)) {
	T pivot = arr[(low + high) / 2];
	int i = low - 1, j = high + 1;

	while (true) {
		do {
			i++;
		} while (compare(arr[i], pivot));

		do {
			j--;
		} while (compare(pivot, arr[j]));

		if (i >= j) {
			return j;
		}
		mySwap(arr[i], arr[j]);
	}
}

template <typename T>
void mySort(T* arr, int low, int high, bool (*compare)(const T&, const T&)) {
	if (low < high) {
		int p = hoarePartition(arr, low, high, compare);

		mySort(arr, low, p, compare);
		mySort(arr, p + 1, high, compare);
	}
}
bool compareLogByTimestamp(const LogEntry& a, const LogEntry& b);
bool compareResourceByAccessCount(const Resource& a, const Resource& b);
void findLogRangeByTime(const DynamicArray<LogEntry>& logs, long long t1, long long t2, int& startIndex, int& endIndex);
void searchUserJourneyRangeByTime(const HaloSystem& sys, const std::string& userId, long long t1, long long t2);
void searchResourceJourneyRangeByTime(const HaloSystem& sys, const std::string& resourceId, long long t1, long long t2);
void top10MostAccessedResources(const HaloSystem& sys, long long t1, long long t2);
