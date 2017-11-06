#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

//	Header files

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

template <class T> class LinkedList;
template <class T> class LinkedListwTail;

/****************************************************************************
*																			*
*	The LinkedListNode class definition										*
*																			*
****************************************************************************/

template <class T>
class LinkedListNode
{
//	Friends

	friend class LinkedList<T>;
	friend class LinkedListwTail<T>;

//	Member functions

	public:
	
		T value() const {return mValue;}
		T& value() {return mValue;}
		LinkedListNode<T>* nextNode() {return next;}
		
	private:
	
		LinkedListNode(const T& value = T()) {mValue = value; next = NULL;}

//	Data members

	private:
	
		T mValue;
		LinkedListNode<T>* next;
};

#endif