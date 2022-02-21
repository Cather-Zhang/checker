#include "Tests.h"
#include<iostream>
using namespace std;

Tests::Tests() {
	// TODO Auto-generated constructor stub
	cout << "Making a new test" << endl;
}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
	cout << "Deleting a test" << endl;
}

bool Tests::tests() {
	bool ok1 = testReadFile();
	bool ok2 = testMeCanJump();
	bool ok3 = testIsEmpty();
	bool ok4 = testGetChecker();
	bool ok5 = testGetLength();
	bool ok6 = testGenJumpList();
	bool ok7 = testGetMove();
	bool ok8 = testGenMoveList();
	bool ok9 = testAppendList();
	bool ok10 = testMove();
	bool ok11 = testIsWinner();
	return ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7 && ok8 && ok9 && ok10 && ok11;
}

bool Tests::testReadFile()
{
	cout << "starting testReadFile" << endl;
	bool ok = false;
	//the file tells how many rows there are
	int answer = -1;
	int rightAnswer = 8;

	Board* bP = new Board();

	Checker* theCheckerEPs[12];//addresses for 12 enemy checkers
	Checker* theCheckerUPs[12];//addresses for 12 our checkers

	Production* pP = new Production();

	ok = pP->readFile((char*)"checkersConfig.txt", &answer, bP, theCheckerEPs, theCheckerUPs); //read the file
	if (ok)
	{
		if (answer != rightAnswer)
		{
			cout << "test failed on number of rooms" << endl;
		}

	}
	for (int i = 0; i < answer; i++)
	{
		for (int j = 0; j < answer; j++)
		{
			cout << bP->getValue(i, j) << " ";

		}
		cout << endl;
	}
	cout << "The board" << endl;
	bP->printBoard();

	int ok2 = -1;
	cout << "Is this correct? Please type 0 for false and 1 for true:" << endl;
	cin >> ok2;

	if (ok && (bool)ok2) {
		puts("testReadFile passed!");
	}
	else
	{
		puts("testReadFile did not pass.");
	}
	delete(bP);
	delete(pP);
	return ok;
}

bool Tests::testMeCanJump() {
	Board* bP = new Board();
	bP->setN(8);
	bP->setEdgesP((char*)malloc(8 * 8 * sizeof(char)));
	bP->init();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j % 2) % 2 == 0)
			{
				bP->setUnusable(i * 8 + j);
			}
			else bP->setUsable(i * 8 + j);
		}
	}

	Checker* cP0 = (Checker*)malloc(sizeof(Checker));
	Checker* cP1 = (Checker*)malloc(sizeof(Checker));
	Checker* cP2 = (Checker*)malloc(sizeof(Checker));
	Checker* cP3 = (Checker*)malloc(sizeof(Checker));
	Checker* cP4 = (Checker*)malloc(sizeof(Checker));
	Checker* cP5 = (Checker*)malloc(sizeof(Checker));
	Checker* cP6 = (Checker*)malloc(sizeof(Checker));

	cP0->num = 0; cP0->row = 7; cP0->col = 0; cP0->isKing = false;
	cP1->num = 1; cP1->row = 6; cP1->col = 1; cP1->isKing = false;
	cP2->num = 2; cP2->row = 7; cP2->col = 6; cP2->isKing = false;
	cP3->num = 3; cP3->row = 6; cP3->col = 5; cP3->isKing = true;
	cP4->num = 4; cP4->row = 5; cP4->col = 6; cP4->isKing = false;
	cP5->num = 5; cP5->row = 4; cP5->col = 5; cP5->isKing = true;
	cP6->num = 6; cP6->row = 6; cP6->col = 5; cP6->isKing = false;


	bP->setChecker(56, 'P'); //0
	bP->setChecker(49, 'p'); //1  

	bP->setChecker(62, 'P'); //2 
	bP->setChecker(53, 'k'); //3

	bP->setChecker(46, 'p'); //4
	bP->setChecker(37, 'K'); //5

	bP->printBoard();

	bool ok1 = (bP->meCanJump(cP0));
	if (ok1) {
		cout << "meCanJump 1 passed!" << endl;
	}
	bool ok2 = bP->meCanJump(cP2);
	if (ok2) {
		cout << "meCanJump 2 passed!" << endl;
	}
	bool ok3 = bP->meCanJump(cP5);
	if (ok3) {
		cout << "meCanJump 3 passed!" << endl;
	}
	else
	{
		cout << "meCanJump 3 did not pass!" << endl;
	}
	
	bool ok = ok1 && ok2 && ok3;
	delete(bP);
	return ok;
}

