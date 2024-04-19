#include <iostream>
using namespace std;
#include "QueueVector.h"

//-----------------------------------
//  class Tree (Binary Trees)
// process nodes in Pre/In/Post  order
//-----------------------------------
template <class T>
class Tree
{
protected:
	//--------------------------------------------------------
	//  inner class Node
	//      a single Node from a binary tree
	//--------------------------------------------------------
	class Node
	{
	public:
		Node* left;
		Node* right;
		T value;
		Node(T val) : value(val), left(NULL), right(NULL) {}
		Node(T val, Node* l, Node* r) : value(val), left(l), right(r) {}
	};		//end of Node class

	//data member of tree
	Node* root;

public:
	// Constructor and Destructor
	Tree() { root = NULL; }	 // initialize tree
	~Tree();

	// Tree Traversal Methods
	int isEmpty() const { return root == NULL; }
	void clear() { clear(root); root = NULL; }
	void preOrder() { preOrder(root); }
	void inOrder() { inOrder(root); }
	void postOrder() { postOrder(root); }

	// Tree Utility Methods
	int height() { return height(root, -1); }
	void reflect() { if (root) reflect(root); }
	void breadthScan() { breadthScan(root); }

private:
	// Private Helper Functions
	void  clear(Node* current); // Clear the tree starting from the given node
	void  preOrder(Node* current); // Print the values of the nodes in pre-order starting from the given node
	void  inOrder(Node* current); // Print the values of the nodes in in-order starting from the given node
	void  postOrder(Node* current); // Print the values of the nodes in post-order starting from the given node
	int height(Node* current, int counter); // Find the height of the tree starting from the given node
	void reflect(Node* current); // Reflect the tree starting from the given node
	void breadthScan(Node* current); // Print the values of the nodes in breadth-first order starting from the given node
};

//----------------------------------------------------------
//  class Tree implementation
//----------------------------------------------------------

// Destructor
template <class T>
Tree<T>::~Tree()
{
	if (root != NULL)
		clear(root);
}

// Clear the tree starting from the given node
template <class T>
void Tree<T>::clear(Node* current)
{
	if (current)
	{
		// Release memory associated with children
		if (current->left)
			clear(current->left);
		if (current->right)
			clear(current->right);
		delete current;
	}
}

// Print the values of the nodes in pre-order starting from the given node
template <class T>
void Tree<T>::preOrder(Node* current)
{
	if (current)
	{
		// Process current Node
		cout << (current->value) << endl;

		// Traverse left subtree
		preOrder(current->left);

		// Traverse right subtree
		preOrder(current->right);
	}
}

// Print the values of the nodes in in-order starting from the given node
template <class T>
void Tree<T>::inOrder(Node* current)
{
	if (current)
	{
		// Traverse left subtree
		inOrder(current->left);

		// Process current Node
		cout << (current->value) << " ";

		// Traverse right subtree
		inOrder(current->right);
	}
}

// Print the values of the nodes in post-order starting from the given node
template <class T>
void Tree<T>::postOrder(Node* current)
{
	if (current)
	{
		// Traverse left subtree
		postOrder(current->left);

		// Traverse right subtree
		postOrder(current->right);

		// Process current Node
		process(current->value);
	}
}

// Find the height of the tree starting from the given node
template<class T>
int Tree<T>::height(Node* current, int counter)
{
	if (!current)
		return counter;
	int left = counter + 1;
	int right = counter + 1;

	// Traverse left subtree
	left = height(current->left, left);

	// Traverse right subtree
	right = height(current->right, right);

	// Return the greater of the two heights
	if (left > right)
		return left;
	return right;
}

// Reflect the tree starting from the given node
template<class T>
void Tree<T>::reflect(Node* current)
{
	// Base case: if the current node is nullptr, return
	if (current == nullptr) {
		return;
	}

	// Swap the left and right child nodes
	Node* temp = current->left;
	current->left = current->right;
	current->right = temp;

	// Recursively reflect the left and right subtrees
	reflect(current->left);
	reflect(current->right);
}

// Print the values of the nodes in breadth-first order starting from the given node
template <class T>
void Tree<T>::breadthScan(Node* current)
{
	if (current)
	{
		QueueVector<Node*> queue;
		queue.enqueue(current);
		while (!queue.isEmpty())
		{
			Node* node = queue.dequeue();

			// Process current node
			cout << (node->value) << " ";

			// Enqueue left child node
			if (node->left)
				queue.enqueue(node->left);

			// Enqueue right child node
			if (node->right)
				queue.enqueue(node->right);
		}
	}
}