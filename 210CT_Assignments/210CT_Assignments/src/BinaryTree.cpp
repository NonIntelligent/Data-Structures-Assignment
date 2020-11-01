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
			node->nextLeft->previous = node;
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
			node->nextRight->previous = node;
			node->nextRight->word = word;
			node->nextRight->count++;
			currentdepth = 0;
		}
	}

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

/* Find the most common words in the binary tree and add them to the unordered map.
This method uses breadth first traversal to count each word in the tree ignoring,
binary tree nodes with the same value.
// Commit 9. Changed from recursive breadth first to iterative (using a queue) from commit 8
*/
void BinaryTree::_findMostCommonWords(std::unordered_map<std::string, BinaryTreeNode*>& map) {
	std::queue<BinaryTreeNode*> nodes;
	BinaryTreeNode* temp;
	nodes.push(root);

	// Traverses until every node is visited
	while(!nodes.empty()) {
		temp = nodes.front();
		nodes.pop();
		// If the word already exists also increment the counter.
		if(map.find(temp->word) == map.end()) {
			int count = _howManyOf(temp->word, root);
			temp->count = count;
			map.emplace(temp->word, temp);
		}
		if (temp->nextLeft != nullptr) nodes.push(temp->nextLeft);
		if (temp->nextRight != nullptr) nodes.push(temp->nextRight);
	}
}

// Used to rebalance an already built binary tree.
// This method is an adjusted form of the insertArrayBalanced method that uses nodes instead of strings
// The setRoot method also needs to be called to set the root.
BinaryTreeNode * BinaryTree::_rebalanceTree(BinaryTreeNode * nodes[], int start, int end) {
	// no more nodes to traverse
	if(start > end) return nullptr;

	// Make the middle element of each list a node
	int mid = (start + end) / 2;
	BinaryTreeNode* node = nodes[mid];

	node->previous = nullptr;
	node->count = 1;
	node->nextLeft = _rebalanceTree(nodes, start, mid - 1);
	node->nextRight = _rebalanceTree(nodes, mid + 1, end);

	if(node->nextLeft != nullptr) node->nextLeft->previous = node;
	if(node->nextRight != nullptr) node->nextRight->previous = node;

	return node;
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

// Recusively calculate the maximum depth of the tree
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
		a->previous = b;
		a->count++;
		if(right) b->nextRight = a; else b->nextLeft = a;
		if(currentdepth > maxdepth) maxdepth = currentdepth;
		currentdepth = 0;
	}

}

// https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
// This method is used to delete a single node that has the word to be removed.
// The child pointers will be reassigned but the Binary Tree will be left unbalanced.
void BinaryTree::remove(std::string & word) {
	BinaryTreeNode* node = _search(word, root);

	// Check if the node is on the left or right of the previous node
	bool rightOfPrevious = node->previous->nextRight == node;

	bool haveRight = node->nextRight != nullptr;
	bool haveLeft = node->nextLeft != nullptr;

	// If node is a leaf then delete and remove previous pointer
	if(!haveLeft && !haveRight) {
		if(rightOfPrevious)
			node->previous->nextRight = nullptr;
		else
			node->previous->nextLeft = nullptr;

		delete node;
	}
	// Node has two children
	else if(haveLeft && haveRight) {
		// Get replacement for node
		BinaryTreeNode* temp = node->nextRight;
		while(temp->nextLeft != nullptr) {
			temp = temp->nextLeft;
		}
		
		// temp will have no more nodes on its left and will be on the parent's left.
		// Temp's parent will take on temp's child.
		if(temp->previous != node)
			temp->previous->nextLeft = temp->nextRight;
		else
			temp->previous->nextRight = temp->nextRight;

		// Reassign the values then delete the replacement node.
		node->word = temp->word;
		node->count = temp->count;

		if (temp->nextRight != nullptr) temp->nextRight->previous = temp->previous;
		
		delete temp;
	}
	// Node only has one child on the left
	else if(haveLeft && !haveRight) {
		if(rightOfPrevious)
			node->previous->nextRight = node->nextLeft;
		else
			node->previous->nextLeft = node->nextLeft;

		delete node;
	}
	// Node only has one child on the right
	else {
		if(rightOfPrevious)
			node->previous->nextRight = node->nextRight;
		else
			node->previous->nextLeft = node->nextRight;

		delete node;
	}

	balanced = false;
}

