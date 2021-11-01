#include "Creature.h"
#include <ctime>
#include <random>
//Constructor

std::mt19937 rng(std::time(NULL));

// Constructor
Creature::Creature(int sbr, double rc, double dc, double sbrc, double mc) {
	spontaneousBirthRate = sbr;
	replicationChance = rc;
	deathChance = dc;
	spontaneousBirthRateChance = sbrc;
	mutationChance = mc;
}
	
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

bool Creature::randomPercentCheck(double percentage) {
	static const std::uniform_real_distribution<double> dist(0, 1);
	bool passed{ dist(rng) < percentage };
	return passed;
}
