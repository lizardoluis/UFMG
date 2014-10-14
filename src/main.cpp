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

	int u, v;

	// Read the list of nodes in the file and add them to the graph
	char buff[BUFFSZ];
	while (fgets(buff, BUFFSZ, fp)) {
		if (buff[0] != '#') {
			sscanf(buff, "%d %d", &u, &v);

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

	double tInput, tSCC, tIN, tOUT, tTendrils, tOutput;
	printf("%s\n", argv[1]);

	TimeProfiler time, time2;
	time.start();

	// Read input file
	Graph graph, graphT, undirectedGraph;

	time2.start();
	read_input(argv[1], graph, graphT, undirectedGraph);
	tInput = time2.reportTime();

	WebClassifier web(graph.getSize());

	// List of components
	int scc;
	list<int> sccList, out, in, tendrilsA, tendrilsB;

	// Classify SCC nodes and returns one node of the component
	time2.start();
	scc = web.classify_scc(graph, graphT);
	tSCC = time2.reportTime();

	sccList.push_back(scc);

	// Classify OUT nodes
	time2.start();
	web.classify_nodes(graph, sccList, out, WebClassifier::OUT);
	tOUT = time2.reportTime();

	// Classify IN nodes
	time2.start();
	web.classify_nodes(graphT, sccList, in, WebClassifier::IN);
	tIN = time2.reportTime();

	// Classify Tendrils_A
	time2.start();
	web.classify_nodes(undirectedGraph, in, tendrilsA, WebClassifier::TENDRILS_A);

	// Classify Tendrils_B and Tendrils_C
	web.classify_nodes(undirectedGraph, out, tendrilsB, WebClassifier::TENDRILS_B);
	tTendrils = time2.reportTime();

	// Export the components at the file
	time2.start();
	web.export_components(graph);
	tOutput = time2.reportTime();

//	printf("Execution Time: %g\n", time.reportTime());
	printf("Execution Time: %.6g - %.6g %.6g %.6g %.6g %.6g %.6g\n\n", time.reportTime(), tInput, tSCC, tIN, tOUT, tTendrils, tOutput);


	return 0;
}
