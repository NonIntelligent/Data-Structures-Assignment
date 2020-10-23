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
Task1 takes ~ 1.3 seconds to complete on main computer */
bool task1(vectorString& list, BinaryTree& binaryTree) {
	// Parsed words includes capital letters as seperate words.
	list = parseTxtAsWords(253, 2867, "res/Shakespeare.txt");
	std::string* test = list.data();
	// Sort the list in acending order (A < z)
	quickSort(test, 0, list.size() - 1);

	binaryTree = BinaryTree();

	// This version of binary tree takes accepts duplicate nodes but is also balanced.
	// The input requires a sorted list though
	binaryTree.setRoot(binaryTree.insertArrayBalanced(test, 0, list.size() - 1));
	int depth = binaryTree.getMaxDepth();

	if(depth == 0) return false;

	return true;
}

// Tests if task 2 succeded
bool task2() {

	return true;
}

int main() {
	// Can be used in other tasks and destoryed at end of main
	vectorString wordsList;
	BinaryTree searchTree;

	auto start = std::chrono::high_resolution_clock::now();
	auto end = start;

	std::cout << "Task1: " << std::boolalpha << task1(wordsList, searchTree);
	end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << " Took " << duration << " milliseconds to execute" << std::endl;

	start = std::chrono::high_resolution_clock::now();

	std::cout << "Task2: " << std::boolalpha << task2();
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << " Took " << duration << " milliseconds to execute" << std::endl;


	return 0;
}