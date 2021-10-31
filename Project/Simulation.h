#pragma once
#include "Creature.h"

void basicSimulation(Creature model, int population, int time);

int deathChanceCalulator(int population, Creature model);

int replicationChanceCalulator(int population, Creature model);

void saveCoords(int time, int population);
