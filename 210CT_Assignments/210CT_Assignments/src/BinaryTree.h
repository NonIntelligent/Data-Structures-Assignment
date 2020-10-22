#pragma once

#include <string>

struct BinaryTreeNode {
	std::string word;

	int count = 0; // Number of copies of this word

	// Pointers to the next node
	struct BinaryTreeNode* nextLeft = nullptr;
	struct BinaryTreeNode* nextRight = nullptr;
};

// A BinaryTree is a Doubly-linked list
class BinaryTree {
private:
	BinaryTreeNode* root = nullptr;
	int currentdepth = 0; // 0 is before root node
	int maxdepth = 0; // Used to iterate over the tree (0 is no root node)

private:
	void destroy_nodes(BinaryTreeNode* node);
	void insert(std::string& word, BinaryTreeNode* node);
	void remove(std::string& word, BinaryTreeNode* node);
	BinaryTreeNode* search(std::string& word, BinaryTreeNode* node);

public:
	BinaryTree();
	~BinaryTree();

	void insert(std::string& word);
	void insert_Iterative(std::string& word);
	void remove_All_Of_Word(std::string& word);
	BinaryTreeNode* search(std::string word);

public:

};