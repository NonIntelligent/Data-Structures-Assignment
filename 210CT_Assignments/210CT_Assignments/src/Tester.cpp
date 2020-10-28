#include "BinaryTree.h"
#include "Graph.h"
#include "Algorithms.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

/* For Task1 I parse the words from the shakespeare text, excluding numbers ands single apostrophes.
Next I sort the list in ascending order then insert that into a Binary Search Tree that
allows for duplicate nodes.
Task1 takes ~ 1.3 seconds (main computer, debug)*/
bool task1(BinaryTree* binaryTree) {
	auto start = std::chrono::high_resolution_clock::now();

	// Parsed words includes capital letters as seperate words.
	vectorString list = parseTxtAsWords(253, 2867, "res/Shakespeare.txt");
	std::string* test = list.data();
	// Sort the list in acending order (A < z)
	quickSort(test, 0, list.size() - 1);

	// This version of binary tree takes accepts duplicate nodes but is also balanced.
	// The input requires a sorted list though
	binaryTree->setRoot(binaryTree->insertArrayBalanced(test, 0, list.size() - 1));
	int depth = binaryTree->getMaxDepth();

	// Measure time taken to run the task
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Took " << duration << " milliseconds to execute";

	if(depth == 0) return false;

	return true;
}
/*
For task2 part a I test the method on some words that I know how many there is.
For part b I use part a and an unordered map to count up a list of words, providing a map with no duplicate words.
The map has values to one node that contains the word and with that I push the nodes into a priority queue for comparison and to print.
However the method that traverses the tree and counts the words takes extremely long to compute.
Task2 currently takes ~ 2.5 seconds (main computer, debug).
*/
bool task2(BinaryTree* binaryTree, vectorString &commonWords) {
	auto start = std::chrono::high_resolution_clock::now();

	// Tests counting of certain words of known number of appearences
	int count1 = binaryTree->howManyOf("the");
	int count2 = binaryTree->howManyOf("I");
	int count3 = binaryTree->howManyOf("zealous");
	int count4 = binaryTree->howManyOf("gobbledygook");

	commonWords = binaryTree->printMostCommonWords(66);

	// Measure time taken to run the task
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Took " << duration << " milliseconds to execute";

	if(count1 != 355 || count2 != 344 || count3 != 1 || count4 != 0) return false;

	return true;
}

/*
For task3 I remove all words that are 'I' and then rebalance the binary tree.
I count the number of nodes that possess 'I' before and after the removal to check that the method has worked correctly.
Task 3 taskes ~ 25 milliseconds (main computer, debug)
*/
bool task3(BinaryTree* binaryTree) {
	auto start = std::chrono::high_resolution_clock::now();

	// Counts the number of I in the tree then removes until none is left.
	// The tree also becomes rebalanced
	int count1 = binaryTree->howManyOf("I");
	binaryTree->remove_All_Of_Word("I");
	int count2 = binaryTree->howManyOf("I");

	// Measure time taken to run the task
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Took " << std::fixed << duration << " microseconds to execute";

	if(count1 != 344 || count2 != 0 || !binaryTree->isBalanced()) return false;

	return true;
}

/*
Task4 I insert all 66 common words into the weighted, undirected graph structure.
The edges between all new vertices are also calculated.
Task 4 take ~20 seconds (main computer, debug).
*/
bool task4(Graph* graph, vectorString &commonWords) {
	auto start = std::chrono::high_resolution_clock::now();
	std::ifstream stream("res/Shakespeare.txt");

	// Insert words into graph
	for(auto word : commonWords) {
		std::vector<int> sonnets = findWordInSonnets(word, stream);
		graph->insert(word, sonnets);
	}

	// Measure time taken to run the task
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Took " << duration << " milliseconds to execute";

	stream.close();

	if(commonWords.size() != 66) return false;

	return true;
}

bool task5() {
	auto start = std::chrono::high_resolution_clock::now();

	// Measure time taken to run the task
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Took " << duration << " milliseconds to execute";
	return true;
}

bool task6() {
	auto start = std::chrono::high_resolution_clock::now();

	// Measure time taken to run the task
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Took " << duration << " milliseconds to execute";
	return true;
}

int main() {
	// Can be used in other tasks and destoryed at end of main
	BinaryTree* searchTree = new BinaryTree();
	Graph* weightedGraph = new Graph();
	vectorString mostCommonWords;

	std::cout << " Task1: " << std::boolalpha << task1(searchTree) << std::endl;

	std::cout << " Task2: " << std::boolalpha << task2(searchTree, mostCommonWords) << std::endl;

	std::cout << " Task3: " << std::boolalpha << task3(searchTree) << std::endl;

	std::cout << " Task4: " << std::boolalpha << task4(weightedGraph, mostCommonWords) << std::endl;

	std::cout << " Task5: " << std::boolalpha << task5() << std::endl;

	std::cout << " Task6: " << std::boolalpha << task6() << std::endl;

	// returns claimed memory
	mostCommonWords.clear();
	delete(searchTree);
	delete(weightedGraph);

	return 0;
}