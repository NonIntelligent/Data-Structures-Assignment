#include "BinaryTree.h"

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <chrono>

#define vectorString std::vector<std::string>

// https://stackoverflow.com/questions/9642292/function-to-check-if-string-contains-a-number
// Does the string contain a digit?
bool has_a_digit(const std::string& s) {
	return std::any_of(s.begin(), s.end(), ::isdigit);
}

// Quicksort partition algorithm
int partition(std::string* arr, int start, int end) {
	std::string pivot = arr[end]; // Pivot is at end(right side of partition)
	int i = start - 1;
	int j = end;

	// Swap values until pivot is reached
	for(int j = start; j < end; j++) {
		if(arr[j] < pivot) {
			i++;
			// Swap the values
			std::string temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		}
	}
	// Swap the values
	std::string temp = arr[end];
	arr[end] = arr[i + 1];
	arr[i + 1] = temp;

	return i + 1;
}

// https://www.geeksforgeeks.org/quick-sort/
// https://www.geeksforgeeks.org/quicksort-tail-call-optimization-reducing-worst-case-space-log-n/
// Quicksort algorithm to sort a list of strings
// Tail-cull optimisation was used to reduce space complexity as we are iterating over 17000 words
// Worst case space is now O(Log n) as opposed to O(n)
void quickSort(std::string* arr, int start, int end) {

	while(start < end) {
		int pivot = partition(arr, start, end);

		if(pivot - start < end - pivot) {
			quickSort(arr, start, pivot - 1);
			start = pivot + 1;
		}
		else {
			quickSort(arr, pivot + 1, end);
			end = pivot - 1;
		}
	}
}

// Parses a txt file for exculsively words and returns an array of words
vectorString parseTxtAsWords(int lineStart, int lineEnd, std::string filePath) {
	// Initialise array and read stream
	vectorString result;
	std::ifstream stream(filePath);

	// Initialise variable to reuse in loops (improving performance)
	std::string line;
	std::string word;
	char letter;
	int currentLine = 1;

	// Skip first part of the text file
	while(currentLine < lineStart) {
		std::getline(stream, line);
		currentLine++;
	}

	// Untill all lines are read, get the words and store them in the results array
	while(currentLine <= lineEnd) {
		std::getline(stream,line);

		// Ignore Sonnet number (assignment requirement)
		if(has_a_digit(line)) {
			currentLine++;
			continue;
		}

		// Read each letter of the line and add it to the word
		for(auto it = line.begin(); it != line.end(); it++) {
			letter = *it;

			// Only add alphablet characters to the word
			// 39 is equivalent to ' (apostrophe)
			if(isalpha(letter) || letter == 39) {
			word.push_back(letter);
			if(word[0] == 39) word.erase(word.begin()); // No apostrophe at beginning of a word
			}
			else if (!word.empty()) {// Once the end of word is reached then push to array
				result.push_back(word);
				word.clear();
			}
		}


		currentLine++;
	}

	// Clears buffers
	stream.close();
	// Can be later accessed as array without any empty elements
	result.shrink_to_fit();
	return result;
}

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
bool task2(BinaryTree* binaryTree) {
	auto start = std::chrono::high_resolution_clock::now();

	// Tests counting of certain words of known number of appearences
	int count1 = binaryTree->howManyOf("the");
	int count2 = binaryTree->howManyOf("I");
	int count3 = binaryTree->howManyOf("zealous");
	int count4 = binaryTree->howManyOf("gobbledygook");

	binaryTree->printMostCommonWords(66);

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

bool task4() {
	auto start = std::chrono::high_resolution_clock::now();

	// Measure time taken to run the task
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Took " << duration << " milliseconds to execute";
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

	std::cout << " Task1: " << std::boolalpha << task1(searchTree) << std::endl;

	std::cout << " Task2: " << std::boolalpha << task2(searchTree) << std::endl;

	std::cout << " Task3: " << std::boolalpha << task3(searchTree) << std::endl;

	std::cout << " Task4: " << std::boolalpha << task4() << std::endl;

	std::cout << " Task5: " << std::boolalpha << task5() << std::endl;

	std::cout << " Task6: " << std::boolalpha << task6() << std::endl;

	delete(searchTree);
	return 0;
}