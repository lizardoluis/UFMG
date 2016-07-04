/*
 * response.h
 *
 *  Created on: Nov 15, 2014
 *      Author: lizardo
 */

#ifndef RESPONSE_H_
#define RESPONSE_H_

#define MIN0 3
#define MIN1 5

// Defines the response type of the algorithms
enum Response {UNDEFINED, TRUE, FALSE, BOTH};

// Prints the response on the stdout
void printResponse(Response r);


#endif /* RESPONSE_H_ */
