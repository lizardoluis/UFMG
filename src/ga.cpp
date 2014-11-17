/*
 * ga.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: lizardo
 */

#include <iostream>
using namespace std;

#include "response.h"

Response greedy(string msg) {

	int count = 0;
	char last = '0';
	bool both = false;
	Response resp = FALSE;

	for (unsigned i = 0; i < msg.length(); i++) {

		if (msg[i] == last) {
			count++;
		} else if (msg[i] != '-') {
			count = 1;
			last = msg[i];
			both = false;
		} else {

			if (i < msg.length() - 1 && msg[i + 1] != '-' && msg[i + 1] != last
					&& ((last == '0' && count < MIN0-1) || (last == '1' && count < MIN1-1))) {
				count = 1;
				last = msg[i + 1];
			} else {
				count++;
			}

			both = true;
		}

		if (((last == '0' && count == MIN0) || (last == '1' && count == MIN1))) {
			if(both == false)
				return TRUE;
			else
				resp = BOTH;
		}
	}

	return resp;
}

int main() {

	int numInstances;
	int s = scanf("%d", &numInstances);

	char msg[101];
	for (int i = 0; i < numInstances; i++) {
		int s = scanf("%s", msg);

		Response resp = greedy(msg);
		printResponse(resp);
	}

	return 0;
}
