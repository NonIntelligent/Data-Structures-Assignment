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
	/* Calculates the edge between two vertex's by iterating through their common sonnets
	Returns the inverse of common sonnets as specified by Task4
	Time complexity is O(n^2) where n is the number of sonnets (max n = 154). */
	float _calculateEdge(GraphVertex *vertex1, GraphVertex *vertex2);

public:
	Graph();
	~Graph();

	/* Creates a new vertex to add to the graph and calculates the new vertex's edges
	Copies the given vector into the newVertex's numbers
	Time complexity of O(n^3) due to calculating the edge for every common sonnet and vertex in list.
	However this only needs to be calculated the once.*/
	void insert(std::string word, std::vector<int> sonnets);

	// Removes a vertex from the graph and all edges to and from the vertex.
	void remove(std:: string word);

	/* https://www.youtube.com/watch?v=vRlaZ7Sh42Y
	Searches through the graph vertices and marks them as visted when traversing through the edges.
	Can also print out the value of the vertex using the 'print' parameter*/
	void depthFirstSearch(int start, bool print);

	// https://www.youtube.com/watch?v=6RQXHIQZYrA
	// Checks if the graph is strongly connected (can every node be visited from start)
	bool isStronglyConnected();

	// Sets all vertices visited attribute to false
	void resetVisited();

	/* https://www.youtube.com/watch?v=q-7KEJD-ZlY
	Uses Dijksrta's algorithm to find the shortest path between two vertices
	Prints out that words traversed from start to end.
	Prints out the most featured sonnet among the traversed words (if tied will print all of them)
	Returns the path as vector
	*/
	std::vector<GraphVertex*> shortestPath(std::string start, std::string end);

	// Retrieves the matching vertex from the vertices list
	GraphVertex* getVertex(std::string word);
	
	//Retrieves the index of the element from the vertices list
	int getIndex(GraphVertex* element);
};

