/*
 * Graph.h
 *
 *  Created on: Sep 18, 2014
 *      Author: lizardo
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stack>
#include <vector>
#include <list>

using namespace std;

class Graph {
private:
	int size;
	vector<list<int> > adjList;

public:

	Graph();

	Graph(int numNodes);

	void insert(int u, int v);

	list<int> & getAdjList(int v);

	int getSize();

	void print();
};

#endif /* GRAPH_H_ */
