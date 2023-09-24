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

    // 入队
    bool EnQueue(const T& data);

    // 出队(保存数据)
    bool DeQueue(T& data);

    // 出队(不保存数据)
    bool DeQueue();

    // 获取队头数据
    bool Front(T& data) const;

    // 获取队尾数据
    bool Rear(T& data) const;

    // 判断队列是否为空
    bool IsEmpty() const;

    // 判断队列是否满
    bool IsFull() const;

    // 获取队列长度
    int Length() const;

    // 清空队列
    void Clear();

    // 重载<<(打印队列)
    friend ostream& operator<< <>(ostream& os, const CircularQueue<T>& seq_queue);

private:
    T* mem_Data;               //!< **元素数组**
    int capacity_;                  //!< **容量**
    int front_;                     //!< **队头索引**
    int rear_;                      //!< **队尾索引**
};

template<typename T>
inline bool CircularQueue<T>::EnQueue(const T& data)
{
	if (IsFull()) return false;
	if (Length() == 0) this->front_ = 0;
	this->rear_ = (this->rear_ + 1 + this->capacity_) % this->capacity_;  /*rear_更新*/
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
		int actual_index = (circular_queue.front_ + i + circular_queue.capacity_) % circular_queue.capacity_;  /*获取当前结点的数组索引*/
		
		os << circular_queue.mem_Data[actual_index] << " ";
	}
	os << "\n___________________________________________\n";

	return os;
}
