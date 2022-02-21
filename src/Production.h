#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>//strncpy
#include <stdlib.h>//strtol
#include "Checkers.h"
#include "Board.h"
#define FILENAMELENGTHALLOWANCE 50

class Production {
public:
	Production();
	virtual ~Production();
	bool prod(int argc, char* argv[]);
	bool readFile(char*, int*, Board*, Checker**, Checker**);
	void isWinner(Checker** cpus, Checker** cpes);
};
