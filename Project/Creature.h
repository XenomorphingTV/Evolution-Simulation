#pragma once
#include <vector>

// Max and min value that the mutation can do
constexpr double MINMUTATION = 0.01;
constexpr double MAXMUTATION = 0.20;

class Creature {
private:
	int spontaneousBirthRate;
	double replicationChance;
	double deathChance;
	double spontaneousBirthRateChance;
	double mutationChance;


public:
	int population{ 0 };
	Creature(int sbr, double rc, double dc, double sbrc, double mc, int sp);
	int getSpontaneousBirthRate();
	double getReplicationChance();
	double getDeathChance();
	double getSpontaneousBirthRateChance();
	double getMutateChance();
	bool randomPercentCheck(double percentage);
	double maxMutateDouble(double fMin, double fMax);
	void mutateCreature(std::vector<Creature> *creatureList);
	double mutationPosOrNeg(double chance, double minMut, double maxMut);
	void pushMutate(std::vector<Creature>* creatureList, int valueToChange);
};