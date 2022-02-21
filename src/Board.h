#pragma once
#include "Checkers.h"
#include "LinkedList.h"

class Board {
public:
	Board();
	virtual ~Board();

	void setUnusable(int position);
	void setUsable(int position);
	void setChecker(int position, char p);
	char getValue(int row, int col); //Returns binary value on adjMatrix given a row and a col
	void init();
	void setN(int set);
	void setEdgesP(char* set);
	void printBoard();
	void printCheckerPos(Checker**, Checker**);

	void meMove(int pos, Checker* cP, Checker** cPEs);
	void enemyMove(int row, int col, Checker* cP, Checker** cPUs);
	void myTurn(Checker** cPUs, Checker** CPEs);
	void enemyTurn(Checker** CPUs, Checker**);
	void enemyTurnFirst(Checker** CPUs, Checker**);
	bool meCanJump(Checker* aCheckerP);
	LLNode* genMyPossibleMove(Checker* cP, LinkedList* LL);
	LLNode* genMyPossibleJump(Checker* cP, LinkedList* LL);
	Checker* getCheckerByPos(Checker**, int);
	Checker* getCheckerByNum(Checker**, int);

private:
	int n;
	char* edgesP;
};

