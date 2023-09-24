#pragma once

#include <iostream>

template<typename T>
struct StaticLinkedListNode
{
	StaticLinkedListNode<T>() :next(0) {};
	explicit StaticLinkedListNode<T>(T data) :data(data), next(-1) {};
	StaticLinkedListNode<T>(T data, int next) :data(data), next(next) {};

	T data;  /*数据项*/
	int next;  /*下一结点的索引*/
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

	static constexpr int NONE = -1  /*表示该数组元素不在静态链表中使用*/;
	static constexpr int HEAD = 0;  /*头结点的数组索引*/

private:
	/*获取插入位置的数组索引*/
	bool GetDataInsertIndex_(int& index) const;

	/*扩容*/
	bool Extend_(int increased_capacity);

	/*根据pos获取结点的数组索引*/
	bool GetDataIndexByPos_(int pos, int& index) const;

	StaticLinkedListNode<T>* mem_Data;  /*静态链表数组*/
	int length_;  /*静态链表长度*/
	int capacity_;  /*静态链表容量*/
};

template<typename T>
inline StaticLinkedList<T>::StaticLinkedList(int capacity)
{
	capacity_ = capacity;
	length_ = 0;
	mem_Data = new StaticLinkedListNode<T>[capacity_ + 1];
	if (!mem_Data) throw std::bad_alloc();

	mem_Data[HEAD].next = HEAD;  //HEAD结点的next指向HEAD(0, 自身)

	for (int i = 1; i <= capacity; i++)
		mem_Data[i].next = StaticLinkedList<T>::NONE;   //当前数组元素的next值为NONE(-1, 表示该数组元素不在静态链表中使用)
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
	if (pos < 0 || pos > length_) {                                 // if pos < 0 || pos大于链表长度
		return false;                                               // 返回false
	}

	// ---------- 2 扩容处理 ----------

	if (length_ == capacity_) {                                     // if 链表长度等于容量
		this->Extend_(capacity_);                                   // 扩容1倍
	}

	// ---------- 3 获取插入位置前一位置的数组索引 ----------
	int prev_index;
	bool res = GetDataIndexByPos_(pos, prev_index);                     // 对pos调用GetDataIndexByPos_, 获取prev_index(插入位置前一位置的数组索引)
	if (!res) {                                                     // if 获取失败
		return false;                                               // 返回false
	}

	// ---------- 4 获取插入位置的数组索引 ----------

	int insertion_index;
	res = GetDataInsertIndex_(insertion_index);                      // 调用GetDataInsertionIndex_, 获取insertion_index(执行插入的索引)
	if (!res) {                                                     // if 获取失败
		return false;                                               // 返回false
	}

	// ---------- 5 执行插入 ----------

	mem_Data[insertion_index].next = mem_Data[prev_index].next;   // 插入位置数组元素的next, 指向pos位置数组元素的next
	mem_Data[prev_index].next = insertion_index;                   // pos位置数组元素的next, 指向插入位置
	mem_Data[insertion_index].data = data;                         // 插入位置的data, 等于参数data

	length_++;
	return true;
}

template<typename T>
inline bool StaticLinkedList<T>::Remove(int pos, T& data)
{
	if (length_ == 0) return false;

	if ((pos < 1) || (pos > length_)) return false;

	/*找到删除结点前一结点*/
	int prev_index = HEAD;
	for (int i = 1; i < pos; i++) prev_index = mem_Data[prev_index].next;

	/*删除*/
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

	for (int cur = mem_Data[HEAD].next; cur != HEAD; cur = mem_Data[cur].next) {  // for loop 遍历链表中的每个结点
		cout << mem_Data[cur].data;                                                // 打印当前结点的data
		if (mem_Data[cur].next != HEAD) {                                          // if 不是最后一个结点
			cout << "-->";                                                          // 打印"-->"(表示next指向)
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
	/*容量数值增加*/
	int old_capacity = capacity_;
	capacity_ += increased_capacity;
	/*开辟新内存*/
	StaticLinkedListNode<T>* new_mem_Data = new StaticLinkedListNode<T>[capacity_ + 1];
	if (!new_mem_Data) return false;
	/*新内存赋值*/
	for (int i = HEAD; i <= old_capacity; i++) new_mem_Data[i] = mem_Data[i];
	for (int i = old_capacity + 1; i <= capacity_; i++) new_mem_Data[i].next = NONE;
	/*使用新内存并释放旧内存*/
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
