/*
 * Graph.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: lizardo
 */

#include "Graph.h"

Graph::Graph() {
	size = 0;
	adjList.reserve(40000000);
	vertex.reserve(4000000);
}

void Graph::insert(int u, int v) {

	int biggestNode;

	biggestNode = u > v ? u : v;

	if (biggestNode >= size) {
		adjList.resize(biggestNode + 1);
		adjListT.resize(biggestNode + 1);
		size = biggestNode + 1;
		vertex.resize(size);
	}

	if (u != v){
		adjList[u].push_back(v);
		adjListT[v].push_back(u);
	}

	vertex[u] = true;
	vertex[v] = true;
}

list<int> & Graph::getAdjList(int v) {
	return adjList[v];
}

list<int> & Graph::getAdjListT(int v) {
	return adjListT[v];
}

int Graph::getSize() {
	return size;
}

bool Graph::isVertex(int v){
	return vertex[v];
}
