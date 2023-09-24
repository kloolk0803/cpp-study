#pragma once

#include "queue.h"

template<typename T>class CircularQueue;
template<typename T>
std::ostream& operator<<(std::ostream& os, const CircularQueue<T>& circular_queue);

template<typename T>
class CircularQueue : public Queue<T>
{
public:
    CircularQueue(int capacity = 20) : capacity_(capacity), front_(-1), rear_(-1) {
        this->mem_Data = new T[this->capacity_];
        if (!this->mem_Data) {
            throw bad_alloc();
        }
    }
    ~CircularQueue() { delete[] this->mem_Data; }

    // ���
    bool EnQueue(const T& data);

    // ����(��������)
    bool DeQueue(T& data);

    // ����(����������)
    bool DeQueue();

    // ��ȡ��ͷ����
    bool Front(T& data) const;

    // ��ȡ��β����
    bool Rear(T& data) const;

    // �ж϶����Ƿ�Ϊ��
    bool IsEmpty() const;

    // �ж϶����Ƿ���
    bool IsFull() const;

    // ��ȡ���г���
    int Length() const;

    // ��ն���
    void Clear();

    // ����<<(��ӡ����)
    friend ostream& operator<< <>(ostream& os, const CircularQueue<T>& seq_queue);

private:
    T* mem_Data;               //!< **Ԫ������**
    int capacity_;                  //!< **����**
    int front_;                     //!< **��ͷ����**
    int rear_;                      //!< **��β����**
};

template<typename T>
inline bool CircularQueue<T>::EnQueue(const T& data)
{
	if (IsFull()) return false;
	if (Length() == 0) this->front_ = 0;
	this->rear_ = (this->rear_ + 1 + this->capacity_) % this->capacity_;  /*rear_����*/
	this->mem_Data[this->rear_] = data;
	return true;
}

template<typename T>
inline bool CircularQueue<T>::DeQueue(T& data)
{
	if (IsEmpty()) return false;
	data = this->mem_Data[this->front_];
	if (Length() == 1)
	{
		this->front_ = -1;
		this->rear_ = -1;
	}
	else front_ = (front_ + 1 + capacity_) % capacity_;
	return true;
}

template<typename T>
inline bool CircularQueue<T>::DeQueue()
{
	if (IsEmpty()) return false;
	if (Length() == 1)
	{
		this->front_ = -1;
		this->rear_ = -1;
	}
	else front_ = (front_ + 1 + capacity_) % capacity_;
	return true;
}

template<typename T>
inline bool CircularQueue<T>::Front(T& data) const
{
	if (IsEmpty()) return false;
	data = this->mem_Data[front_];
	return true;
}

template<typename T>
inline bool CircularQueue<T>::Rear(T& data) const
{
	if (IsEmpty()) return false;
	data = this->mem_Data[rear_];
	return true;
}

template<typename T>
inline bool CircularQueue<T>::IsEmpty() const
{
	return this->Length() == 0;
}

template<typename T>
inline bool CircularQueue<T>::IsFull() const
{
	return this->Length() == capacity_;
}

template<typename T>
inline int CircularQueue<T>::Length() const
{
	if (this->rear_ == -1 && this->front_ == -1) return 0;
	return (rear_ - front_ + 1 + capacity_) % capacity_;
}

template<typename T>
inline void CircularQueue<T>::Clear()
{
	this->rear_ = -1;
	this->front_ = -1;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const CircularQueue<T>& circular_queue)
{
	os << "The size of link queue:" << circular_queue.Length() << '\n';
	os << "___________________________________________\n";
	for (int i = 0; i < circular_queue.Length(); i++)
	{
		int actual_index = (circular_queue.front_ + i + circular_queue.capacity_) % circular_queue.capacity_;  /*��ȡ��ǰ������������*/
		
		os << circular_queue.mem_Data[actual_index] << " ";
	}
	os << "\n___________________________________________\n";

	return os;
}
