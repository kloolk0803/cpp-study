#pragma once

#include "stack.h"

template<typename T>class SeqStack;

template<typename T>
class SeqStack :public Stack<T>
{
public:
	SeqStack(int capacity = 20) :capacity_(capacity), top_(-1)
	{
		this->mem_Data = new T[this->capacity_];
		if (!this->mem_Data) throw std::bad_alloc();
	}

	~SeqStack();
	/*��ջ*/
	bool Push(const T& data);
	/*��ջ(��������)*/
	bool Pop(T& data);
	/*��ջ(����������)*/
	bool Pop();
	/*��ȡջ������*/
	bool Top(T& data) const;
	/*�ж�ջ�Ƿ�Ϊ��*/
	bool IsEmpty() const;
	/*�ж�ջ�Ƿ���*/
	bool IsFull() const;
	/*��ȡջ��С*/
	int Length() const;
	/*���*/
	void clear();

	/*����<<*/
	friend std::ostream& operator<< <>(std::ostream& os, const SeqStack<T>& seq_stack);

private:
	T* mem_Data;  /*Ԫ������*/
	int capacity_;  /*����*/
	int top_;  /*ջ������*/
};

template<typename T>
inline SeqStack<T>::~SeqStack()
{
	delete[] this->mem_Data;
}

template<typename T>
inline bool SeqStack<T>::Push(const T& data)
{
	if (this->IsFull()) return false;
	this->top_++;
	this->mem_Data[this->top_] = data;
	return true;
}

template<typename T>
inline bool SeqStack<T>::Pop(T& data)
{
	if (this->Length() == 0) return false;
	data = this->mem_Data[this->top_];
	this->top_--;
	return true;
}

template<typename T>
inline bool SeqStack<T>::Pop()
{
	if (this->Length() == 0) return false;
	this->top_--;
	return true;
}

template<typename T>
inline bool SeqStack<T>::Top(T& data) const
{
	if (this->Length() == 0) return false;
	data = this->mem_Data[this->top_];
	return true;
}

template<typename T>
inline bool SeqStack<T>::IsEmpty() const
{
	return this->top_ == -1;
}

template<typename T>
inline bool SeqStack<T>::IsFull() const
{
	return this->top_ == this->capacity_ - 1;
}

template<typename T>
inline int SeqStack<T>::Length() const
{
	return this->top_ + 1;
}

template<typename T>
inline void SeqStack<T>::clear()
{
	int length = this->Length();
	if (length == 0) return;

	for (int i = 0; i < length; i++) this->Pop();
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const SeqStack<T>& seq_stack)
{
	os << "ջ��Ԫ�ظ�����" << seq_stack.Length() << '\n';
	for (int i = seq_stack.top_; i >= 0; i--)
		os << seq_stack.mem_Data[i] << '\n';
	return os;
}