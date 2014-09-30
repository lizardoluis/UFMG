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

	int heapSize;

	vector<pair<int, double> > weights;

	vector<int> index;

	int parent(int i);

	int left(int i);

	int right(int i);

	void maxHeapify(int i);

	void swap(int a, int b);

public:
	MaxPriorityQueue(vector<double> & v);

	pair<int, double> extractMax();

	bool increaseKey(int v, double key);

	bool empty();
};

#endif /* MAXPRIORITYQUEUE_H_ */
