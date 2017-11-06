#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//	Header files

#include <iostream>
#include <cassert>
#include "linkedlistnode.h"

using namespace std;

/****************************************************************************
*																			*
*	The LinkedList class													*
*																			*
****************************************************************************/

template <class T>
class LinkedList
{
//	Public member functions

	public:

	//	Constructors

		LinkedList(int sz = 0, const T& value = T());
		LinkedList(const LinkedList<T>& lst) {makeCopy(lst);}
	
	//	Destructor
	
		~LinkedList() {makeEmpty();}

	//	Inspectors

		T getElement(int pos) const;
		T& getElement(int pos);
		int size() const {return mSize;}
		bool isEmpty() const {return mSize == 0;}

	//	Mutators

		void setElement(int pos, const T& value);
		void insert(int pos, const T& value);
		void remove(int pos);
		void pushFront(const T& value) {insert(0, value);}
		void pushBack(const T& value) {insert(mSize, value);}
		T popFront() {T value = getElement(0); remove(0); return value;}
		T popBack() {T value = getElement(mSize - 1); remove(mSize - 1); return value;}
		void makeEmpty();

	//	Facilitators
	
		void input(istream& in);
		void output(ostream& out) const;
	
	//	Operators
	
		LinkedList<T>& operator=(const LinkedList<T>& lst);
		T operator[](int pos) const;
		T& operator[](int pos);

	//	Other functions
	
		void swap(LinkedList<T>& lst);
		int search(const T& value) const;
		void sort();
		bool isValid() const;
	
//	Private member functions

	private:
	
		void makeCopy(const LinkedList<T>& lst)
			{mSize = lst.mSize; head = makeCopy(lst.head);}
		LinkedListNode<T>* makeCopy(LinkedListNode<T>* old_node);
		LinkedListNode<T>* locateNode(int pos) const;

//	Data members

	protected:
	
		int mSize;					// Number of nodes
		LinkedListNode<T>* head;	// Pointer to the first node
};

//	LinkedList operators

template <class T>
istream& operator>>(istream& in, LinkedList<T>& lst);
template <class T>
ostream& operator<<(ostream& out, const LinkedList<T>& lst);

/****************************************************************************
*																			*
*	Function:	LinkedList(int = 0, T = T())								*
*																			*
*	Purpose:	To create a linked list from a float						*
*																			*
****************************************************************************/

