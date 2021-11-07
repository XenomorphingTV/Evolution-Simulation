#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

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

void saveCoords(int time, int* population) {
	std::ofstream myFile;
	myFile.open("GraphPlots.csv", std::ios_base::app);

	// The required template for cvs files
	myFile << time << "," << *population << "\n";
}

//--------------------------//
//Start of second simulation//
//--------------------------//

void simulationV2(std::vector<Creature> *allCreatures, int time) {
	std::remove("GraphPlots.csv");

	bool tableHeader = false;

	saveCoordsV2(0, &tableHeader, (allCreatures->size() - 1), allCreatures);
	tableHeader = true;
	saveCoordsV2(time, &tableHeader, (allCreatures->size() - 1), allCreatures);
}


// New method of saving data, making it in an aranged table, and replacing the headers
void saveCoordsV2(int time, bool *header, int size, std::vector<Creature>* allCreatures) {
	std::ifstream checkFile;
	std::ofstream myFile;
	
	// Opening file to check if it exists
	checkFile.open("GraphPlotsNoHeader.csv");
	
	// If it doesn't, create it with a "Header" placeholder
	if(!checkFile) {
		myFile.open("GraphPlotsNoHeader.csv", std::ios_base::app);
			myFile << "Header\n";
			myFile.close();
	}
	checkFile.close();

	// Checking if we need to add the headers, they are done last so that all mutations are added at the end
	if (*header) {
		// File to read from, before headers are added
		std::ifstream fileIn("GraphPlotsNoHeader.csv");
		// Output file, since we need to copy all data after adding headers
		std::ofstream fileOut("GraphPlots.csv");
		if (!fileIn || !fileOut)
		{
			std::cout << "Error opening files!\n";
			exit(1);
		}

		std::string strTemp;
		std::string replace{ "" };

		// Getting the lines from our file
		while (getline(fileIn, strTemp))
		{
			// If "Header" placeholder is found, replace it with population and then number of total species
			if (strTemp == "Header") {
				for (int i = 0; i <= size; i++) {
					replace += "Time,Population " + std::to_string(i) + ",";
				}
				replace += "\n";
				fileOut << replace;
			}

			// The rest is just coppied
			else {
				fileOut << strTemp;
			}
		}

		// Let out function know the header is set
		*header = false;
		fileIn.close();
		fileOut.close();

		// Delete the temp file
		std::remove("GraphPlotsNoHeader.csv");
	}

	// If its not yet time to add headers, just save the data
	else {
		myFile.open("GraphPlotsNoHeader.csv", std::ios_base::app);
		for (int i = 0; i <= size; i++) {
			myFile << time << "," << (allCreatures->at(i)).population << ",";
		}
		myFile << "\n";
	}
}