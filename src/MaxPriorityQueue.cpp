/*
 * MaxPriorityQueue.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: lizardo
 */

#include "MaxPriorityQueue.h"

#include <iostream>

MaxPriorityQueue::MaxPriorityQueue(vector<float> a) {

	this->a.resize(a.size());
	this->index.resize(a.size());
	for (int i = 0; i < (int) a.size(); i++) {
		this->a[i] = make_pair(a[i], i);
		this->index[i] = i;
	}

	// build max heap
	for (int i = a.size() / 2; i >= 0; i--) {
		maxHeapify(i);
	}
}

void MaxPriorityQueue::maxHeapify(int i) {
	int l = 2 * i;
	int r = 2 * i + 1;
	int largest;

	if (l <= (int) a.size() && a[l].first > a[i].first) {
		largest = l;
	} else {
		largest = i;
	}

	if (r <= (int) a.size() && a[r].first > a[largest].first) {
		largest = r;
	}

	if (largest != i) {
		// exchange a[i] with a[largest]
		pair<float, int> tmp = a[i];
		a[i] = a[largest];
		a[largest] = tmp;

		index[i] = largest;
		index[largest] = i;

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
	a.pop_back();

	index[0] = index[a.size() - 1];
	index.pop_back();

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
	while (j > 0 && a[j / 2].first < a[j].first) {

		// exchange a[i] with a[parent(i)];
		pair<float, int> tmp = a[j];
		a[j] = a[j / 2];
		a[j / 2] = tmp;

		j = j / 2;
	}

	return true;
}

bool MaxPriorityQueue::empty() {
	return a.empty();
}
