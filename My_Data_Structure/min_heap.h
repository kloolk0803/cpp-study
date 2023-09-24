#pragma once

#include <iostream>

constexpr int DEFAULT_CAPACITY = 200;

template<typename T>
class MinHeap
{
public:
	explicit MinHeap(int capacity = DEFAULT_CAPACITY);
	MinHeap(T* elements, int length, int capacity);
	~MinHeap() { delete[] elements_; }

	//插入
	bool Insert(const T& element);
	//堆顶出堆
	bool Pop(T& element);
	//获取堆顶
	bool Top(T& element);
	//是否空堆
	bool IsEmpty() const { return size_ == 0; }
	//是否满堆
	bool IsFull() const { return size_ == capacity_; }
	//获取堆大小
	int Size() { return size_; }
	//清空堆
	void Clear() { size_ = 0; }

private:
	T* elements_;  //堆元素数组
	int size_;  //当前堆size
	int capacity_;  //容量
	void SiftDown_(int index);  
	void SiftUp_(int index);
	void Swap_(T& element1, T& element2);
};

template<typename T>
inline MinHeap<T>::MinHeap(int capacity)
{
	capacity_ = (capacity > DEFAULT_CAPACITY) ? capacity : DEFAULT_CAPACITY;
	size_ = 0;
	elements_ = new T[capacity_];
	if (elements_ == nullptr) throw std::bad_alloc();
}

template<typename T>
inline MinHeap<T>::MinHeap(T* elements, int length, int capacity)
{
	capacity_ = (capacity > DEFAULT_CAPACITY) ? capacity : DEFAULT_CAPACITY;                // 设置capacity_(容量)
	size_ = length;                                                                              // 设置size_(当前堆大小)为0

	elements_ = new T[capacity_];                                                    // elements_分配内存
	if (elements_ == NULL) {                                                                // if 内存分配失败
		throw bad_alloc();                                                                  // 抛出bad_alloc()错误
	}

	for (int i = 0; i < capacity; i++) {                                                    // for loop 遍历capacity
		elements_[i] = elements[i];                                                         // elements_[i]赋值
	}

	// ----------- 2 建堆 ----------

	for (int i = (size_ - 2) / 2; i >= 0; i--) {                                            // for loop 从索引(size_ - 2) / 2 到 0
		SiftDown_(i);                                                                       // 对i(当前索引)执行SiftDown_
	}
}

template<typename T>
inline bool MinHeap<T>::Insert(const T& element)
{
	if (size_ == capacity_) return false;
	/*数组末尾插入元素*/
	elements_[size_] = element;
	/*调整堆*/
	SiftUp_(size_);
	size_++;
	return true;
}

template<typename T>
inline bool MinHeap<T>::Pop(T& element)
{
	if (!size_) return false;
	/*保存堆顶*/
	element = elements_[0];
	/*替换堆顶*/
	elements_[0] = elements_[size_ - 1];
	size_--;
	/*调整堆*/
	SiftDown_(0);
	return true;
}

template<typename T>
inline bool MinHeap<T>::Top(T& element)
{
	if (!size_) return false;
	element = elements_[0];
	return true;
}

template<typename T>
inline void MinHeap<T>::SiftDown_(int index)
{
	for (int child_index = 2 * index + 1; child_index < size_; index = child_index, child_index = child_index * 2 + 1)  //遍历索引index的后代结点
	{
		if (child_index + 1 < size_ && elements_[child_index] > elements_[child_index + 1])  //如果当前左孩子结点索引 + 1 < 堆大小 && 左孩子结点元素 > 右孩子节点元素
			child_index++;
		if (elements_[index] <= elements_[child_index])break;  //如果当前结点索引元 <= 最小孩子元素，则跳出循环
		Swap_(elements_[index], elements_[child_index]);  //交换（当前结点，最小孩子节点）
	}
}

template<typename T>
inline void MinHeap<T>::SiftUp_(int index)
{
	for (int parent_index = (index - 1) / 2; parent_index >= 0; index = parent_index, parent_index = (index - 1) / 2)
	{
		if (elements_[parent_index] <= elements_[index])break;  //如果当前父节点元素 <= 当前结点元素
		Swap_(elements_[parent_index], elements_[index]);
	}
}

template<typename T>
inline void MinHeap<T>::Swap_(T& element1, T& element2)
{
	T tmp = element1;
	element1 = element2;
	element2 = tmp;
}
