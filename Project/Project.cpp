#include "Creature.h"
#include "Simulation.h"
#include <iostream>
#include <random>
#include <time.h>

int main()
{
	// Add a clock to measure the time of execution
	clock_t tStart = clock();

	// Create a random seed for our randomization
	srand(std::time(NULL));

	// Time of evolution, will change this to input later
	int time{ 300000 };

	// Create our creature, will change to input later
	Creature model1(1, 0, 0.2);

	// Our starting population
	int population = 0;

	// Run our basic simulation
	basicSimulation(model1, &population, time);

	// Print the recorded time of program
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	std::cout << "Press Enter to Continue";
	std::cin.ignore();
	return 0;
}