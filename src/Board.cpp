#include "Board.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;


Board::Board() {
	// TODO Auto-generated constructor stub
	cout << "Making a new board" << endl;
}

Board::~Board() {
	// TODO Auto-generated destructor stub
	cout << "Deleting a board" << endl;
}

void Board::init()
{
	int ncols = n;
	printf("In init with ncols = %d\n", ncols);
	for (int row = 0; row < ncols; row++)
	{
		for (int col = 0; col < ncols; col++)
		{
			*((edgesP)+(row * ncols) + col) = ' ';
		}
	}
}

void Board::setUnusable(int position)
{
	char* arrayBeginning = edgesP;
	*(arrayBeginning + position) = (char)178;
}

void Board::setUsable(int position)
{
	char* arrayBeginning = edgesP;
	*(arrayBeginning + position) = (char)176;
}

void Board::setChecker(int position, char p)
{
	char* arrayBeginning = edgesP;
	*(arrayBeginning + position) = p;
}

char Board::getValue(int row, int col)
{
	int ncols = n;
	char* arrayBeginning = edgesP;
	return *(arrayBeginning + (ncols * row) + col);
}

void Board::setN(int set)
{
	n = set;
}

void Board::setEdgesP(char* set)
{
	edgesP = set;
}

void Board::printBoard() {
	cout << "  0 1 2 3 4 5 6 7" << endl;
	for (int i = 0; i < n*n; i++) 
	{
		if (i % 8 == 0)
		{
			cout << i / 8 << " ";
		}
		cout << *(edgesP + i) << ' ';
		if (i % 8 == 7) {
			cout << endl;
		}
	}
	cout << "  A B C D E F G H" << endl;
	cout << endl;
} 

void Board::printCheckerPos(Checker** cpus, Checker** cpes)
{
	cout << "  0 1 2 3 4 5 6 7" << endl;
	for (int i = 0; i < n * n; i++)
	{
		if (i % 8 == 0)
		{
			cout << i / 8 << " ";
		}
		if ((*(edgesP + i) == 'K') || (*(edgesP + i) == 'P'))
		{
			cout << (char) (getCheckerByPos(cpus, i)->num + 65) << ' ';
		}
		else if ((*(edgesP + i) == 'p') || (*(edgesP + i) == 'k'))
		{
			cout << (char) (getCheckerByPos(cpes, i)->num + 97) << ' ';
		}
		else cout << *(edgesP + i) << ' ';
		if (i % 8 == 7) {
			cout << endl;
		}
	}
	cout << "  A B C D E F G H" << endl;
}

ofstream outFile("moveHistory.txt");

void Board::myTurn(Checker** cPUs, Checker** cPEs) 
{
	LinkedList* LL = new LinkedList();
	LLNode* jumpList = LL->makeEmptyLinkedList();
	LLNode* moveList = LL->makeEmptyLinkedList();

	Checker** aCheckerP = cPUs;

	for (int i = 0; i < (n / 2) * (n / 2 - 1); i++)
	{
		Checker* temp = *(aCheckerP + i);
		if (!(temp->isDead))
		{
			if (meCanJump(temp))
			{
				jumpList = LL->appendList(jumpList, genMyPossibleJump(temp, LL));
				cout << "Printing possible jump list for checker " << temp->num << endl;
				LL->printList(genMyPossibleJump(temp, LL));
			}
			else
			{
				moveList = LL->appendList(moveList, genMyPossibleMove(temp, LL));
				cout << "Printing possible move list for checker " << temp->num << endl;
				LL->printList(genMyPossibleMove(temp, LL));
			}
		}
	}

	LL->printJumpLL(jumpList);
	LL->printMoveLL(moveList);

	if (!(LL->isEmpty(jumpList)))
	{
		cout << "I can jump!" << endl;
		int size = LL->getLength(jumpList);
		int randIndex = rand() % size;
		LLNode* jumpP = LL->getMove(jumpList, randIndex);
		Checker* cp = getCheckerByNum(cPUs, jumpP->checkerNum);
		int newCol = jumpP->move % n;
		int newRow = (jumpP->move - newCol) / n;
		cout << "Checker " << (char)(cp->num + 65) << " jumped from row " << cp->row << ", col " << cp->col << ": " << (char)(cp->col + 65) << cp->row << endl << 
			"                   to row " << newRow << ", col " << newCol << ": " << (char)(newCol + 65) << newRow << endl;
		outFile << "Checker " << (char)(cp->num + 65) << " jumped from row " << cp->row << ", col " << cp->col << ": " << (char)(cp->col + 65) << cp->row << endl <<
			"                   to row " << newRow << ", col " << newCol << ": " << (char)(newCol + 65) << newRow << endl;
		meMove(jumpP->move, cp, cPEs);
	}
	else
	{
		int size = LL->getLength(moveList);
		int randIndex = rand() % size;
		LLNode* moveP = LL->getMove(moveList, randIndex);
		Checker* cp = getCheckerByNum(cPUs, moveP->checkerNum);
		int newCol = moveP->move % n;
		int newRow = (moveP->move - newCol) / n;
		cout << "Moving checker " << (char)(cp->num + 65) << " from row " << cp->row << ", col " << cp->col << ": " << (char)(cp->col + 65) << cp->row << endl <<
			"                   to row " << newRow << ", col " << newCol << ": " << (char)(newCol + 65) << newRow << endl;
		meMove(moveP->move, cp, cPEs);
	}
	delete(LL);
}

