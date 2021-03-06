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
#include <math.h>

#include "Graph.h"
#include "MaxPriorityQueue.h"

#define COMPARE_FLOATS(x,y) (fabs((x) - (y)) < 0.0001)

using namespace std;

int main() {

	int numUsers;
	string line;

	while (scanf("%d\n", &numUsers) > 0) {

		Graph graph(numUsers);

		int u, v, f, d, fSum = 0, eCount = 0;

		while (getline(cin, line) && line.size() > 0) {
			sscanf(line.c_str(), "%d %d %d %d", &u, &v, &f, &d);
			graph.insert(u, v, f, d);
			fSum += f;
			eCount++;
		}

		if (graph.isConex()) {

			double upperBound = (double) fSum / (double) eCount;
			double lowerBound = 0;
			double ratio = (lowerBound + upperBound) / 2;

			double maxSpanning = graph.maximalSpanning(ratio);

			while (COMPARE_FLOATS(maxSpanning, 0.000) == false) {

				if (maxSpanning > 0) {
					lowerBound = ratio;
				} else if (maxSpanning < 0) {
					upperBound = ratio;
				}

				ratio = (lowerBound + upperBound) / 2;
				maxSpanning = graph.maximalSpanning(ratio);
			}

			printf("%.3f\n", ratio);
		} else {
			printf("-1000\n");
		}
	}

	return 0;
}
