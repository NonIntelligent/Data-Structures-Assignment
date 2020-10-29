#include "Algorithms.h"

#include <array>
#include <iostream>

// https://stackoverflow.com/questions/9642292/function-to-check-if-string-contains-a-number
// Does the string contain a digit?
bool has_a_digit(std::string& s) {
	return std::any_of(s.begin(), s.end(), ::isdigit);
}

int getNumberFromLine(std::string& line) {
	return std::stoi(line);
}

template <typename T>
int partition(T* arr, int start, int end) {
	T pivot = arr[end]; // Pivot is at end(right side of partition)
	int i = start - 1;
	int j = end;

	// Swap values until pivot is reached
	for(int j = start; j < end; j++) {
		if(arr[j] < pivot) {
			i++;
			// Swap the values
			T temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		}
	}
	// Swap the values
	T temp = arr[end];
	arr[end] = arr[i + 1];
	arr[i + 1] = temp;

	return i + 1;
}

void quickSort(int* arr, int start, int end) {

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
		std::getline(stream, line);

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
			else if(!word.empty()) {// Once the end of word is reached then push to array
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

std::vector<int> findWordInSonnets(std::string &target, std::ifstream &stream) {
	// Initialise array and read stream
	std::vector<int> result;

	// Set stream back to start of the sonnets
	stream.clear();
	stream.seekg(0, std::ios::beg);

	// Initialise variable to reuse in loops (improving performance)
	std::string line;
	std::string currentWord;
	char letter;
	int currentSonnet = 0;
	int currentLine = 1;

	// Skip first part of the text file
	while(currentLine < 253) {
		std::getline(stream, line);
		currentLine++;
	}

	// Untill all lines are read, get the words and store them in the results array
	while(currentLine <= 2867) {
		std::getline(stream, line);

		// Set the current sonnet number
		if(has_a_digit(line)) {
			currentSonnet = getNumberFromLine(line);
			currentLine++;
			continue;
		}

		// Read each letter of the line and add it to the word
		for(auto it = line.begin(); it != line.end(); it++) {
			letter = *it;

			// Only add alphablet characters to the word
			// 39 is equivalent to ' (apostrophe)
			if(isalpha(letter) || letter == 39) {
				currentWord.push_back(letter);
				if(currentWord[0] == 39) currentWord.erase(currentWord.begin()); // No apostrophe at beginning of a word
			}
			else if(!currentWord.empty()) {// Once the end of word is reached then check if it's the target word
				// If target word is found and the sonnet is not already in the list
				bool sonnetDuplicate = std::find(result.begin(), result.end(), currentSonnet) != result.end();
				if(target == currentWord && !sonnetDuplicate) {
					result.push_back(currentSonnet);
				}
				currentWord.clear();
			}
		}

		currentLine++;
	}

	// Can be later accessed as array without any empty elements
	result.shrink_to_fit();
	return result;
}