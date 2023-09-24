#pragma once

#include <iostream>
#include <cstdlib>
#include <exception>

template<typename T>
class Stack
{
	/*��ջ*/
	virtual bool Push(const T& data) = 0;
	/*��ջ*/
	virtual bool Pop(T& data) = 0;
	/*��ȡջ������*/
	virtual bool Top(T& data) const = 0;
	/*�ж��Ƿ�Ϊ��*/
	virtual bool IsEmpty() const = 0;
	/*��ȡ����*/
	virtual int Length() const = 0;
};