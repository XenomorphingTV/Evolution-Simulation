#pragma once
#include "CreatureV2.h"
#include <vector>
#include <iostream>
#include <Windows.h>

void clearScreen();
void creatureMenu(std::vector<CreatureV2>* creatureList);
void pushCreature(std::vector<CreatureV2>* creatureList, CreatureV2 userCreature, int population);
void mainMenu(std::vector<CreatureV2>* creatureList);