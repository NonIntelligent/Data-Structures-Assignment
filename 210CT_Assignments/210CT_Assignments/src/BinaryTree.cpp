#include "BinaryTree.h"

// Recaim memory by deleting nodes from tree
void BinaryTree::destroy_nodes(BinaryTreeNode* node) {
	if(node != nullptr) {
		// First recursively delete all nodes that are pointed to
		// then delete the current node
		destroy_nodes(node->nextLeft);
		destroy_nodes(node->nextRight);
		delete node;
	}
}

// Recursively search for the node to place the word in.
// If node is a duplicate then increment count (saves a lot of space and is easy to get duplicate count)
void BinaryTree::insert(std::string word, BinaryTreeNode * node) {
	if(word < node->word) { // Word is less than current node
		if(node->nextLeft != nullptr) {
			insert(word, node->nextLeft);
		}
		else {
			node->nextLeft = new BinaryTreeNode;
			node->nextLeft->word = word;
			node->nextLeft->count++;
		}
	}

	else if(word == node->word) { // increment count as it's a duplicate
		node->count++;
	}
	else { // Word is greater than node
		if(node->nextRight != nullptr) {
			insert(word, node->nextRight);
		}
		else {
			node->nextRight = new BinaryTreeNode;
			node->nextRight->word = word;
			node->nextRight->count++;
		}
	}

}

void BinaryTree::remove(std::string word, BinaryTreeNode * node) {
}

// Searches through the nodes starting at root to find the word
BinaryTreeNode* BinaryTree::search(std::string word, BinaryTreeNode * node) {
	if(node != nullptr) {
		if(word == node->word) {
			return node;
		}
		if(word < node->word) {
			return search(word, node->nextLeft);
		}
		else {
			return search(word, node->nextRight);
		}
	}
	else return nullptr;
}

BinaryTree::BinaryTree() {
}

// Recaim all memory taken by nodes
BinaryTree::~BinaryTree() {
	destroy_nodes(root);
}

// Insert a word into the binary tree
void BinaryTree::insert(std::string word) {
	// Insert following the root path else create a root
	if(root != nullptr) {
		insert(word, root);
	}
	else {
		root = new BinaryTreeNode;
		root->word = word;
		root->count++;
	}
}

void BinaryTree::remove_All_Of_Word(std::string word) {
}

BinaryTreeNode * BinaryTree::search(std::string word) {
	return search(word, root);
}
