#include "CreatureV2.h"

CreatureV2::CreatureV2(int dr, int s, char cc) {
	creatureChar = cc;
	detectionRange = dr;
	speed = s;
}

void CreatureV2::setCoordinates(int x, int y) {
	coordinates.first = x;
	coordinates.second = y;
}

void CreatureV2::placeOnBoard(std::vector<std::vector<char>>* board) {
	int x;
	int y;
	bool placed;
	do {
		placed = false;
		x = rand() % board->size();
		y = rand() % board->size();

		if ((*board)[y][x] == ' ') {
			(*board)[y][x] = creatureChar;
			setCoordinates(x, y);
			placed = true;
		}
	} while (placed != true);
}