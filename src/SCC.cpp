/*
 * SCC.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: lizardo
 */

#include "SCC.h"
#include <vector>
#include <stack>
#include <iostream>

#define MIN(a, b) (a < b ? a : b)

SCC::SCC(Graph &graph, Graph &graphT) {
	this->graph = &graph;
	this->graphT = &graphT;
}

void SCC::dfs() {

	int graphSize = graph->getSize();
	int time = 0;
	stack<int> nodesStack;
	vector<int> finishTime(graphSize);
	vector<bool> discovered(graphSize, false);

	for (int i = 0; i < graphSize; i++) {
		if (!discovered[i]) {
			nodesStack.push(i);

			while (!nodesStack.empty()) {
				int u = nodesStack.top();
				nodesStack.pop();
				discovered[u] = true;

				list<int> adjList = graph->getAdjList(u);
				for (int v : adjList) {
					if (!discovered[v]) {
						nodesStack.push(v);
					}
				}
				finishTime[u] = time++;
			}
		}
	}
}

list<list<int> > SCC::kosaraju() {

	stack<int> kosarajuStack;
	stack<int> dfsStack;

	vector<bool> discovered(graph->getSize(), false);

	/*
	 * Choose an arbitrary vertex v not in S. Perform a depth-first search
	 * starting at v. Each time that depth-first search finishes expanding
	 * a vertex u, push u onto S.
	 *
	 * DFS graph
	 */
	for (int i = 0; i < graph->getSize(); i++) {
		if (!discovered[i]) {
			dfsStack.push(i);

			while (!dfsStack.empty()) {
				int u = dfsStack.top();
				dfsStack.pop();

				if (!discovered[u]) {
					discovered[u] = true;
					list<int> adjList = graph->getAdjList(u);
					for (int v : adjList) {
						dfsStack.push(v);
					}
					kosarajuStack.push(u);
				}
			}
		}
	}

	/*
	 * Pop the top vertex v from S. Perform a depth-first search starting at
	 * v in the transpose graph. The set of visited vertices will give the
	 * strongly connected component containing v; record this and remove all
	 * these vertices from the graph G and the stack S.
	 */
	vector<bool> visited(graphT->getSize(), false);
	list<list<int> > scc;

	while (!kosarajuStack.empty()) {

		list<int> component;

		int w = kosarajuStack.top();
		kosarajuStack.pop();

		if (!visited[w]) {
			/*
			 * DFS graphT
			 */
			dfsStack.push(w);

			while (!dfsStack.empty()) {
				int u = dfsStack.top();
				dfsStack.pop();

				if (!visited[u]) {
					visited[u] = true;
					component.push_back(u);

					list<int> adjList = graphT->getAdjList(u);
					for (int v : adjList) {
						dfsStack.push(v);
					}
				}
			}
			scc.push_back(component);
		}
	}

	return scc;
}

list<list<int> > SCC::tarjan() {

	int id = 0;
	vector<int> index(graph->getSize(), -1);
	vector<int> lowLink(graph->getSize());
	vector<bool> inStack(graph->getSize());

	stack<int> S;

	for (int v = 0; v < graph->getSize(); v++) {
		if (index[v] == -1) {
			strongConnect(v, id, index, lowLink, S, inStack);
		}
	}

	list<list<int> > scc;
	return scc;
}

void SCC::strongConnect(int v, int &id, vector<int> &index,
		vector<int> &lowLink, stack<int> &S, vector<bool> &inStack) {

	// Set the depth index for v to the smallest unused index
	index[v] = id;
	lowLink[v] = id;
	id++;

	S.push(v);
	inStack[v] = true;

	// Consider successors of v
	list<int> adjList = graph->getAdjList(v);

	for (int w : adjList) {
		if (index[w] == -1) {
			// Successor w has not yet been visited; recurse on it
			strongConnect(w, id, index, lowLink, S, inStack);
			lowLink[v] = MIN(lowLink[w], lowLink[v]);

		} else if (inStack[w]) {
			// Successor w is in stack S and hence in the current SCC
			lowLink[v] = MIN(index[w], lowLink[v]);
		}
	}

	// If v is a root node, pop the stack and generate an SCC
	if (lowLink[v] == index[v]) {
		list<int> component;

		int w;
		do {
			w = S.top();
			S.pop();
			inStack[w] = false;

			component.push_back(w);
			cout << w + 1 << " ";

		} while (w != v);

		cout << endl;
	}
}
