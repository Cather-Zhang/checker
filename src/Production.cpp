#include "Production.h"
#include <iostream>
using namespace std;


Production::Production() {
	// TODO Auto-generated constructor stub
	cout << "Making a new production" << endl;
}

Production::~Production() {
	// TODO Auto-generated destructor stub
	cout << "Deleting a new production" << endl;
}

bool Production::prod(int argc, char* argv[])
{
	puts("Starting Production\n");
	bool answer = false;

	if (argc <= 1) //no interesting information
	{
		puts("Didn't find any arguments.");
		fflush(stdout);
		answer = false;
	}
	else //there is interesting information
	{
		printf("Found %d interesting arguments.\n", argc - 1);
		fflush(stdout);
		char filename[FILENAMELENGTHALLOWANCE];
		char* eptr = (char*)malloc(sizeof(char*));
		long aL = -1L;
		int maxTurns = 100;

		for (int i = 1; i < argc; i++) //don't want to read argv[0]
		{//argv[i] is a string

			switch (i)
			{
			case 1:
				//this is filename
				printf("The length of the filename is %d.\n", strlen(argv[i]));
				printf("The proposed filename is %s.\n", argv[i]);
				if (strlen(argv[i]) >= FILENAMELENGTHALLOWANCE)
				{
					puts("Filename is too long.");
					fflush(stdout);
					answer = false;
				}
				else
				{
					strcpy(filename, argv[i]);
					printf("Filename was %s.\n", filename);
					fflush(stdout);
				}
				break;

			case 2:
				//this is maximum number of turns

				aL = strtol(argv[i], &eptr, 10);
				maxTurns = (int)aL;
				cout << "Maximum number of rounds in this game is " << maxTurns << endl;
				break;

			default:
				puts("Unexpected argument count."); fflush(stdout);
				answer = false;
				break;

			}//end of switch
		}//end of for loop on argument count
		puts("after reading arguments"); fflush(stdout);

		//we'll want to read the file
		int nrows = -1;
		Board* bP = new (Board);

		Checker* theCheckerPUs[12]; //for my side checkers
		Checker* theCheckerPEs[12]; //for enemy side checkers

		cout << "Before read file" << endl;
		answer = readFile(filename, &nrows, bP, theCheckerPUs, theCheckerPEs); //read the file
		cout << "Back from read file" << endl; 
		bP->printBoard();
		bP->printCheckerPos(theCheckerPUs, theCheckerPEs);

		int turnNum = 0;
		int whoseTurn = -1;
		cout << "Please type 1 if you are moving first, type 0 your enemy moves first: " << endl;
		cin >> whoseTurn;

		if (whoseTurn == 0) {
			cout << "Turn " << turnNum + 1<< endl;
			cout << "Your enemy's turn." << endl;
			bP->enemyTurn(theCheckerPUs, theCheckerPEs);
			turnNum++;
		}

		while (turnNum <= maxTurns) {
			cout << "Turn " << turnNum + 1<< endl;
			cout << "Your turn." << endl;
			bP->myTurn(theCheckerPUs, theCheckerPEs);
			turnNum++;
			bP->printBoard();
			bP->printCheckerPos(theCheckerPUs, theCheckerPEs);
			if (turnNum <= maxTurns) {
				cout << "Turn " << turnNum + 1 << endl;
				cout << "Your enemy's turn." << endl;
				bP->enemyTurn(theCheckerPUs, theCheckerPEs);
				turnNum++;
				bP->printBoard();
				bP->printCheckerPos(theCheckerPUs, theCheckerPEs);
			}
		}
		isWinner(theCheckerPUs, theCheckerPEs);
	}
	return answer;
}


