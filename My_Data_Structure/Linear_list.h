#pragma once

#include <iostream>
#include <cstdlib>
#include <exception>

template<typename T>
class Linear_list
{
public:
	/*��ȡ����*/
	virtual int Length() const = 0;
	/*��ȡĳλ��Ԫ�ص�������*/
	virtual bool GetData(int pos, T& data) const = 0;
	/*����ĳλ��Ԫ�ص�������*/
	virtual bool SetData(int pos, const T& data) = 0;
	/*��������*/
	virtual bool Insert(int prev_pos, const T& data) = 0;
	/*ɾ������*/
	virtual bool Remove(int delete_pos, T& data) = 0;
	/*�ж��Ƿ�Ϊ��*/
	virtual bool IsEmpty() const = 0;
	/*��ӡ���Ա�*/
	virtual void Print() = 0;
	virtual ~Linear_list();
};

template<typename T>
inline Linear_list<T>::~Linear_list()
{
}
