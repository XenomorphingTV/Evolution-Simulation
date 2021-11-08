#include "Creature.h"
#include "Simulation.h"
#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <fstream>

void saveCreatureData(std::vector<Creature>* allCreatures) {
	std::remove("CreatureData.txt");
	std::ofstream txtOutput;

	txtOutput.open("CreatureData.txt", std::ios_base::app);
	for (int i = 0; i <= (allCreatures->size() - 1); i++) {
		txtOutput << "Creature " << i << std::endl;
		txtOutput << "Spontaneous Birth Rate = " << allCreatures->at(i).getSpontaneousBirthRate() << std::endl;
		txtOutput << "Replication Chance = " << allCreatures->at(i).getReplicationChance() << std::endl;
		txtOutput << "Death Chance = " << allCreatures->at(i).getDeathChance() << std::endl;
		txtOutput << "Spontaneous Birth Rate Chance = " << allCreatures->at(i).getSpontaneousBirthRateChance() << std::endl;
		txtOutput << "Mutation Chance = " << allCreatures->at(i).getMutateChance() << std::endl << std::endl;
	}

	txtOutput.close();
}

int main()
{
	// Add a clock to measure the time of execution
	clock_t tStart = clock();

	// Create a random seed for our randomization
	srand(std::time(NULL));
	int time{ 1000 };
	std::vector<Creature> allCreatures;
	Creature model1(0, 0.5, 0.05, 0, 0.001, 10);
	allCreatures.push_back(model1);

	//basicSimulation(model1, &population, time);
	simulationV2(&allCreatures, time);
	saveCreatureData(&allCreatures);
	printf("Time taken: %.2fs\n", (double)(clock() - (uint16_t)tStart) / CLOCKS_PER_SEC);

	std::cout << "Press Enter to Continue";
	std::cin.ignore();
	return 0;
}