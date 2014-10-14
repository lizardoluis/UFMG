/*
 * WebClassifier.cpp
 *
 *  Created on: Oct 9, 2014
 *      Author: lizardo
 */

#include "WebClassifier.h"

#include <cstdio>
#include <queue>
#include <stack>

WebClassifier::WebClassifier(int webSize) {
	nodesType.resize(webSize, DISCONNECTED);
}

int WebClassifier::classify_scc(Graph &graph, Graph &graphT) {

	list<int> scc;
	stack<int> S, dfsStack;
	vector<bool> discovered(graph.getSize(), false);

	/*
	 * Choose an arbitrary vertex v not in S. Perform a depth-first search
	 * starting at v. Each time that depth-first search finishes expanding
	 * a vertex u, push u onto S.
	 *
	 * DFS graph
	 */
	for (int i = 0; i < graph.getSize(); i++) {
		if (!discovered[i] && graph.isVertex(i)) {
			dfsStack.push(i);

			while (!dfsStack.empty()) {
				int u = dfsStack.top();
				if (discovered[u]) {
					dfsStack.pop();
					S.push(u);
					continue;
				} else {
					discovered[u] = true;
					list<int> adjList = graph.getAdjList(u);
					for (int v : adjList) {
						if (!discovered[v]) {
							dfsStack.push(v);
						}
					}

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

	while (!S.empty()) {

		list<int> component;

		int w = S.top();
		S.pop();

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

	// Set the nodes type to SCC
	for (int i : scc) {
		nodesType[i] = SCC;
	}

	// Returns one node of the SCC
	return scc.front();
}

void WebClassifier::classify_nodes(Graph &graph, list<int> &startNodes,
		list<int> &nodesList, Type setType) {

	list<int> scc;
	stack<int> nStack;
	vector<bool> visited(graph.getSize(), false);

	// DFS
	for (int startNode : startNodes) {
		if (!visited[startNode]) {
			nStack.push(startNode);

			while (!nStack.empty()) {
				int u = nStack.top();
				nStack.pop();

				if (!visited[u]) {
					visited[u] = true;

					// if node is not classified, classify it as setType
					if (nodesType[u] == DISCONNECTED) {
						scc.push_back(u);
						nodesType[u] = setType;
					} else if (setType == TENDRILS_A) {
						// Avoid the SCC or OUT nodes in the DFS of the undirected graph.
						if (nodesType[u] == SCC || nodesType[u] == OUT) {
							continue;
						} else if (nodesType[u] == TENDRILS_B) {
							nodesType[u] = TENDRILS_C;
						}
					} else if (setType == TENDRILS_B) {
						// Avoid the SCC or IN nodes in the DFS of the undirected graph.
						if (nodesType[u] == SCC || nodesType[u] == IN) {
							continue;
						}
						// Classify it as Tendrils-C
						else if (nodesType[u] == TENDRILS_A) {
							nodesType[u] = TENDRILS_C;
						}
					}

					list<int> adjList = graph.getAdjList(u);
					for (int v : adjList) {
						nStack.push(v);
					}
				}
			}
		}
	}

	nodesList = scc;
}

void WebClassifier::export_components(Graph &graph) {
	FILE *fpSCC = fopen(SCC_FILE, "w");
	FILE *fpIn = fopen(IN_FILE, "w");
	FILE *fpOut = fopen(OUT_FILE, "w");
	FILE *fpTendrilsA = fopen(TENDRILS_A_FILE, "w");
	FILE *fpTendrilsB = fopen(TENDRILS_B_FILE, "w");
	FILE *fpTendrilsC = fopen(TENDRILS_C_FILE, "w");
	FILE *fpDisconnected = fopen(DISCONNECTED_FILE, "w");

	int cSCC=0, cIN=0, cOUT=0, cTENDRILS_A=0, cTENDRILS_B=0, cTENDRILS_C=0, cDISCONNECTED=0;

	for (unsigned i = 0; i < nodesType.size(); i++) {
		if (graph.isVertex(i)) {
			switch (nodesType[i]) {
			case SCC:
				fprintf(fpSCC, "%d\n", i);
				cSCC++;
				break;
			case IN:
				fprintf(fpIn, "%d\n", i);
				cIN++;
				break;
			case OUT:
				fprintf(fpOut, "%d\n", i);
				cOUT++;
				break;
			case TENDRILS_A:
				fprintf(fpTendrilsA, "%d\n", i);
				cTENDRILS_A++;
				break;
			case TENDRILS_B:
				fprintf(fpTendrilsB, "%d\n", i);
				cTENDRILS_B++;
				break;
			case TENDRILS_C:
				fprintf(fpTendrilsC, "%d\n", i);
				cTENDRILS_C++;
				break;
			case DISCONNECTED:
				fprintf(fpDisconnected, "%d\n", i);
				cDISCONNECTED++;
				break;
			}
		}
	}

	printf("FileSize: %d %d %d %d %d %d %d\n", cSCC, cIN, cOUT, cTENDRILS_A, cTENDRILS_B, cTENDRILS_C, cDISCONNECTED);

	fclose(fpSCC);
	fclose(fpIn);
	fclose(fpOut);
	fclose(fpTendrilsA);
	fclose(fpTendrilsB);
	fclose(fpTendrilsC);
	fclose(fpDisconnected);
}

//void WebClassifier::export_dot(Graph &graph) {
//	FILE *fp = fopen("test.dot", "w");
//
//	fprintf(fp, "digraph world {\n");
//
//	// SCC
//	fprintf(fp, "subgraph clusterA {\n label = \"SCC\";");
//	for (unsigned i = 0; i < nodesType.size(); i++) {
//		if (nodesType[i] == SCC)
//			fprintf(fp, "%d;\n", i + 1);
//	}
//	fprintf(fp, "}\n");
//
//	// IN
//	fprintf(fp, "subgraph clusterB {\n label = \"IN\";");
//	for (unsigned i = 0; i < nodesType.size(); i++) {
//		if (nodesType[i] == IN)
//			fprintf(fp, "%d;\n", i + 1);
//	}
//	fprintf(fp, "}\n");
//
//	// OUT
//	fprintf(fp, "subgraph clusterC {\n label = \"OUT\";");
//	for (unsigned i = 0; i < nodesType.size(); i++) {
//		if (nodesType[i] == OUT)
//			fprintf(fp, "%d;\n", i + 1);
//	}
//	fprintf(fp, "}\n");
//
//	// TENDRILS_A
//	fprintf(fp, "subgraph clusterD {\n label = \"Tendrils_A\";");
//	for (unsigned i = 0; i < nodesType.size(); i++) {
//		if (nodesType[i] == TENDRILS_A)
//			fprintf(fp, "%d;\n", i + 1);
//	}
//	fprintf(fp, "}\n");
//
//	// TENDRILS_B
//	fprintf(fp, "subgraph clusterE {\n label = \"Tendrils_B\";");
//	for (unsigned i = 0; i < nodesType.size(); i++) {
//		if (nodesType[i] == TENDRILS_B)
//			fprintf(fp, "%d;\n", i + 1);
//	}
//	fprintf(fp, "}\n");
//
//	// TENDRILS_C
//	fprintf(fp, "subgraph clusterF {\n label = \"Tendrils_C\";");
//	for (unsigned i = 0; i < nodesType.size(); i++) {
//		if (nodesType[i] == TENDRILS_C)
//			fprintf(fp, "%d;\n", i + 1);
//	}
//	fprintf(fp, "}\n");
//
//	// DISCONNECTED
//	fprintf(fp, "subgraph clusterG {\n label = \"Disconnected\";");
//	for (unsigned i = 0; i < nodesType.size(); i++) {
//		if (nodesType[i] == DISCONNECTED)
//			fprintf(fp, "%d;\n", i + 1);
//	}
//	fprintf(fp, "}\n");
//
//	for (int u = 0; u < graph.getSize(); u++) {
//		list<int> adjList = graph.getAdjList(u);
//		for (int v : adjList) {
//			fprintf(fp, "%d -> %d;\n", u + 1, v + 1);
//		}
//	}
//
//	for (int u = 0; u < graph.getSize(); u++) {
//		fprintf(fp,
//				"%d [label=\"\",shape=circle,height=0.1,width=0.1,fontsize=1];\n",
//				u + 1);
//	}
//
//	fprintf(fp, "}\n");
//
//	fclose(fp);
//}
