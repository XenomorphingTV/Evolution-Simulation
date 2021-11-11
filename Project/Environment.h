#pragma once
#include "Creature.h"
#include <iostream>
#include <random>
#include <ctime>

double calculateChanceOfFood(int totalFood, int totalPopNotEaten);
int willCreatureEat(double chanceToFindFood);