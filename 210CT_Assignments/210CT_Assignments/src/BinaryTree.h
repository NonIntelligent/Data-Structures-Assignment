#pragma once

#include <string>

struct BinaryTreeNode {
	std::string word;

	int count = 0; // Number of copies of this word

	// Pointers to the nodes around it
	struct BinaryTreeNode* previous = nullptr; // previous is currently not used
	struct BinaryTreeNode* nextLeft = nullptr;
	struct BinaryTreeNode* nextRight = nullptr;
};

// A BinaryTree is a Doubly-linked list
class BinaryTree {
private:
	BinaryTreeNode* root = nullptr;
	// Used to help calculate the max depth of the tree.
	int currentdepth = 0;
	int maxdepth = 0; // Used to iterate over the tree (0 is no root node)

private:
	void destroy_nodes(BinaryTreeNode* node);
	void insert(std::string& word, BinaryTreeNode* node);
	void remove(std::string& word, BinaryTreeNode* node);
	BinaryTreeNode* search(std::string& word, BinaryTreeNode* node);

	int getMaxDepth(BinaryTreeNode* node);

public:
	BinaryTree();
	~BinaryTree();

	void insert(std::string& word);
	BinaryTreeNode* insertArrayBalanced(std::string arr_words[], int start, int end);
	void insert_Iterative(std::string& word);
	void remove_All_Of_Word(std::string& word);
	BinaryTreeNode* search(std::string word);

	int howManyOf(std::string word);
	void printMostCommonWords(int wordCount);

	int getMaxDepth();
	void setRoot(BinaryTreeNode* root);

};