#include "CuckooHash.h"

int main()
{
	CuckooHash cuckoo = CuckooHash(6);
	int* four = new int(4);
	int* ten = new int(10);
	int* twentyeight = new int(28);

	cuckoo.insert(four);
	cuckoo.insert(ten);
	cuckoo.insert(twentyeight);

	cuckoo.remove(*ten);

	bool hasTen = cuckoo.has(10);
	bool hasTwentyEight = cuckoo.has(28);

	return 0;
}