//-----------------------------------------------------------------------------
// File:		BinTree.cpp
// Programmer:	Anthony Waddell
// Resources:
//		for getHeight https://www.geeksforgeeks.org/get-level-of-a-node-in-a-binary-tree/
//			and https://stackoverflow.com/questions/2597637/finding-height-in-binary-search-tree
//		for bsttoarray
//			https://stackoverflow.com/questions/22103718/binary-tree-to-array-wrong-values-inserted-into-array
//		for arraytobst
//			https://www.geeksforgeeks.org/sorted-array-to-balanced-bst/
//-----------------------------------------------------------------------------
#include "bintree.h"
using namespace std;

//-----------------------------------------------------------------------------
// Function:	BinTree::BinTree()
// Title:		Constructor
// Description: Constructs an empty BST object and sets root equal to NULL
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		N/A
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
BinTree::BinTree()
{
	root = NULL;
}

//-----------------------------------------------------------------------------
// Function:	BinTree::BinTree(const BinTree & other_tree)
// Title:		Copy Constructor
// Description: Constructs an empty BST object and sets equal to parameter tree
//
// Programmer:	Anthony Waddell
//
// Parameters:	const BinTree & other_tree; the other tree 
// Returns:		N/A
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
BinTree::BinTree(const BinTree &other_tree)
{
	root = NULL;
	*this = other_tree;
}

//-----------------------------------------------------------------------------
// Function:	BinTree::~BinTree(
// Title:		Destructor
// Description: Destructor for BST class object
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		N/A
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
BinTree::~BinTree()
{
	makeEmpty();
}

//-----------------------------------------------------------------------------
// Function:	bool BinTree::isEmpty() const
// Title:		boolean empty function
// Description: Tests to see if BST object is empty
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		true if BST object is empty; false if not
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
	bool empty;
	// If tree is empty
	if (root == NULL)
	{
		empty = true;
	}
	// Tree is not empy
	else
	{
		empty = false;
	}
	return empty;
}

//-----------------------------------------------------------------------------
// Function:	bool BinTree::isEmpty() const
// Title:		boolean empty function
// Description: Tests to see if BST object is empty
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		void
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
void BinTree::makeEmpty()
{
	makeEmpty_Helper(root);
}

//-----------------------------------------------------------------------------
// Function:	void BinTree::makeEmpty_Helper(Node *&cur)
// Title:		Helper function for makeEmpty
// Description: Clears data pointed to by BST nodes and then deletes node until
//					BST is empty in post order traversal
//
// Programmer:	Anthony Waddell
//
// Parameters:	Node *&cur; the current node to delete
// Returns:		void
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
void BinTree::makeEmpty_Helper(Node *&cur)
{
	// If node doesn't exist
	if (cur == NULL)
	{
		return;
	}
	// Recursively empy tree from left to right
	makeEmpty_Helper(cur->left_child);
	makeEmpty_Helper(cur->right_child);
	// Delete NodeData pointed to by node
	if (cur->data != NULL)
	{
		delete cur->data;
		cur->data = NULL;
	}
	// Delete node
	delete cur;
	cur = NULL;
}

//-----------------------------------------------------------------------------
// Function:	BinTree & BinTree::operator=(const BinTree & other_tree)
// Title:		Overloaded assignment operator for BST class
// Description: Sets *this equal to the BST object passed in
//
// Programmer:	Anthony Waddell
//
// Parameters:	const BinTree &other_tree; the tree to set equal to
// Returns:		BinTree; *this
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
BinTree &BinTree::operator=(const BinTree &other_tree)
{
	// Avoid self-assignment
	if (*this != other_tree)
	{
		// Clear *this first before assigning
		makeEmpty();
		assignment_Helper(other_tree.root, root);
	}
	return *this;
}

//-----------------------------------------------------------------------------
// Function:	void BinTree::assignment_Helper(Node *other_cur, Node *&cur)
// Title:		Helper function for assignment operator
// Description: Preorder traversal assignment
//
// Programmer:	Anthony Waddell
//
// Parameters:	Node *other_cur; pointer to node to copy data from
//				Node *&cur; reference to pointer to node to copy data into
// Returns:		void
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
void BinTree::assignment_Helper(Node *other_cur, Node *&cur)
{
	// As long as there is data to copy over
	if (other_cur != NULL)
	{
		// Allocate memory for new node and copy data from other_cur
		cur = new Node;
		NodeData *temp = new NodeData(*other_cur->data);
		cur->data = temp;
		// Recursively assign left and right child nodes
		assignment_Helper(other_cur->left_child, cur->left_child);
		assignment_Helper(other_cur->right_child, cur->right_child);
	}
	// Prevent memory leak
	else
	{
		cur = NULL;
	}
}

