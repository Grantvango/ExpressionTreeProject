#ifndef LINKEDLISTWTAIL_H
#define LINKEDLISTWTAIL_H

//	Header files

#include <iostream>
#include <string>
#include <cassert>

#include "linkedlist.h"

using namespace std;

/****************************************************************************
*																			*
*	The LinkedListwTail class												*
*																			*
****************************************************************************/

template <class T>
class LinkedListwTail : public LinkedList<T>
{
//	Public member functions

	public:

	//	Constructors

		LinkedListwTail(int sz = 0, const T& value = T());
		LinkedListwTail(const LinkedListwTail<T>& lst) {makeCopy(lst);}
	
	//	Inspectors

		T getElement(int pos) const;
		T& getElement(int pos);

	//	Mutators

		void setElement(int pos, const T& value) {getElement(pos) = value; return;}
		void insert(int pos, const T& value);
		void remove(int pos);
		void pushFront(const T& value) {insert(0, value);}
		void pushBack(const T& value);
		T popFront() {T value = getElement(0); remove(0); return value;}
		T popBack();
		void makeEmpty() {LinkedList<T>::makeEmpty(); tail = NULL;}

	//	Facilitators
	
		void input(istream& in);
		void output(ostream& out) const {LinkedList<T>::output(out);}
	
	//	Operators
	
		LinkedListwTail<T>& operator=(const LinkedListwTail<T>& lst);
		T operator[](int pos) const {return getElement(pos);}
		T& operator[](int pos) {return getElement(pos);}

	//	Other functions
	
		void swap(LinkedListwTail<T>& lst);
		bool isValid() const;
	
//	Private member functions

	private:
	
		void makeCopy(const LinkedListwTail<T>& lst);

//	Private data members

	private:
	
		LinkedListNode<T>* tail;	// Pointer to the last node
};

//	LinkedListwTail operators

template <class T>
istream& operator>>(istream& in, LinkedListwTail<T>& lst);
template <class T>
ostream& operator<<(ostream& out, const LinkedListwTail<T>& lst);

/****************************************************************************
*																			*
*	Function:	LinkedListwTail(int = 0, T = T())							*
*																			*
*	Purpose:	To create a linked list from a float						*
*																			*
****************************************************************************/

template <class T>
LinkedListwTail<T>::LinkedListwTail(int sz, const T& value)
{
	mSize = sz;
	
	if (sz == 0)
	{
		head = NULL;
		tail = NULL;
	}
	else
	{
	//	Create first node
	
		head = new LinkedListNode<T>(value);
		LinkedListNode<T>* node = head;
	
	//	Create all subsequent nodes
	
		for (int i = 1; i < mSize; i++)
		{
			node->next = new LinkedListNode<T>(value);
			node = node->next;
		}
		tail = node;
	}
	return;
}

/****************************************************************************
*																			*
*	Function:	getElement													*
*																			*
*	Purpose:	To return the element in the specified position of a 		*
*				linked list													*
*																			*
****************************************************************************/

template <class T>
T LinkedListwTail<T>::getElement(int pos) const
{
	if (pos == mSize - 1)
		return tail->mValue;
	else
		return LinkedList<T>::getElement(pos);
}

/****************************************************************************
*																			*
*	Function:	getElement													*
*																			*
*	Purpose:	To return the element in the specified position of a 		*
*				linked list													*
*																			*
****************************************************************************/

template <class T>
T& LinkedListwTail<T>::getElement(int pos)
{
	if (pos == mSize - 1)
		return tail->mValue;
	else
		return LinkedList<T>::getElement(pos);
}

/****************************************************************************
*																			*
*	Function:	insert														*
*																			*
*	Purpose:	To insert a new element into a linked list at the 			*
*				specified position											*
*																			*
****************************************************************************/

template <class T>
void LinkedListwTail<T>::insert(int pos, const T& value)
{
	assert(pos >= 0 && pos <= mSize);
	
	if (pos == mSize)
	{
		pushBack(value);
		return;
	}

//	Create a new node

	LinkedListNode<T>* new_node = new LinkedListNode<T>(value);

//	Chase pointers to find location of the insertion.
//	New node should be inserted between prev_node and curr_node.

	LinkedListNode<T>* prev_node = NULL;
	LinkedListNode<T>* curr_node = head;
	
	for (int i = 1; i < pos; i++)
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
	}

//	insert the new node into the list

	new_node->next = curr_node;
	
	if (prev_node != NULL)
		prev_node->next = new_node;
	else
		head = new_node;

//	Increment the list size

	mSize++;
	return;
}

/****************************************************************************
*																			*
*	Function:	remove														*
*																			*
*	Purpose:	To delete an element from the specified position of a 		*
*				linked list													*
*																			*
****************************************************************************/

template <class T>
void LinkedListwTail<T>::remove(int pos)
{
	assert(pos >= 0 && pos < mSize);
	
//	Chase pointers to find the node to be deleted.
//	curr_node will be the node to be deleted.

	LinkedListNode<T>* prev_node = NULL;
	LinkedListNode<T>* curr_node = head;
	for (int i = 0; i < pos; i++)
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	
//	Redirect the pointers around the node

	if (prev_node == NULL)
		head = curr_node->next;
	else
		prev_node->next = curr_node->next;

//	Update the tail, if necessary

	if (pos == mSize - 1)
		tail = (prev_node == NULL) ? head : prev_node;
	
//	Delete the node

	delete curr_node;
	mSize--;
	return;
}

