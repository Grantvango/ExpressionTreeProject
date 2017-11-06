#include <cassert>
#include "menu.h"

/****************************************************************************
*																			*
*	Function:	Menu(string [], char [], int)								*
*																			*
*	Purpose:	To construct a menu from the specified arrays of strings	*
*				and characters of the specified size					 	*
*																			*
****************************************************************************/

Menu::Menu(string it[], char ab[], int sz)
{
	assert(sz >= 0);

//	Store each item and abbreviation

	for (int i = 0; i < sz; i++)
	{
		item.pushBack(it[i]);
		abbrev.pushBack(ab[i]);
	}
	return;
}
		
/****************************************************************************
*																			*
*	Function:	addItem														*
*																			*
*	Purpose:	To add the specified menu item at the specified position 	*
*																			*
****************************************************************************/

void Menu::addItem(string it, char ab, int pos)
{
//	Add the new items to the menu in the specified positions

	item.insert(pos, it);
	abbrev.insert(pos, ab);
	return;
}

/****************************************************************************
*																			*
*	Function:	appendItem													*
*																			*
*	Purpose:	To apped the specified menu item to the end of the array 	*
*																			*
****************************************************************************/

void Menu::appendItem(string it, char ab)
{
//	Add the new item to the end of the array

	item.pushBack(it);
	abbrev.pushBack(ab);
	return;
}

/****************************************************************************
*																			*
*	Function:	deleteItem													*
*																			*
*	Purpose:	To delete the menu item that is in the specified position 	*
*																			*
****************************************************************************/

void Menu::deleteItem(int pos)
{
	item.remove(pos);
	abbrev.remove(pos);
	return;
}

/****************************************************************************
*																			*
*	Function:	replaceItem													*
*																			*
*	Purpose:	To replace the menu item that is in the specified position	*
*				with the specified menu item							 	*
*																			*
****************************************************************************/

void Menu::replaceItem(string it, char ab, int pos)
{
	item[pos] = it;
	abbrev[pos] = ab;
	return;
}

/****************************************************************************
*																			*
*	Function:	moveItem													*
*																			*
*	Purpose:	To move the menu item that is in the specified old posi-	*
*				tion to the specified new position							*
*																			*
****************************************************************************/

void Menu::moveItem(int oldPos, int newPos)
{
//	Swap the menu items

	string tempItem = item[oldPos];
	item[oldPos] = item[newPos];
	item[newPos] = tempItem;

//	Swap the abbreviations

	char tempAbbrev = abbrev[oldPos];
	abbrev[oldPos] = abbrev[newPos];
	abbrev[newPos] = tempAbbrev;
	return;
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To display the menu items along with their one-character	*
*				abbrevations											 	*
*																			*
****************************************************************************/

void Menu::output(ostream& out) const
{
	cout << "MENU" << endl << endl;
	for (int i = 0; i < size(); i++)
		cout << '(' << abbrev[i] << ") " << item[i] << endl;
	return;
}

/****************************************************************************
*																			*
*	Function:	getChoice													*
*																			*
*	Purpose:	To read the  user's menu choice. The function returns the 	*
*				one-character abbreviation if the input is valid, and it 	*
*				returns a blank space if it is not valid 					*
*																			*
****************************************************************************/

char Menu::getChoice() const
{
//	Get the user's menu choice

	char choice;
	cin >> choice;
	choice = toupper(choice);

//	Search for it in the array of abbreviations

	int pos = abbrev.search(choice);

//	See whether it is valid

	if (pos == -1)
		return ' ';
	else
		return choice;
}

/****************************************************************************
*																			*
*	Function:	operator<<													*
*																			*
*	Purpose:	To display the menu items along with their one-character	*
*				abbrevations											 	*
*																			*
****************************************************************************/

ostream& operator<<(ostream& out, const Menu& m)
{
	m.output(out);
	return out;
}
