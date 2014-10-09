//============================================================================
// Name        : paa-tp2.cpp
// Author      : Luis Lizardo
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <string>
#include "Graph.h"
#include "SCC.h"

#define DISCONNECTED_FILE "disconnected.txt" //disconnected nodes.
#define IN_FILE "in.txt" //IN nodes.
#define SCC_FILE "scc.txt" //nodes in the largest strongly connected component.
#define SCC_OUT "out.txt" //OUT nodes.
#define TENDRILS_A_FILE "tendrils_a.txt" //tendrils nodes of types (a).
#define TENDRILS_B_FILE "tendrils_b.txt" //tendrils nodes of types (b).
#define TENDRILS_C_FILE "tendrils_c.txt" //tendrils

using namespace std;

int main(int argc, char *argv[]) {

	string fileName = argv[1];
	FILE *fp = fopen(fileName.c_str(), "r");

	int u, v;

	Graph graph;
	Graph graphT;

	// Read the list of nodes in the file and add them to the graph
	while (fscanf(fp, "%d %d", &u, &v) == 2) {
		graph.insert(u, v);
		graphT.insert(v, u);
	}

	fclose(fp);

	SCC scc(graph, graphT);

	list<int> sccComponent = scc.kosaraju();

	for (int u : sccComponent) {
		printf("%d ", u + 1);
	}

	printf("\n\n\n");

//	scc.tarjan();

	return 0;
}
