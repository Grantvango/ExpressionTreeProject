#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

//	Header files

#include <iostream>
#include "linkedlist.h"

using namespace std;

/************************************************************************
*																		*
*	The LinkedStack class definition									*
*																		*
************************************************************************/

template <class T>
class LinkedStack
{
//	Public member functions

	public:

	//	Constructors

		LinkedStack() {}
		LinkedStack(const LinkedStack<T>& s) : list(s) {}

	//	Inspectors

		T top() const {return list.getElement(0);}
		int size() const {return list.size();}
		bool isEmpty() const {return list.isEmpty();}

	//	Mutators

		void push(const T& value) {list.pushFront(value);}
		T pop() {return list.popFront();}
		void makeEmpty() {list.makeEmpty();}
		
	//	Facilitators
	
		void input(istream& in) {list.input(in);}
		void output(ostream& out) const {list.output(out);}
	
	//	Other member functions
	
		bool isValid() const {list.isValid();}
		
	private:
	
		LinkedList<T> list;
};

/************************************************************************
*																		*
*	Function:	operator>>												*
*																		*
*	Purpose:	To extract a LinkedStack from the input stream			*
*																		*
************************************************************************/

template <class T>
istream& operator>>(istream& in, LinkedStack<T>& s)
{
	s.input(in);
	return in;
}

/************************************************************************
*																		*
*	Function:	operator<<												*
*																		*
*	Purpose:	To insert a LinkedStack into the output stream			*
*																		*
************************************************************************/

template <class T>
ostream& operator<<(ostream& out, const LinkedStack<T>& s)
{
	s.output(out);
	return out;
}

#endif
