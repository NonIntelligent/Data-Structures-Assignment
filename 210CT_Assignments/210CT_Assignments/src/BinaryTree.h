#pragma once

#include <string>
#include <unordered_map>

struct BinaryTreeNode {
	std::string word;

	int count = 0; // Number of copies of this word

	// Pointers to the nodes around it
	struct BinaryTreeNode* previous = nullptr;
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

	bool balanced = false;

private:
	void _destroy_nodes(BinaryTreeNode* node);
	void _insert(std::string& word, BinaryTreeNode* node);
	BinaryTreeNode* _search(std::string& word, BinaryTreeNode* node);
	void _findMostCommonWords(std::unordered_map<std::string, BinaryTreeNode*>& map);

	BinaryTreeNode* _rebalanceTree(BinaryTreeNode* nodes[], int start, int end);
	int _howManyOf(std::string& word, BinaryTreeNode* node);

	int _getMaxDepth(BinaryTreeNode* node);

public:
	BinaryTree();
	~BinaryTree();

	void insert(std::string& word);
	BinaryTreeNode* insertArrayBalanced(std::string arr_words[], int start, int end);
	void insert_Iterative(std::string& word);
	void remove(std::string& word);
	void remove_All_Of_Word(std::string word);
	BinaryTreeNode* search(std::string word);
	void inOrderTraversal(std::vector<BinaryTreeNode*>& list, BinaryTreeNode* node);

	int howManyOf(std::string word);
	std::vector<std::string> printMostCommonWords(int wordCount);
	void balanceTree(BinaryTreeNode* nodes[], int lastIndex);

	int getMaxDepth();
	BinaryTreeNode* getMinValue(BinaryTreeNode* node);
	bool isBalanced() const;
	void setRoot(BinaryTreeNode* root);

};