/*
 * bf.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: lizardo
 */

#include <stdio.h>
#include <string>
#include "response.h"

using namespace std;

Response bruteForce(string &msg, unsigned i, int c0, int c1) {

	int msgSize = msg.length();

	while (true) {

		// stop conditions
		if (c0 == MIN0 || c1 == MIN1)
			return TRUE;
		if (i == msgSize)
			break;

		if (msg[i] == '0') {
			//bruteForce(msg, i + 1, c0 + 1, 0);
			c0++;
			i++;
			c1 = 0;
		} else if (msg[i] == '1') {
			//bruteForce(msg, i + 1, 0, c1 + 1);
			c1++;
			i++;
			c0 = 0;
		} else {

			// Recurse
			Response r0 = bruteForce(msg, i + 1, c0 + 1, 0);
			Response r1 = bruteForce(msg, i + 1, 0, c1 + 1);

			if (r0 != r1)
				return BOTH;
			else
				return r0;
		}
	}

	return FALSE;
}

Response bruteForce(string msg){
	return bruteForce(msg, 0, 0, 0);
}

int main() {

	int numInstances;
	int s = scanf("%d", &numInstances);

	char msg[101];
	for (int i = 0; i < numInstances; i++) {
		int s = scanf("%s", msg);

		Response resp = bruteForce(msg);
		printResponse(resp);
	}

	return 0;
}
