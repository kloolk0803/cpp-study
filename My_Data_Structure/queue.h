#pragma once

#include <iostream>

template<typename T>
class Queue
{
	virtual bool EnQueue(const T& data) = 0;
	virtual bool DeQueue(T& data) = 0;
	virtual bool Front(T& data) const = 0;
	virtual bool IsEmpty() const = 0;
	virtual int Length() const = 0;
};