#include <iostream>
using namespace std;
#include "Tests.h"
#include "Production.h"
#include <time.h>

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));
	cout << "!!!Hello World,  we are on HW5!!!" << endl; // prints !!!Hello World!!!
	Tests* tsP = new Tests();
	if (tsP->tests())
	{
		Production* pP = new Production();
		if (pP->prod(argc, argv))
		{
			cout << "Production passed." << endl;
		}
		delete(pP);
	}
	else
	{
		cout << "Not all tests passed." << endl;
	}
	delete(tsP);
	return 0;
}
