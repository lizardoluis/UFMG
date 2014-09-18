//============================================================================
// Name        : paa-tp1.cpp
// Author      : Luis Lizardo
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <string>

#include "Graph.h"

using namespace std;

int main() {

	int numUsers, u, v, f, d;
	string line;

	while (scanf("%d\n", &numUsers) > 0) {

		Graph graph(numUsers);

		while (getline(cin, line) && line.size() > 0) {
			sscanf(line.c_str(), "%d %d %d %d", &u, &v, &f, &d);
			graph.insert(u, v, f, d);
		}

		cout << graph.isConex() << endl;
	}

	return 0;
}
