#pragma once

#include "Tree.h"
#include "QueueVector.h"
#include <iostream>
using namespace std;

template<class T>
class SearchTree : public Tree<T>
{
public:
	// Adds a value to the binary search tree
	void add(T value);
	// Searches for a value in the binary search tree
	bool  search(T value)
	{
		return search(Tree<T>::root, value);
	}
	//Removes a value from the binary search tree
	void remove(T val);
	// Returns the successor of a given value in the binary search tree
	T successor(T val) {
		return successor(val, Tree<T>::root);
	}
	void deleteDuplicates()
	{
		if (Tree<T>::root)
			deleteDuplicates(Tree<T>::root);
	}
private:
	// Helper function for finding the parent of a given node in the binary search tree
	typename Tree<T>::Node* parent(typename Tree<T>::Node* parent, typename Tree<T>::Node* current);
	void add(typename Tree<T>::Node* current, T val);
	bool  search(typename Tree<T>::Node* current, T val);
	typename Tree<T>::Node* searchPointer(typename Tree<T>::Node* current, T val);
	void remove(typename Tree<T>::Node* current, T val, typename Tree<T>::Node* parent);
	// Helper function for deleting a node from the binary search tree
	void deleteNode(typename Tree<T>::Node* parent, typename Tree<T>::Node* current);
	T successor(T val, typename Tree<T>::Node* current);
	// Helper function for deleting duplicate values from the binary search tree
	void deleteDuplicates(typename Tree<T>::Node* current);
};

template <class T>
void SearchTree<T>::add(T val)
{
	// add value to binary search tree 
	if (!Tree<T>::root)
	{
		Tree<T>::root = new typename Tree<T>::Node(val);
		return;
	}
	add(Tree<T>::root, val);
}

template<class T>
inline void SearchTree<T>::remove(T val)
{
	remove(Tree<T>::root, val, nullptr);
}

template<class T>
inline typename Tree<T>::Node* SearchTree<T>::parent(typename Tree<T>::Node* node, typename Tree<T>::Node* current)
{
	//if we search all the tree or the current is the root of the tree
	if (current == nullptr || current == node)
		return nullptr;
	if (current->left == node || current->right == node)
		return current;
	if (node->value < current->value)
		return parent(node, current->left);
	else
		return parent(node, current->right);
}

template <class T>
void SearchTree<T>::add(typename Tree<T>::Node* current, T val)
{
	if (current->value < val)

		if (!current->right)
		{
			current->right = new typename Tree<T>::Node(val);
			return;
		}
		else add(current->right, val);
	else
		if (!current->left)
		{
			current->left = new typename Tree<T>::Node(val);
			return;
		}
		else add(current->left, val);
}

template <class T>
bool SearchTree<T>::search(typename Tree<T>::Node* current, T val)
{
	// see if argument value occurs in tree
	if (!current)
		return false;	// not found
	if (current->value == val)
		return true;
	if (current->value < val)
		return search(current->right, val);
	else
		return search(current->left, val);
}
//find the node with value of val
template<class T>
inline typename Tree<T>::Node* SearchTree<T>::searchPointer(typename Tree<T>::Node* current, T val)
{
	// see if argument value occurs in tree
	if (!current)
		throw "the number doesn't exists";	// not found
	if (current->value == val)
		return current;
	//if the pointer suppose to be in the right of the tree
	if (current->value < val)
		return searchPointer(current->right, val);
	else//if the pointer suppose to be in the left side of the tree
		return searchPointer(current->left, val);
}

template<class T>
inline void SearchTree<T>::remove(typename Tree<T>::Node* current, T val, typename Tree<T>::Node* parent)
{
	//if we found the node we have to remove
	if (current->value == val)
	{
		deleteNode(parent, current);
		return;
	}
	//try find the node to remove in the tree
	if (current->value < val)
	{
		if (!current->right)
			throw "not exist"; 	// not found
		remove(current->right, val, current);
	}
	else {
		if (!current->left)
			throw "not exist";
		remove(current->left, val, current);
	}
}
template<class T>
void SearchTree<T>::deleteNode(typename Tree<T>::Node* parent, typename Tree<T>::Node* current) {
	if (parent == nullptr) {
		if (current->left == nullptr && current->right == nullptr) {
			Tree<T>::root = nullptr;
		}
		else if (current->left == nullptr || current->right == nullptr) {
			Tree<T>::root = (current->left != nullptr) ? current->left : current->right;
		}
		else {
			typename Tree<T>::Node* successorParent = current;
			typename Tree<T>::Node* successor = current->right;

			while (successor->left != nullptr) {
				successorParent = successor;
				successor = successor->left;
			}

			Tree<T>::root = successor;
			Tree<T>::root->left = current->left;

			if (successorParent != current) {
				successorParent->left = successor->right;
				successor->right = current->right;
			}
		}

		delete current;
		return;
	}
	// Case 1: Deleting a leaf node
	if (current->left == nullptr && current->right == nullptr) {
		if (parent->left == current) {
			parent->left = nullptr;
		}
		else {
			parent->right = nullptr;
		}

		delete current;
		return;
	}

	// Case 2: Deleting a node with only one child
	if (current->left == nullptr || current->right == nullptr) {
		typename Tree<T>::Node* child = (current->left != nullptr) ? current->left : current->right;

		if (parent->left == current) {
			parent->left = child;
		}
		else {
			parent->right = child;
		}

		delete current;
		return;
	}

	// Case 3: Deleting a node with two children
	typename Tree<T>::Node* successorParent = current;
	typename Tree<T>::Node* successor = current->right;

	while (successor->left != nullptr) {
		successorParent = successor;
		successor = successor->left;
	}

	if (parent->left == current) {
		parent->left = successor;
	}
	else {
		parent->right = successor;
	}

	successor->left = current->left;

	if (successorParent != current) {
		successorParent->left = successor->right;
		successor->right = current->right;
	}

	delete current;
	return;
}

template<class T>
inline T SearchTree<T>::successor(T val, typename Tree<T>::Node* current)
{
	typename Tree<T>::Node* node = searchPointer(current, val);//find the node of the given val
	if (!node->right)//if it doesn't have a right son may it's have a smaller father that can be the successor
	{
		typename Tree<T>::Node* parentNode = parent(node, Tree<T>::root);
		while (parentNode && node == parentNode->right)
		{
			node = parentNode;
			parentNode = parent(node, Tree<T>::root);
		}
		if (parentNode)
			return parentNode->value;
		throw "no successor";
	}
	else
	{
		node = node->right;
		//find the smaller value from the bigger values
		while (node->left)
		{
			node = node->left;
		}
		return node->value;
	}
}
template<class T>
void SearchTree<T>::deleteDuplicates(typename Tree<T>::Node* current) {
	if (!current) {
		return;
	}

	typename Tree<T>::Node* parentNode = current;
	typename Tree<T>::Node* cleft = current->left;

	while (cleft != nullptr) {
		if (cleft && cleft->value && current->value == cleft->value) {
			typename Tree<T>::Node* nextNode = cleft->right;
			deleteNode(parentNode, cleft);
			deleteDuplicates(current);
			cleft = nextNode;
		}
		else {
			parentNode = cleft;
			cleft = cleft->right;
		}
	}

	// Recursively process the left and right subtrees
	deleteDuplicates(current->left);
	deleteDuplicates(current->right);
}