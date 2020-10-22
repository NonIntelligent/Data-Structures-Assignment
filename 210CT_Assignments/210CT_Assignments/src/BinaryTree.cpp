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
void BinaryTree::insert(std::string& word, BinaryTreeNode * node) {
	if(word < node->word) { // Word is less than current node
		if(node->nextLeft != nullptr) {
			currentdepth++;
			insert(word, node->nextLeft);
		}
		else {
			if(currentdepth > maxdepth) maxdepth = currentdepth;
			node->nextLeft = new BinaryTreeNode;
			node->nextLeft->word = word;
			node->nextLeft->count++;
			currentdepth = 0;
		}
	}

	else if(word == node->word) { // increment count as it's a duplicate
		node->count++;
		currentdepth = 0;
	}
	else { // Word is greater than node
		if(node->nextRight != nullptr) {
			currentdepth++;
			insert(word, node->nextRight);
		}
		else {
			if(currentdepth > maxdepth) maxdepth = currentdepth;
			node->nextRight = new BinaryTreeNode;
			node->nextRight->word = word;
			node->nextRight->count++;
			currentdepth = 0;
		}
	}

}

void BinaryTree::remove(std::string& word, BinaryTreeNode * node) {
}

// Searches through the nodes starting at root to find the word
BinaryTreeNode* BinaryTree::search(std::string& word, BinaryTreeNode * node) {
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
void BinaryTree::insert(std::string& word) {
	// Insert following the root path else create a root
	if(root != nullptr) {
		insert(word, root);
	}
	else {
		maxdepth = 1;
		root = new BinaryTreeNode;
		root->word = word;
		root->count++;
	}
}

void BinaryTree::insert_Iterative(std::string & word) {
	BinaryTreeNode* a = root; // ptr to traverse down the tree to find node location
	BinaryTreeNode* b = nullptr; // Ptr follows a in traversal
	bool right = false;
	currentdepth++;

	while(a != nullptr) {// Condition will exit if root is nullptr of node position is found
		b = a;
		if(word < a->word) {
			a = a->nextLeft;
			right = false;
			currentdepth++;
		}
		else if(word == a->word) {
			a->count++;
			currentdepth = 0;
			return;
		}
		else {
			a = a->nextRight;
			right = true;
			currentdepth++;
		}
	}

	// If root is null
	if(root == nullptr) {
		maxdepth = 1;
		root = new BinaryTreeNode;
		root->word = word;
		root->count++;
		return;
	}

	// Create a new node to store the word if it does not already exist
	if(word != b->word) {
		a = new BinaryTreeNode;
		a->word = word;
		a->count++;
		if(right) b->nextRight = a; else b->nextLeft = a;
		if(currentdepth > maxdepth) maxdepth = currentdepth;
		currentdepth = 0;
	}

}

void BinaryTree::remove_All_Of_Word(std::string& word) {
}

BinaryTreeNode * BinaryTree::search(std::string word) {
	return search(word, root);
}
