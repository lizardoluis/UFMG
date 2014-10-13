/*
 * Graph.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: lizardo
 */

#include "Graph.h"

Graph::Graph() {
	size = 0;
	adjList.reserve(100000);
}

void Graph::insert(int u, int v) {

	int biggestNode;

	biggestNode = u > v ? u : v;

	if (biggestNode >= size) {
		adjList.resize(biggestNode+1);
		size = biggestNode+1;
	}

	if (u != v)
		adjList[u].push_back(v);
}

list<int> & Graph::getAdjList(int v) {
	return adjList[v];
}

int Graph::getSize() {
	return size;
}
