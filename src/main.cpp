//============================================================================
// Name        : paa-tp2.cpp
// Author      : Luis Lizardo
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <stack>
#include "Graph.h"
#include "WebClassifier.h"
#include "TimeProfiler.h"

#define BUFFSZ 200

using namespace std;

void read_input(string &fileName, Graph &graph, Graph &graphT) {
	FILE *fp = fopen(fileName.c_str(), "r");
	if (fp == NULL) {
		printf("Error when opening the file.");
		exit(0);
	}

	int u, v;

	// Read the list of nodes in the file and add them to the graph
	char buff[BUFFSZ];
	while (fgets(buff, BUFFSZ, fp)) {
		if (buff[0] != '#') {
			sscanf(buff, "%d %d", &u, &v);
			graph.insert(u, v);
			graphT.insert(v, u);
		}
	}

	fclose(fp);
}

int main(int argc, char *argv[]) {

	TimeProfiler time;
	time.start();

	string fileName = argv[1];
	Graph graph, graphT;
	int scc;
	list<int> sccList, out, in, tendrilsA, tendrilsB;

	read_input(fileName, graph, graphT);

	WebClassifier web(graph.getSize());

	scc = web.classify_SCC(graph, graphT);
	sccList.push_back(scc);

	web.classify_Component(graph, sccList, out, WebClassifier::OUT);
	web.classify_Component(graphT, sccList, in, WebClassifier::IN);
	web.classify_Component(graph, in, tendrilsA, WebClassifier::TENDRILS_A);
	web.classify_Component(graphT, tendrilsA, tendrilsA,
			WebClassifier::TENDRILS_A);
	web.classify_Component(graphT, out, tendrilsB, WebClassifier::TENDRILS_B);
	web.classify_Component(graphT, tendrilsB, tendrilsB,
			WebClassifier::TENDRILS_B);

	web.print_components();

	printf("Execution Time: %g\n", time.reportTime());

	return 0;
}
