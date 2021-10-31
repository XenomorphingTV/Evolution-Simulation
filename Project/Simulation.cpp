#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <stdlib.h>

void basicSimulation(Creature model, int population, int time) {
	std::cout << "Time: 0 | Population: " << population << "\n";
	std::remove("GraphPlots.dat");

	saveCoords(0, population);
	for (int currentTime = 1; currentTime <= time; currentTime++) {
		std::future<int> deathChanceCalcAsync = std::async(std::launch::async, deathChanceCalulator, population, model);
		population = population + model.getSpontaneousBirthRate();
		int deaths = 0;
		int births = replicationChanceCalulator(population, model);
		try {
			deaths = deathChanceCalcAsync.get();
		}
		catch (std::future_error& e) {
			std::cout << "future_error caught: " << e.what() << '\n';
		}
		population = population + (births - deaths);
		population = (population < 0) ? 0 : (population);
		if (currentTime % 100 == 0) {
			std::cout << "Time: " << currentTime << " | " << "Population: " << population << "\n";
		}
		saveCoords(currentTime, population);
	}
}

int deathChanceCalulator(int population, Creature model) {
	int tempPop{ 0 };
	for (int i = 0; i <= population; i++) {
		if (model.randomPercentCheck(model.getDeathChance())) {
			tempPop++;
		}
	}
	return tempPop;
}

int replicationChanceCalulator(int population, Creature model) {
	int tempPop{ 0 };
	for (int i = 0; i <= population; i++) {
		if (model.randomPercentCheck(model.getReplicationChance())) {
			tempPop++;
		}
	}
	return tempPop;
}

void saveCoords(int time, int population) {
	std::ofstream MyFile;
	MyFile.open("GraphPlots.dat", std::ios_base::app);
	MyFile << time << "\t" << population << "\n";
}