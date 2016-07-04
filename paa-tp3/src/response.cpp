/*
 * response.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: lizardo
 */

#include "response.h"

#include <stdio.h>

using namespace std;

void printResponse(Response r) {
	switch (r) {
	case TRUE:
		//cout << "true\n";
		printf("true\n");
		break;
	case FALSE:
//		cout << "false\n";
		printf("false\n");
		break;
	case BOTH:
//		cout << "both\n";
		printf("both\n");
		break;
	}
}
