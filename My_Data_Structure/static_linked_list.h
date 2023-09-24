#pragma once

#include <iostream>

template<typename T>
struct StaticLinkedListNode
{
	StaticLinkedListNode<T>() :next(0) {};
	explicit StaticLinkedListNode<T>(T data) :data(data), next(-1) {};
	StaticLinkedListNode<T>(T data, int next) :data(data), next(next) {};

	T data;  /*������*/
	int next;  /*��һ��������*/
};

template<typename T>
class StaticLinkedList
{
public:
	explicit StaticLinkedList(int capacity = 100);
	int Length() const { return length_; }
	int Capacity() const { return capacity_; }
	bool IsEmpty() const { return length_ == 0; }
	bool Search(const T& data, int& pos) const;
	bool Insert(int pos, const T& data);
	bool Remove(int pos, T& data);
	void Print() const;
	StaticLinkedListNode<T>& operator [](size_t index);

	static constexpr int NONE = -1  /*��ʾ������Ԫ�ز��ھ�̬������ʹ��*/;
	static constexpr int HEAD = 0;  /*ͷ������������*/

private:
	/*��ȡ����λ�õ���������*/
	bool GetDataInsertIndex_(int& index) const;

	/*����*/
	bool Extend_(int increased_capacity);

	/*����pos��ȡ������������*/
	bool GetDataIndexByPos_(int pos, int& index) const;

	StaticLinkedListNode<T>* mem_Data;  /*��̬��������*/
	int length_;  /*��̬������*/
	int capacity_;  /*��̬��������*/
};

template<typename T>
inline StaticLinkedList<T>::StaticLinkedList(int capacity)
{
	capacity_ = capacity;
	length_ = 0;
	mem_Data = new StaticLinkedListNode<T>[capacity_ + 1];
	if (!mem_Data) throw std::bad_alloc();

	mem_Data[HEAD].next = HEAD;  //HEAD����nextָ��HEAD(0, ����)

	for (int i = 1; i <= capacity; i++)
		mem_Data[i].next = StaticLinkedList<T>::NONE;   //��ǰ����Ԫ�ص�nextֵΪNONE(-1, ��ʾ������Ԫ�ز��ھ�̬������ʹ��)
}

template<typename T>
inline bool StaticLinkedList<T>::Search(const T& data, int& pos) const
{
	if (length_ == 0) return false;

	for (int cur_pos = 1, i = mem_Data[HEAD].next; i != HEAD; i = mem_Data[i].next, cur_pos++)
	{
		if (mem_Data[i].data == data)
		{
			pos = cur_pos;
			return true;
		}
	}
	return false;
}

template<typename T>
inline bool StaticLinkedList<T>::Insert(int pos, const T& data)
{
	if (pos < 0 || pos > length_) {                                 // if pos < 0 || pos����������
		return false;                                               // ����false
	}

	// ---------- 2 ���ݴ��� ----------

	if (length_ == capacity_) {                                     // if �����ȵ�������
		this->Extend_(capacity_);                                   // ����1��
	}

	// ---------- 3 ��ȡ����λ��ǰһλ�õ��������� ----------
	int prev_index;
	bool res = GetDataIndexByPos_(pos, prev_index);                     // ��pos����GetDataIndexByPos_, ��ȡprev_index(����λ��ǰһλ�õ���������)
	if (!res) {                                                     // if ��ȡʧ��
		return false;                                               // ����false
	}

	// ---------- 4 ��ȡ����λ�õ��������� ----------

	int insertion_index;
	res = GetDataInsertIndex_(insertion_index);                      // ����GetDataInsertionIndex_, ��ȡinsertion_index(ִ�в��������)
	if (!res) {                                                     // if ��ȡʧ��
		return false;                                               // ����false
	}

	// ---------- 5 ִ�в��� ----------

	mem_Data[insertion_index].next = mem_Data[prev_index].next;   // ����λ������Ԫ�ص�next, ָ��posλ������Ԫ�ص�next
	mem_Data[prev_index].next = insertion_index;                   // posλ������Ԫ�ص�next, ָ�����λ��
	mem_Data[insertion_index].data = data;                         // ����λ�õ�data, ���ڲ���data

	length_++;
	return true;
}

template<typename T>
inline bool StaticLinkedList<T>::Remove(int pos, T& data)
{
	if (length_ == 0) return false;

	if ((pos < 1) || (pos > length_)) return false;

	/*�ҵ�ɾ�����ǰһ���*/
	int prev_index = HEAD;
	for (int i = 1; i < pos; i++) prev_index = mem_Data[prev_index].next;

	/*ɾ��*/
	int delete_index = mem_Data[prev_index].next;
	mem_Data[prev_index].next = mem_Data[delete_index].next;
	mem_Data[delete_index].next = NONE;
	data = mem_Data[delete_index].data;

	length_--;
	return true;
}

template<typename T>
inline void StaticLinkedList<T>::Print() const
{
	if (length_ == 0)std::cout << "Empty list\n";

	for (int cur = mem_Data[HEAD].next; cur != HEAD; cur = mem_Data[cur].next) {  // for loop ���������е�ÿ�����
		cout << mem_Data[cur].data;                                                // ��ӡ��ǰ����data
		if (mem_Data[cur].next != HEAD) {                                          // if �������һ�����
			cout << "-->";                                                          // ��ӡ"-->"(��ʾnextָ��)
		}
	}
	std::cout << '\n';
	std::cout << "--------------------------------------------------------------------------\n";
}

template<typename T>
inline StaticLinkedListNode<T>& StaticLinkedList<T>::operator[](size_t index)
{
	if ((int)index > length_) throw std::out_of_range("wrong index");
	return this->mem_Data[index];
}

template<typename T>
inline bool StaticLinkedList<T>::GetDataInsertIndex_(int& index) const
{
	if (length_ == capacity_) return false;

	for (int i = 1; i <= length_ + 1; i++)
	{
		if (mem_Data[i].next == StaticLinkedList<T>::NONE)
		{
			index = i;
			return true;
		}
	}
}

template<typename T>
inline bool StaticLinkedList<T>::Extend_(int increased_capacity) 
{
	/*������ֵ����*/
	int old_capacity = capacity_;
	capacity_ += increased_capacity;
	/*�������ڴ�*/
	StaticLinkedListNode<T>* new_mem_Data = new StaticLinkedListNode<T>[capacity_ + 1];
	if (!new_mem_Data) return false;
	/*���ڴ渳ֵ*/
	for (int i = HEAD; i <= old_capacity; i++) new_mem_Data[i] = mem_Data[i];
	for (int i = old_capacity + 1; i <= capacity_; i++) new_mem_Data[i].next = NONE;
	/*ʹ�����ڴ沢�ͷž��ڴ�*/
	delete[] mem_Data;
	mem_Data = new_mem_Data;
	return true;
}

template<typename T>
inline bool StaticLinkedList<T>::GetDataIndexByPos_(int pos, int& index) const
{
	if ((pos < 0) || (pos > length_)) return false;
	if (pos == 0)
	{
		index = HEAD;
		return true;
	}

	int cur_index = this->mem_Data[HEAD].next; 
	for (int i = 1; i < pos; i++) cur_index = this->mem_Data[cur_index].next;
	index = cur_index;
	return true;
}
