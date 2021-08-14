#pragma once

#include <string>
#include <unordered_map>

struct BinaryTreeNode {
	std::string word;

	int count = 0; // Number of copies of this word (Only to be used when implementation does not allow duplicate physical nodes)

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
	// Recaim memory by deleting nodes from tree
	void _destroy_nodes(BinaryTreeNode* node);

	// Recursively search for the node to place the word in.
	// If node is a duplicate then increment count (saves a lot of space and is easy to get duplicate count)
	void _insert(std::string& word, BinaryTreeNode* node);

	// Searches through the nodes starting at root to find the word
	BinaryTreeNode* _search(std::string& word, BinaryTreeNode* node);

	/* Find the most common words in the binary tree and add them to the unordered map.
	This method uses breadth first traversal to count each word in the tree ignoring,
	binary tree nodes with the same value.
	++ Commit 9. Changed from recursive breadth first to iterative (using a queue) from commit 8
	*/
	void _findMostCommonWords(std::unordered_map<std::string, BinaryTreeNode*>& map);

	// Used to rebalance an already built binary tree.
	// This method is an adjusted form of the insertArrayBalanced method that uses nodes instead of strings
	// @return The root node of which needs to be set to the binaryTree using setRoot(root)
	BinaryTreeNode* _rebalanceTree(BinaryTreeNode* nodes[], int start, int end);

	// Recursively counts the number of times a certain word appears in the tree
	// ++ Commit 9 fixes time consuming problem of commit 8 by not needing to traverse the entire tree every time
	int _howManyOf(std::string& word, BinaryTreeNode* node);

	// Recusively calculate the maximum depth of the tree
	int _getMaxDepth(BinaryTreeNode* node);

public:
	BinaryTree();
	// Recaim all memory taken by nodes
	~BinaryTree();

	// Insert a word into the binary tree
	void insert(std::string& word);

	// Given a sorted array, this method will construct a binary search tree with duplicate nodes and set it root node;
	// This method should only be used on an empty/destoryed tree 
	// @return The root node of which needs to be set to the binaryTree using setRoot(root)
	BinaryTreeNode* insertArrayBalanced(std::string arr_words[], int start, int end);

	// Insert words iteratively saving memory and stack space (best with unsorted lists)
	void insert_Iterative(std::string& word);

	// https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
	// This method is used to delete a single node that has the word to be removed.
	// The child pointers will be reassigned but the Binary Tree will be left unbalanced.
	void remove(std::string& word);

	// Removes all nodes that possess the word to be removed.
	// Also rebalances the tree.
	void remove_All_Of_Word(std::string word);

	// Search for a word in the tree
	BinaryTreeNode* search(std::string word);

	// Given a dynamic list this method will traverse the tree in-order and store the nodes in the list
	void inOrderTraversal(std::vector<BinaryTreeNode*>& list, BinaryTreeNode* node);

	// Altered version of the getMaxDepth method which increments a counter on any duplicates.
	int howManyOf(std::string word);

	// https://en.cppreference.com/w/cpp/container/priority_queue
	// This method creates a map and a priority queue to traverse the tree, count the number of duplicates
	// and print out the top duplicate words
	std::vector<std::string> printMostCommonWords(int wordCount);

	// Will balance the Binary Tree if not already balanced
	void balanceTree(BinaryTreeNode* nodes[], int lastIndex);

	// Returns the depth of the tree (root inclusive)
	int getMaxDepth();

	// Returns the minimum value node following the left path of a given node.
	BinaryTreeNode* getMinValue(BinaryTreeNode* node);

	bool isBalanced() const;

	// Set the root of the binary tree (does not accept nullptr)
	void setRoot(BinaryTreeNode* root);

};