bool Tests::testIsEmpty() {
	LinkedList* LL = new LinkedList();
	LLNode* LL1 = LL->makeEmptyLinkedList();
	LLNode* LL2 = LL->makeEmptyLinkedList();
	LL->saveMove(LL2, 1,0);
	bool ok1 = LL->isEmpty(LL1);
	bool ok2 = !(LL->isEmpty(LL2));
	bool ok = ok1 && ok2;
	if (ok)
	{
		cout << "TestIsEmpty passed!" << endl;
	}
	else
		cout << "TestIsEmpty did not pass." << endl;
	delete(LL);
	return ok;
}

bool Tests::testGetMove()
{
	LinkedList* LL = new LinkedList();
	LLNode* lp1 = LL->makeEmptyLinkedList();
	LLNode* lp2 = LL->makeEmptyLinkedList();
	LL->saveMove(lp2, 0, 0);
	LL->saveMove(lp2, 20, 0);
	LL->saveMove(lp2, 3, 0);
	LL->saveMove(lp2, 54, 0);

	bool ok1 = LL->getMove(lp1, 2) == nullptr;
	bool ok2 = LL->getMove(lp2, 0)->move == 0;
	bool ok3 = LL->getMove(lp2, 1)->move == 20;
	bool ok4 = LL->getMove(lp2, 2)->move == 3;
	bool ok5 = LL->getMove(lp2, 3)->move == 54;

	bool ok = ok1 && ok2 && ok3 && ok4 && ok5;
	if (ok) 
	{
		cout << "TestGetMove passed!" << endl;
	}
	else
	{
		cout << "TestGetMove did not pass" << endl;
	}
	delete(LL);
	return ok;
}

bool Tests::testGetLength() {
	LinkedList* LL = new LinkedList();
	LLNode* lp1 = LL->makeEmptyLinkedList();
	LLNode* lp2 = LL->makeEmptyLinkedList();
	LL->saveMove(lp2, 0, 0);
	LL->saveMove(lp2, 20, 0);
	LL->saveMove(lp2, 3, 0);
	LL->saveMove(lp2, 54, 0);

	bool ok1 = LL->getLength(lp1) == 0;
	bool ok2 = LL->getLength(lp2) == 4;

	bool ok = ok1 && ok2;
	if (ok)
	{
		cout << "TestGetLength passed!" << endl;
	}
	else
	{
		cout << "TestGetLength did not pass" << endl;
	}
	delete(LL);
	return ok;
}

bool Tests::testGenJumpList()
{
	int nrows = -1;
	Board* bP = new (Board);
	Production* pP = new Production();

	Checker* cPUs[12];
	Checker* cPEs[12];

	cout << "Before read file" << endl;
	bool answer = pP->readFile((char*)"testGenJump.txt", &nrows, bP, cPUs, cPEs); //read the file
	cout << "Back from read file" << endl;
	bP->printBoard();
	bP->printCheckerPos(cPUs, cPEs);

	LinkedList* LL = new LinkedList();

	LLNode* LL1 = bP->genMyPossibleJump(*(cPUs + 4), LL);
	bool ok1 = LL->getLength(LL1) == 2;
	if (ok1)
	{
		cout << "Test genjump 1 passed!" << endl;
	}
	LLNode* LL2 = bP->genMyPossibleJump(*(cPUs + 2), LL);
	bool ok2 = LL2->move == 28;
	if (ok2)
	{
		cout << "Test genjump 2 passed!" << endl;
	}
	LLNode* LL3 = bP->genMyPossibleJump(*(cPUs + 1), LL);
	bool ok3 = LL->isEmpty(LL3);
	if (ok3)
	{
		cout << "Test genjump 3 passed!" << endl;
	}
	LLNode* LL4 = bP->genMyPossibleJump(*(cPUs + 3), LL);
	bool ok4 = LL->getLength(LL4) == 2;
	if (ok4)
	{
		cout << "Test genjump 4 passed!" << endl;
	}
	LLNode* LL5 = bP->genMyPossibleJump(*cPUs, LL);
	bool ok5 = LL->isEmpty(LL5);
	if (ok5)
	{
		cout << "Test genjump 5 passed!" << endl;
	}
	bool ok = ok1 && ok2 && ok3 && ok4 && ok5;
	if (ok)
	{
		cout << "Test genjump all passed!" << endl;
	}
	else
	{
		cout << "Not all Test genjump passed." << endl;
	}
	delete(bP);
	delete(pP);
	delete(LL);
	return true;

}

