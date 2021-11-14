#include "Menu.h"

void clearScreen()
{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void creatureMenu(std::vector<CreatureV2>* creatureList) {
	int detectionRange;
	int speed;
	int population;
	int count{ 1 };
	char creatureChar{ 'a' };
	bool finished = false;
	char yesOrNo;

	while (finished != true) {
		try {
			std::cout << "Creature Creation " << count << "\n";
			std::cout << "-------------------" << "\n\n";

			std::cout << "Enter the distance in grids, how far it can detect food: ";
			std::cin >> detectionRange;
			if (std::cin.fail()) {
				throw "Error Input";
			}

			std::cout << "Enter the speed the creature can move, deciding the order of who moves first: ";
			std::cin >> speed;
			if (std::cin.fail()) {
				throw "Error Input";
				std::cin.clear();
			}

			std::cout << "How big is the population of this creature: ";
			std::cin >> population;
			if (std::cin.fail()) {
				throw "Error Input";
			}

			std::cout << "Is this the creature you want to input? (y/n): ";
			std::cin >> yesOrNo;
			if (std::cin.fail()) {
				throw "Error Input";
			}
			if (yesOrNo == 'n') {
				clearScreen();
				continue;
			}
			else if(yesOrNo != 'n' && yesOrNo != 'y') {
				throw "Please input y or n.";
			}
			
			CreatureV2 userCreature(detectionRange, speed, creatureChar);
			pushCreature(creatureList, userCreature, population);

			std::cout << "Do you want to make more creatures?\nIts recomended that you keep the amount low due to the time it would take to complete the simulation.\n(y/n): ";
			std::cin >> yesOrNo;
			if (std::cin.fail()) {
				throw "Error Input";
			}
			else if (yesOrNo != 'n' && yesOrNo != 'y') {
				throw "Please input y or n.";
			}

			if (yesOrNo == 'n') {
				finished = true;
				clearScreen();
			}

			else if (yesOrNo == 'y') {
				count++;
				if (creatureChar == 'z') {
					std::cout << "Currently the limit for creatures is 26\n";
					clearScreen();
					break;
				}
				creatureChar++;
				clearScreen();
			}
		}
		catch (const char* error){
			clearScreen();
			std::cout << error << "\n\n";
			std::cin.clear();
			std::cin.ignore();
			continue;
		}

	}
}

void pushCreature(std::vector<CreatureV2>* creatureList, CreatureV2 userCreature, int population) {
	for (int i = 0; i < population; i++) {
		creatureList->push_back(userCreature);
	}
}

void mainMenu(std::vector<CreatureV2>* creatureList) {
	creatureMenu(creatureList);
}
