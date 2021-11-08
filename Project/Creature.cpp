#include "Creature.h"
#include <ctime>
#include <random>
#include <vector>
//Constructor

std::mt19937 rng(std::time(NULL));

// Constructor
Creature::Creature(int sbr, double rc, double dc, double sbrc, double mc, int sp) {
	population = sp;
	spontaneousBirthRate = sbr;
	replicationChance = rc;
	deathChance = dc;
	spontaneousBirthRateChance = sbrc;
	mutationChance = mc;
}

// Return private data fields
int Creature::getSpontaneousBirthRate() {
	return spontaneousBirthRate;
}

double Creature::getSpontaneousBirthRateChance() {
	return spontaneousBirthRateChance;
}

double Creature::getReplicationChance() {
	return replicationChance;
}

double Creature::getDeathChance() {
	return deathChance;
}

double Creature::getMutateChance() {
	return mutationChance;
}

// Random result based on percentage chance
bool Creature::randomPercentCheck(double percentage) {
	static const std::uniform_real_distribution<double> dist(0, 1);
	bool passed{ dist(rng) < percentage };
	return passed;
}

double Creature::maxMutateDouble(double fMin, double fMax){
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void Creature::mutateCreature(std::vector<Creature> *creatureList){
	if (randomPercentCheck(mutationChance) && population != 0) {
		// Use this to randomize which value to change
		int temp{ rand() % 3 };
		pushMutate(creatureList, temp);
	}
}


double Creature::mutationPosOrNeg(double chance, double minMut, double maxMut) {
	if (rand() % 2) {
		return (chance + maxMutateDouble(minMut, maxMut));
	}
	else {
		return (chance - maxMutateDouble(minMut, maxMut));
	}
}

void Creature::pushMutate(std::vector<Creature>* creatureList, int valueToChange) {
	double rc{ replicationChance };
	double dc{ deathChance };
	double sbrc{ spontaneousBirthRateChance };
	double mc{ mutationChance };
	switch (valueToChange) {
	case 0:
		rc = mutationPosOrNeg(rc, MINMUTATION, MAXMUTATION);
		if (rc < 0) {
			rc = 0;
		}
		else if (rc > 1) {
			rc = 1;
		}
		break;
	case 1:
		dc = mutationPosOrNeg(dc, MINMUTATION, MAXMUTATION);
		if (dc < 0) {
			dc = 0;
		}
		else if(dc > 1) {
			dc = 1;
		}
		break;
	case 2:
		sbrc = mutationPosOrNeg(sbrc, MINMUTATION, MAXMUTATION);
		if (sbrc < 0) {
			sbrc = 0;
		}
		else if (sbrc > 1) {
			sbrc = 1;
		}
		break;
	/*case 3:
		mc = mutationPosOrNeg(mutationChance, 0.00, 0.02);
		if (mc < 0) {
			mc = 0;
		}
		else if (mc > 1) {
			mc = 1;
		}
		break;*/
	}

	if (!(replicationChance == rc && deathChance == dc && spontaneousBirthRateChance == sbrc && mutationChance == mc)) {
		Creature mutated(spontaneousBirthRate, rc, dc, sbrc, mc, 10);
		creatureList->push_back(mutated);
	}
}