//-----------------------------------------------------------------------------
// Function:	bool BinTree::operator==(const BinTree & other_tree) const
// Title:		Comparison operator
// Description: Overloaded comparison operator for BST class objects
//
// Programmer:	Anthony Waddell
//
// Parameters:	const BinTree &other_tree; the BST object to be compared to
// Returns:		true if trees are equal; false if not
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
bool BinTree::operator==(const BinTree &other_tree) const
{
	bool equal = compare_Nodes(root, other_tree.root);
	return equal;
}

//-----------------------------------------------------------------------------
// Function:	int BinTree::compare_Nodes(Node * left, Node * right) const
// Title:		Helper function for equals operator for BST class
// Description: Recursively compares nodes in preorder traversal to check for 
//					equality
//
// Programmer:	Anthony Waddell
//
// Parameters:	Node *left; the node of *this
//				Node *right; the node of the comparator
// Returns:		int
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
int BinTree::compare_Nodes(Node *left, Node *right) const
{
	// Both empty (not in tree)
	if (left == NULL && right == NULL)
	{
		return 1;
	}
	// Both contain data
	else if (left != NULL && right != NULL)
	{
		return
			// Confirm equal data and equal left and right sub trees
			(*left->data == *right->data &&
			compare_Nodes(left->left_child, right->left_child) &&
			compare_Nodes(left->right_child, right->right_child))
			;
	}
	// Fail state, one empty and one not
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
// Function:	bool BinTree::insert(NodeData *datum)
// Title:		Insert function for BST class
// Description: Attempts to insert a pointer to NodeData object into BST object
//
// Programmer:	Anthony Waddell
//
// Parameters:	NodeData *datum; the data to be inserted
// Returns:		true if data data inserted; false if not
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
bool BinTree::insert(NodeData *datum)
{
	bool inserted = insert_Helper(root, datum);
	return inserted;
}

//-----------------------------------------------------------------------------
// Function:	bool BinTree::insert_Helper(Node *& cur, NodeData * datum)
// Title:		Helper function for insert function of BST class
// Description: Inserts data into tree if it does not already exist
//
// Programmer:	Anthony Waddell
//
// Parameters:	Node *&cur; reference to pointer to Node object to insert data
//				NodeData * datum; pointer to NodeData to be inserted
// Returns:		true if data data inserted; false if not
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
bool BinTree::insert_Helper(Node *&cur, NodeData *datum)
{
	// Insert when empty spot is found
	if (cur == NULL)
	{
		cur = new Node;
		cur->data = datum;
		cur->left_child = NULL;
		cur->right_child = NULL;
		// If tree is empty, this is root node
		if (isEmpty())
		{
			root = cur;
		}
		return true;
	}
	// Duplicate node found, do not insert
	else if (*datum == *cur->data)
	{
		return false;
	}
	// Insert left for smaller data value
	else if (*datum < *cur->data)
	{
		insert_Helper(cur->left_child, datum);
	}
	// Insert right for larger data value
	else
	{
		insert_Helper(cur->right_child, datum);
	}
}

//-----------------------------------------------------------------------------
// Function:	bool BinTree::retrieve
//					(const NodeData &find_value, NodeData *& datum)
// Title:		Retrieve function for insert function of BST class
// Description: Calls helper to search tree for node containing given data
//
// Programmer:	Anthony Waddell
//
// Parameters:	const NodeData &find_value; the value to look for
//				NodeData *&datum; the NodeData object to fill with data if 
//					found
// Returns:		true if data data found and inserted into datum; false if not
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData &find_value, NodeData *&datum)
{
	bool found = false;
	retrieve_Helper(find_value, datum, root);
	// If data was found and placed in datum
	if (datum != NULL)
	{
		found = true;
		return found;
	}
	// Data not found
	else
	{
		return found;
	}
}

