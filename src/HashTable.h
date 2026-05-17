#pragma once
#include <string>

const int HASH_TABLE_SIZE = 100003;

struct HashNode {
	std::string key;
	int value;
	HashNode* next;
};

struct HashTable {
	HashNode** table;
	int size;
};
void initHashTable(HashTable& ht);
int hashString(const std::string& str);
int getIndex(const HashTable& ht, const std::string& key);
void insertNode(HashTable& ht, const std::string& key, int value);
void freeHashTable(HashTable& ht);