#pragma once
#include "Creature.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

double calculateChanceOfFood(int totalFood, int totalPopNotEaten);
int willCreatureEat(double chanceToFindFood);
std::vector<std::vector<char>> makeBoard(int length);
void placeFoodOnBoard(std::vector<std::vector<char>>* board, int totalFood);