void Board::enemyTurnFirst(Checker** cPUs, Checker** cPEs) {
	int row;
	char colLetter;
	char letter;
	while (true) {
		cout << "Please type letter of the piece: " << endl;
		cin >> letter;
		if (letter >= 'a' && letter <= 'l')
			break;
		else
			cout << "Please select a legit checker" << endl;
	}
	int num = (int)letter - 97;
	while (true) {
		while (true) {
			cout << "Please type enemy's move for col: " << endl;
			cin >> colLetter;
			if (colLetter >= 'A' && colLetter <= 'H')
				break;
			else
				cout << "Invalid entry for column letter." << endl;
		}
		while (true) {
			cout << "Please type enemy's move for row: " << endl;
			cin >> row;
			if (row >= 0 && row <= 9)
				break;
			else
				cout << "Invalid entry for row number." << endl;
		}
		int a = -1;
		while (true) {
			cout << "Is this move correct?" << endl;
			cin >> a;
			if (a == 0 || a == 1)
				break;
		}		
		if (a)
			break;
		else
			cout << "Please type in another move:" << endl;
	}
	int col = (int)colLetter - 65;
	int oriRow = getCheckerByNum(cPEs, num)->row;
	int oriCol = getCheckerByNum(cPEs, num)->col;
	cout << "Enemy " << letter << " moved from row " << oriRow << ", col " << oriCol << ": " << (char)(oriCol + 65) << oriRow << endl <<
		"                to row " << row << ", col " << col << ": " << (char)(col + 65) << row << endl;
	outFile << "Enemy " << letter << " moved from row " << oriRow << ", col " << oriCol << ": " << (char)(oriCol + 65) << oriRow << endl <<
		"                to row " << row << ", col " << col << ": " << (char)(col + 65) << row << endl;
	enemyMove(row, col, getCheckerByNum(cPEs, num), cPUs);
}
void Board::enemyTurn(Checker** cPUs, Checker** cPEs) {
	enemyTurnFirst(cPUs, cPEs);
	int a = 1;
	while (a) {
		cout << "Can your enemy move again?" << endl;
		cin >> a;
		if (a)
		{
			enemyTurnFirst(cPUs, cPEs);
		}
	}
}

//tested
bool Board::meCanJump(Checker* cP) {
	int row = cP->row;
	int col = cP->col;
	int pos = row * n + col;

	bool rightF = getValue(cP->row - 2, cP->col + 2) == (char)176 && 
		                //if the space I am jumping too is available
		(getValue(cP->row - 1, cP->col + 1) == 'p') || (getValue(cP->row - 1, cP->col + 1) == 'k'); 
	                        //if the space I jump over is enemy
	bool leftF = getValue(cP->row - 2, cP->col - 2) == (char)176 &&
		(getValue(cP->row - 1, cP->col - 1) == 'p') || (getValue(cP->row - 1, cP->col - 1) == 'k');
	bool rightB = getValue(cP->row + 2, cP->col + 2) == (char)176 &&
		(getValue(cP->row + 1, cP->col + 1) == 'p') || (getValue(cP->row + 1, cP->col + 1) == 'k');
	bool leftB = getValue(cP->row + 2, cP->col - 2) == (char)176 &&
		(getValue(cP->row + 1, cP->col - 1) == 'p') || (getValue(cP->row + 1, cP->col - 1) == 'k');

	if (cP->isKing)
	{
		return (rightF || rightB || leftF || leftB);
	}
	else
	{
		return (rightF || leftF);
	}
} 

//tested
LLNode* Board::genMyPossibleJump(Checker* cP, LinkedList* LL) {
	bool rightF = (getValue(cP->row - 1, cP->col + 1) == 'p' || getValue(cP->row - 1, cP->col + 1) == 'k') &&
		getValue(cP->row - 2, cP->col + 2) == (char)176;
	bool leftF =  (getValue(cP->row - 1, cP->col - 1) == 'p' || getValue(cP->row - 1, cP->col - 1) == 'k') &&
		getValue(cP->row - 2, cP->col - 2) == (char)176;
	bool rightB = (getValue(cP->row + 1, cP->col + 1) == 'p' || getValue(cP->row + 1, cP->col + 1) == 'k') &&
		getValue(cP->row + 2, cP->col + 2) == (char)176;
	bool leftB = (getValue(cP->row + 1, cP->col - 1) == 'p' || getValue(cP->row + 1, cP->col - 1) == 'k') &&
		getValue(cP->row + 2, cP->col - 2) == (char)176;

	LLNode* jumpLL = LL->makeEmptyLinkedList();

	int col = cP->col;
	int row = cP->row;

	int pos = row * n + col;
	int rF = pos - 2 * (n - 1);
	int lF = pos - 2 * (n + 1);
	int rB = pos + 2 * (n + 1);
	int lB = pos + 2 * (n - 1);

	if (cP->isKing)
	{
		if (rightF) 
		{
			LL->saveMove(jumpLL, rF, cP->num);
		}
		if (rightB)
		{
			LL->saveMove(jumpLL, rB, cP->num);
		}
		if (leftF)
		{
			LL->saveMove(jumpLL, lF, cP->num);
		}
		if (leftB)
		{
			LL->saveMove(jumpLL, lB, cP->num);
		}
	}
	else
	{
		if (rightF)
		{
			LL->saveMove(jumpLL, rF, cP->num);
		}
		if (leftF)
		{
			LL->saveMove(jumpLL, lF, cP->num);
		}
	}
	return jumpLL;
} 

