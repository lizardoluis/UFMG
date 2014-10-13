//============================================================================
// Name        : paa-tp2.cpp
// Author      : Luis Lizardo
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <cstdlib>
#include <list>
#include <string>

#include "Graph.h"
#include "TimeProfiler.h"
#include "WebClassifier.h"

#define BUFFSZ 200

using namespace std;

void read_input(string fileName, Graph &graph, Graph &graphT, Graph &undirectedGraph) {
	FILE *fp = fopen(fileName.c_str(), "r");
	if (fp == NULL) {
		printf("Error when opening the input file.");
		exit(0);
	}

	int u, v, v1, v2;

	// Read the list of nodes in the file and add them to the graph
	char buff[BUFFSZ];
	while (fgets(buff, BUFFSZ, fp)) {
		if (buff[0] != '#') {
			sscanf(buff, "%d %d", &v1, &v2);

			// Normal graph
			graph.insert(u, v);

			// Transpose graph
			graphT.insert(v, u);

			// Undirected-graph
			undirectedGraph.insert(u, v);
			undirectedGraph.insert(v, u);
		}
	}

	fclose(fp);
}

int main(int argc, char *argv[]) {

	TimeProfiler time;
	time.start();

	// Read input file
	Graph graph, graphT, undirectedGraph;
	read_input(argv[1], graph, graphT, undirectedGraph);

	WebClassifier web(graph.getSize());

	// List of components
	int scc;
	list<int> sccList, out, in, tendrilsA, tendrilsB;

	// Classify SCC nodes and returns one node of the component
	scc = web.classify_scc(graph, graphT);
	sccList.push_back(scc);

	// Classify OUT nodes
	web.classify_nodes(graph, sccList, out, WebClassifier::OUT);

	// Classify IN nodes
	web.classify_nodes(graphT, sccList, in, WebClassifier::IN);

	// Classify Tendrils_A
	web.classify_nodes(undirectedGraph, in, tendrilsA, WebClassifier::TENDRILS_A);

	// Classify Tendrils_B and Tendrils_C
	web.classify_nodes(undirectedGraph, out, tendrilsB, WebClassifier::TENDRILS_B);

	// Export the components at the file
	web.export_components();

//	printf("Execution Time: %g\n", time.reportTime());
	printf("Execution Time: %s - %g\n", argv[1], time.reportTime());


	return 0;
}
