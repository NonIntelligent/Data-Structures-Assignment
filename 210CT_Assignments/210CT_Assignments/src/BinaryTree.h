#pragma once

#include <string>

struct BinaryTreeNode {
	const std::string word;

	// Pointers to the next node
	struct Node* previous = nullptr;
	struct Node* nextLeft = nullptr;
	struct Node* nextRight = nullptr;
};

// A BinaryTree is a Doubly-linked list
class BinaryTree {
private:
	BinaryTreeNode* root = nullptr;

private:
	void destroy_tree();
	void insert(std::string word, BinaryTreeNode* leaf);
	void remove(std::string word, BinaryTreeNode* leaf);

public:
	BinaryTree();
	~BinaryTree();

	void insert(std::string word);
	void remove_All_Of_Word(std::string word);
	BinaryTreeNode* search(std::string word);

public:

};