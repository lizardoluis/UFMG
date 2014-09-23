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
#include "MaxPriorityQueue.h"

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

		if(graph.isConex()){
			printf("%.3f\n", graph.maximalSpanning(111.33333));
		}
		else {
			cout << "-1000\n";
		}

		break;
	}

//	vector<float> v = { 0.0, -2.5, -0.5, -4.5, -1.5 };
//
//	MaxPriorityQueue maxPQ(v);
//
//	cout << endl << endl;
//
//	pair<float, int> pair;
//
//	pair = maxPQ.extractMax();
//	cout << pair.first << " - " << pair.second << endl;
//
////	maxPQ.increaseKey(0, 3.8);
//
//	pair = maxPQ.extractMax();
//	cout << pair.first << " - " << pair.second << endl;
//
//	pair = maxPQ.extractMax();
//	cout << pair.first << " - " << pair.second << endl;
//
//	pair = maxPQ.extractMax();
//	cout << pair.first << " - " << pair.second << endl;
//
//	pair = maxPQ.extractMax();
//	cout << pair.first << " - " << pair.second << endl;

	return 0;
}

/*
 4.5 - 3
 3.5 - 0
 2.5 - 1
 1.5 - 4
 0.5 - 2
 * */
