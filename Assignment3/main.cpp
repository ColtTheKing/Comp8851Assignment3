#include "CuckooHash.h"
#include "RoundRobin.h"

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

	RoundRobin robin;
	std::vector<std::string> teams;
	teams.push_back("Canucks");
	teams.push_back("Flames");
	teams.push_back("Oilers");
	teams.push_back("Canadians");
	teams.push_back("Senators");
	teams.push_back("Maple Leafs");
	teams.push_back("Penguins");
	teams.push_back("Mighty Ducks");

	robin.runTournament(teams);

	return 0;
}