#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

//	Header files

#include <iostream>
#include <cassert>
#include "../../Labs/Project_4A/number.h"
#include "../../Labs/Project_4A/operator.h"
#include "../../Lab Source Files/Lab 13/BinaryTree Class/binarytree.h"

using namespace std;

/****************************************************************************
*																			*
*	The ExpressionTree class definition										*
*																			*
****************************************************************************/

class ExpressionTree: public BinaryTree<Token*>
{
	
	public:
			
	//	Constructor
		
		ExpressionTree() : BinaryTree<Token*>() {}
		ExpressionTree(Token* tok) : BinaryTree<Token*>(tok) {}
		ExpressionTree(Token* tok, ExpressionTree tr, ExpressionTree tr2) : BinaryTree<Token*>(tok, tr, tr2) {}

	//Member Functions

		void draw() const {draw(root, 0);}
		void draw(BinaryTreeNode<Token*>* node, int indent) const;

	//	Traversal functions

		double evaluate() const
			{return evaluate(root);}
		void infix(void (* visit) (BinaryTreeNode<Token*>*)) const
			{infix(root, visit);}

	//	Used by traversal functions

		double evaluate(BinaryTreeNode<Token*>* node) const;
		void infix(BinaryTreeNode<Token*>* node,
			void (* Visit) (BinaryTreeNode<Token*>* node)) const;
	
				
	//	protected data members

		protected:
	
};

/****************************************************************************
*																			*
*	Function:	draw														*
*																			*
*	Purpose:	To output recursive the data part of the nodes, indenting	*
*				according to the level in the tree.							*
*																			*
****************************************************************************/

void ExpressionTree::draw(BinaryTreeNode<Token*>* node, int indent) const
{
	if (node != NULL)
	{
	//	Draw the right subtree
	
		draw(node->rightNode(), indent + 1);
	
	//	Indent and print node
	
		for (int i = 0; i < indent; i++)
			cout << "    ";
		cout << *node->value() << endl;
	
	//	Draw the left subtree
	
		draw(node->leftNode(), indent + 1);
	}
}

/****************************************************************************
*																			*
*	Function:	evaluate													*
*																			*
*	Purpose:	To visit recursively the nodes of a Expression tree	and 	*
*				and give a value											*
*																			*
****************************************************************************/

double ExpressionTree::evaluate(BinaryTreeNode<Token*>* node) const
{
	char c;
	Token* tok = node->value();

	if(node->leftNode() == NULL || node->rightNode() == NULL)
		return ((Number*)node->value())->value();

	if(typeid(*tok) == typeid(Operator))
	{
		c = ((Operator*)tok)->value();
		if(c == '+')
		{
			return evaluate(node->leftNode()) + evaluate(node->rightNode());
		}
		if(c == '*')
		{
			return evaluate(node->leftNode()) * evaluate(node->rightNode());
		}
		if(c == '/')
		{
			return evaluate(node->leftNode()) / evaluate(node->rightNode());
		}
	}
	return 0.0;
}

/****************************************************************************
*																			*
*	Function:	infix														*
*																			*
*	Purpose:	To visit recursively the nodes of an expression tree		*
*				and put them in infix order									*
*																			*
****************************************************************************/

void ExpressionTree::
infix(BinaryTreeNode<Token*>* node, void (* Visit) (BinaryTreeNode<Token*>*)) const
{
	Token* tok = node->value();
	Token* right; Token* left;

	if (node != NULL)
	{
		if(node->leftNode() != NULL)
			left = node->leftNode()->value();
		if(node->rightNode() != NULL)
			right = node->rightNode()->value();

		if(((left->prec() <= tok->prec()) && (typeid(*left) == typeid(Operator))) && ((right->prec() <= tok->prec()) && (typeid(*right) == typeid(Operator)))){
			infix(node->leftNode(), Visit);
			Visit(node);
			infix(node->rightNode(), Visit);
		} else if((right->prec() <= tok->prec()) && (typeid(*right) == typeid(Operator))){
			inorderTraversal(node->leftNode(), Visit);
			Visit(node);
			cout << '(';
			infix(node->rightNode(), Visit);
			cout << ')';
		} else if((left->prec() <= tok->prec()) && (typeid(*left) == typeid(Operator))){
			cout << '(';
			infix(node->leftNode(), Visit);
			cout << ')';
			Visit(node);
			inorderTraversal(node->rightNode(), Visit);
		} else if((left->prec() <= tok->prec()) && (typeid(*left) == typeid(Operator)) && (typeid(*right) == typeid(Number))){
			cout << '(';
			infix(node->leftNode(), Visit);
			Visit(node);
			inorderTraversal(node->rightNode(), Visit);
			cout << ')';
		} else {
			inorderTraversal(node->leftNode(), Visit);
			Visit(node);
			inorderTraversal(node->rightNode(), Visit);
		}
	}
}

#endif