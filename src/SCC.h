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

	void dfs();

	void strongConnect(int v, int &id, vector<int> &index, vector<int> &lowLink, stack<int> &S, vector<bool> &inStack);
public:
	SCC(Graph &graph, Graph &graphT);

	list< list<int> > kosaraju();

	list<list<int> > tarjan();
};

#endif /* SCC_H_ */
