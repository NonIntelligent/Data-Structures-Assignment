#pragma once
#include <string>
#include <vector>

// Using this website as a guide
// https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/

struct GraphVertex {
	std::string value;

	std::vector<int> sonnetNumbers;
	std::vector<std::pair<GraphVertex*, float>> edges;

	GraphVertex(std::string word) {
		this->value = word;
	};
};

class Graph {
private:
	std::vector<GraphVertex> vertices;

private:
	float _calculateEdge(GraphVertex &vertex1, GraphVertex &vertex2);

public:
	Graph();
	~Graph();

	void insert(std::string word, std::vector<int> sonnets);
	void remove(std:: string word);

	void recalculateAllEdges();
};

