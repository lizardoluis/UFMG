/*
 * WebClassifier.h
 *
 *  Created on: Oct 9, 2014
 *      Author: lizardo
 */

#ifndef WEBCLASSIFIER_H_
#define WEBCLASSIFIER_H_

#include <list>
#include <stack>
#include <vector>

#include <stdio.h>

#include "Graph.h"

#define DISCONNECTED_FILE "disconnected.txt" //disconnected nodes.
#define IN_FILE "in.txt" //IN nodes.
#define SCC_FILE "scc.txt" //nodes in the largest strongly connected component.
#define OUT_FILE "out.txt" //OUT nodes.
#define TENDRILS_A_FILE "tendrils_a.txt" //tendrils nodes of types (a).
#define TENDRILS_B_FILE "tendrils_b.txt" //tendrils nodes of types (b).
#define TENDRILS_C_FILE "tendrils_c.txt" //tendrils

using namespace std;

class WebClassifier {
public:
	enum Type {DISCONNECTED, SCC, IN, OUT, TENDRILS_A, TENDRILS_B, TENDRILS_C};

	WebClassifier(int webSize);

	vector<Type> nodesType;

	int classify_SCC(Graph &graph, Graph &graphT);

	void classify_Component(Graph &graph, list<int> &startComponent, list<int> &component, Type setType);

	void print_components();

};

#endif /* WEBCLASSIFIER_H_ */
