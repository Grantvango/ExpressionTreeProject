#ifndef MENU_H
#define MENU_H

//	Include header files

#include <iostream>
#include <string>
#include <cassert>
#include "../LinkedList Class/linkedlist.h"

using namespace std;

/****************************************************************************
*																			*
*	The definition of te Menu class											*
*																			*
****************************************************************************/

class Menu
{
//	Public member functions
	
	public:
	
	//	Constructors
	
		Menu() {}
		Menu(string it[], char ab[], int sz);

	//	Inspectors
	
		string getItem(int i) const {return item[i];}
		char getAbbrev(int i) const {return abbrev[i];}
		int size() const {return item.size();}
		
	//	Mutator
	
		void addItem(string it, char ab, int pos);
		void appendItem(string it, char ab);
		void deleteItem(int pos);
		void replaceItem(string it, char ab, int pos);
		void moveItem(int oldPos, int newPos);
		
	//	facilitators
	
		void output(ostream& out) const;
		
	//	Other member functions
	
		char getChoice() const;
		
//	Private data members

	private:
		LinkedList<string> item;
		LinkedList<char> abbrev;
};

//	Global operators

ostream& operator<<(ostream& out, const Menu& m);

#endif