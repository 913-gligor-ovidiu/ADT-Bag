#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
	this->relation = r;
	this->root = nullptr;
	this->length = 0;
}//Theta(1)

void SortedBag::add(TComp e) {
	//TODO - Implementation
	if (this->root == nullptr)
	{	
		//tree is empty
		auto* node = new BTSNode();
		node->fr = 1;
		node->info = e;
		this->root = node;
		this->length++;
	}
	else
	{
		BTSNode* current = this->root;
		BTSNode* prev = nullptr;
		while (current != nullptr)
		{	

			if (current->info == e)
			{
				current->fr++;
				this->length++;
				return;
			}
			if (relation(current->info, e))
			{
				prev = current;
				current = current->left;
			}
			else if (!relation(current->info, e))
			{	
				prev = current;
				current = current->right;
			}
			
		}
		if (relation(prev->info, e))
		{
			auto* node = new BTSNode();
			node->fr = 1;
			node->info = e;
			this->length++;
			prev->left = node;
		}
		else if (!relation(prev->info, e))
		{
			auto* node = new BTSNode();
			node->fr = 1;
			node->info = e;
			this->length++;
			prev->right = node;
		}

	}
}//BC:Theta(1) AC:Theta(log n) WC:Theta(log n) Total: O(log n)


bool SortedBag::remove(TComp e) {
	//TODO - Implementation
	BTSNode* current = this->root;
	BTSNode* prev = nullptr;
	while (current!=nullptr && current->info!=e)
	{	
		prev = current;
		
		if (this->relation(current->info, e))
		{		
			current = current->left;
		}
		else if (!this->relation(current->info, e))
		{
			current = current->right;
		}
	}
	//elem not in bst
	if (current == nullptr)
		return false;

	if (current->info == e && current->fr > 1)
	{
		//The simplest case is when we want to remove an element that has a frequency greater than 1
		//in that case we just decrement it's frequency
		current->fr--;
		this->length--;
		return true;
	}

	//check if the node of the elem has 0 or 1 children
	if (current->left == nullptr || current->right == nullptr)
	{
		BTSNode* newCurrent;

		//set newCurrent to correct child
		if (current->left == nullptr)
			newCurrent = current->right;
		else
			newCurrent = current->left;

		if (prev == nullptr)
		{
			this->root = newCurrent;
			this->length--;
			return true;
		}

		if (current == prev->left)
			prev->left = newCurrent;
		else
			prev->right = newCurrent;

		delete current;
		this->length--;
		return true;
	}
	else //two children case
	{
		BTSNode* temp = current->right;
		BTSNode* successor = nullptr;

		//find the succesor node	
		while (temp->left != nullptr)
		{
			successor = temp;
			temp = temp->left;
		}

		if (successor != nullptr)
			successor->left = temp->right;
		else
			current->right = temp->right;

		current->info = temp->info;

		delete temp;
		this->length--;
		return true;

	}

	return false;
}//BC:Theta(1) AC:Theta(log n) WC:Theta(log n) Total: O(log n)


bool SortedBag::search(TComp elem) const {
	//TODO - Implementation
	BTSNode* current = this->root;
	while (current != nullptr)
	{
		if (current->info == elem)
			return true;
		if (this->relation(current->info, elem))
			current = current->left;
		else if (!this->relation(current->info, elem))
			current = current->right;
	}
	return false;
}//BC:Theta(1) AC:Theta(log n) WC:Theta(log n) Total: O(log n)


int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation
	BTSNode* current = this->root;
	while (current != nullptr)
	{
		if (current->info == elem)
			return current->fr;
		if (this->relation(current->info, elem))
			current = current->left;
		else if (!this->relation(current->info, elem))
			current = current->right;
	}
}//BC:Theta(1) AC:Theta(log n) WC:Theta(log n) Total: O(log n)



int SortedBag::size() const {
	//TODO - Implementation
	return this->length;
}//Theta(1)


bool SortedBag::isEmpty() const {
	//TODO - Implementation
	if (this->length == 0)
		return true;
	return false;
}//Theta(1)


void SortedBag::destroy(BTSNode* node)
{	
	if (node == nullptr) return;

	// recursively destroy all nodes of BST
	destroy(node->left);
	destroy(node->right);

	delete node;
}
//Theta(1)


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}//Theta(1)


SortedBag::~SortedBag() {
	//TODO - Implementation
	this->destroy(this->root);
}//Theta(1)


int SortedBag::removeOccurrences(int nr, TComp elem)
{
	if (nr < 0)
		throw std::exception();

	for (int i = 0; i < nr; i++)
		this->remove(elem);

	return nr;
}

