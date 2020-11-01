#pragma once
#include <string>
#include <vector>

// Using this website as a guide
// https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/

struct GraphVertex {
	std::string value;

	// Used to complete Task 5 and 6 as this helps keep track of specific vertex values.
	// Used to make desicions in those Tasks (find shortest path or strong connection)
	bool visited = false; 
	GraphVertex* parent = nullptr; 
	float distance = 0.f;

	// Task 4 requirement and used in Task 6.
	std::vector<int> sonnetNumbers;
	// Allows me to easily complete Task 5 as I can traverse the vertex edges to see if every vertex and visit another vertex.
	std::vector<std::pair<GraphVertex*, float>> edges;

	GraphVertex(std::string word) {
		this->value = word;
	};
};

class Graph {
private:
	std::vector<GraphVertex*> vertices;

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

