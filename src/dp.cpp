/*
 * dp.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: lizardo
 */

#include <iostream>
using namespace std;

#include "response.h"

#include <vector>

Response topDown(string &msg, vector < vector<vector<Response> > > &table, unsigned i, int c0, int c1) {

	// stop conditions
	if (c0 == MIN0 || c1 == MIN1)
		return TRUE;

	if (i == msg.length())
		return FALSE;

	if (msg[i] == '0') {

		if(table[i+1][c0+1][0] == UNDEFINED)
			table[i+1][c0+1][0] = topDown(msg, table, i + 1, c0 + 1, 0);

		return table[i+1][c0+1][0];

	} else if (msg[i] == '1') {

		if(table[i+1][0][c1 + 1] == UNDEFINED)
			table[i+1][0][c1 + 1] = topDown(msg, table, i + 1, 0, c1 + 1);

		return table[i+1][0][c1 + 1];

	} else {

		if(table[i+1][c0+1][0] == UNDEFINED)
			table[i+1][c0+1][0] = topDown(msg, table, i + 1, c0 + 1, 0);

		if(table[i+1][0][c1+1] == UNDEFINED)
			table[i+1][0][c1+1] = topDown(msg, table, i + 1, 0, c1 + 1);

		Response r0 = table[i+1][c0+1][0];
		Response r1 = table[i+1][0][c1+1];

		if (r0 != r1)
			return BOTH;
		else
			return r0;
	}

	return FALSE;
}

Response topDown(string &msg){

	vector < vector<vector<Response> > > table(msg.length()+1, vector < vector<Response> > (MIN0+1, vector<Response>(MIN1+1, UNDEFINED)));

	return topDown(msg, table, 0, 0, 0);
}



Response bottomUp(string &msg){

	vector < vector<vector<Response> > > table(msg.length()+1, vector < vector<Response> > (MIN0+1, vector<Response>(MIN1+1, UNDEFINED)));
	int msgSize = msg.length();

	for (int c0 = 0; c0 <= MIN0; c0++) {
		for (int c1 = 0; c1 <= MIN1; c1++) {
			if (c0 == MIN0 || c1 == MIN1)
				table[msgSize][c0][c1] = TRUE;
			else
				table[msgSize][c0][c1] = FALSE;
		}
	}

	for (int i = msg.length() - 1; i >= 0; i--) {

		for (int c0 = 0; c0 <= MIN0; c0++) {
			for (int c1 = 0; c1 <= MIN1; c1++) {

				if (c0 == MIN0 || c1 == MIN1) {
					table[i][c0][c1] = TRUE;
				} else if (msg[i] == '0') {
					table[i][c0][c1] = table[i + 1][c0 + 1][0];
				} else if (msg[i] == '1') {
					table[i][c0][c1] = table[i + 1][0][c1 + 1];
				} else {
					Response r0 = table[i + 1][c0 + 1][0];
					Response r1 = table[i + 1][0][c1 + 1];

					if (r0 != r1)
						table[i][c0][c1] = BOTH;
					else
						table[i][c0][c1] = r0;
				}
			}
		}

	}

	return table[0][0][0];
}

int main() {

	int numInstances;

	cin >> numInstances;

	for (int i = 0; i < numInstances; i++) {
		string msg;
		cin >> msg;

//		Response resp = topDown(msg);
		Response resp = bottomUp(msg);
		printResponse(resp);
	}

	return 0;
}
