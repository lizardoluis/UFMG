/*
 * MaxPriorityQueue.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: lizardo
 */

#include "MaxPriorityQueue.h"
#include <iostream>

int MaxPriorityQueue::parent(int i) {
	return (i - 1) / 2;
}

int MaxPriorityQueue::left(int i) {
	return 2 * i + 1;
}

int MaxPriorityQueue::right(int i) {
	return 2 * i + 2;
}

void MaxPriorityQueue::swap(int i, int j) {
	index[weights[i].first] = j;
	index[weights[j].first] = i;

	pair<int, double> tmp = weights[i];
	weights[i] = weights[j];
	weights[j] = tmp;
}

MaxPriorityQueue::MaxPriorityQueue(vector<double> & v) {
	index.resize(v.size());
	weights.resize(v.size());

	for (unsigned i = 0; i < v.size(); i++) {
		index[i] = i;
		weights[i] = make_pair(i, v[i]);
	}

	// build max heap
	for (int i = weights.size() / 2 - 1; i >= 0; i--) {
		maxHeapify(i);
	}
}

void MaxPriorityQueue::maxHeapify(int i) {
	int l = left(i);
	int r = right(i);
	int largest = i;

	if (l < (int) weights.size() && weights[l].second > weights[largest].second) {
		largest = l;
	}

	if (r < (int) weights.size() && weights[r].second > weights[largest].second) {
		largest = r;
	}

	if (largest != i) {
		swap(i, largest);
		maxHeapify(largest);
	}
}

pair<int, double> MaxPriorityQueue::extractMax() {
	if (weights.size() < 1) {
		printf("Heap underflow\n");
		return make_pair(-1.0, -1);
	}

	pair<int, double> max = weights[0];

	swap(0, weights.size() - 1);

	weights.pop_back();

	maxHeapify(0);

	return max;
}

bool MaxPriorityQueue::increaseKey(int v, double key) {

	if (key <= weights[index[v]].second) {
//		printf("New key is smaller than current key\n");
		return false;
	}

	if( index[v] == -1 ){
		printf("V (%d) is not in the queue\n", v);
		return false;
	}

	weights[index[v]].second = key;

	int i = index[v];

	while (i > 0 && weights[parent(i)].second < weights[i].second) {
		swap(i, parent(i));
		i = parent(i);
	}

	return true;
}

bool MaxPriorityQueue::empty() {
	return weights.empty();
}
