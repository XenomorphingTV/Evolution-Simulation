#pragma once
#include "Creature.h"
#include <vector>

void basicSimulation(Creature model, int* population, int time);
void deathChanceCalulator(int* population, Creature model, int tempPop);

void replicationChanceCalulator(int* population, Creature model, int tempPop);
void spontaneousBirthChanceCalulator(int* population, Creature model, int tempPop);
void saveCoords(int time, int* population);


void simulationV2(std::vector<Creature>* allCreatures, int time);
void saveCoordsV2(int time, bool* header, int size, std::vector<Creature>* allCreatures);