bool Tests::testGetChecker() {
	int nrows = -1;
	Board* bP = new (Board);
	Production* pP = new Production();

	Checker* cPUs[12];
	Checker* cPEs[12];

	cout << "Before read file" << endl;
	bool answer = pP->readFile((char*)"testGenJump.txt", &nrows, bP, cPUs, cPEs); //read the file
	cout << "Back from read file" << endl;

	bool ok1 = bP->getCheckerByPos(cPEs, 3)->num == 0;
	if (ok1)
	{
		cout << "test get checker by pos 1 passed!" << endl;
	}
	
	bool ok2 = bP->getCheckerByPos(cPEs, 21)->num == 6;
	if (ok2)
	{
		cout << "test get checker by pos 2 passed!" << endl;
	}
	bool ok3 = bP->getCheckerByPos(cPUs, 46)->num == 4;
	if (ok3)
	{
		cout << "test get checker by pos 3 passed!" << endl;
	}
	bool ok4 = bP->getCheckerByPos(cPUs, 62)->num == 8;
	if (ok4)
	{
		cout << "test get checker by pos 4 passed!" << endl;
	}
	
	bool okpos = ok1 && ok2 && ok3 && ok4;
	if (okpos)
	{
		cout << "Test get Checker By Position passed!" << endl;
	}

	bool ok5 = bP->getCheckerByNum(cPUs, 8)->col + bP->getCheckerByNum(cPUs, 8)->row * 8 == 62;
	if (ok5)
	{
		cout << "test get checker by num 1 passed!" << endl;
	}
	bool ok6 = bP->getCheckerByNum(cPUs, 4)->col + bP->getCheckerByNum(cPUs, 4)->row * 8 == 46;
	if (ok6)
	{
		cout << "test get checker by num 2 passed!" << endl;
	}
	bool ok7 = bP->getCheckerByNum(cPEs, 6)->col + bP->getCheckerByNum(cPEs, 6)->row * 8 == 21;
	if (ok7)
	{
		cout << "test get checker by num 3 passed!" << endl;
	}

	bool oknum = ok5 && ok6 && ok7;
	if (oknum)
	{
		cout << "Test get Checker By Number passed!" << endl;
	}

	bool ok = oknum && okpos;
	if (ok) 
	{
		cout << "All tests get Checker passed!" << endl;
	}
	else
	{
		cout << "Not all tests get Checker passed." << endl;
	}
	delete(bP);
	delete(pP);
	return ok;
}

bool Tests::testGenMoveList()
{
	int nrows = -1;
	Board* bP = new (Board);
	Production* pP = new Production();

	Checker* cPUs[12];
	Checker* cPEs[12];

	cout << "Before read file" << endl;
	bool answer = pP->readFile((char*)"testGenMove.txt", &nrows, bP, cPUs, cPEs); //read the file
	cout << "Back from read file" << endl;
	bP->printBoard();
	bP->printCheckerPos(cPUs, cPEs);

	LinkedList* LL = new LinkedList();

	LLNode* LL1 = bP->genMyPossibleMove(*cPUs, LL);
	bool ok1 = LL->getLength(LL1) == 3;
	if (ok1)
	{
		cout << "Test generate move list 1 passed!" << endl;
	}

	LLNode* LL2 = bP->genMyPossibleMove(*(cPUs + 4), LL);
	bool ok2 = LL2->move == 39;
	if (ok2)
	{
		cout << "Test generate move list 2 passed!" << endl;
	}

	LLNode* LL3 = bP->genMyPossibleMove(*(cPUs + 3), LL);
	bool ok3 = LL3->move == 35;
	if (ok3)
	{
		cout << "Test generate move list 3 passed!" << endl;
	}

	LLNode* LL4 = bP->genMyPossibleMove(*(cPUs + 2), LL);
	bool ok4 = LL->getLength(LL4) == 2;
	if (ok4)
	{
		cout << "Test generate move list 4 passed!" << endl;
	}

	LLNode* LL5 = bP->genMyPossibleMove(*(cPUs + 5), LL);
	bool ok5 = LL5->move == 56;
	if (ok5)
	{
		cout << "Test generate move list 5 passed!" << endl;
	}

	bool ok = ok1 && ok2 && ok3 && ok4 && ok5;
	if (ok)
	{
		cout << "Test generate move list all passed!" << endl;
	}
	else
	{
		cout << "Not all test generate move list passed." << endl;
	}
	delete(bP);
	delete(pP);
	delete(LL);
	return ok;
}

