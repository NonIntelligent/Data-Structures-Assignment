#pragma once
#include <string>
#include <vector>
#include <fstream>


#define vectorString std::vector<std::string>

/*
This file is used to contain any other methods and algorithms that I need to use in main
*/

// https://stackoverflow.com/questions/9642292/function-to-check-if-string-contains-a-number
// Does the string contain a digit?
bool has_a_digit(std::string &s);

// Convert the string into an integer
int getNumberFromLine(std::string& line);

// Quicksort partition algorithm (works for string or ints)
template <typename T>
int partition(T* arr, int start, int end);

// https://www.geeksforgeeks.org/quick-sort/
// https://www.geeksforgeeks.org/quicksort-tail-call-optimization-reducing-worst-case-space-log-n/
// Quicksort algorithm to sort a list of strings
// Tail-cull optimisation was used to reduce space complexity as we are iterating over 17000 words
// Worst case space is now O(Log n) as opposed to O(n)
void quickSort(int* arr, int start, int end);
void quickSort(std::string* arr, int start, int end);

// Parses a txt file for exculsively words and returns an array of words
vectorString parseTxtAsWords(int lineStart, int lineEnd, std::string filePath);

// Used to find all of the sonnets that the word can be found in and returns a vector of sonnet numbers
// This version requires an already opened stream to the Shakespeare text file.
std::vector<int> findWordInSonnets(std::string &target, std::ifstream &stream);
