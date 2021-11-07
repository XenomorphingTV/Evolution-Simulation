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
	if (randomPercentCheck(mutationChance)) {
		switch (rand() % 4) {
		case 0:
		{
			Creature mutated0(spontaneousBirthRate, replicationChance, deathChance, pushNewMutation(spontaneousBirthRateChance), mutationChance, 1);
			creatureList->push_back(mutated0);
		}
			break;
		case 1:
		{
			Creature mutated1(spontaneousBirthRate, pushNewMutation(replicationChance), deathChance, spontaneousBirthRateChance, mutationChance, 1);
			creatureList->push_back(mutated1);
		}
			break;
		case 2:
		{
			Creature mutated2(spontaneousBirthRate, replicationChance, pushNewMutation(deathChance), spontaneousBirthRateChance, mutationChance, 1);
			creatureList->push_back(mutated2);
		}
			break;
		case 3:
		{
			Creature mutated3(spontaneousBirthRate, replicationChance, deathChance, spontaneousBirthRateChance, pushNewMutation(mutationChance), 1);
			creatureList->push_back(mutated3);
		}
			break;
		}
	}
}

double Creature::pushNewMutation(double chance) {
	if (rand() % 2) {
		return (chance + maxMutateDouble(MINMUTATION, MAXMUTATION));
	}
	else {
		return (chance - maxMutateDouble(MINMUTATION, MAXMUTATION));
	}
}