/****************************************************************************
*																			*
*	Function:	pushBack													*
*																			*
*	Purpose:	To add a new node to the tail of the list					*
*																			*
****************************************************************************/

template <class T>
void LinkedListwTail<T>::pushBack(const T& value)
{
//	Create a new node

	LinkedListNode<T>* node = new LinkedListNode<T>(value);

//	Append the new node

	if (tail == NULL)			// List is empty
		head = node;
	else						// List is not empty
		tail->next = node;
	
	tail = node;
	mSize++;

	return;
}

/****************************************************************************
*																			*
*	Function:	popBack														*
*																			*
*	Purpose:	To delete the node at the tail of the list					*
*																			*
****************************************************************************/

template <class T>
T LinkedListwTail<T>::popBack()
{
	LinkedListNode<T>* prev_node = NULL;
	LinkedListNode<T>* curr_node = head;
	
	for (int i = 1; i < mSize; i++)
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	
	if (prev_node == NULL)
		head = NULL;
	else
		prev_node->next = NULL;

	tail = prev_node;
	T value = curr_node->mValue;
	delete curr_node;
	mSize--;
	
	return value;
}

/****************************************************************************
*																			*
*	Function:	input														*
*																			*
*	Purpose:	To extract a linked list object from the input stream		*
*																			*
****************************************************************************/

template <class T>
void LinkedListwTail<T>::input(istream& in)
{
//	Clear out old list

	makeEmpty();
	char c;

//	Read open brace

	in >> c;
	assert(c == '{');			// Verify open brace

//	Read remainder of list

	in >> c;					// Read next character
	if (c != '}')
	{
		in.putback(c);			// Put char back in input stream
		T value;
	
	//	Read until '}' is found
	
		while (c != '}')
		{
			in >> value;		// Read the element
		 	pushBack(value);	// Append the element to the list
		 	in >> c;			// Read the comma or close brace
		}
	}
	return;
}

/****************************************************************************
*																			*
*	Function:	operator=													*
*																			*
*	Purpose:	To assign one linked list to another						*
*																			*
****************************************************************************/

template <class T>
LinkedListwTail<T>& LinkedListwTail<T>::operator=(const LinkedListwTail<T>& lst)
{
	if (this != &lst)
	{
		makeEmpty();
		makeCopy(lst);
	}
	return *this;
}

/****************************************************************************
*																			*
*	Function:	swap														*
*																			*
*	Purpose:	To swap two LinkedLists										*
*																			*
****************************************************************************/

template <class T>
void LinkedListwTail<T>::swap(LinkedListwTail<T>& lst)
{
//	Swap tails

	LinkedListNode<T>* tempTail = tail;
	tail = lst.tail;
	lst.tail = tempTail;

//	Swap everything else

	LinkedList<T>::swap(lst);
	
	return;
}

/****************************************************************************
*																			*
*	Function:	isValid													*
*																			*
*	Purpose:	To verify that a linked list has a valid structure			*
*																			*
****************************************************************************/

template <class T>
bool LinkedListwTail<T>::isValid() const
{
//	Verify that the size is nonnegative

	if (mSize < 0)
	{
		cerr << "LinkedListwTail: mSize < 0" << endl;
		return false;
	}

//	Verify that all but the last pointer are not null

	LinkedListNode<T>* prev_node = NULL;
	LinkedListNode<T>* node = head;
	for (int i = 0; i < mSize; i++)
	{
		if (node == NULL)
		{
			cerr << "LinkedListwTail: node == NULL" << endl;
			return false;
		}
		prev_node = node;
		node = node->next;
	}

//	Verify that tail points to last node

	if (prev_node != tail)
	{
		cerr << "LinkedListwTail: prev_node != tail" << endl;
		return false;
	}

//	Verify that the last pointer is null

	if (node != NULL)
	{
		cerr << "LinkedListwTail: node != NULL)" << endl;
		return false;
	}
	
	return true;
}

/****************************************************************************
*																			*
*	Function:	makeCopy													*
*																			*
*	Purpose:	To make a copy of a list of nodes of a LinkedListwTail		*
*																			*
****************************************************************************/

template <class T>
void LinkedListwTail<T>::makeCopy(const LinkedListwTail<T>& lst)
{
	mSize = lst.mSize;
	
//	See if old list is empty

	if (lst.head == NULL)
	{
		head = NULL;
		tail = NULL;
		return;
	}

//	Copy first node

	LinkedListNode<T>* old_node = lst.head;
	head = new LinkedListNode<T>(old_node->mValue);
	LinkedListNode<T>* new_node = head;
	old_node = old_node->next;
	
//	Copy all subsequent nodes

	while (old_node != NULL)
	{
		new_node->next = new LinkedListNode<T>(old_node->mValue);
		new_node = new_node->next;
		old_node = old_node->next;
	}
	
	tail = new_node;

	return;
}

/****************************************************************************
*																			*
*	Function:	operator>>													*
*																			*
*	Purpose:	To extract a linked list object from the input stream		*
*																			*
****************************************************************************/

template <class T>
istream& operator>>(istream& in, LinkedListwTail<T>& lst)
{
	lst.input(in);
	return in;
}

/****************************************************************************
*																			*
*	Function:	operator<<													*
*																			*
*	Purpose:	To insert a linked list object into the output stream		*
*																			*
****************************************************************************/

template <class T>
ostream& operator<<(ostream& out, const LinkedListwTail<T>& lst)
{
	lst.output(out);
	return out;
}

#endif