template <class T>
LinkedList<T>::LinkedList(int sz, const T& value)
{
	assert(sz >= 0);
	
	mSize = sz;
	
	if (sz == 0)
		head = NULL;
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
T LinkedList<T>::getElement(int pos) const
{
	return locateNode(pos)->mValue;
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
T& LinkedList<T>::getElement(int pos)
{
	return locateNode(pos)->mValue;
}

/****************************************************************************
*																			*
*	Function:	setElement													*
*																			*
*	Purpose:	To assign the specified value to the specified position of 	*
*				the linked list												*
*																			*
****************************************************************************/

template <class T>
void LinkedList<T>::setElement(int pos, const T& value)
{
	locateNode(pos)->mValue = value;
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
void LinkedList<T>::insert(int pos, const T& value)
{
	assert(pos >= 0 && pos <= mSize);
	
	LinkedListNode<T>* new_node = new LinkedListNode<T>(value);
	
	LinkedListNode<T>* prev_node = NULL;
	LinkedListNode<T>* curr_node = head;
	
	for (int i = 0; i < pos; i++)
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	
	new_node->next = curr_node;
	
	if(curr_node == head)
		head = new_node;
	else
		prev_node->next = new_node;
	
	mSize++;
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
void LinkedList<T>::remove(int pos)
{
	assert(pos >= 0 && pos < mSize);
	
	LinkedListNode<T>* curr_node = head;
	LinkedListNode<T>* prev_node = NULL;
	
	for(int i = 0; i < pos; i++)
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	
	if(prev_node == NULL)
		head = curr_node->next;
	else
		prev_node->next = curr_node->next;
	
	delete curr_node;
	
	mSize--;
	
}
/****************************************************************************
*																			*
*	Function:	makeEmpty													*
*																			*
*	Purpose:	To remove all nodes from the list							*
*																			*
****************************************************************************/

template <class T>
void LinkedList<T>::makeEmpty()
{
//	Use two node pointers

	LinkedListNode<T>* prev_node = NULL;
	LinkedListNode<T>* curr_node = head;

//	Delete each node

	for (int i = 0; i < mSize; i++)
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
		delete prev_node;
	}

//	Initialize data members

	mSize = 0;
	head = NULL;
	return;
}

/****************************************************************************
*																			*
*	Function:	input														*
*																			*
*	Purpose:	To extract a linked list object from the input stream		*
*																			*
****************************************************************************/

template <class T>
void LinkedList<T>::input(istream& in)
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
*	Function:	output														*
*																			*
*	Purpose:	To insert a linked list object into the output stream		*
*																			*
****************************************************************************/

template <class T>
void LinkedList<T>::output(ostream& out) const
{
//	Print open brace

	out << "{";
	if (!isEmpty())
	{
	//	Print the first node
	
		out << head->mValue;
		
	//	Print each element followed by a comma
	
		LinkedListNode<T>* node = head;
		for (int i = 1; i < mSize; i++)
		{
			node = node->next; 
			out << ", " << node->mValue;
		}
	}

//	Print close brace

	out << "}";
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
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& lst)
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
*	Function:	operator[]													*
*																			*
*	Purpose:	To return a reference to the element in the specified 		*
*				position of the linked list									*
*																			*
****************************************************************************/

template <class T>
T LinkedList<T>::operator[](int pos) const
{
	return locateNode(pos)->mValue;
}

/****************************************************************************
*																			*
*	Function:	operator[]													*
*																			*
*	Purpose:	To return a reference to the element in the specified 		*
*				position of the linked list									*
*																			*
****************************************************************************/

template <class T>
T& LinkedList<T>::operator[](int pos)
{
	return locateNode(pos)->mValue;
}

/****************************************************************************
*																			*
*	Function:	swap														*
*																			*
*	Purpose:	To swap two LinkedLists										*
*																			*
****************************************************************************/

template <class T>
void LinkedList<T>::swap(LinkedList<T>& lst)
{
	int temp = mSize;
	LinkedListNode<T>* tempPtr = head;
	
	mSize = lst.size();
	lst.mSize = temp;
	
	head = lst.head;
	lst.head = tempPtr;	
}
/****************************************************************************
*																			*
*	Function:	search(T)													*
*																			*
*	Purpose:	This function will search the list for the specified 		*
*				element and report its location								*
*																			*
*	Note:		If the element was not found, the function returns 0		*
*																			*
****************************************************************************/

template <class T>
int LinkedList<T>::search(const T& value) const
{
//	Start at head of list

	LinkedListNode<T>* node = head;
	int pos = 0;

//	Look for end of list and search value

	while (node != NULL && node->mValue != value)
	{
		node = node->next;
		pos++;
	}

//	See if value was found

	if (node == NULL)
		return -1;			// Value was not found
	else
		return pos; 		// Value was found
}

/****************************************************************************
*																			*
*	Function:	sort														*
*																			*
*	Purpose:	To arrange the elements of a list into increasing order		*
*																			*
*	Note:		The less than operator < must be defined on the class T		*
*																			*
****************************************************************************/

template <class T>
void LinkedList<T>::sort()
{
	LinkedListNode<T>* base_node = head;
	while (base_node != NULL)
	{
		LinkedListNode<T>* min_node = base_node;
		LinkedListNode<T>* curr_node = base_node->next;
		while (curr_node != NULL)
		{
			if (curr_node->mValue < min_node->mValue)
				min_node = curr_node;
			curr_node = curr_node->next;
		}
		T temp = min_node->mValue;
		min_node->mValue = base_node->mValue;
		base_node->mValue = temp;

		base_node = base_node->next;
	}
	return;
}

/****************************************************************************
*																			*
*	Function:	isValid														*
*																			*
*	Purpose:	To verify that a linked list has a valid structure			*
*																			*
****************************************************************************/

template <class T>
bool LinkedList<T>::isValid() const
{
//	Verify that the size is nonnegative

	if (mSize < 0)
	{
		cerr << "Error: LinkedList<T>: mSize < 0" << endl;
		return false;
	}

//	Verify that all but the last pointer are not null

	LinkedListNode<T>* node = head;
	for (int i = 0; i < mSize; i++)
	{
		if (node == NULL)
		{
			cerr << "Error: LinkedList<T>: non-final pointer is null" << endl;
			return false;
		}
		node = node->next;
	}

//	Verify that the last pointer is null

	if (node != NULL)
	{
		cerr << "Error: LinkedList<T>: final pointer not null" << endl;
		return false;
	}
	return true;
}

/****************************************************************************
*																			*
*	Function:	makeCopy													*
*																			*
*	Purpose:	To make a copy of a list of nodes of a LinkedList			*
*																			*
****************************************************************************/

template <class T>
LinkedListNode<T>* LinkedList<T>::makeCopy(LinkedListNode<T>* old_node)
{
//	See if old list is empty

	if (old_node == NULL)
		return NULL;

//	Copy first node

	LinkedListNode<T>* first_node = new LinkedListNode<T>(old_node->mValue);
	LinkedListNode<T>* new_node = first_node;
	old_node = old_node->next;
	
//	Copy all subsequent nodes

	while (old_node != NULL)
	{
		new_node->next = new LinkedListNode<T>(old_node->mValue);
		new_node = new_node->next;
		old_node = old_node->next;
	}

//	Return pointer to first node

	return first_node;
}

/****************************************************************************
*																			*
*	Function:	locateNode													*
*																			*
*	Purpose:	To return a pointer to the node in the specified position	*
*																			*
****************************************************************************/
template <class T>
LinkedListNode<T>* LinkedList<T>::locateNode(int pos) const
{
	assert(pos >= 0 && pos < mSize);
	
	LinkedListNode<T>* node = head;
	for (int i = 0; i < pos; i++)
		node = node->next;
	
	return node;
}

/****************************************************************************
*																			*
*	Function:	operator>>													*
*																			*
*	Purpose:	To extract a linked list object from the input stream		*
*																			*
****************************************************************************/

template <class T>
istream& operator>>(istream& in, LinkedList<T>& lst)
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
ostream& operator<<(ostream& out, const LinkedList<T>& lst)
{
	lst.output(out);
	return out;
}

#endif