//-----------------------------------------------------------------------------
// Function:	bool BinTree::retrieve_Helper(const NodeData & find_value,
//					NodeData *& datum, Node *& cur) const
// Title:		Helper function for Retrieve function for insert function of 
//					BST class
// Description: Preorder traversal of BST looking for data, if found will
//					return a NodeData object with found data inserted
//
// Programmer:	Anthony Waddell
//
// Parameters:	const NodeData &find_value; the value to look for
//				NodeData *&datum; the NodeData object to fill with data if 
//					found
//				Node *& cur; the Node it's looking at
// Returns:		true if data data found and inserted into datum; false if not
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
bool BinTree::retrieve_Helper(const NodeData & find_value, NodeData *& datum, Node *& cur) const
{
	bool found = false;
	// Data not found in tree
	if (cur == NULL)
	{
		datum = NULL;
		return found;
	}
	// Data was found, place in datum
	else if (*cur->data == find_value)
	{
		datum = cur->data;
		found = true;
		return found;
	}
	// Continue looking for data
	else
	{
		// Search left child subtree
		if (find_value < *cur->data)
		{
			retrieve_Helper(find_value, datum, cur->left_child);
		}
		// Search right child subtree
		if (find_value > *cur->data)
		{
			retrieve_Helper(find_value, datum, cur->right_child);
		}
	}
}

//-----------------------------------------------------------------------------
// Function:	int BinTree::getHeight(const NodeData &find_value) const
// Title:		Get Height of node
// Description: Finds the greatest height of a node to its lowest leaf node
//
// Programmer:	Anthony Waddell
//
// Parameters:	const NodeData &find_value; the value to look for
// Returns:		int; the height of node containing data. 0 if not found
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
int BinTree::getHeight(const NodeData &find_value) const
{
	return getHeight_Helper(root, find_value);
}

//-----------------------------------------------------------------------------
// Function:	int BinTree::getHeight_Helper
//					(Node *cur, const NodeData &find_value) const
// Title:		Helper function for getHeight function of BST class
// Description: Calls level function to begin preorder traversal looking for
//					given data
//
// Programmer:	Anthony Waddell
//
// Parameters:	Node *cur; the current Node its looking at
//				const NodeData &find_value; the value to look for
// Returns:		int; the height of node containing data. 0 if not found
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
int BinTree::getHeight_Helper(Node *cur, const NodeData &find_value) const
{
	return level(find_value, cur);
}

//-----------------------------------------------------------------------------
// Function:	int BinTree::level(const NodeData &find_value, Node *cur) const
// Title:		Helper function for getHeight function of BST class
// Description: Preorder traversal of tree looking for data contained in node
//
// Programmer:	Anthony Waddell
//
// Parameters:	const NodeData &find_value; the value to look for
//				Node *cur; the current Node its looking at
// Returns:		int; the height of node containing data. 0 if not found
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
int BinTree::level(const NodeData &find_value, Node *cur) const
{
	// Data not in tree
	if (cur == NULL)
	{
		return 0;
	}
	// Found node containing data
	else if (*cur->data == find_value)
	{
		return level_Helper(cur);
	}
	// Search left subtree
	else if (find_value < *cur->data)
	{
		level(find_value, cur->left_child);
	}
	// Search right subtree
	else
	{
		level(find_value, cur->right_child);
	}
}

//-----------------------------------------------------------------------------
// Function:	int BinTree::level_Helper(Node *cur) const
// Title:		Helper function for level function of BST class
// Description: Counts height of left child tree and right child path and
//					return gretaer of two depths
//
// Programmer:	Anthony Waddell
//
// Parameters:	Node *cur; the current node
// Returns:		int; the greatest height of the node to its lowest leaf
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
int BinTree::level_Helper(Node *cur) const
{
	// Base case, one beyond leaf level
	if (cur == NULL)
	{
		return 0;
	}
	else
	{
		// Recursively count levels of subtree and return greatest height
		return 1 + max(level_Helper(cur->left_child),
			level_Helper(cur->right_child));
	}
}

//-----------------------------------------------------------------------------
// Function:	void BinTree::bstreeToArray(NodeData *arr[])
// Title:		Creates array from BST object
// Description: Creates an in-order array using data from BST object
//
// Programmer:	Anthony Waddell
//
// Parameters:	NodeData *arr[]; array of pointers to NodeData objects
// Returns:		void
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData *arr[])
{
	int i = 0;
	// Call helper function to fill in array
	bstToArray_Helper(arr, root, i);
	// Leave the tree empty
	makeEmpty();
}

