#pragma once
#include <string>
#include <vector>

// Using this website as a guide
// https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/

struct GraphVertex {
	std::string value;

	int* sonnetNumbers = nullptr;
	std::vector<std::pair<GraphVertex*, int>> edges;
};

class Graph {
private:
	std::vector<GraphVertex*> vertices;

private:
	void _insert(std::string word);
	void _remove(std:: string word);
	void _calculateEdge();

public:
	Graph();
	~Graph();
};

