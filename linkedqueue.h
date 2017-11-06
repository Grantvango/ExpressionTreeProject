#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <iostream>
#include <cassert>
#include "linkedlistwtail.h"

using namespace std;

template<class T>
class LinkedQueue
{
	public:
	
	// Inspector
	
	T head() const {return list.getElement(0);}
	int size() const {return list.size();}
	
	// Mutators
	
	void enqueue(const T& value) {list.pushBack(value);}
	T dequeue() {return list.popFront();}
	
	// Other
	
	void makeEmpty() {list.makeEmpty();}
	bool isEmpty() {return list.isEmpty();}	
	
	//Facilitators
	
	void input(istream& in) {list.input(in);}
	void output(ostream& out) const {list.output(out);}
	
	private:
	
	LinkedListwTail<T> list;
};

/************************************************************************
*																		*
*	Function:	operator>>												*
*																		*
*	Purpose:	To extract a LinkedQueue from the input stream			*
*																		*
************************************************************************/

template <class T>
istream& operator>>(istream& in, LinkedQueue<T>& q)
{
	s.input(in);
	return in;
}

/************************************************************************
*																		*
*	Function:	operator<<												*
*																		*
*	Purpose:	To insert a LinkedQueue into the output stream			*
*																		*
************************************************************************/

template <class T>
ostream& operator<<(ostream& out, const LinkedQueue<T>& q)
{
	s.output(out);
	return out;
}

#endif
