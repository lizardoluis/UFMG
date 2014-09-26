/*
 * MaxPriorityQueue.h
 *
 *  Created on: Sep 21, 2014
 *      Author: lizardo
 */

#ifndef MAXPRIORITYQUEUE_H_
#define MAXPRIORITYQUEUE_H_

#include <stdio.h>
#include <vector>

using namespace std;

class MaxPriorityQueue {
private:

	vector<pair<float, int> > a;

	vector<int> index;

	int parent(int i);

	int left(int i);

	int right(int i);

	void maxHeapify(int i);

public:
	MaxPriorityQueue(vector<float> & v);

	pair<float, int> extractMax();

	bool increaseKey(int i, float key);

	bool empty();
};

#endif /* MAXPRIORITYQUEUE_H_ */
