#include "Environment.h"


std::mt19937 rng2(std::time(NULL));

double calculateChanceOfFood(int totalFood, int totalPopNotEaten) {
	double chance((double)totalFood / (double)totalPopNotEaten);
	// return (((double)totalFood / (double)totalPopNotEaten <= 1) ? (double)totalFood / (double)totalPopNotEaten : 1);
	if (chance - 0.3 < 0) {
		return 0;
	}
	else if (chance - 0.3 > 1){
		return 0.7;
	}
	else {
		return (chance - 0.3);
	}
}

int willCreatureEat(double chanceToFindFood) {
	static const std::uniform_real_distribution<double> dist(0, 1);
	int foodEaten{ 0 };
	bool passed{false};
	for (int i = 0; i <= 1; i++) {
		passed = false;
		passed = dist(rng2) < chanceToFindFood;
		if (passed) {
			foodEaten++;
		}
	}

	return foodEaten;
}