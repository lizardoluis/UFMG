/*
 * SCC.h
 *
 *  Created on: Oct 5, 2014
 *      Author: lizardo
 */

#ifndef SCC_H_
#define SCC_H_

using namespace std;

#include "Graph.h"

#include <list>

class SCC {
private:
	Graph *graph;
	Graph *graphT;

	void dfs(int node);

	void strongConnect(int v, int &id, vector<int> &index, vector<int> &lowLink, stack<int> &S, vector<bool> &inStack);
public:
	SCC(Graph &graph, Graph &graphT);

	list<int> kosaraju();

	list<int> tarjan();

	void classify(list<list<int> > components);
};

#endif /* SCC_H_ */
