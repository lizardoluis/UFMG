/*
 * WebClassifier.h
 *
 *  Created on: Oct 9, 2014
 *      Author: lizardo
 */

#ifndef WEBCLASSIFIER_H_
#define WEBCLASSIFIER_H_

#include <list>
#include <vector>

#include "Graph.h"

/*
 * Output files.
 */
#define DISCONNECTED_FILE "disconnected.txt" //disconnected nodes.
#define IN_FILE "in.txt" //IN nodes.
#define SCC_FILE "scc.txt" //nodes in the largest strongly connected component.
#define OUT_FILE "out.txt" //OUT nodes.
#define TENDRILS_A_FILE "tendrils_a.txt" //tendrils nodes of types (a).
#define TENDRILS_B_FILE "tendrils_b.txt" //tendrils nodes of types (b).
#define TENDRILS_C_FILE "tendrils_c.txt" //tendrils nodes of types (a) and (b).

using namespace std;

class WebClassifier {
public:

	/*
	 * Types of components.
	 */
	enum Type {DISCONNECTED, SCC, IN, OUT, TENDRILS_A, TENDRILS_B, TENDRILS_C};

	/*
	 * Constructor.
	 */
	WebClassifier(int webSize);

	/*
	 * Kosaraju's algorithm to find the largest strongly connected component.
	 *
	 * @returns one node of the SCC.
	 */
	int classify_scc(Graph &graph, Graph &graphT);

	/*
	 * DFS to classify the nodes of the graph accordingly to the type (setType) desired.
	 *
	 * @param graph: is the graph to be searched;
	 * @param startNodes: is the list of nodes to start the DFS out of it;
	 * @param nodesList: is the list of classified nodes to be returned by the function;
	 * @param setType: is the type to be set in the nodes.
	 */
	void classify_nodes(Graph &graph, list<int> &startNodes, list<int> &nodesList, Type setType);

	/*
	 * Export the components to the corresponding files.
	 */
	void export_components();

//	void export_dot(Graph &graph);

private:
	/*
	 * Vector of types to classify the nodes.
	 */
	vector<Type> nodesType;
};

#endif /* WEBCLASSIFIER_H_ */
