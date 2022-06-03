#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//TODO - Implementation
	this->current = 0;
	this->counter = 0;
	this->currentFr = 1;
	this->start = b.root;
	this->inOrderRecursive(this->start);
}//Theta(1)

TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (!valid()) {
		throw std::exception();
	}
	
	return this->stack[this->stack.getNrElements() - this->current - 1];
}//Theta(1)

bool SortedBagIterator::valid() {
	//TODO - Implementation
	if (this->current >= this->stack.getNrElements() && this->counter>=this->stack.getNrAllElements()) 
		return false;
	return true;
}//Theta(1)

void SortedBagIterator::next() {
	//TODO - Implementation
	if (!valid()) {
		throw std::exception();
	}
	if (this->stack(this->stack.getNrElements() - 1 - this->current) > this->currentFr)
	{
		this->currentFr++;
		this->counter++;
	}
	else
	{
		this->currentFr = 1;
		this->counter++;
		this->current++;
	}
}//Theta(1)

void SortedBagIterator::first() {
	//TODO - Implementation
	this->current = 0;
	this->counter = 0;
	this->currentFr = 1;
}//Theta(1)

void SortedBagIterator::inOrderRecursive(BTSNode* startNode)
{	
	
	if (startNode != nullptr) {
		this->inOrderRecursive(startNode->left);
		this->stack.push(startNode);
		this->inOrderRecursive(startNode->right);
	}
	
}//Theta(1)

Stack::Stack() :nrElements{ 0 }, capacity{ 10 }, nrAllElemets{ 0 } {
	this->elements = new BTSNode * [capacity];
}//Theta(1)

int Stack::getNrElements() const
{
	return this->nrElements;
}//Theta(1)

int Stack::getNrAllElements() const
{
	return this->nrAllElemets;
}//Theta(1)

int Stack::getCapacity() const
{
	return this->capacity;
}//Theta(1)

void Stack::push(BTSNode* element)
{
	if (this->nrElements == this->capacity)
		this->resize();
	this->elements[this->nrElements] = element;
	this->nrElements++;
	this->nrAllElemets += element->fr;
}//Theta(1)

void Stack::resize()
{
	auto** newElements = new BTSNode * [this->capacity * 2];
	int index;
	for (index = 0; index < this->nrElements; ++index) {
		newElements[index] = this->elements[index];
	}
	this->capacity = this->capacity * 2;
	delete[] this->elements;
	this->elements = newElements;
}//O(nrElements)

BTSNode* Stack::pop()
{
	this->nrElements--;
	return this->elements[this->nrElements];
}//Theta(1)

TComp Stack::operator[](int position) const
{
	return this->elements[position]->info;
}//Theta(1)

Stack::~Stack()
{
	delete[] this->elements;
}//Theta(1)

int Stack::operator()(int position)const
{
	return this->elements[position]->fr;
}//Theta(1)