bool Tests::testAppendList() {
	LinkedList* LL = new LinkedList();
	LLNode* lp1 = LL->makeEmptyLinkedList();
	LLNode* lp2 = LL->makeEmptyLinkedList();
	LLNode* lp3 = LL->makeEmptyLinkedList();
	LL->saveMove(lp1, 0, 0);
	LL->saveMove(lp1, 20, 0);
	LL->saveMove(lp1, 3, 0);
	LL->saveMove(lp1, 54, 0);
	
	LL->saveMove(lp2, 0, 0);
	LL->saveMove(lp2, 20, 0);
	LL->saveMove(lp2, 3, 0);
	LL->saveMove(lp2, 54, 0);

	bool ok1 = LL->getLength(LL->appendList(lp1, lp2)) == 8;

	bool ok2 = LL->getLength(LL->appendList(lp3, lp2)) == 4;

	bool ok3 = LL->getLength(LL->appendList(lp2, lp3)) == 4;

	bool ok = ok1 && ok2 && ok3;

	if (ok)
	{
		cout << "Test append list passed!" << endl;
	}
	else
	{
		cout << "Test append list did not pass." << endl;
	}
	delete(LL);
	return ok;
}

bool Tests::testMove() 
{
	int nrows = -1;
	Board* bP = new (Board);
	Production* pP = new Production();

	Checker* cPUs[12];
	Checker* cPEs[12];

	cout << "Before read file" << endl;
	bool answer = pP->readFile((char*)"testMove.txt", &nrows, bP, cPUs, cPEs); //read the file
	cout << "Back from read file" << endl;
	bP->printBoard();
	bP->printCheckerPos(cPUs, cPEs);

	LinkedList* LL = new LinkedList();

	Checker* D = bP->getCheckerByPos(cPUs, 42);
	Checker* i = bP->getCheckerByPos(cPEs, 35);
	bP->meMove(28, D, cPEs);
	bool ok1 = D->row == 3 && D->col == 4 && i->isDead;

	if (ok1)
	{
		cout << "Test me move passed!" << endl;
	}

	Checker* d = bP->getCheckerByPos(cPEs, 10);
	Checker* A = bP->getCheckerByPos(cPUs, 17);
	bP->enemyMove(3, 0, d, cPUs);
	bool ok2 = d->row == 3 && d->col == 0 && A->isDead;
	if (ok2)
	{
		cout << "Test enemy move passed!" << endl;
	}

	bool ok = ok1 && ok2;

	if (ok)
	{
		cout << "Test move all passed!" << endl;
	}
	else
	{
		cout << "Not all test move passed." << endl;
	}
	delete(bP);
	delete(pP);
	return ok;
}

bool Tests::testIsWinner()
{
	int nrows = -1;
	Board* bP = new (Board);
	Production* pP = new Production();

	Checker* cPUs[12];
	Checker* cPEs[12];

	cout << "Before read file" << endl;
	bool answer = pP->readFile((char*)"checkersConfig.txt", &nrows, bP, cPUs, cPEs); //read the file
	cout << "Back from read file" << endl;

	Checker** cpe = cPEs;
	(*(cpe + 1))->isDead = true;
	bP->setUsable(3);
	cout << "one enemy checker is set to dead" << endl;

	bP->printBoard();
	bP->printCheckerPos(cPUs, cPEs);

	pP->isWinner(cPUs, cPEs);
	int a = -1;
	cout << "Does this look correct? Type 0 for false and type 1 for true." << endl;
	cin >> a;

	if (a)
	{
		cout << "Test is winner passed!" << endl;
	}
	else
	{
		cout << "Test is winner did not pass." << endl;
	}
	delete(bP);
	delete(pP);
	return (bool)a;
}
