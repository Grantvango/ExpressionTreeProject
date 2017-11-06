#ifndef TOKEN_H
#define TOKEN_H

//	Header files

#include <iostream>
#include <cassert>

using namespace std;

/************************************************************************
*																		*
*	Definition of the Token class										*
*																		*
************************************************************************/

enum Prec {NULL_PREC, PAREN_PREC, ADD_PREC, MUL_PREC};

class Token
{
//	Public member functions

	public:
	
		virtual void input(istream& in) = 0;
		virtual void output(ostream& out) const = 0;
		virtual Prec prec() const = 0;
		
};

//	Operators

istream& operator>>(istream& in, Token& t);
ostream& operator<<(ostream& out, const Token& t);

istream& operator>>(istream& in, Token& t)
{
	t.input(in);
	return in;
}

ostream& operator<<(ostream& out, const Token& t)
{
	t.output(out);
	return out;
}

#endif