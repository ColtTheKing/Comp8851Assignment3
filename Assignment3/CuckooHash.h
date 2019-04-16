#pragma once
#include <vector>

constexpr auto HASH1_MOD = 1;
constexpr auto HASH2_MOD = 3;
constexpr auto HASH1_CHANGED_MOD = 5;
constexpr auto HASH2_CHANGED_MOD = 7;

class CuckooHash
{
public:
	CuckooHash(int tSize);
	void insert(int* n);
	void remove(int n);
	bool has(int n);
	void rehash();
private:
	std::vector<int*> *cuckooTable;
	int* numToPut;
	int tableSize, num;
	bool changedHash;
};