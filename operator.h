#ifndef OPERATOR_H
#define OPERATOR_H

//	Header files

#include "token.h"

/************************************************************************
*																		*
*	Definition of the Operator class									*
*																		*
************************************************************************/

class Operator : public Token
{
//	Public member functions

	public:
		
	//	Inspectors
	
		char value() const {return mOper;}
		
	//	Facilitators
	
		void input(istream& in) {char c; in >> c; assert(c == '+' || c == '-' || c == '/' || c == '*'); mOper = c;}
		void output(ostream& out) const {out << mOper;}
		
	//	Other member functions
	
		Prec prec() const 
			{if (mOper == '+' || mOper == '-') return ADD_PREC; 
			 else return MUL_PREC;}
		
//	Private data members

	private:
	
		char mOper;
};

#endif