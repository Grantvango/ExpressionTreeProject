//	Include header files

#include <iostream>
#include <fstream>
#include <string>
#include "../../Labs/Project_4A/token.h"
#include "../../Labs/Project_4A/number.h"
#include "../../Labs/Project_4A/lparen.h"
#include "../../Labs/Project_4A/rparen.h"
#include "../../Labs/Project_4A/operator.h"
#include "../../Lab Source Files/Project 4A - Infix to Postfix/linkedlist.h"
#include "../../Lab Source Files/Project 4A - Infix to Postfix/linkedlistnode.h"
#include "../../Lab Source Files/Project 4A - Infix to Postfix/linkedlistwtail.h"
#include "../../Lab Source Files/Project 4A - Infix to Postfix/linkedqueue.h"
#include "../../Lab Source Files/Project 4A - Infix to Postfix/linkedstack.h"
#include "../../Lab Source Files/Project 3B - Hash Tables/Menu Class/menu.h"
#include "../../Lab Source Files/Lab 13/BinaryTree Class/binarytree.h"
#include "expressiontree.h"


using namespace std;

void print(BinaryTreeNode<Token*>* node);
void print2(BinaryTreeNode<Token*>* node);
Token* getToken();
LinkedQueue<Token*> infix2postfix();
ExpressionTree buildTree(LinkedQueue<Token*> q);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main()
{
	//Creates a menu to edit table 
	Menu main_Menu;
	main_Menu.appendItem("Enter an expression", 'N'); 
	main_Menu.appendItem("Draw expression tree", 'D'); 
	main_Menu.appendItem("Prefix notation", 'R'); 
	main_Menu.appendItem("Infix notation", 'I'); 
	main_Menu.appendItem("Postfix notation", 'P'); 
	main_Menu.appendItem("Evaluate expression", 'E'); 
	main_Menu.appendItem("Quit", 'Q'); 

	cout << main_Menu << endl;
	cout << "Enter a menu choice: ";
	char choice = main_Menu.getChoice();
	cout << endl;
	
	ExpressionTree tree;
	LinkedQueue<Token*> q1;

	//gets choice from user and edits table 
	while (choice != 'Q'){

		switch (choice)
		{
			case 'N': q1 = infix2postfix(); tree = buildTree(q1);
				break;
			case 'D': tree.draw();
				break;
			case 'R': tree.preorderTraversal(print);
				break;
			case 'I': tree.infix(print2);
				break;
			case 'P': tree.postorderTraversal(print);
				break;
			case 'E': cout << tree.evaluate() << endl;
				break;
			case 'Q': exit(-1);
				break;
		}	

		cout << endl;
		cout << main_Menu << endl;
		cout << "Enter a menu choice: ";
		choice = main_Menu.getChoice();
		cout << endl;

	}
	
	cout << endl << "Good-bye!" << endl;

	return 0;
}

/****************************************************************************
*																			*
*	Function:	print														*
*																			*
*	Purpose:	To print the data component of the node						*
*																			*
****************************************************************************/

void print(BinaryTreeNode<Token*>* node)
{
	cout << *node->value() << " ";
	return;
}

/****************************************************************************
*																			*
*	Function:	print														*
*																			*
*	Purpose:	To print the data component of the node						*
*																			*
****************************************************************************/

void print2(BinaryTreeNode<Token*>* node)
{
	cout << *node->value();
	return;
}


/****************************************************************************
*																			*
*	Function:	getToken													*
*																			*
*	Purpose:	To return the next token from the input stream				*
*																			*
****************************************************************************/

Token* getToken()
{
	Token* p;

//	Get first character in istream buffer

	char c;
	cin.get(c);

	if (c == '\n')
		return NULL;
	
//	Skip past any whitespace characters

	while (isspace(c))
		cin.get(c);

	cin.putback(c);
	
//	If it is a number, create a Number object

	if (isdigit(c))
		p = new Number;

//	If it is an operator, create an Operator object

	else if (c == '+' || c == '-' || c == '/' || c == '*')
		p = new Operator;

//	If it is a left parenthesis, create an LParen object

	else if (c == '(')
		p = new LParen;

//	If it is a right parenthesis, create an RParen object

	else if (c == ')')
		p = new RParen;

//	Anything else indicates the end of the expression

	else
	{
		cout << "Invalid token." << endl;
		return NULL;
	}

//	Read token;

	cin >> *p;

//	Return a pointer to the token

	return p;
}

/****************************************************************************
*																			*
*	Function:	infix2postfix												*
*																			*
*	Purpose:	Turns a infix expression into postfix expression			*
*																			*
****************************************************************************/

LinkedQueue<Token*> infix2postfix()
{
	//Creates a stack and queue
	LinkedQueue<Token*> queue;
	LinkedStack<Token*> stack;


	//How do I fix this
	cin.ignore();
	cout << "Enter an infix expression: ";
	 	 
	//A token tok to store all the tokens
	Token* tok = getToken();

	//While loop that runs through entire expression either pushing or enqueueing the expression
	while(tok != NULL)
	{
		//Numbers are enqueued
		if(typeid(*tok) == typeid(Number)) 
			queue.enqueue(tok);

		//LParen are pushed onto stack
		if(typeid(*tok) == typeid(LParen))
			stack.push(tok);
		
		//RParen pops tokens from stack and queues them and then gets rid of parens
		if(typeid(*tok) == typeid(RParen)) 
		{
			//Pops off token
			tok = stack.pop();

			//While loop to enqueue, checks if tok is not LParen
			while((typeid(*tok) != typeid(LParen)))
			{
				queue.enqueue(tok);
				tok = stack.pop();
			}
		}
		
		//Operators are pushed onto stack unless the while loop is true which then enqueues 
		if(typeid(*tok) == typeid(Operator)) 
		{
			while(!stack.isEmpty() && (typeid(*stack.top()) != typeid(LParen)) && (tok->prec() <= stack.top()->prec()))
				queue.enqueue(stack.pop());
			stack.push(tok);
		}
		tok = getToken();

	}
	
	//Pop off and enqueue all the operators
	while(!stack.isEmpty()){
		queue.enqueue(stack.pop());
	}

	return queue;
}

/****************************************************************************
*																			*
*	Function:	buildTree													*
*																			*
*	Purpose:	Turns a postfix expression into a single Expression Tree	*
*																			*
****************************************************************************/

ExpressionTree buildTree(LinkedQueue<Token*> q)
{
	ExpressionTree tr; ExpressionTree tr2;
	LinkedQueue<Token*> queue = q;
	LinkedStack<ExpressionTree> stk;
	Token* tok;

	while(!queue.isEmpty())
	{
	
		tok = queue.dequeue();

		if(typeid(*tok) == typeid(Number))
			stk.push(ExpressionTree(tok));

		if(typeid(*tok) == typeid(Operator))
		{
			tr = stk.pop();
			tr2 = stk.pop();
			stk.push(ExpressionTree(tok, tr2, tr));
		}
	}

	tr = stk.pop();
	return tr;
}






