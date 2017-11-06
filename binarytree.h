#ifndef BINARYTREE_H
#define BINARYTREE_H

//	Header files

#include <iostream>
#include <string>
#include <cassert>
#include "../BinaryTreeNode Class/binarytreenode.h"
#include "../LinkedQueue Class/linkedqueue.h"

//	Forward class declarations for classes that use the BinaryTree class

template <class T> class BinaryTreeIterator;
template <class T> class BinaryTreePreorderIterator;
template <class T> class BinaryTreeInorderIterator;
template <class T> class BinaryTreePostorderIterator;
template <class T> class BinaryTreeLevelorderIterator;

using namespace std;

/****************************************************************************
*																			*
*	The BinaryTree class definition											*
*																			*
****************************************************************************/

template<class T>
class BinaryTree
{
//	Friends

	friend class BinaryTreeIterator<T>;
	friend class BinaryTreePreorderIterator<T>;
	friend class BinaryTreeInorderIterator<T>;
	friend class BinaryTreePostorderIterator<T>;
	friend class BinaryTreeLevelorderIterator<T>;
	
//	Public member functions

	public:
	
	//	Constructors

		BinaryTree() {root = NULL;}
		
		BinaryTree(const T& value) {root = new BinaryTreeNode<T>(value);}
		
		BinaryTree(const BinaryTree<T>& lf, const BinaryTree<T>& rt)
			{root = new BinaryTreeNode<T>; makeCopy(root->left, lf.root), makeCopy(root->right, rt.root);}
			
		BinaryTree(const T& value, const BinaryTree<T>& lf, const BinaryTree<T>& rt)
			{root = new BinaryTreeNode<T>(value); makeCopy(root->left, lf.root), makeCopy(root->right, rt.root);}
			
		BinaryTree(const BinaryTree<T>& tree)
			{makeCopy(root, tree.root);}

	//	Destructor

		~BinaryTree() {makeEmpty();}

	//	Inspectors

		int size() const {return size(root);}
		int height() const {return height(root);}
		bool isEmpty() const {return root == NULL;}

		T& rootValue() const {assert(root != NULL); return root->data;}

		BinaryTree<T> leftSubtree();
		BinaryTree<T> rightSubtree();

		bool isCountBalanced() const {return isCountBalanced(root);}
		bool isHeightBalanced() const {return isHeightBalanced(root);}

	//	Mutators

		void makeEmpty() {makeEmpty(root);}
		void setRoot(const T& value)
			{assert(root != NULL); root->data = value;}
		
	//	Facilitators
	
		bool isEqual(BinaryTree<T> tree) const {return isEqual(root, tree.root);}
		void input(istream& in) {makeEmpty(); input(root, in);}
		void output(ostream& out) const {output(root, out);}
	
	//	Operators

		BinaryTree<T>& operator=(const BinaryTree<T>&);

	//	Traversal functions
	
		void preorderTraversal(void (* visit) (BinaryTreeNode<T>*)) const
			{preorderTraversal(root, visit);}
		void inorderTraversal(void (* visit) (BinaryTreeNode<T>*)) const
			{inorderTraversal(root, visit);}
		void postorderTraversal(void (* visit) (BinaryTreeNode<T>*)) const
			{postorderTraversal(root, visit);}
		void levelorderTraversal(void (* visit) (BinaryTreeNode<T>*)) const;

	//	Other member functions
	
		T* search(const T& value) const {return Search(root, value);}
		void draw() const {draw(root, 0);}
		void validate() const;

//	Private member functions

	protected:

		void makeCopy(BinaryTreeNode<T>*& new_node, const BinaryTreeNode<T>* old_node);
		void makeEmpty(BinaryTreeNode<T>*& node);

	//	Used by the inspectors

		int size(BinaryTreeNode<T>* node) const;
		int height(BinaryTreeNode<T>* node) const;
		bool isHeightBalanced(BinaryTreeNode<T>* node) const;
		bool isCountBalanced(BinaryTreeNode<T>* node) const;

	//	Used by the facilitators

		bool isEqual(BinaryTreeNode<T>* node1, BinaryTreeNode<T>* node2) const;
		void input(BinaryTreeNode<T>*& node, istream& in);
		void output(const BinaryTreeNode<T>* node, ostream& out) const ;

	//	Used by other member functions

		T* search(BinaryTreeNode<T>* node, const T& value) const;
		void draw(BinaryTreeNode<T>* node, int indent) const;
		void addNodePtrsToArray(BinaryTreeNode<T>** array, int& pos,
			BinaryTreeNode<T>* node) const;
	
