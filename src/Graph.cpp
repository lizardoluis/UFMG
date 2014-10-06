/*
 * Graph.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: lizardo
 */

#include "Graph.h"

#include <iostream>

Graph::Graph(){
	size = 0;
	adjList.reserve(100);
}

Graph::Graph(int numNodes) {
	this->size = numNodes;
	adjList.resize(numNodes);
}

void Graph::insert(int u, int v) {

	int biggestNode;

	biggestNode = u > v ? u : v;

	if(biggestNode > size){
		adjList.resize(biggestNode);
		size = biggestNode;
	}

	adjList[u - 1].push_back(v - 1);
}

list<int> & Graph::getAdjList(int v){
	return adjList[v];
}

int Graph::getSize(){
	return size;
}

void Graph::print(){
	for(int i=0; i<size; i++){
		cout << i+1 << ": ";
		for(int j : adjList[i]){
			cout << j+1 << " ";
		}
		cout << endl;
	}
}
