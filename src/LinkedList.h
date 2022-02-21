#pragma once

typedef struct LLNode
{
	struct LLNode* next;
	int checkerNum;
	int move;
}LLNode;

class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();

	LLNode* makeEmptyLinkedList();
	bool isEmpty(LLNode*);
	int getLength(LLNode* lp);
	void saveMove(LLNode* lp, int pos, int cn);
	void printList(LLNode*);
	void printMoveLL(LLNode* lp);
	void printJumpLL(LLNode* lp);
	LLNode* getMove(LLNode*, int index);
	LLNode* appendList(LLNode*, LLNode* lp);
};

