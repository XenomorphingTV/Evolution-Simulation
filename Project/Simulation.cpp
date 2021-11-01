#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

void basicSimulation(Creature model, int *population, int time) {
	// Remove previously created file, becuase we always append to it
	std::remove("GraphPlots.csv");

	// Save *population at the time of 0	
	saveCoords(0, population);

	// Loop to go through the time from zero until the specified number
	for (int currentTime = 1; currentTime <= time; currentTime++) {



		// Do all the maths for *population, add the spontaneous birth rate before doing any other calculations
		*population = *population + model.getSpontaneousBirthRate();
		int tempPop = *population;
		deathChanceCalulator(population, model, tempPop);
		replicationChanceCalulator(population, model, tempPop);



		// Check if the *population ever drops below zero, if it does then make *population zero
		*population = (*population < 0) ? 0 : (*population);

		// Save the data to a .cvs file, will later be edited to plot graphs using gnu-plot
		saveCoords(currentTime, population);
	}
}

void deathChanceCalulator(int *population, Creature model, int tempPop) {
	// Check how many creatures die in the population, edit the population directly to cut down on execution speed
	for (int i = 0; i <= tempPop; i++) {
		if (model.randomPercentCheck(model.getDeathChance())) {
			--(*population);
		}
	}

}

void replicationChanceCalulator(int *population, Creature model, int tempPop) {
	// Same as deathChanceCalculator, do maths on the population
	for (int i = 0; i <= tempPop; i++) {
		if (model.randomPercentCheck(model.getReplicationChance())) {
			++(*population);
		}
	}
}

void spontaneousBirthChanceCalulator(int* population, Creature model, int tempPop) {
	if (model.randomPercentCheck(model.getSpontaneousBirthRateChance())) {
		++(*population);
	}
}

void saveCoords(int time, int *population) {
	std::ofstream MyFile;
	MyFile.open("GraphPlots.csv", std::ios_base::app);

	// The required template for cvs files
	MyFile << time << "," << *population << "\n";
}