//-----------------------------------------------------------------------------
// Function:	void BinTree::bstToArray_Helper
//					(NodeData *arr[], Node *cur, int &index)
// Title:		Helper function for bestreeToArray function of BST class
// Description: Traverses tree in order to create an array using data from BST
//					object
// Programmer:	Anthony Waddell
//
// Parameters:	NodeData *arr[]; array of pointers to NodeData objects
//				Node *cur; the current node
//				int &index; memory address of array index to store data
// Returns:		void
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
void BinTree::bstToArray_Helper(NodeData *arr[], Node *cur, int &index)
{
	// Base case
	if (cur == NULL)
	{
		return;
	}
	// If there is data in left subtree
	if (cur->left_child != NULL)
	{
		bstToArray_Helper(arr, cur->left_child, index);
	}
	// Insert pointer to NodeData object into array and prevent memory leak
	NodeData *temp(cur->data);
	cur->data = NULL;
	arr[index++] = temp;
	// If there is data left in right subtree
	if (cur->right_child != NULL)
	{
		bstToArray_Helper(arr, cur->right_child, index);
	}
}

//-----------------------------------------------------------------------------
// Function:	void BinTree::arrayToBSTree(NodeData *arr[])
// Title:		Creates BST object from array
// Description: Creates a balanced BST object from array values, leaves array
//					filled with NULL values
// Programmer:	Anthony Waddell
//
// Parameters:	NodeData *arr[]; the array to make a BST object from
// Returns:		void
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData *arr[])
{
	// Make sure tree is empty to begin with
	makeEmpty();
	// Max array elements available
	int size = 100;
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		// Count actual number of data elements in array
		if (arr[i] != NULL)
		{
			count++;
		}
	}
	// Build BST object from array
	arrayToBST_Helper(arr, root, 0, count - 1);
	// Leave array full of NULL values
	for (int i = 0; i < size; i++)
	{
		arr[i] = NULL;
	}
}

//-----------------------------------------------------------------------------
// Function:	void BinTree::arrayToBST_Helper
//					(NodeData *arr[], Node *cur, int first, int last)
// Title:		Helper function for arrayToBST function of BST class
// Description: Recursiveley creates a balanced BST object from array values
// Programmer:	Anthony Waddell
//
// Parameters:	NodeData * arr[]; the array to make a BST object from
//				Node *cur; the current node to make
//				int first; the lowest subscript in array range
//				int last; the highest subscript in array range
// Returns:		void
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
void BinTree::arrayToBST_Helper(NodeData *arr[], Node *cur, int first, int last)
{
	// Base case
	if (first > last)
	{
		cur = NULL;
		return;
	}
	// Recursively set middle as root 
	int mid = (first + last) / 2;
	//NodeData *temp = new NodeData;
	NodeData *temp;
	temp = arr[mid];
	// Prevent memory leaks
	arr[mid] = NULL;
	// Insert NodeData object into BST object
	this->insert(temp);
	// Prevent memory leaks
	temp = NULL;
	// Recursively build the left and right subtrees
	arrayToBST_Helper(arr, cur, first, mid - 1);
	arrayToBST_Helper(arr, cur, mid + 1, last);
}

//-----------------------------------------------------------------------------
// Function:	ostream &operator<<(ostream &sout, BinTree &tree)
// Title:		Overloaded output operator for BST class
// Description: Calls helper function to output data contained in BST object
// Programmer:	Anthony Waddell
//
// Parameters:	ostream &sout; reference to output stream
//				BinTree &tree; the BST object to display
// Returns:		sout; a reference to the given output stream
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
ostream &operator<<(ostream &sout, BinTree &tree)
{
	tree.inorder_Helper(tree.root);
	cout << endl;
	return sout;
}

//-----------------------------------------------------------------------------
// Function:	void BinTree::inorder_Helper(Node *cur) const
// Title:		Helper function for overloaded output operator of BST class
// Description: Prints out in order traversal of BST object
// Programmer:	Anthony Waddell
//
// Parameters:	Node *cur; the cureent node
// Returns:		void
// History Log: 01/24/18 AW Completed Function
//-----------------------------------------------------------------------------
void BinTree::inorder_Helper(Node *cur) const
{
	if (cur == NULL)
	{
		return;
	}
	else
	{
		// Move down left subtree
		inorder_Helper(cur->left_child);
		// Display data
		cout << " " << *cur->data;
		// Move down right subtree
		inorder_Helper(cur->right_child);
	}
}

// Functions Below came with assignment

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const
{
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const
{
	if (current != NULL) {
		level++;
		sideways(current->right_child, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left_child, level);
	}
}
