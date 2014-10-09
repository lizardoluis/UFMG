/*
 * WebClassifier.cpp
 *
 *  Created on: Oct 9, 2014
 *      Author: lizardo
 */

#include "WebClassifier.h"

WebClassifier::WebClassifier(int webSize) {
	nodesType.resize(webSize, DISCONNECTED);
}

int WebClassifier::classify_SCC(Graph &graph, Graph &graphT) {

	list<int> scc;
	stack<int> kosarajuStack;
	stack<int> dfsStack;

	vector<bool> discovered(graph.getSize(), false);

	/*
	 * Choose an arbitrary vertex v not in S. Perform a depth-first search
	 * starting at v. Each time that depth-first search finishes expanding
	 * a vertex u, push u onto S.
	 *
	 * DFS graph
	 */
	for (int i = 0; i < graph.getSize(); i++) {
		if (!discovered[i]) {
			dfsStack.push(i);

			while (!dfsStack.empty()) {
				int u = dfsStack.top();
				dfsStack.pop();

				if (!discovered[u]) {
					discovered[u] = true;
					list<int> adjList = graph.getAdjList(u);
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
	vector<bool> visited(graphT.getSize(), false);

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

					list<int> adjList = graphT.getAdjList(u);
					for (int v : adjList) {
						dfsStack.push(v);
					}
				}
			}

			if (component.size() > scc.size()) {
				scc = component;
			}
		}
	}

	for (int i : scc) {
		nodesType[i] = SCC;
	}

	return scc.front();
}

void WebClassifier::classify_Component(Graph &graph, list<int> &startComponent,
		list<int> &component, Type setType) {

	list<int> scc;
	stack<int> nStack;
	vector<bool> visited(graph.getSize(), false);

	for (int startNode : startComponent) {
		if (!visited[startNode]) {
			nStack.push(startNode);

			while (!nStack.empty()) {
				int u = nStack.top();
				nStack.pop();

				if (!visited[u]) {
					visited[u] = true;

					if (nodesType[u] == DISCONNECTED) {
						scc.push_back(u);
						nodesType[u] = setType;
					}
					else if (setType == TENDRILS_A && nodesType[u] == TENDRILS_B) {
						nodesType[u] = TENDRILS_C;
					}
					else if(setType == TENDRILS_B && nodesType[u] == TENDRILS_A) {
						nodesType[u] = TENDRILS_C;
					}

					list<int> adjList = graph.getAdjList(u);
					for (int v : adjList) {
						nStack.push(v);
					}
				}
			}
		}
	}

	component = scc;
}

void WebClassifier::print_components() {
	FILE *fpSCC = fopen(SCC_FILE, "w");
	FILE *fpIn = fopen(IN_FILE, "w");
	FILE *fpOut = fopen(OUT_FILE, "w");
	FILE *fpTendrilsA = fopen(TENDRILS_A_FILE, "w");
	FILE *fpTendrilsB = fopen(TENDRILS_B_FILE, "w");
	FILE *fpTendrilsC = fopen(TENDRILS_C_FILE, "w");
	FILE *fpDisconnected = fopen(DISCONNECTED_FILE, "w");

	for (unsigned i = 0; i < nodesType.size(); i++) {
		switch (nodesType[i]) {
		case SCC:
			fprintf(fpSCC, "%d\n", i + 1);
			break;
		case IN:
			fprintf(fpIn, "%d\n", i + 1);
			break;
		case OUT:
			fprintf(fpOut, "%d\n", i + 1);
			break;
		case TENDRILS_A:
			fprintf(fpTendrilsA, "%d\n", i + 1);
			break;
		case TENDRILS_B:
			fprintf(fpTendrilsB, "%d\n", i + 1);
			break;
		case TENDRILS_C:
			fprintf(fpTendrilsC, "%d\n", i + 1);
			break;
		case DISCONNECTED:
			fprintf(fpDisconnected, "%d\n", i + 1);
			break;
		}
	}

	fclose(fpSCC);
	fclose(fpIn);
	fclose(fpOut);
	fclose(fpTendrilsA);
	fclose(fpTendrilsB);
	fclose(fpTendrilsC);
	fclose(fpDisconnected);
}
