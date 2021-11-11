#include "Simulation.h"

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

		// Added a crowding coefficient to make the population balance out depending on the population
		if (model.randomPercentCheck(model.getDeathChance() + (0.001 * model.population))) {
			--(*population);
		}
	}

}

void replicationChanceCalulator(int *population, Creature model, int tempPop) {
	// Same as deathChanceCalculator, do maths on the population
	for (int i = 0; i <= tempPop; i++) {
		if (model.randomPercentCheck(model.getReplicationChance()) && *population != 0) {
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

	// Set a header flag. We use this to tell saveCoordsV2 that we need to replace temp header with all population names
	bool tableHeader = false;
	// Save population at time = 0
	saveCoordsV2(0, &tableHeader, (allCreatures->size() - 1), allCreatures);
	int totalPop;

	// Itterate through time
	for (int currentTime = 1; currentTime <= time; currentTime++) {

		// Reset total pop so we can recalculate it
		totalPop = 0;
		for (int creatureIndex = 0; creatureIndex <= (allCreatures->size() - 1); creatureIndex++) {
			totalPop += allCreatures->at(creatureIndex).population;
		}

		// Here we itterate through our vector, applying the same calculations to all our populations
		for (int creatureIndex = 0; creatureIndex <= (allCreatures->size() - 1); creatureIndex++) {
			// Add spontaneous birth rate too population
			allCreatures->at(creatureIndex).population = allCreatures->at(creatureIndex).population + allCreatures->at(creatureIndex).getSpontaneousBirthRate();
			int tempPop = allCreatures->at(creatureIndex).population;

			// Attempted using threads here, seemed to slow the program down rather than speeding it up, I guess I had to join it too often to make use of the multi thread
			// std::thread thread1(replicationChanceCalulator, &(allCreatures->at(creatureIndex).population), allCreatures->at(creatureIndex), tempPop);
			// std::thread thread2(deathChanceCalulatorv2, &(allCreatures->at(creatureIndex).population), allCreatures->at(creatureIndex), tempPop, totalPop);

			replicationChanceCalulator(&(allCreatures->at(creatureIndex).population), allCreatures->at(creatureIndex), tempPop);
			deathChanceCalulatorv2(&(allCreatures->at(creatureIndex).population), allCreatures->at(creatureIndex), tempPop, totalPop);
			
			allCreatures->at(creatureIndex).mutateCreature(allCreatures);

			// thread1.join();
			// thread2.join();

			allCreatures->at(creatureIndex).population = (allCreatures->at(creatureIndex).population < 0) ? 0 : (allCreatures->at(creatureIndex).population);
		}
		saveCoordsV2(currentTime, &tableHeader, (allCreatures->size() - 1), allCreatures);
	}
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
				replace += "Time";
				for (int i = 0; i <= size; i++) {
					replace += ",Population " + std::to_string(i);
				}
				replace += "\n";
				fileOut << replace;
			}

			// The rest is just coppied
			else {
				fileOut << strTemp << std::endl;
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
		myFile << time;
		for (int i = 0; i <= size; i++) {
			myFile << "," << (allCreatures->at(i)).population;
		}
		myFile << std::endl;
	}
}


// Remade the deathChance calculator to include the crowding coefficient for the entire pop
void deathChanceCalulatorv2(int* population, Creature model, int tempPop, int totalPop) {
	// Check how many creatures die in the population, edit the population directly to cut down on execution speed
	for (int i = 0; i <= tempPop; i++) {

		// Added a crowding coefficient to make the population balance out depending on the population
		if (model.randomPercentCheck(model.getDeathChance() + (0.001 * totalPop))) {
			--(*population);
		}
	}

}


//-------------------------//
//Start of third simulation//
//-------------------------//

void simulationV3(std::vector<Creature>* allCreatures, int time, int food) {
	std::remove("GraphPlots.csv");

	// Set a header flag. We use this to tell saveCoordsV2 that we need to replace temp header with all population names
	bool tableHeader = false;
	// Save population at time = 0
	saveCoordsV2(0, &tableHeader, (allCreatures->size() - 1), allCreatures);

	// Itterate through time
	for (int currentTime = 1; currentTime <= time; currentTime++) {

		int tempFood{ food };

		// Here we itterate through our vector, applying the same calculations to all our populations
		for (int creatureIndex = 0; creatureIndex <= (allCreatures->size() - 1); creatureIndex++) {
			// Add spontaneous birth rate too population
			allCreatures->at(creatureIndex).population = allCreatures->at(creatureIndex).population + allCreatures->at(creatureIndex).getSpontaneousBirthRate();
			int tempPop = allCreatures->at(creatureIndex).population;

			// Attempted using threads here, seemed to slow the program down rather than speeding it up, I guess I had to join it too often to make use of the multi thread
			// std::thread thread1(replicationChanceCalulator, &(allCreatures->at(creatureIndex).population), allCreatures->at(creatureIndex), tempPop);
			// std::thread thread2(deathChanceCalulatorv2, &(allCreatures->at(creatureIndex).population), allCreatures->at(creatureIndex), tempPop, totalPop);

			foodReplicationAndDeath(&(allCreatures->at(creatureIndex).population), tempPop, &tempFood);

			allCreatures->at(creatureIndex).mutateCreature(allCreatures);

			// thread1.join();
			// thread2.join();

			allCreatures->at(creatureIndex).population = (allCreatures->at(creatureIndex).population < 0) ? 0 : (allCreatures->at(creatureIndex).population);
		}
		saveCoordsV2(currentTime, &tableHeader, (allCreatures->size() - 1), allCreatures);
	}
	tableHeader = true;
	saveCoordsV2(time, &tableHeader, (allCreatures->size() - 1), allCreatures);
}


void foodReplicationAndDeath(int* population, int tempPop, int *totalFood) {
	// Same as deathChanceCalculator, do maths on the population
	for (int i = 0; i <= tempPop; i++) {
		int foodEaten{ willCreatureEat(calculateChanceOfFood(*totalFood, tempPop)) };
		if (foodEaten == 2) {
			++(*population);
		}
		else if (foodEaten == 0) {
			--(*population);
		}
		*totalFood -= foodEaten;
	}
}
