#pragma once
#include "Board.h"
#include "Checkers.h"
#include "Production.h"

class Tests {
public:
	Tests();
	virtual ~Tests();
	bool tests();

	bool testReadFile();
	bool testMeCanJump();
	bool testIsEmpty();
	bool testGetMove();
	bool testGetLength();
	bool testGenJumpList();
	bool testGenMoveList();
	bool testGetChecker();
	bool testAppendList();
	bool testMove();
	bool testIsWinner();
};

