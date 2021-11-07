#include "Creature.h"
#include "Simulation.h"
#include <iostream>
#include <random>
#include <time.h>
#include <vector>

int main()
{
	// Add a clock to measure the time of execution
	clock_t tStart = clock();

	// Create a random seed for our randomization
	srand(std::time(NULL));
	int time{ 10 };
	std::vector<Creature> allCreatures;
	Creature model1(1, 0, 0.2, 1, 0, 1);
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
