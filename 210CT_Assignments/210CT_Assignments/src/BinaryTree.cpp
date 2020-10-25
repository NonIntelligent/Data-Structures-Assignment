#include "BinaryTree.h"

#include <iostream>
#include <queue>
#include <stack>

// Recaim memory by deleting nodes from tree
void BinaryTree::_destroy_nodes(BinaryTreeNode* node) {
	if(node != nullptr) {
		// First recursively delete all nodes that are pointed to
		// then delete the current node
		_destroy_nodes(node->nextLeft);
		_destroy_nodes(node->nextRight);
		delete node;
	}
}

// Recursively search for the node to place the word in.
// If node is a duplicate then increment count (saves a lot of space and is easy to get duplicate count)
void BinaryTree::_insert(std::string& word, BinaryTreeNode * node) {
	if(word < node->word) { // Word is less than current node
		if(node->nextLeft != nullptr) {
			currentdepth++;
			_insert(word, node->nextLeft);
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
			_insert(word, node->nextRight);
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

void BinaryTree::_remove(std::string& word, BinaryTreeNode * node) {
}

// Searches through the nodes starting at root to find the word
BinaryTreeNode* BinaryTree::_search(std::string& word, BinaryTreeNode * node) {
	if(node != nullptr) {
		if(word == node->word) {
			return node;
		}
		if(word < node->word) {
			return _search(word, node->nextLeft);
		}
		else {
			return _search(word, node->nextRight);
		}
	}
	else return nullptr;
}

// Recursively counts the number of times a certain word appears in the tree
// Commit 9 fixes time consuming problem of commit 8 by not needing to traverse the entire tree every time
int BinaryTree::_howManyOf(std::string& word, BinaryTreeNode * node) {
	if(node == nullptr) return 0;
	int countLeft;
	int countRight;

	// The if statements focuses the traversal to where duplicates would be located,
	if(node->nextLeft != nullptr && node->nextLeft->word < word) 
		countLeft = _howManyOf(word, node->nextLeft->nextRight);
	else 
		countLeft = _howManyOf(word, node->nextLeft);

	if(node->nextRight != nullptr && node->nextRight->word > word)
		countRight = _howManyOf(word, node->nextRight->nextLeft);
	else
		countRight = _howManyOf(word, node->nextRight);
	

	if(node->word == word) 
		return countLeft + countRight + 1; // Add up all of left and right + self
	else 
		return countLeft + countRight; // return what node has counted so far
}


/* Find the most common words in the binary tree and add them to the unordered map.
This method uses breadth first traversal to count each word in the tree ignoring,
binary tree nodes with the same value.
// 9. Changed from recursive breadth first to iterative (using a queue) from commit 8
*/
void BinaryTree::_findMostCommonWords(std::unordered_map<std::string, BinaryTreeNode*>& map) {
	std::queue<BinaryTreeNode*> nodes;
	BinaryTreeNode* temp;
	nodes.push(root);

	// Traverses until every node is visited
	while(!nodes.empty()) {
		temp = nodes.front();
		nodes.pop();

		if(map.find(temp->word) == map.end()) {
			int count = _howManyOf(temp->word, root);
			temp->count = count;
			map.emplace(temp->word, temp);
		}
		if (temp->nextLeft != nullptr) nodes.push(temp->nextLeft);
		if (temp->nextRight != nullptr) nodes.push(temp->nextRight);
	}
}

int BinaryTree::_getMaxDepth(BinaryTreeNode * node) {
	
	// If node does not exist, do not change depth
	if(node == nullptr) return 0;

	int leftdepth = _getMaxDepth(node->nextLeft);
	int rightdepth = _getMaxDepth(node->nextRight);

	if(leftdepth > rightdepth)
		return leftdepth + 1;
	else
		return rightdepth + 1;
}

BinaryTree::BinaryTree() {
}

// Recaim all memory taken by nodes
BinaryTree::~BinaryTree() {
	_destroy_nodes(root);
}

// Insert a word into the binary tree
void BinaryTree::insert(std::string& word) {
	// Insert following the root path else create a root
	if(root != nullptr) {
		_insert(word, root);
	}
	else {
		maxdepth = 1;
		root = new BinaryTreeNode;
		root->word = word;
		root->count++;
	}
}

// Given a sorted array, this method will construct a binary search tree with duplicate nodes and set it root node;
// This method should only be used on an empty/destoryed tree 
// @return The root node of which needs to be set to the binaryTree using setRoot(root)
BinaryTreeNode* BinaryTree::insertArrayBalanced(std::string arr_words[], int start, int end) {

	// no more nodes to traverse/create
	if(start > end) return nullptr;

	// Make the middle element of each list a node
	int mid = (start + end) / 2;
	BinaryTreeNode* node = new BinaryTreeNode;

	node->word = arr_words[mid];
	node->count++;
	node->nextLeft = insertArrayBalanced(arr_words, start, mid - 1);
	node->nextRight = insertArrayBalanced(arr_words, mid + 1, end);

	if (node->nextLeft != nullptr) node->nextLeft->previous = node;
	if (node->nextRight != nullptr) node->nextRight->previous = node;
	
	balanced = true;
	return node;
}

// Insert words iteratively saving memory and stack space (best with unsorted lists)
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

// Search for a word in the tree (can be nullptr)
BinaryTreeNode * BinaryTree::search(std::string word) {
	return _search(word, root);
}

// Altered version of the getMaxDepth method which increments a counter on any duplicates.
int BinaryTree::howManyOf(std::string word) {
	if(root == nullptr) return -1;

	return _howManyOf(word, root);
}

// https://en.cppreference.com/w/cpp/container/priority_queue
// This method creates a map and a priority queue to traverse the tree, count the number of duplicates
// and print out the top duplicate words
void BinaryTree::printMostCommonWords(int wordCount) {
	std::unordered_map<std::string, BinaryTreeNode*> hashmap;

	// Create the priority queue to sort BinaryTreeNodes by its count
	auto cmp = [](BinaryTreeNode* left, BinaryTreeNode* right) {return left->count < right->count; };
	std::priority_queue<BinaryTreeNode*, std::vector<BinaryTreeNode*> ,decltype(cmp)> queue(cmp);

	_findMostCommonWords(hashmap);

	// Add nodes from hashmap to queue to be sorted in decending order by duplicate count
	for(auto it = hashmap.begin(); it != hashmap.end(); it++) {
		queue.push(it->second);
	}

	// Prints out the words in the queue of the top (wordCount) of words
	for(int i = 0; i < wordCount; i++) {
		if(queue.empty()) return;

		BinaryTreeNode* node = queue.top();

		// Task 2 requirement to exclude 'the' and 'a'
		if(node->word == "The" || node->word == "the" || node->word == "a" || node->word == "A") {
			queue.pop();
			i--;
			continue;
		}
		// Print out the word and number of duplicates
		std::cout << queue.top()->word << ": " << queue.top()->count << std::endl;
		queue.pop();
	}
}

// Returns tha depth of the tree (root inclusive)
int BinaryTree::getMaxDepth() {
	if(maxdepth > 0) return maxdepth;

	return maxdepth = _getMaxDepth(root);
}

// Set the root of the binary tree if it has no root (parameter does not accept nullptr)
void BinaryTree::setRoot(BinaryTreeNode * root) {
	if(root == nullptr) return;
	if(this->root == nullptr) this->root = root;
}