bool Production::readFile(char* filename, int* nrows, Board* bP, Checker** theCheckerPUs, Checker** theCheckerPEs)
{
	bool ok = false;
	//the file tells how many rooms there are
	FILE* fp = fopen(filename, "r"); //read the file

	if (fp == NULL)
	{
		puts("Error! opening file");

	}
	else
	{
		fscanf(fp, "%d", nrows);
		bP->setN(*nrows);
		int howManyRows = *nrows;
		bP->setEdgesP((char*)malloc(howManyRows * howManyRows * sizeof(char)));
		bP->init();
	
		
		char temp[5];
		int countU = -1;
		int countE = -1;
		for (int i = 0; i < (*nrows); i++)
		{
			printf("on row %d\n", i); fflush(stdout);
			for (int j = 0; j < (*nrows); j++) {
				int pos = i * 8 + j;
				fscanf(fp, "%s", temp);
				if (!(*temp == '\n')) {
					cout << "in column " << j << " read " << temp << endl;
				}
				if (*temp == '0')
					if ((i + j % 2) % 2 == 1) {
						bP->setUsable(pos);
					}
					else
					{
						bP->setUnusable(pos);
					}
				else if (*temp == 'p') {
					countE++;
					bP->setChecker(pos, *temp);
					Checker** aECheckerP = theCheckerPEs;
					aECheckerP = aECheckerP + countE;
					*aECheckerP = (Checker*)malloc(sizeof(Checker));

					(*aECheckerP)->isKing = false;
					(*aECheckerP)->isDead = false;
					(*aECheckerP)->row = i;
					(*aECheckerP)->col = j;
					(*aECheckerP)->num = countE;
					cout << "Enemy checker " << (*aECheckerP)->num << " is made on row " << i << " col " << j << endl;

				}
				else if (*temp == 'k') {
					countE++;
					bP->setChecker(pos, *temp);
					Checker** aECheckerP = theCheckerPEs;
					aECheckerP = aECheckerP + countE;
					*aECheckerP = (Checker*)malloc(sizeof(Checker));

					(*aECheckerP)->isKing = true;
					(*aECheckerP)->isDead = false;
					(*aECheckerP)->row = i;
					(*aECheckerP)->col = j;
					(*aECheckerP)->num = countE;
					cout << "Enemy king " << (*aECheckerP)->num << " is made on row " << i << " col " << j << endl;
				}

				else if (*temp == 'P') {
					countU++;
					bP->setChecker(pos, *temp);
					Checker** aUCheckerP = theCheckerPUs;
					aUCheckerP = aUCheckerP + countU;
					*aUCheckerP = (Checker*)malloc(sizeof(Checker));

					(*aUCheckerP)->isKing = false;
					(*aUCheckerP)->row = i;
					(*aUCheckerP)->col = j;
					(*aUCheckerP)->num = countU;
					(*aUCheckerP)->isDead = false;
					cout << "Our side checker " << (*aUCheckerP)->num << " is made on row " << i << " col " << j << endl;
				}
				else if (*temp == 'K') {
					countU++;
					bP->setChecker(pos, *temp);
					Checker** aUCheckerP = theCheckerPUs;
					aUCheckerP = aUCheckerP + countU;
					*aUCheckerP = (Checker*)malloc(sizeof(Checker));

					(*aUCheckerP)->isKing = true;
					(*aUCheckerP)->row = i;
					(*aUCheckerP)->col = j;
					(*aUCheckerP)->num = countU;
					(*aUCheckerP)->isDead = false;
					cout << "Our side king " << (*aUCheckerP)->num << " is made on row " << i << " col " << j << endl;
				}
			}
		}
		ok = true;
		fclose(fp);
	}
	return ok;
}

void Production::isWinner(Checker** cpus, Checker** cpes) 
{
	int meLive = 0;
	int enemyLive = 0;

	for (int i = 0; i < 12; i++)
	{
		Checker* aCPU = *(cpus + i);
		Checker* aCPE = *(cpes + i);

		if (!(aCPU->isDead))
		{
			meLive++;
		}
		if (!(aCPE->isDead))
		{
			enemyLive++;
		}
	}
	cout << "You have " << meLive << " checkers left on the board." << endl;
	cout << "Enemy has " << enemyLive << " checkers left on the board." << endl;

	if (meLive > enemyLive)
	{
		cout << "Congratulatios! You won!" << endl;
	}
	else if (meLive < enemyLive)
	{
		cout << "Sorry, you did not win :( " << endl;
	}
	else cout << "It was a tie, but I will count as you win :)" << endl;
}
