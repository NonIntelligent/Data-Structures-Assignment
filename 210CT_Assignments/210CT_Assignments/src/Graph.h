#pragma once
#include <string>
#include <vector>

// Using this website as a guide
// https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/

struct GraphVertex {
	std::string value;

	// Used in other methods
	GraphVertex* parent = nullptr;
	bool visited = false;
	float distance = 0.f;

	std::vector<int> sonnetNumbers;
	std::vector<std::pair<GraphVertex*, float>> edges;

	GraphVertex(std::string word) {
		this->value = word;
	};
};

struct GraphEdge {
	GraphVertex* first;
	GraphVertex* second;
	float weight = 0;
};

class Graph {
private:
	std::vector<GraphVertex*> vertices;
	std::vector<GraphEdge*> edges;

private:
	float _calculateEdge(GraphVertex *vertex1, GraphVertex *vertex2);

public:
	Graph();
	~Graph();

	void insert(std::string word, std::vector<int> sonnets);
	void remove(std:: string word);

	void depthFirstSearch(int start, bool print);

	bool isStronglyConnected();
	void resetVisited();
	std::vector<GraphVertex*> shortestPath(std::string start, std::string end);
	void recalculateAllEdges();

	GraphVertex* getVertex(std::string word);
	int getIndex(GraphVertex* element);
};

