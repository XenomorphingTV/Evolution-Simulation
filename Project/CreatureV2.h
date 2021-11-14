#pragma once
#include <utility>
#include <vector>
#include <random>

class CreatureV2
{
private:
	int detectionRange;
	int speed;

public:
	std::pair<int, int> coordinates;
	char creatureChar;
	CreatureV2(int dr, int s, char cc);
	void setCoordinates(int x, int y);
	void placeOnBoard(std::vector<std::vector<char>>* board);
};

