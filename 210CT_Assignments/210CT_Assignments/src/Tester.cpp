#include "BinaryTree.h"
#include "Graph.h"
#include "Algorithms.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

/* For Task1 I parse the words from the shakespeare text, excluding numbers ands single apostrophes.
Next I sort the list in ascending order then insert that into a Binary Search Tree that
allows for duplicate nodes.
Task1 takes ~ 1.3 seconds (main computer, debug).
Task1 takes ~ 12 milliseconds (main computer, release).
*/
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
	double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Took " << duration * 0.001 << " milliseconds to execute";

	if(depth == 0) return false;

	return true;
}
/*
For task2 part a I test the method on some words that I know how many there is.
For part b I use part a and an unordered map to count up a list of words, providing a map with no duplicate words.
The map has values to one node that contains the word and with that I push the nodes into a priority queue for comparison and to print.
However the method that traverses the tree and counts the words takes extremely long to compute.
Task2 currently takes ~ 2.5 seconds (main computer, debug).
Task2 currently takes ~ 70 milliseconds (main computer, release).
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
	double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Took " << duration * 0.001 << " milliseconds to execute";

	if(count1 != 355 || count2 != 344 || count3 != 1 || count4 != 0) return false;

	return true;
}

/*
For task3 I remove all words that are 'I' and then rebalance the binary tree.
I count the number of nodes that possess 'I' before and after the removal to check that the method has worked correctly.
Task 3 takes ~ 25 milliseconds (main computer, debug).
Task 3 takes ~ 1 milliseconds (main computer, release).
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
	double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Took " << std::fixed << duration * 0.001 << " milliseconds to execute";

	if(count1 != 344 || count2 != 0 || !binaryTree->isBalanced()) return false;

	return true;
}

/*
Task4 I insert all 66 common words into the weighted, undirected graph structure.
The edges between all new vertices are also calculated.
Task 4 takes ~ 17 seconds (main computer, debug).
Task 4 takes ~ 120 milliseconds (main computer, release).
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
	double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Took " << duration * 0.001 << " milliseconds to execute";

	stream.close();

	if(commonWords.size() != 66) return false;

	return true;
}

/*
Task 5 I simply check if the graph is strongly connected (it should be true).
Task 5 takes ~ 27 milliseconds (main computer, debug).
Task 5 takes ~ 0.5 milliseconds (main computer, release).
*/
bool task5(Graph* graph) {
	auto start = std::chrono::high_resolution_clock::now();

	// Is the graph strongly connected?
	bool strongConnection = graph->isStronglyConnected();

	// Measure time taken to run the task
	auto end = std::chrono::high_resolution_clock::now();
	double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Took " << duration * 0.001 << " milliseconds to execute";

	if(!strongConnection) return false;

	return true;
}

/*
Task 6 I use Dijkstra's algorithm to find the shortest path between two vertices.
I will compare the result with the actual answer that I manually calculated.
Task 6 takes ~ 4 milliseconds (main computer, debug).
Task 6 takes ~ 1 milliseconds (main computer, release).
*/
bool task6(Graph* graph) {
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<GraphVertex*> path = graph->shortestPath("have", "will");

	// Measure time taken to run the task
	auto end = std::chrono::high_resolution_clock::now();
	double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Took " << duration * 0.001 << " milliseconds to execute";

	if(path.at(1)->value != "to") return false;

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

	std::cout << " Task5: " << std::boolalpha << task5(weightedGraph) << std::endl;

	std::cout << " Task6: " << std::boolalpha << task6(weightedGraph) << std::endl;

	// returns claimed memory
	mostCommonWords.clear();
	delete(searchTree);
	delete(weightedGraph);

	return 0;
}