	//	Used by traversal functions
	
		void preorderTraversal(BinaryTreeNode<T>* node,
			void (* Visit) (BinaryTreeNode<T>* node)) const;
		void inorderTraversal(BinaryTreeNode<T>* node,
			void (* Visit) (BinaryTreeNode<T>* node)) const;
		void postorderTraversal(BinaryTreeNode<T>* node,
			void (* Visit) (BinaryTreeNode<T>* node)) const;

//	Data members

	protected:
	
		BinaryTreeNode<T>* root;	// Pointer to the root node
};

//	Operators

template <class T>
bool operator==(const BinaryTree<T>& tree1, const BinaryTree<T>& tree2);
template <class T>
bool operator!=(const BinaryTree<T>& tree1, const BinaryTree<T>& tree2);

template <class T>
istream& operator>>(istream& in, BinaryTree<T>& tree);
template <class T>
ostream& operator<<(ostream& out, const BinaryTree<T>& tree);

/****************************************************************************
*																			*
*	Function:	leftSubtree													*
*																			*
*	Purpose:	To create a copy of the left subtree						*
*																			*
****************************************************************************/

template <class T>
BinaryTree<T> BinaryTree<T>::leftSubtree()
{
	assert(root != NULL);
	BinaryTree<T> tree;
	makeCopy(tree.root, root->left);
	return tree;
}

/****************************************************************************
*																			*
*	Function:	rightSubtree												*
*																			*
*	Purpose:	To create a copy of the right subtree						*
*																			*
****************************************************************************/

template <class T>
BinaryTree<T> BinaryTree<T>::rightSubtree()
{
	assert(root != NULL);
	BinaryTree<T> tree;
	makeCopy(tree.root, root->right);
	return tree;
}

/****************************************************************************
*																			*
*	Function:	makeCopy													*
*																			*
*	Purpose:	To create a copy of an existing binary tree					*
*																			*
****************************************************************************/

template <class T>
void BinaryTree<T>::
makeCopy(BinaryTreeNode<T>*& new_node, const BinaryTreeNode<T>* old_node)
{
	if (old_node == NULL)
		new_node = NULL;
	else
	{
		new_node = new BinaryTreeNode<T>(old_node->data);
		makeCopy(new_node->left, old_node->left);
		makeCopy(new_node->right, old_node->right);
	}
	return;
}

/****************************************************************************
*																			*
*	Function:	size														*
*																			*
*	Purpose:	To determine recursively the number of nodes in a binary	*
*				tree								  						*
*																			*
****************************************************************************/

template<class T>
int BinaryTree<T>::size(BinaryTreeNode<T>* node) const
{
	if (node == NULL)
		return 0;
	else
		return 1 + size(node->left) + size(node->right);
}
		
/****************************************************************************
*																			*
*	Function:	height														*
*																			*
*	Purpose:	To determine recursively the height of a binary tree		*
*																			*
****************************************************************************/

template<class T>
int BinaryTree<T>::height(BinaryTreeNode<T>* node) const
{
	if (node == NULL)
		return -1;
	else
		return 1 + max(height(node->left), height(node->right));
}
		
/****************************************************************************
*																			*
*	Function:	isCountBalanced												*
*																			*
*	Purpose:	To determine recursively whether a binary tree is 			*
*				count-balanced												*
*																			*
****************************************************************************/

template <class T>
bool BinaryTree<T>::isCountBalanced(BinaryTreeNode<T>* node) const
{
	if (node == NULL)
		return true;
		
	if (!isCountBalanced(node->left))
		return false;
		
	if (!isCountBalanced(node->right))
		return false;
		
	return abs(size(node->left) - size(node->right)) <= 1;
}

/****************************************************************************
*																			*
*	Function:	isHeightBalanced											*
*																			*
*	Purpose:	To determine recursively whether a binary tree is 			*
*				height-balanced												*
*																			*
****************************************************************************/

template <class T>
bool BinaryTree<T>::isHeightBalanced(BinaryTreeNode<T>* node) const
{
	if (node == NULL)
		return true;
		
	if (!isHeightBalanced(node->left))
		return false;
		
	if (!isHeightBalanced(node->right))
		return false;
		
	return abs(height(node->left) - height(node->right)) <= 1;
}

/****************************************************************************
*																			*
*	Function:	makeEmpty													*
*																			*
*	Purpose:	To delete the nodes of a binary tree  						*
*																			*
****************************************************************************/

