#include "CuckooHash.h"

CuckooHash::CuckooHash(int tSize)
{
	cuckooTable = new std::vector<int*>();
	tableSize = tSize;
	num = 0;
	numToPut = nullptr;

	for (int i = 0; i < tableSize * 2; i++)
		cuckooTable->push_back(nullptr);
}

void CuckooHash::insert(int* n)
{
	//Check first table
	int hash1 = *n / (changedHash ? HASH1_CHANGED_MOD : HASH1_MOD) % tableSize;

	if (cuckooTable->at(hash1) == nullptr)
	{
		cuckooTable->at(hash1) = n;
		num++;
		return;
	}

	//Check second table
	int hash2 = *n / (changedHash ? HASH2_CHANGED_MOD : HASH2_MOD) % tableSize;

	if (cuckooTable->at(hash2 + tableSize) == nullptr)
	{
		cuckooTable->at(hash2 + tableSize) = n;
		num++;
		return;
	}

	bool leftTable = false;
	numToPut = n;

	for (int i = 0; i < num; i++)
	{
		leftTable = !leftTable;
		int ind;

		if (leftTable)
		{
			ind = hash1;
			hash1 = *numToPut / (changedHash ? HASH1_CHANGED_MOD : HASH1_MOD) % tableSize;
		}
		else
		{
			ind = hash2 + tableSize;
			hash2 = *numToPut / (changedHash ? HASH2_CHANGED_MOD : HASH2_MOD) % tableSize;
		}

		//Hold onto the number currently there if there is one and put n in
		int* temp = cuckooTable->at(ind);
		cuckooTable->at(ind) = numToPut;
		numToPut = temp;

		if (numToPut == nullptr)
			return;
	}

	//We need to rehash, so just change the hashes to the alternate hashes
	//There's definitely a better way but I didn't do it
	rehash();
}

void CuckooHash::remove(int n)
{
	//Check first table
	int hash1 = n / (changedHash ? HASH1_CHANGED_MOD : HASH1_MOD) % tableSize;

	if (cuckooTable->at(hash1) != nullptr && *cuckooTable->at(hash1) == n)
	{
		cuckooTable->at(hash1) = nullptr;
		num--;
		return;
	}

	//Check second table
	int hash2 = n / (changedHash ? HASH2_CHANGED_MOD : HASH2_MOD) % tableSize;

	if (cuckooTable->at(hash2 + tableSize) != nullptr && *cuckooTable->at(hash2 + tableSize) == n)
	{
		cuckooTable->at(hash2 + tableSize) = nullptr;
		num--;
	}
}

bool CuckooHash::has(int n)
{
	//Check first table
	int hash1 = n / (changedHash ? HASH1_CHANGED_MOD : HASH1_MOD) % tableSize;

	if (cuckooTable->at(hash1) != nullptr && *cuckooTable->at(hash1) == n)
		return true;

	//Check second table
	int hash2 = n / (changedHash ? HASH2_CHANGED_MOD : HASH2_MOD) % tableSize;

	if (cuckooTable->at(hash2 + tableSize) != nullptr && *cuckooTable->at(hash2 + tableSize) == n)
		return true;

	return false;
}

void CuckooHash::rehash()
{
	changedHash = !changedHash;
	num = 0;

	std::vector<int*> *prevTable = cuckooTable;
	cuckooTable = new std::vector<int*>();

	for(int i = 0; i < prevTable->size(); i++)
		cuckooTable->push_back(nullptr);

	//Reinsert everything
	for (int i = 0; i < prevTable->size(); i++)
	{
		if (prevTable->at(i) != nullptr)
		{
			insert(prevTable->at(i));
		}
	}

	//Then try to add the thing that you were previously unable to add
	if (numToPut != nullptr)
		insert(numToPut);

	numToPut = nullptr;
}