//tested
LLNode* Board::genMyPossibleMove(Checker* cP, LinkedList* LL) {
	bool rightF = getValue(cP->row - 1, cP->col + 1) == (char)176;
	bool leftF = getValue(cP->row - 1, cP->col - 1) == (char)176;
	bool rightB = getValue(cP->row + 1, cP->col + 1) == (char)176;
	bool leftB = getValue(cP->row + 1, cP->col - 1) == (char)176;

	LLNode* moveLL = LL->makeEmptyLinkedList();

	int pos = cP->row * n + cP->col;
	int rF = pos - (n - 1);
	int lF = pos - (n + 1);
	int rB = pos + (n + 1);
	int lB = pos + (n - 1);

	if (cP->isKing)
	{
		if (rightF)
		{
			LL->saveMove(moveLL, rF, cP->num);
		}
		if (rightB)
		{
			LL->saveMove(moveLL, rB, cP->num);
		}
		if (leftF)
		{
			LL->saveMove(moveLL, lF, cP->num);
		}
		if (leftB)
		{
			LL->saveMove(moveLL, lB, cP->num);
		}
	}
	else
	{
		if (rightF)
		{
			LL->saveMove(moveLL, rF, cP->num);
		}
		if (leftF)
		{
			LL->saveMove(moveLL, lF, cP->num);
		}
	}
	return moveLL;
} 

//tested
void Board::meMove(int pos, Checker* cP, Checker** cPE) {
	int col = pos % n;
	int row = (pos - col) / n;
	int oldPos = cP->row * n + cP->col;
	setUsable(oldPos);

	cP->row = row;
	cP->col = col;
	if (cP->row == 0) 
	{
		cP->isKing = true;
	}

	if (cP->isKing)
	{
		setChecker(pos, 'K');
	}
	else
	{
		setChecker(pos, 'P');
	}

	if (abs(pos - oldPos) > 10)
	{
		int cPos = (pos + oldPos) / 2;
		
		cout << "Yay! You just killed enemy checker " << (char)(getCheckerByPos(cPE, cPos)->num + 97) << endl;
		outFile << "And killed enemy checker " << (char)(getCheckerByPos(cPE, cPos)->num + 97) << endl;

		getCheckerByPos(cPE, cPos)->isDead = true;
		setUsable(cPos);
	}
}

//tested
void Board::enemyMove(int row, int col, Checker* cP, Checker** cPU) {
	int pos = row * n + col;
	int oldPos = cP->row * n + cP->col;

	setUsable(oldPos);

	cP->row = row;
	cP->col = col;

	if (cP->row == n - 1) 
	{
		cP->isKing = true;
	}

	if (cP->isKing)
	{
		setChecker(pos, 'k');
	}
	else
	{
		setChecker(pos, 'p');
	}

	if (abs(pos - oldPos) > 10)
	{
		int cPos = (pos + oldPos) / 2;
		
		cout << "Oh no! Enemy just killed you checker " << (char)(getCheckerByPos(cPU, cPos)->num + 65) << endl;
		outFile << "And killed your checker " << (char)(getCheckerByPos(cPU, cPos)->num + 65) << endl;
		getCheckerByPos(cPU, cPos)->isDead = true;
		setUsable(cPos);
	}
}

//tested
Checker* Board::getCheckerByPos(Checker** cPs, int pos)
{
	Checker** aCheckerP = cPs;

	for (int i = 0; i < (n / 2) * (n / 2 - 1); i++)
	{
		Checker* temp = *(aCheckerP + i);
		if (!(temp->isDead))
		{
			int checkerPosition = temp->col + temp->row * 8;
			if (checkerPosition == pos)
			{
				return temp;
			}
		}
	}
	cout << "Checker not found" << endl;
	return nullptr;
} 

//tested
Checker* Board::getCheckerByNum(Checker** cPs, int num)
{
	Checker** aCheckerP = cPs;

	for (int i = 0; i < (n / 2) * (n / 2 - 1); i++)
	{
		Checker* temp = *(aCheckerP + i); 
		if (!(temp->isDead))
		{
			int checkerNumber = temp->num;
			if (num == checkerNumber)
			{
				return temp;
			}
		}
	}
	cout << "Can not find the checker by number :(" << endl;
	return nullptr;
} //tested