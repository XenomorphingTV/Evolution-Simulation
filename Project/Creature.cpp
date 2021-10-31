#include "Creature.h"
#include <ctime>
#include <random>

std::mt19937 rng(std::time(NULL));

// Constructor
Creature::Creature(int sbr, double rc, double dc) {
	spontaneousBirthRate = sbr;
	replicationChance = rc;
	deathChance = dc;
}

// Return private data fields
int Creature::getSpontaneousBirthRate() {
	return spontaneousBirthRate;
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
