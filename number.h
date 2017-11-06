#ifndef NUMBER_H
#define NUMBER_H

//	Header files

#include "token.h"

/************************************************************************
*																		*
*	Definition of the Number class										*
*																		*
************************************************************************/

class Number : public Token
{
//	Public member functions

	public:
		
	//	Constructors
	
		Number(double val = 0.0) : mValue(val) {}
	
	//	Inspectors
	
		double value() const {return mValue;}
		
	//	Facilitators
	
		void input(istream& in) {in >> mValue;}
		void output(ostream& out) const {out << mValue;}
		
	//	Other member functions
	
		Prec prec() const {return NULL_PREC;}
		
//	Private data members

	private:
	
		double mValue;
};

#endif