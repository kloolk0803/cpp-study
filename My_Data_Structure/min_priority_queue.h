#pragma once

#include "min_heap.h"

template<typename T>
class MinPriorityQueue
{
public:
	MinPriorityQueue() :min_heap_() {};
	MinPriorityQueue(T elements[], int size) :min_heap_(elements, size) {};
	bool Enqueue(const T& element) { return min_heap_.Insert(element); }
	bool Dequeue(T& item) { return min_heap_.Pop(item); }
	bool Front(T& item) { return min_heap_.Top(item); }
	int Size() { return min_heap_.Size(); }
	void Clear() { min_heap_.Clear(); }

private:
	MinHeap<T> min_heap_;  //Ð¡¶¥¶Ñ
};
