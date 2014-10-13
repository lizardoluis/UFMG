/*
 * Graph.h
 *
 *  Created on: Sep 18, 2014
 *      Author: lizardo
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <vector>

using namespace std;

/*
 * Directed graph.
 */
class Graph {
private:

	/*
	 * Graph size.
	 */
	int size;

	/*
	 * Adjacent list.
	 */
	vector<list<int> > adjList;

public:

	/*
	 * Constructor.
	 */
	Graph();

	/*
	 * Insert the edge(u, v) in the graph. If u or v is greater than the graph
	 * size, it resizes the graph to |u| or |v|.
	 */
	void insert(int u, int v);

	/*
	 * Returns the reference to the adjacent list of the graph.
	 */
	list<int> & getAdjList(int v);

	/*
	 * Returns the size of the graph.
	 */
	int getSize();
};

#endif /* GRAPH_H_ */
