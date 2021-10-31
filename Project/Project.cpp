#include "Creature.h"
#include "Simulation.h"
#include <iostream>
#include <random>
#include <time.h>

int main()
{
	clock_t tStart = clock();
	srand(std::time(NULL));
	int time{ 300000 };
	Creature model1(1, 0, 0.2);
	int population{ 0 };

	basicSimulation(model1, population, time);
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	std::cout << "Press Enter to Continue";
	std::cin.ignore();
	return 0;
}