#include "RoundRobin.h"

RoundRobin::RoundRobin() {}

void RoundRobin::runTournament(std::vector<std::string> teams)
{
	if (teams.size() < 2)
		return;

	std::vector<std::string> set1 = std::vector<std::string>(teams.begin(), teams.begin() + (teams.size() / 2));
	std::vector<std::string> set2 = std::vector<std::string>(teams.begin() + (teams.size() / 2), teams.end());

	for (int i = 0; i < set1.size(); i++)
	{
		for (int j = 0, k = i; j < set1.size(); j++)
		{
			int randWin = rand() % 2;
			
			std::cout << set1[j] << " vs " << set2[k] << std::endl;

			std::cout << (randWin ? set1[j] : set2[k]) << " is the winner!" << std::endl;

			//Update k
			if (++k >= set1.size())
				k = 0;
		}
	}

	runTournament(set1);
	runTournament(set2);
}