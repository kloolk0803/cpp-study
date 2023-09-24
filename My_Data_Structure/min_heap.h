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

	//����
	bool Insert(const T& element);
	//�Ѷ�����
	bool Pop(T& element);
	//��ȡ�Ѷ�
	bool Top(T& element);
	//�Ƿ�ն�
	bool IsEmpty() const { return size_ == 0; }
	//�Ƿ�����
	bool IsFull() const { return size_ == capacity_; }
	//��ȡ�Ѵ�С
	int Size() { return size_; }
	//��ն�
	void Clear() { size_ = 0; }

private:
	T* elements_;  //��Ԫ������
	int size_;  //��ǰ��size
	int capacity_;  //����
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
	capacity_ = (capacity > DEFAULT_CAPACITY) ? capacity : DEFAULT_CAPACITY;                // ����capacity_(����)
	size_ = length;                                                                              // ����size_(��ǰ�Ѵ�С)Ϊ0

	elements_ = new T[capacity_];                                                    // elements_�����ڴ�
	if (elements_ == NULL) {                                                                // if �ڴ����ʧ��
		throw bad_alloc();                                                                  // �׳�bad_alloc()����
	}

	for (int i = 0; i < capacity; i++) {                                                    // for loop ����capacity
		elements_[i] = elements[i];                                                         // elements_[i]��ֵ
	}

	// ----------- 2 ���� ----------

	for (int i = (size_ - 2) / 2; i >= 0; i--) {                                            // for loop ������(size_ - 2) / 2 �� 0
		SiftDown_(i);                                                                       // ��i(��ǰ����)ִ��SiftDown_
	}
}

template<typename T>
inline bool MinHeap<T>::Insert(const T& element)
{
	if (size_ == capacity_) return false;
	/*����ĩβ����Ԫ��*/
	elements_[size_] = element;
	/*������*/
	SiftUp_(size_);
	size_++;
	return true;
}

template<typename T>
inline bool MinHeap<T>::Pop(T& element)
{
	if (!size_) return false;
	/*����Ѷ�*/
	element = elements_[0];
	/*�滻�Ѷ�*/
	elements_[0] = elements_[size_ - 1];
	size_--;
	/*������*/
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
	for (int child_index = 2 * index + 1; child_index < size_; index = child_index, child_index = child_index * 2 + 1)  //��������index�ĺ�����
	{
		if (child_index + 1 < size_ && elements_[child_index] > elements_[child_index + 1])  //�����ǰ���ӽ������ + 1 < �Ѵ�С && ���ӽ��Ԫ�� > �Һ��ӽڵ�Ԫ��
			child_index++;
		if (elements_[index] <= elements_[child_index])break;  //�����ǰ�������Ԫ <= ��С����Ԫ�أ�������ѭ��
		Swap_(elements_[index], elements_[child_index]);  //��������ǰ��㣬��С���ӽڵ㣩
	}
}

template<typename T>
inline void MinHeap<T>::SiftUp_(int index)
{
	for (int parent_index = (index - 1) / 2; parent_index >= 0; index = parent_index, parent_index = (index - 1) / 2)
	{
		if (elements_[parent_index] <= elements_[index])break;  //�����ǰ���ڵ�Ԫ�� <= ��ǰ���Ԫ��
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
