/*
 * Graph.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: lizardo
 */

#include "Graph.h"

Graph::Graph(int numNodes) {
	this->numNodes = numNodes;
	adjList.resize(numNodes);
}

void Graph::insert(int u, int v, int f, int d) {

	EdgeData eData;
	eData.friendship = f;
	eData.distance = d;

	adjList[u].push_back(make_pair(v, eData));
	adjList[v].push_back(make_pair(u, eData));
}

int Graph::nextAdj(int v, int a, EdgeData &data) {

	if ( (unsigned) v >= adjList.size() || adjList[v].size() == 0 || (unsigned) a >= adjList[v].size())
		return -1;
	else {
		data = adjList[v][a].second;
		return adjList[v][a].first;
	}
}

bool Graph::isConex(){
	vector <bool> visited(numNodes, false);
	queue <int> nodesQueue;

	nodesQueue.push(0);

	while(!nodesQueue.empty()){
		int u = nodesQueue.front();
		nodesQueue.pop();
		visited[u] = true;

		for(pair<int, EdgeData> edge : adjList[u]){
			int v = edge.first;
			if(visited[v] == false){
				nodesQueue.push(v);
			}
		}
	}

	for(bool b : visited){
		if(b == false)
			return false;
	}

	return true;
}
