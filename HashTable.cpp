#include"HashTable.h"


void initHashTable(HashTable& ht) {
	ht.size = HASH_TABLE_SIZE;
	ht.table = new HashNode * [HASH_TABLE_SIZE];
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		ht.table[i] = nullptr;
	}
}
int hashString(const std::string& str) {
	long long hashValue = 0;
	const int p = 31;
	for (int i = 0; i < str.length(); i++) {
		hashValue = ((hashValue * p) % HASH_TABLE_SIZE + str[i] % HASH_TABLE_SIZE) % HASH_TABLE_SIZE;
	}
	return (int)hashValue;
}
int getIndex(const HashTable& ht, const std::string& key) {
	int hashIndex = hashString(key);
	HashNode* current = ht.table[hashIndex];
	while (current != nullptr) {
		if (current->key == key) {
			return current->value;
		}
		current = current->next;
	}
	return -1;
}
void insertNode(HashTable& ht, const std::string& key, int value) {
	int hashIndex = hashString(key);
	HashNode* newNode = new HashNode();
	newNode->key = key;
	newNode->value = value;
	newNode->next = ht.table[hashIndex];
	ht.table[hashIndex] = newNode;
}
void freeHashTable(HashTable& ht) {
	if (ht.table == nullptr) return;

	for (int i = 0; i < ht.size; i++) {
		HashNode* current = ht.table[i];
		while (current != nullptr) {
			HashNode* temp = current;
			current = current->next;
			delete temp;
		}
	}
	delete[] ht.table;
	ht.table = nullptr;
}
