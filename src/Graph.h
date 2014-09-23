/*
 * Graph.h
 *
 *  Created on: Sep 18, 2014
 *      Author: lizardo
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <queue>
#include <vector>
#include <limits>

#include "MaxPriorityQueue.h"

using namespace std;

typedef struct EdgeData {
	int friendship;
	int distance;
} EdgeData;

class Graph {
private:
	int numNodes;
	vector<vector<pair<int, EdgeData> > > adjList;

public:
	Graph(int numNodes);

	void insert(int u, int v, int f, int d);

	int nextAdj(int v, int a, EdgeData &data);

	bool isConex();

	float maximalSpanning(float rate);
};

#endif /* GRAPH_H_ */
