#pragma once

#include <iostream>
#include <cstdlib>
#include <exception>

template<typename T>
class Linear_list
{
public:
	/*获取长度*/
	virtual int Length() const = 0;
	/*获取某位置元素的数据项*/
	virtual bool GetData(int pos, T& data) const = 0;
	/*设置某位置元素的数据项*/
	virtual bool SetData(int pos, const T& data) = 0;
	/*插入数据*/
	virtual bool Insert(int prev_pos, const T& data) = 0;
	/*删除数据*/
	virtual bool Remove(int delete_pos, T& data) = 0;
	/*判断是否为空*/
	virtual bool IsEmpty() const = 0;
	/*打印线性表*/
	virtual void Print() = 0;
	virtual ~Linear_list();
};

template<typename T>
inline Linear_list<T>::~Linear_list()
{
}
