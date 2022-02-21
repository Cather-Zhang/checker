#pragma once

typedef struct Checker {
	bool isKing;
	bool isDead;
	int row;
	int col;
	int num;
}Checker;

class Checkers {

public:
	Checkers();
	virtual ~Checkers();
};

