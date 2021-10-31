#include "Creature.h"
#include <ctime>
#include <random>
//Constructor

std::mt19937 rng(std::time(NULL));

Creature::Creature(int sbr, double rc, double dc) {
	spontaneousBirthRate = sbr;
	replicationChance = rc;
	deathChance = dc;
}
	
int Creature::getSpontaneousBirthRate() {
	return spontaneousBirthRate;
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
