#include "Graph.h"

#include "Algorithms.h"

#include <stack>
#include <iostream>

// Calculates the edge between two vertex's by iterating through their common sonnets
// Returns the inverse of common sonnets as specified by Task4
// Time complexity is O(n^2) where n is the number of sonnets.
float Graph::_calculateEdge(GraphVertex *vertex1, GraphVertex *vertex2) {
	float count = 0.f;
	int* arr1 = vertex1->sonnetNumbers.data();
	int* arr2 = vertex2->sonnetNumbers.data();
	int size1 = vertex1->sonnetNumbers.size();
	int size2 = vertex2->sonnetNumbers.size();

	// Iterate through list and count up all sonnets where both words appear
	for(int i = 0; i < size1; i++) {
		for(int j = 0; j < size2; j++) {
			if(arr1[i] == arr2[j]) count++;
		}
	}

	// Return the inverse of the count as the edge if not 0 to avoid error
	if(count == 0)
		return count;
	else
		return 1 / count;
}

Graph::Graph() {
}

Graph::~Graph() {
	vertices.clear();
}

// Creates a new vertex to add to the graph and calculates the new vertex's edges
// Copies the given vector into the newVertex's numbers
// Time complexity of O(n^3) due to calculating the edge for every common sonnet and vertex in list.
void Graph::insert(std::string word, std::vector<int> sonnets) {
	GraphVertex* newVertex = new GraphVertex(word);
	newVertex->sonnetNumbers = std::vector<int>(sonnets);

	// re-used in for loop to not waste time on allocation
	float edge = 0.f;

	// Calculate the edges for each vertex.
	for(int i = 0; i < vertices.size(); i++) {
		GraphVertex* vertexNode = vertices.at(i);
		edge = _calculateEdge(newVertex, vertexNode);
		// Add edges to both verticess
		if(edge > 0.f) {
			newVertex->edges.push_back(std::make_pair(vertexNode, edge));
			vertexNode->edges.push_back(std::make_pair(newVertex, edge));
		} 
	}

	vertices.push_back(newVertex);
}

void Graph::remove(std::string word) {
}

// https://www.youtube.com/watch?v=vRlaZ7Sh42Y
// Searches through the graph vertices and marks them as visted when traversing through the edges.
// Can also print out the value of the vertex using the 'print' parameter
void Graph::depthFirstSearch(int start, bool print) {
	if(start >= vertices.size()) return;

	GraphVertex* vertex = vertices.at(start);
	std::stack<GraphVertex*> stack;
	stack.push(vertex);
	vertex->visited = true;

	// Until every vertex is checked for any possible paths
	while(!stack.empty()) {
		vertex = stack.top();
		stack.pop();

		if (print) std::cout << vertex->value << std::endl;

		// Mark each connected vertex as visited and push to stack
		for(auto pair : vertex->edges) {
			if(!pair.first->visited) {
				stack.push(pair.first);
				pair.first->visited = true;
			}
		}

	}

}
// https://www.youtube.com/watch?v=6RQXHIQZYrA
// Checks if the graph is strongly connected (can every node be visited from start)
bool Graph::isStronglyConnected() {
	for(int i = 0; i < vertices.size(); i++) {
		depthFirstSearch(i, false);

		for(int j = 0; j < vertices.size(); j++) {
			if(!vertices.at(j)->visited) {
				return false;
			}
		}
		// sets visited to false to prepare for next iteration
		resetVisited();
	}

	// When every starting vertex can visit every other vertex
	return true;
}

// Sets all vertices visited attribute to false
void Graph::resetVisited() {
	for(int i = 0; i < vertices.size(); i++) {
		vertices.at(i)->visited = false;
	}
		
}

void Graph::recalculateAllEdges() {
}
