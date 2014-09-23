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

float Graph::maximalSpanning(float ratio) {

	float weight = 0.0;

	vector<float> keys(numNodes, -numeric_limits<float>::max());
	vector<bool> inHeap(numNodes, true);
	vector<int> predecessor(numNodes, -1);

	keys[0] = 0.0;// numeric_limits<float>::max();

	MaxPriorityQueue priorityQueue(keys);

	while (!priorityQueue.empty()) {
		pair<float, int> u = priorityQueue.extractMax();
		inHeap[u.second] = false;
		weight += u.first;

		for (pair<int, EdgeData> edge : adjList[u.second]) {
			int v = edge.first;
			EdgeData eData = edge.second;

			float key = eData.friendship - ratio * eData.distance;

			if (inHeap[v] && priorityQueue.increaseKey(v, key)) {
				predecessor[v] = u.second;
			}
		}
	}

//	for (unsigned u = 0; u < keys.size(); u++)
//		if (predecessor[u] != -1) {
//			if (u < (unsigned) predecessor[u])
//				printf("%d %d\n", u + 1, predecessor[u] + 1);
//			else
//				printf("%d %d\n", predecessor[u] + 1, u + 1);
//		}
//	printf("\n");

	return weight;
}
