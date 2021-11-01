#pragma once
class Creature {
private:
	int spontaneousBirthRate;
	double replicationChance;
	double deathChance;
	double spontaneousBirthRateChance;
	double mutationChance;

public:
	Creature(int sbr, double rc, double dc, double sbrc, double mc);
	int getSpontaneousBirthRate();
	double getReplicationChance();
	double getDeathChance();
	double getSpontaneousBirthRateChance();
	bool randomPercentCheck(double percentage);

};