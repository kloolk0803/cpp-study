#pragma once

#include <iostream>

template<typename T> class DoubleEndedQueue;
template<typename T> std::ostream& operator<<(std::ostream& os, const DoubleEndedQueue<T>& circular_queue);

template<typename T>
class DoubleEndedQueue
{
public:
	DoubleEndedQueue(int capacity_ = 20) :capacity_(capacity_), front_(-1), rear_(-1)
	{
		mem_data_ = new T[capacity_];
		if (!mem_data_) throw std::bad_alloc();
	}
	~DoubleEndedQueue() { delete[] mem_data_; }

	/*��β���*/
	bool PushBack(const T& data);
	/*��ͷ���*/
	bool PushFront(const T& data);
	/*��ͷ���ӣ��������ݣ�*/
	bool PopFront(T& data);
	/*��ͷ���ӣ����������ݣ�*/
	bool PopFront();
	/*��β���ӣ��������ݣ�*/
	bool PopBack(T& data);
	/*��β���ӣ����������ݣ�*/
	bool PopBack();
	/*��ȡ��ͷ����*/
	bool Front(T& data) const;
	/*��ȡ��β����*/
	bool Rear(T& data) const;
	/*�ж��Ƿ�ն�*/
	bool IsEmpty() const;
	/*�ж��Ƿ�����*/
	bool IsFull() const;
	/*��ȡ����*/
	int Length() const;
	/*��ն���*/
	void Clear();

	/*����<<��ӡ����*/
	friend std::ostream& operator<< <>(std::ostream& os, const DoubleEndedQueue<T>& seq_queue);

private:
	T* mem_data_;  /*Ԫ������*/
	int capacity_;  /*����*/
	int front_;  /*��ͷ����*/
	int rear_;   /*��β����*/
};

template<typename T>
inline bool DoubleEndedQueue<T>::PushBack(const T& data)
{
	if (IsFull()) return false;
	if (Length() == 0) front_ = 0;
	rear_ = (rear_ + 1 + capacity_) % capacity_;
	mem_data_[rear_] = data;
	return true;
}

template<typename T>
inline bool DoubleEndedQueue<T>::PushFront(const T& data)
{
	if (IsFull()) return false;
	if (Length() == 0) rear_ = 0;
	front_ = (front_ - 1 + capacity_) % capacity_;
	mem_data_[front_] = data;
	return true;
}

template<typename T>
inline bool DoubleEndedQueue<T>::PopFront(T& data)
{
	if (IsFull()) return false;
	data = mem_data_[front_];
	if (Length() == 1) front_ = rear_ = -1;
	else front_ = (front_ + 1 + capacity_) % capacity_;
	return true;
}

template<typename T>
inline bool DoubleEndedQueue<T>::PopFront()
{
	if (IsFull()) return false;
	if (Length() == 1) front_ = rear_ = -1;
	else front_ = (front_ + 1 + capacity_) % capacity_;
	return true;
}

template<typename T>
inline bool DoubleEndedQueue<T>::PopBack(T& data)
{
	if (IsFull()) return false;
	data = mem_data_[rear_];
	if (Length() == 1) front_ = rear_ = -1;
	else rear_ = (rear_ - 1 + capacity_) % capacity_;
	return true;
}

template<typename T>
inline bool DoubleEndedQueue<T>::PopBack()
{
	if (IsFull()) return false;
	if (Length() == 1) front_ = rear_ = -1;
	else rear_ = (rear_ - 1 + capacity_) % capacity_;
	return true;
}

template<typename T>
inline bool DoubleEndedQueue<T>::Front(T& data) const
{
	if (IsFull()) return false;
	data = mem_data_[front_];
	return true;
}

template<typename T>
inline bool DoubleEndedQueue<T>::Rear(T& data) const
{
	if (IsFull()) return false;
	data = mem_data_[rear_];
	return true;
}

template<typename T>
inline bool DoubleEndedQueue<T>::IsEmpty() const
{
	return Length() == 0;
}

template<typename T>
inline bool DoubleEndedQueue<T>::IsFull() const
{
	return Length() == capacity_;
}

template<typename T>
inline int DoubleEndedQueue<T>::Length() const
{
	if (rear_ == -1 && front_ == -1)return 0;
	return (rear_ - front_ + 1 + capacity_) % capacity_;
}

template<typename T>
inline void DoubleEndedQueue<T>::Clear()
{
	front_ = rear_ = -1;
}

template<typename T> 
std::ostream& operator<<(std::ostream& os, const DoubleEndedQueue<T>& circular_queue)
{
	os << "The size of link queue: " << circular_queue.Length() << endl;
	os << "______________________________________________________________________________________\n";
	for (int i = 0; i < circular_queue.Length(); i++)
	{
		int actual_index = (circular_queue.front_ + i + circular_queue.capacity_) % circular_queue.capacity_;
		os << circular_queue.mem_data_[actual_index] << " ";
	}
	os << "\n______________________________________________________________________________________\n";
	return os;
}