// Removes all nodes that possess the word to be removed.
// Also rebalances the tree.
void BinaryTree::remove_All_Of_Word(std::string word) {
	// Counts the number of duplicate nodes to delete
	int count = howManyOf(word);

	// Removes all duplicate nodes
	for(int i = 0; i < count; i++) {
		remove(word);
	}

	// Store all nodes in the binary in a list in order 
	// (already sorted in ascending value order as it's a binary tree)
	std::vector<BinaryTreeNode*> allNodes;
	inOrderTraversal(allNodes, root);

	// Shrink so no elements in the underlying array are empty
	allNodes.shrink_to_fit();
	// Balances the tree
	balanceTree(allNodes.data(), allNodes.size() - 1);
}

// Search for a word in the tree (can be nullptr)
BinaryTreeNode * BinaryTree::search(std::string word) {
	return _search(word, root);
}

// Given a dynamic list this method will traverse the tree in-order and store the nodes in the list
void BinaryTree::inOrderTraversal(std::vector<BinaryTreeNode*>& list, BinaryTreeNode* node) {
	if(node == nullptr) return;

	inOrderTraversal(list, node->nextLeft);

	list.push_back(node);

	inOrderTraversal(list, node->nextRight);
}

// Altered version of the getMaxDepth method which increments a counter on any duplicates.
int BinaryTree::howManyOf(std::string word) {
	if(root == nullptr) return -1;

	return _howManyOf(word, root);
}

// https://en.cppreference.com/w/cpp/container/priority_queue
// This method creates a map and a priority queue to traverse the tree, count the number of duplicates
// and print out the top duplicate words
std::vector<std::string> BinaryTree::printMostCommonWords(int wordCount) {
	// Using an unordered map to keep a unique copy of each word and keep a track of it duplicates.
	std::unordered_map<std::string, BinaryTreeNode*> hashmap;
	std::vector<std::string> commonWords;

	// Create the priority queue to sort BinaryTreeNodes by its count so that output is easy to do.
	auto cmp = [](BinaryTreeNode* left, BinaryTreeNode* right) {return left->count < right->count; };
	std::priority_queue<BinaryTreeNode*, std::vector<BinaryTreeNode*> ,decltype(cmp)> queue(cmp);

	_findMostCommonWords(hashmap);

	// Add nodes from hashmap to queue to be sorted in decending order by duplicate count
	for(auto it = hashmap.begin(); it != hashmap.end(); it++) {
		queue.push(it->second);
	}

	// Prints out the words in the queue of the top (wordCount) of words
	for(int i = 0; i < wordCount; i++) {
		if(queue.empty()) break;

		BinaryTreeNode* node = queue.top();

		// Task 2 requirement to exclude 'the' and 'a'
		if(node->word == "The" || node->word == "the" || node->word == "a" || node->word == "A") {
			queue.pop();
			i--;
			continue;
		}
		// Print out the word and number of duplicates, also adds to the list
		commonWords.emplace_back(queue.top()->word);
		std::cout << queue.top()->word << ": " << queue.top()->count << std::endl;
		queue.pop();
	}

	commonWords.shrink_to_fit();
	return commonWords;
}

// Will balance the Binary Tree if not already balanced
void BinaryTree::balanceTree(BinaryTreeNode* nodes[], int lastIndex) {
	if(balanced) return;

	// Set the new root of the binaryTree
	setRoot(_rebalanceTree(nodes, 0, lastIndex));
	
	// recalculates the max depth
	maxdepth = 0;
	getMaxDepth();

	balanced = true;
}

// Returns tha depth of the tree (root inclusive)
int BinaryTree::getMaxDepth() {
	if(maxdepth > 0) return maxdepth;

	return maxdepth = _getMaxDepth(root);
}

// Returns the minimum value node following the left path of a given node.
BinaryTreeNode * BinaryTree::getMinValue(BinaryTreeNode * node) {
	BinaryTreeNode* current = node;
	while(current != nullptr && current->nextLeft != nullptr) {
		current = current->nextLeft;
	}
	return current;
}

bool BinaryTree::isBalanced() const{
	return balanced;
}

// Set the root of the binary tree (parameter does not accept nullptr)
void BinaryTree::setRoot(BinaryTreeNode * root) {
	if(root == nullptr) return;
	this->root = root;
}