template<class T>
void BinaryTree<T>::makeEmpty(BinaryTreeNode<T>*& node)
{
	if (node != NULL)
	{
		makeEmpty(node->left);
		makeEmpty(node->right);
		delete node;
		node = NULL;
	}
	return;
}

/****************************************************************************
*																			*
*	Function:	isEqual														*
*																			*
*	Purpose:	To determine recursively whether this binary tree is 		*
*				equal to the specified binary tree					  		*
*																			*
****************************************************************************/

template<class T>
bool BinaryTree<T>::isEqual(BinaryTreeNode<T>* node1, BinaryTreeNode<T>* node2) const
{
	if (node1 == NULL && node2 == NULL)
		return true;
	else if (node1 == NULL || node2 == NULL)
		return false;
	else
		return (node1->data == node2->data) 
			&& isEqual(node1->left, node2->left) 
			&& isEqual(node1->right, node2->right);
}

/****************************************************************************
*																			*
*	Function:	input														*
*																			*
*	Purpose:	To extract recursively a binary tree from the input stream	*
*																			*
****************************************************************************/

template <class T>
void BinaryTree<T>::input(BinaryTreeNode<T>*& node, istream& in)
{
//	Read the open brace
	
	char c;
	in >> c;
	assert(c == '{');

//	Read the tree

	in >> c;
	in.putback(c);
	if (c != '}')
	{
	//	Read the root of the tree
	
		T value;
		in >> value;
		node = new BinaryTreeNode<T>(value);
	
	//	Read a comma and then the left subtree
	
		in >> c;
		assert(c == ',');
		input(node->left, in);
	
	//	Read a comma and then the right subtree
	
		in >> c;
		assert(c == ',');
		input(node->right, in);
	}
	
//	Read the close brace

	in >> c;
	assert(c == '}');
	return;
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To insert recursively a binary tree into the output stream	*
*																			*
****************************************************************************/

template <class T>
void BinaryTree<T>::output(const BinaryTreeNode<T>* node, ostream& out) const
{
	out << "{";
	if (node != NULL)
	{
	//	Output the root
	
		out << node->data;
		out << ", ";
	
	//	Output the left subtree
	
		output(node->left, out);
		out << ", ";
	
	//	Output the right subtree
	
		output(node->right, out);
	}
	out << "}";
	return;
}

/****************************************************************************
*																			*
*	Function:	operator=													*
*																			*
*	Purpose:	To assign a binary tree to a binary tree.  This is the		*
*				assignment operator.										*
*																			*
****************************************************************************/

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& tree)
{
	if (this != &tree)
	{
		makeEmpty();
		makeCopy(root, tree.root);
	}
	return *this;
}

/****************************************************************************
*																			*
*	Function:	search														*
*																			*
*	Purpose:	To inspect recursively every node to find a specified 		*
*				value  														*
*																			*
****************************************************************************/

template<class T>
T* BinaryTree<T>::search(BinaryTreeNode<T>* node, const T& value) const
{
	if (node == NULL)
		return NULL;
	else if (node->data == value)
		return &(node->data);
	else
	{
		T* found = search(node->left, value);
		if (found != NULL)
			return found;
		else
			return search(node->right, value);
	}
}

/****************************************************************************
*																			*
*	Function:	draw														*
*																			*
*	Purpose:	To output recursive the data part of the nodes, indenting	*
*				according to the level in the tree.							*
*																			*
****************************************************************************/

template<class T>
void BinaryTree<T>::draw(BinaryTreeNode<T>* node, int indent) const
{
	if (node != NULL)
	{
	//	Draw the right subtree
	
		draw(node->right, indent + 1);
	
	//	Indent and print node
	
		for (int i = 0; i < indent; i++)
			cout << "    ";
		cout << node->data << endl;
	
	//	Draw the left subtree
	
		draw(node->left, indent + 1);
	}
}

/****************************************************************************
*																			*
*	Function:	validate													*
*																			*
*	Purpose:	To verify that the BinaryTree has a valid structure			*
*																			*
****************************************************************************/

template <class T>
void BinaryTree<T>::validate() const
{
	int sz = size();
	BinaryTreeNode<T>** array = new BinaryTreeNode<T>*[sz];
	int pos = 0;
	addNodePtrsToArray(array, pos, root);
	for (int i = 1; i < sz; i++)
		for (int j = 0; j < i; j++)
			assert(array[i] != array[j]);
	return;
}

