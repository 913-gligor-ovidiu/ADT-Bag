#pragma once
#include "SortedBag.h"
#include <stack>

class SortedBag;
class Stack {
private:
    BTSNode** elements;
    int nrElements;
    int nrAllElemets;
    int capacity;
public:
    Stack();
    int getNrElements() const;
    int getNrAllElements()const;
    int getCapacity() const;
    void push(BTSNode* element);
    void resize();
    BTSNode* pop();
    TComp operator[](int position) const;
    int operator()(int position)const;
    ~Stack();
};


class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
    Stack stack{};
	int current;
    int currentFr;
    int counter;
    BTSNode* start;
	//TODO - Representation

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
    void inOrderRecursive(BTSNode* startNode);
};

