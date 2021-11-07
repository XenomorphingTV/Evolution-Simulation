#include "Creature.h"
#include "Simulation.h"
#include <iostream>
#include <random>
#include <time.h>
#include <vector>

int main()
{
	clock_t tStart = clock();
	srand(std::time(NULL));
	int time{ 10 };
	std::vector<Creature> allCreatures;
	Creature model1(1, 0, 0.2, 1, 0, 0);
	Creature model2(1, 0, 0.2, 1, 0, 0);
	allCreatures.push_back(model1);
	allCreatures.push_back(model2);

	//basicSimulation(model1, &population, time);
	simulationV2(&allCreatures, time);
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	std::cout << "Press Enter to Continue";
	std::cin.ignore();
	return 0;
}