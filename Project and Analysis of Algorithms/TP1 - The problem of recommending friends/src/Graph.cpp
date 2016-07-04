/*
 * Graph.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: lizardo
 */

#include "Graph.h"
#include <iostream>

Graph::Graph(int numNodes) {
	this->numNodes = numNodes;
	adjList.resize(numNodes);
}

void Graph::insert(int u, int v, int f, int d) {

	EdgeData eData;
	eData.friendship = f;
	eData.distance = d;

	adjList[u - 1].push_back(make_pair(v - 1, eData));
	adjList[v - 1].push_back(make_pair(u - 1, eData));
}

int Graph::nextAdj(int v, int a, EdgeData &data) {

	if ((unsigned) v >= adjList.size() || adjList[v].size() == 0
			|| (unsigned) a >= adjList[v].size())
		return -1;
	else {
		data = adjList[v][a].second;
		return adjList[v][a].first;
	}
}

bool Graph::isConex() {
	vector<bool> visited(numNodes, false);
	queue<int> nodesQueue;

	nodesQueue.push(0);

	while (!nodesQueue.empty()) {
		int u = nodesQueue.front();
		nodesQueue.pop();
		visited[u] = true;

		for (pair<int, EdgeData> edge : adjList[u]) {
			int v = edge.first;
			if (visited[v] == false) {
				nodesQueue.push(v);
			}
		}
	}

	for (bool b : visited) {
		if (b == false)
			return false;
	}

	return true;
}

double Graph::maximalSpanning(double ratio) {

	double weight = 0.0;

	vector<double> keys(numNodes, -numeric_limits<double>::max());
	vector<bool> inHeap(numNodes, true);
	vector<int> predecessor(numNodes, -1);

	keys[0] = 0.0;

	MaxPriorityQueue priorityQueue(keys);

	// Prim's algorithm - max spanning tree
	while (!priorityQueue.empty()) {
		pair<int, double> u = priorityQueue.extractMax();
		inHeap[u.first] = false;

		// Add negative edges only if they are bridges
		if (u.second < 0) {
			weight += u.second;
		}

		for (pair<int, EdgeData> edge : adjList[u.first]) {
			int v = edge.first;
			EdgeData eData = edge.second;

			double key = eData.friendship - ratio * (double)eData.distance;

			// Add other positive edges to the maximal spanning graph
			if (inHeap[v] && key > 0) {
				weight += key;
			}

			if (inHeap[v] && priorityQueue.increaseKey(v, key)) {
				predecessor[v] = u.first;
			}
		}
	}

	return weight;
}
