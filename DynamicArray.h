#pragma once
#include"DataModels.h"

template <typename T>
struct DynamicArray {
	T* data;
	int size;
	int capacity;
};

template <typename T>
void initArray(DynamicArray<T>& arr, int capacity) {
	arr.size = 0;
	arr.capacity = capacity;
	arr.data = new T[arr.capacity];
}

template <typename T>
void freeArray(DynamicArray<T>& arr) {
	if (arr.data != nullptr) {
		delete[]arr.data;
		arr.data = nullptr;
	}
	arr.size = 0;
	arr.capacity = 0;
}

template <typename T>
void addElement(DynamicArray<T>& arr, const T& element) {
	if (arr.capacity == 0) {
		arr.capacity = 10;
		arr.data = new T[arr.capacity];
	}
	else if (arr.capacity <= arr.size) {
		arr.capacity *= 2;
		T* newArr = new T[arr.capacity];

		for (int i = 0; i < arr.size; i++) {
			newArr[i] = arr.data[i];
		}

		delete[] arr.data;
		arr.data = newArr;
	}

	arr.data[arr.size] = element;
	arr.size += 1;
}






