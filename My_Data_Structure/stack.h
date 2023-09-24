#pragma once

#include <iostream>
#include <cstdlib>
#include <exception>

template<typename T>
class Stack
{
	/*入栈*/
	virtual bool Push(const T& data) = 0;
	/*出栈*/
	virtual bool Pop(T& data) = 0;
	/*获取栈顶数据*/
	virtual bool Top(T& data) const = 0;
	/*判断是否为空*/
	virtual bool IsEmpty() const = 0;
	/*获取长度*/
	virtual int Length() const = 0;
};