/****************************************************************************
*																			*
*	Function:	addNodePtrsToArray											*
*																			*
*	Purpose:	To add addresses of the nodes to an array of node pointers	*
*																			*
****************************************************************************/

template <class T>
void BinaryTree<T>::addNodePtrsToArray(BinaryTreeNode<T>** array, int& pos,
BinaryTreeNode<T>* node) const
{
	if (node != NULL)
	{
		array[pos++] = node;
		addNodePtrsToArray(array, pos, node->left);
		addNodePtrsToArray(array, pos, node->right);
	}
	return;
}

/****************************************************************************
*																			*
*	Function:	preorderTraversal											*
*																			*
*	Purpose:	To visit recursively the nodes of a binary tree in NLR 		*
*				order, executing the function Visit at each node			*
*																			*
****************************************************************************/

template<class T>
void BinaryTree<T>::
preorderTraversal(BinaryTreeNode<T>* node, void (* Visit) (BinaryTreeNode<T>*)) const
{
	if (node != NULL)
	{
		Visit(node);
		preorderTraversal(node->left, Visit);
		preorderTraversal(node->right, Visit);
	}
}

/****************************************************************************
*																			*
*	Function:	inorderTraversal											*
*																			*
*	Purpose:	To visit recursively the nodes of a binary tree in NLR 		*
*				order, executing the function Visit at each node			*
*																			*
****************************************************************************/

template<class T>
void BinaryTree<T>::
inorderTraversal(BinaryTreeNode<T>* node, void (* Visit) (BinaryTreeNode<T>*)) const
{
	if (node != NULL)
	{
		inorderTraversal(node->left, Visit);
		Visit(node);
		inorderTraversal(node->right, Visit);
	}
}

/****************************************************************************
*																			*
*	Function:	postorderTraversal											*
*																			*
*	Purpose:	To visit recursively the nodes of a binary tree in NLR 		*
*				order, executing the function Visit at each node			*
*																			*
****************************************************************************/

template<class T>
void BinaryTree<T>::
postorderTraversal(BinaryTreeNode<T>* node, void (* Visit) (BinaryTreeNode<T>*)) const
{
	if (node != NULL)
	{
		postorderTraversal(node->left, Visit);
		postorderTraversal(node->right, Visit);
		Visit(node);
	}
}

/****************************************************************************
*																			*
*	Function:	levelorderTraversal											*
*																			*
*	Purpose:	To visit recursively the nodes of a binary tree in level	*
*				order, executing the function Visit at each node			*
*																			*
****************************************************************************/

template<class T>
void BinaryTree<T>::
levelorderTraversal(void (* Visit) (BinaryTreeNode<T>*)) const
{
	LinkedQueue<BinaryTreeNode<T>*> queue;
	
	BinaryTreeNode<T>* node;
	
	if (root != NULL)
		queue.enqueue(root);
	
	while (!queue.isEmpty())
	{
		node = queue.dequeue();
		
		Visit(node);
		
		if (node->left != NULL)
			queue.enqueue(node->left);
			
		if (node->right != NULL) 
			queue.enqueue(node->right);
	}
	
	return;	
}

/****************************************************************************
*																			*
*	Function:	operator==													*
*																			*
*	Purpose:	To compare two binary trees to see if they are equal		*
*																			*
****************************************************************************/

template <class T>
bool operator==(const BinaryTree<T>& tree1, const BinaryTree<T>& tree2)
{
	return tree1.isEqual(tree2);
}

/****************************************************************************
*																			*
*	Function:	operator!=													*
*																			*
*	Purpose:	To compare two binary trees to see if they are not 			*
*				equal														*
*																			*
****************************************************************************/

template <class T>
bool operator!=(const BinaryTree<T>& tree1, const BinaryTree<T>& tree2)
{
	return !tree1.isEqual(tree2);
}

/****************************************************************************
*																			*
*	Function:	operator>>													*
*																			*
*	Purpose:	To extract a binary tree from the input stream				*
*																			*
****************************************************************************/

template <class T>
istream& operator>>(istream& in, BinaryTree<T>& tree)
{
	tree.input(in);
	return in;
}

/****************************************************************************
*																			*
*	Function:	operator<<													*
*																			*
*	Purpose:	To insert a binary tree into the output stream				*
*																			*
****************************************************************************/

template <class T>
ostream& operator<<(ostream& out, const BinaryTree<T>& tree)
{
	tree.output(out);
	return out;
}

#endif