#pragma once
#include "Creature.h"

void basicSimulation(Creature model, int* population, int time);
void deathChanceCalulator(int* population, Creature model, int tempPop);

void replicationChanceCalulator(int* population, Creature model, int tempPop);
void spontaneousBirthChanceCalulator(int* population, Creature model, int tempPop);
void saveCoords(int time, int* population);
