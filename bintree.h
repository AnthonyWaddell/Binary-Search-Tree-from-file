#ifndef BINTREE_H
#define BINTREE_H
//----------------------------------------------------------------------------
// File: Poly.h
// 
// Description: Function outlines for the Poly class
// 
// Programmer:	Anthony Waddell
// 
// Environment: Hardware: PC, i7
//              Software: OS: Windows 10 
//              Compiles under Microsoft Visual C++ 2015, g++
//---------------------------------------------------------------------------
#include "nodedata.h"
#include <algorithm>

using namespace std;

class BinTree
{
private:

	// Node to contain data and fill in tree
	struct Node
	{
		NodeData* data;						// pointer to data object
		Node* left_child;					// left subtree pointer
		Node* right_child;					// right subtree pointer
	};
	Node* root;								// root of the tree

public:

	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	bool isEmpty() const;					// true if tree is empty, otherwise false

	// Make Empty function and helper
	void makeEmpty();						// make the tree empty so isEmpty returns true
	void makeEmpty_Helper(Node *&cur);

	// Assignment operator and helper
	BinTree& operator=(const BinTree &other_tree);
	void assignment_Helper(Node *other_cur, Node *&cur);

	// Comparison operators and helper
	bool operator==(const BinTree &other_tree) const;
	int compare_Nodes(Node * left, Node * right) const;
	inline bool operator!=(const BinTree &other_tree) const
	{
		return !(*this == other_tree);
	}

	// Insert function and helper
	bool insert(NodeData *datum);
	bool insert_Helper(Node *& cur, NodeData *datum);

	// Retrival function and helper
	bool retrieve(const NodeData &find_value, NodeData *&datum);
	bool retrieve_Helper(const NodeData &find_value, NodeData *&datum, Node *&cur) const;

	// Get height function and helpers
	int getHeight(const NodeData &find_value) const;
	int getHeight_Helper(Node *cur, const NodeData &find_value) const;
	int level(const NodeData &find_value, Node *cur) const;
	int level_Helper(Node *cur) const;

	// BST to array function and helper
	void bstreeToArray(NodeData *arr[]);
	void bstToArray_Helper(NodeData *arr[], Node *cur, int &index);

	// Array to BST and helper
	void arrayToBSTree(NodeData *arr[]);
	void arrayToBST_Helper(NodeData *arr[], Node *cur, int first, int last);

	// Display function and helper 
	void displaySideways() const;
	void sideways(Node*, int) const;
	
	// Overloaded output operator and helper function
	friend ostream & operator<<(ostream &sout, BinTree &tree);
	void inorder_Helper(Node *cur) const;
};
#endif