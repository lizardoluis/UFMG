/*
 * MaxPriorityQueue.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: lizardo
 */

#include "MaxPriorityQueue.h"

int MaxPriorityQueue::parent(int i) {
	return (i - 1) / 2;
}

int MaxPriorityQueue::left(int i) {
	return 2 * i + 1;
}

int MaxPriorityQueue::right(int i) {
	return 2 * i + 2;
}

MaxPriorityQueue::MaxPriorityQueue(vector<float> & v) {

	this->a.resize(v.size());
	this->index.resize(v.size());

	for (unsigned i = 0; i < v.size(); i++) {
		this->a[i] = make_pair(v[i], i);
		this->index[i] = i;
	}

	// build max heap
	for (int i = a.size() / 2 - 1; i >= 0; i--) {
		maxHeapify(i);
	}
}

void MaxPriorityQueue::maxHeapify(int i) {
	int l = left(i);
	int r = right(i);
	int largest = i;

	if (l < (int) a.size() && a[l].first > a[largest].first) {
		largest = l;
	}

	if (r < (int) a.size() && a[r].first > a[largest].first) {
		largest = r;
	}

	if (largest != i) {
		// exchange a[i] with a[largest]
		pair<float, int> tmp = a[i];

		index[i] = largest;
		index[largest] = i;

		a[i] = a[largest];
		a[largest] = tmp;

		maxHeapify(largest);
	}
}

pair<float, int> MaxPriorityQueue::extractMax() {
	if (a.size() < 1) {
		printf("Heap underflow\n");
		return make_pair(-1.0, -1);
	}

	pair<float, int> max = a[0];

	a[0] = a[a.size() - 1];
	index[a[0].second] = 0;

	a.pop_back();

	maxHeapify(0);

	return max;
}

bool MaxPriorityQueue::increaseKey(int i, float key) {

	int j = index[i];

	if (key <= a[j].first) {
//		printf("New key is smaller than current key\n");
		return false;
	}

	a[j].first = key;
	while (j > 0 && a[parent(j)].first < a[j].first) {

		// exchange a[i] with a[parent(i)];
		index[a[j].second] = parent(j);
		index[a[parent(j)].second] = j;

		pair<float, int> tmp = a[j];
		a[j] = a[parent(j)];
		a[parent(j)] = tmp;

		j = parent(j);
	}

	return true;
}

bool MaxPriorityQueue::empty() {
	return a.empty();
}
