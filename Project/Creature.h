#pragma once
class Creature {
private:
	double spontaneousBirthRate;
	double replicationChance;
	double deathChance;
public:
	Creature(int sbr, double rc, double dc);
	int getSpontaneousBirthRate();
	double getReplicationChance();
	double getDeathChance();
	bool randomPercentCheck(double percentage);

};