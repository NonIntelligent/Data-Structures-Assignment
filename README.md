# University Programming Assignment by Amaan Miah
Code was run and compiled on two seperate machines in debug and in release mode.
The performance was approximately measured using a Ryzen 5 3600 CPU

Task 1. Parse the Shakespear's sonnets file from lines 253 to 2867. 
Only parse the words and construct a Binary Search tree allowing duplicate nodes.

Task 2. Write 2 functions for the tree:
- Search the tree for a user-specified word and return the number of times it appears in the tree.
- Search the tree for 66 most commonly used words in the text (excluding "the" and "a"),
	printed in alphabetical order.
	
Task 3. Implement a function that deletes every instance of a given word form the tree
and also rebalances it.

Task 4. Implement a structure for a weighted, undirected graph where the vertices represent the words in task 2.
The vertex data structure shall include an array of the numbers of the Sonnets in which the word appears.
Create an edge between words which share the same sonnet and the weighting is inversely proportional to the number of sonnets.

Task 5. Implement a function which determines whether or not the graph is strongly connected returning true or false.

Task 6. Implement Dijkstra's algorithm which accepts two words a start and a goal.
The algorithm will traverse the graph and find the shortest path between the two words
and output in terms of words traversed. Additionally an integer score shall be generated for each sonnet
the traversed words feature, incrementing for each appearance of the sonnet and output the highest scoring sonnet.