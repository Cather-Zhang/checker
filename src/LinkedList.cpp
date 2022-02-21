#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

LinkedList::LinkedList() {
	// TODO Auto-generated constructor stub
}

LinkedList::~LinkedList() {
	// TODO Auto-generated destructor stub
}

bool LinkedList::isEmpty(LLNode* lp)
{
	if (lp->move == -1)
	{
		return true;
	}
	return false;
}


LLNode* LinkedList::makeEmptyLinkedList()
{
	LLNode* lp = (LLNode*)malloc(sizeof(LLNode));
	lp->next = nullptr;
	lp->move = -1;
	return lp;
}

void LinkedList::saveMove(LLNode* lp, int pos, int cn) {
	if (isEmpty(lp))
	{
		lp->move = pos;
		lp->checkerNum = cn;
	}
	else
	{
		LLNode* temp = lp;
		while (temp->next)
		{
			temp = (LLNode*)temp->next;
		}
		//now temp points to the last element

		//make a new element, attach mp to it, wire up the new element
		LLNode* newList = makeEmptyLinkedList();
		newList->move = pos;
		newList->checkerNum = cn;
		temp->next = (struct LLNode*)newList;
	}
}

void LinkedList::printList(LLNode* lp) 
{
	cout << "Printing list" << endl;
	if (isEmpty(lp))
	{
		cout << "Empty list" << endl;
	}
	else
	{
		int size = 0;
		LLNode* temp = lp;
		while (temp)
		{
			size++;
			cout << "For my checker " << lp->checkerNum << ". Possible movement #" << size << " is to " << temp->move << endl;
			temp = temp->next;  //points to the next
		}
	}
}

void LinkedList::printJumpLL(LLNode* lp)
{
	if (isEmpty(lp))
	{
		cout << "Empty list" << endl;
	}
	else
	{
		LLNode* temp = lp;
		while (temp)
		{
			cout << lp->checkerNum << " jump to " << temp->move << endl;
			temp = temp->next;  //points to the next
		}
	}
}
void LinkedList::printMoveLL(LLNode* lp)
{
	if (isEmpty(lp))
	{
		cout << "Empty list" << endl;
	}
	else
	{
		LLNode* temp = lp;
		while (temp)
		{
			cout << lp->checkerNum << " move to " << temp->move << endl;
			temp = temp->next;  //points to the next
		}
	}
}

int LinkedList::getLength(LLNode* lp) 
{	
	if (isEmpty(lp))
	{
		return 0;
	}
	else
	{
		int size = 0; 
		LLNode* temp = lp;
		while (temp)
		{
			size++;
			temp = temp->next;  //points to the next
		}
		return size;
	}
}

LLNode* LinkedList::getMove(LLNode* lp, int i) {
	if (isEmpty(lp)) 
	{
		return nullptr;
	}
	else
	{
		LLNode* temp = lp;
		int index = 0;
		while (temp)
		{
			if (i == index)
			{
				return temp;
			}
			else
			{
				temp = temp->next;
				index++;
			}

		}
	}
}

LLNode* LinkedList::appendList(LLNode* oldList, LLNode* lp)
{
	if (!(isEmpty(lp)))
	{
		LLNode* temp = oldList;
			if (isEmpty(oldList))
			{
				oldList = lp;
			}
			else
			{
				while (temp->next)
				{
					temp = temp->next;
				}
				temp->next = lp;
			}
	}
	return oldList;
}