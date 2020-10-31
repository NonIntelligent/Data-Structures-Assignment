#include "Graph.h"

#include "Algorithms.h"

#include <stack>
#include <queue>
#include <iostream>

// Calculates the edge between two vertex's by iterating through their common sonnets
// Returns the inverse of common sonnets as specified by Task4
// Time complexity is O(n^2) where n is the number of sonnets (max n = 154).
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

// Removes a vertex from the graph and all edges to and from the vertex.
void Graph::remove(std::string word) {
	GraphVertex* vertex = getVertex(word);
	for(auto edge : vertex->edges) {
		for(auto other : edge.first->edges) {
			if(other.first == vertex) {
				other.first = nullptr;
				other.second = 0;
			}
		}
		edge.first = nullptr;
		edge.second = 0;
	}
	vertices.erase(std::remove(vertices.begin(), vertices.end(), vertex), vertices.end());
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
/* https://www.youtube.com/watch?v=q-7KEJD-ZlY
Uses Dijksrta's algorithm to find the shortest path between two vertices
Prints out that words traversed from start to end.
Prints out the most featured sonnet among the traversed words (if tied will print all of them)
// Returns the path as vector
*/
std::vector<GraphVertex*> Graph::shortestPath(std::string start, std::string end) {
	if(start == end) return std::vector<GraphVertex*>();
	// Check if the word exists as a vertex
	GraphVertex* vertex1 = getVertex(start);
	GraphVertex* vertex2 = getVertex(end);

	if(vertex1 == nullptr || vertex2 == nullptr) {
		std::cout << "Input word does not exist" << std::endl;
		return std::vector<GraphVertex*>();
	}

	// Setup values (distance is default to infinity, visited is false, parent is null)
	for(int i = 0; i < vertices.size(); i++) {
		vertices.at(i)->distance = 1000.f;
		vertices.at(i)->parent = nullptr;
		resetVisited();
	}

	// i.e sonnet 3 would be at index 3
	int sonnetScore[155] = {0};

	// Sort in ascending order (shortest distance first)
	auto cmp = [](GraphVertex* left, GraphVertex* right) {return left->distance > right->distance; };
	std::priority_queue<GraphVertex*, std::vector<GraphVertex*>, decltype(cmp)> minimumQueue(cmp);

	vertex1->distance = 0.f;
	minimumQueue.push(vertex1);
	// While there is a path/solution to the problem
	while(!minimumQueue.empty()) {
		GraphVertex* current = minimumQueue.top();
		minimumQueue.pop();

		if(current->visited) continue;

		current->visited = true;

		for(auto edge : current->edges) {
			GraphVertex* target = edge.first;
			float distance = edge.second;
			// If there is a shorter path then adjust values
			if(!target->visited && current->distance + distance < target->distance) {
				target->distance = current->distance + distance;
				target->parent = current;
				minimumQueue.push(target);
			}
		}
	}

	// Construct the path following the parent of vertex2 (end parameter)
	std::vector<GraphVertex*> path;
	path.insert(path.begin(), vertex2);
	GraphVertex* step = vertex2->parent;

	while(step != nullptr) {
		path.insert(path.begin(), step);
		step = step->parent;
	}

	// work out highest scoring sonnet (Task 6 requirement)
	int highScore = 0;

	std::cout << "Vertex path is: "<< vertex1->value;
	for(GraphVertex* v : path) {
		if (v != vertex1)
			std::cout << ", " << v->value;

		// Increment the sonnet score for each sonnet that the word appears in
		for(int sonnet : v->sonnetNumbers) {
			sonnetScore[sonnet] ++;
			if(highScore < sonnetScore[sonnet]) highScore = sonnetScore[sonnet];
		}
	}


	// Print sonnet scores
	std::cout << ": Highest Scoring Sonnets are";
	for(int i = 1; i < 155; i++) {
		if(sonnetScore[i] == highScore) {
			std::cout << ", "<< i;
		}
	}

	std::cout << " " << std::endl;
	std::cout << " " << std::endl;

	return path;
}

void Graph::recalculateAllEdges() {
}

// Retrieves the matching vertex from the vertices list
GraphVertex * Graph::getVertex(std::string word) {
	GraphVertex* vertex = nullptr;
	for(GraphVertex* v : vertices) {
		if(v->value == word) vertex = v;
	}
	return vertex;
}

//Retrieves the index of the element from the vertices list
int Graph::getIndex(GraphVertex * element) {
	int index = -1;
	auto it = std::find(vertices.begin(), vertices.end(), element);

	if(it != vertices.end()) {
		index = std::distance(vertices.begin(), it);
	}

	return index;
}
