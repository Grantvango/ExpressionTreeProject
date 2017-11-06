#ifndef RPAREN_H
#define RPAREN_H

//	Header files

#include "token.h"

/************************************************************************
*																		*
*	Definition of the RParen class										*
*																		*
************************************************************************/

class RParen : public Token
{
//	Public member functions

	public:
		
	//	Inspectors
	
		char value() const {return ')';}
		
	//	Facilitators
	
		void input(istream& in) {char c; in >> c; assert(c == ')');}
		void output(ostream& out) const {out << ')';}
		
	//	Other member functions
	
		Prec prec() const {return PAREN_PREC;}
};

#endif