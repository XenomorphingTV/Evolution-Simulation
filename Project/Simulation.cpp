#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <stdlib.h>

void basicSimulation(Creature model, int population, int time) {
	// Remove previously created file, becuase we always append to it
	std::remove("GraphPlots.csv");

	// Output and save population at the time of 0
	std::cout << "Time: 0 | Population: " << population << "\n";	
	saveCoords(0, population);

	// Loop to go through the time from zero until the specified number
	for (int currentTime = 1; currentTime <= time; currentTime++) {

		// Using async to make our program faster by multithreading
		std::future<int> deathChanceCalcAsync = std::async(std::launch::async, deathChanceCalulator, population, model);

		// Do all the maths for population, add the spontaneous birth rate before doing any other calculations
		population = population + model.getSpontaneousBirthRate();
		int deaths = deathChanceCalcAsync.get();
		int births = replicationChanceCalulator(population, model);
		population = population + (births - deaths);

		// Check if the population ever drops below zero, if it does then make population zero
		population = (population < 0) ? 0 : (population);

		// Output the data to screen, change the modulus to change how often you get results outputted
		if (currentTime % 100 == 0) {
			std::cout << "Time: " << currentTime << " | " << "Population: " << population << "\n";
		}

		// Save the data to a .cvs file, will later be edited to plot graphs using gnu-plot
		saveCoords(currentTime, population);
	}
}

int deathChanceCalulator(int population, Creature model) {
	int tempPop{ 0 };

	// Check how many creatures die in the population, store them in a temp value to take away from the population later
	for (int i = 0; i <= population; i++) {
		if (model.randomPercentCheck(model.getDeathChance())) {
			tempPop++;
		}
	}
	return tempPop;
}

int replicationChanceCalulator(int population, Creature model) {
	int tempPop{ 0 };

	// Same as deathChanceCalculator, but we add the temp value to population later
	for (int i = 0; i <= population; i++) {
		if (model.randomPercentCheck(model.getReplicationChance())) {
			tempPop++;
		}
	}
	return tempPop;
}

void saveCoords(int time, int population) {
	std::ofstream MyFile;
	MyFile.open("GraphPlots.csv", std::ios_base::app);

	// The required template for cvs files
	MyFile << time << "," << population << "\n";
}