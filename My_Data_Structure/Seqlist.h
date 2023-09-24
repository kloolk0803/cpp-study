#pragma once

#include "linear_list.h"

template<typename T>
class SeqList : public Linear_list<T> {

public:
    /*默认构造函数*/
    SeqList() : mem_Data(NULL), capacity_(0), last_index_(-1) {}
    /*构造函数(容量)*/
    explicit SeqList(int capacity = 100);
    /*复制构造函数*/
    SeqList(const SeqList<T>& seq_list);
    /*赋值运算符重载函数*/
    SeqList<T>& operator =(const SeqList<T>& seq_list);
    /*析构函数*/
    ~SeqList() { delete[] mem_Data; }

    /*获取容量*/
    int Capacity() const { return capacity_; }
    /*获取当前长度*/
    int Length() const override{ return last_index_ + 1; }
    /*搜索数据的位置*/
    int Search(const T& data) const;
    /*获取结点数据*/
    bool GetData(int pos, T& data) const override; 
    /*设置结点数据*/
    bool SetData(int pos, const T& data) override;
    /*插入结点*/
    bool Insert(int prev_pos, const T& data) override;
    /*删除结点*/
    bool Remove(int tarGetData_pos, T& data) override;
    /*是否为空*/
    bool IsEmpty() const override;
    /*是否满*/
    bool IsFull() const;
    /*重置容量*/
    bool ReSetDataCapacity(int capacity);
    /*排序*/
    void Sort();
    /*打印顺序表*/
    void Print() override;

private:
    T* mem_Data;        /*数据项数组 下标从0开始*/
    int capacity_;           /*容量*/
    int last_index_;         /*最后一项的数组索引*/
};

/*构造函数(容量)*/
template<typename T>
inline SeqList<T>::SeqList(int capacity) :capacity_(capacity), last_index_(-1)
{
    if (capacity_ < 0)
    {
        throw std::out_of_range("capacity < 0");  /*报告访问试图受定义范围外的元素所带来的错误。*/
    }
    this->mem_Data = new T[capacity];
    if (!this->mem_Data)
    {
        throw std::bad_alloc();  /*内存分配失败抛出异常*/
    }
}

/*复制构造函数*/
template<typename T>
inline SeqList<T>::SeqList(const SeqList<T>& seq_list)
{
    /*初始化*/
    capacity_ = seq_list.Capacity();
    last_index_ = seq_list.Length() - 1;
    if (capacity_ == 0)
        return;
    /*mem_Data分配内存*/
    mem_Data = new T[Capacity()];
    if (!mem_Data) {
        std::bad_alloc();
    }
    /*mem_Data内存赋值*/
    for (int pos = 1; pos <= seq_list.Length(); pos++)
    {
        T cur_data;
        seq_list.GetData(pos, cur_data);  /*seq_list位置pos的变量赋给cur_data*/
        mem_Data[pos - 1] = cur_data;    /*cur_data赋给mem_Data[pos - 1]*/
    }
}

/*赋值运算符重载函数*/
template<typename T>
inline SeqList<T>& SeqList<T>::operator=(const SeqList<T>& seq_list)
{
    if (&seq_list != this)
    {
        capacity_ = seq_list.Capacity();
        int length = seq_list.Length();
        for (int i = 0; i < length; i++)
        {
            int curData;
            seq_list.GetData(i, curData);
            SetData(i, curData);
        }
    }
    return *this;
}

/*搜索数据的位置*/
template<typename T>
inline int SeqList<T>::Search(const T& data)const 
{
    for (int i = 0; i <= last_index_; i++)
    {
        if (mem_Data[i] == data)
            return i + 1;
    }
    return 0;
}

/*获取结点数据*/
template<typename T>
inline bool SeqList<T>::GetData(int pos, T& data) const
{
    if ((pos <= 0) || (pos > last_index_ + 1))
        return false;
    data = mem_Data[pos - 1];
    return true;
}

/*设置结点数据*/
template<typename T>
inline bool SeqList<T>::SetData(int pos, const T& data)
{
    if ((pos <= 0) || (pos > last_index_ + 1))  //位置越界
        return false;
    mem_Data[pos - 1] = data;
    return true;
}

/*插入结点*/
template<typename T>
inline bool SeqList<T>::Insert(int prev_pos, const T& data)
{
    if (last_index_ == capacity_ - 1)  //顺序表已经满了
        return false;
    if ((prev_pos < 0) || (prev_pos > last_index_ + 1))
        return false;
    for (int i = last_index_; i >= prev_pos; i--)  //prev_pos后面的元素往后移动一位
        mem_Data[i + 1] = mem_Data[i];
    mem_Data[prev_pos] = data;
    last_index_++;  //索引++
    return true;
}

/*删除结点*/
template<typename T>
inline bool SeqList<T>::Remove(int tarGetData_pos, T& data)
{
    if (last_index_ == -1)  //顺序表为空
        return false;
    if ((tarGetData_pos < 1) || (tarGetData_pos > Length()))
        return false;
    data = mem_Data[tarGetData_pos - 1];
    for (int i = tarGetData_pos; i <= last_index_; i++)  //tarGetData_pos后面的元素往前移动一位
        mem_Data[i - 1] = mem_Data[i];
    last_index_--;
    return true;
}

/*是否为空*/
template<typename T>
inline bool SeqList<T>::IsEmpty() const
{
    if(last_index_ == -1)
        return true;
    return false;
}

/*是否满*/
template<typename T>
inline bool SeqList<T>::IsFull() const
{
    if (last_index_ == capacity_ - 1)
        return true;
    return false;
}

/*重置容量*/
template<typename T>
inline bool SeqList<T>::ReSetDataCapacity(int capacity)
{
    if(capacity < Length())
        return false;
    /*重新分配内存*/
    T* new_mem_Data = new T[capacity];  
    if (new_mem_Data == nullptr)
        throw std::bad_alloc();
    /*将已有的数据赋值到新内存*/
    for (int i = 0; i < Length(); i++)
        new_mem_Data[i] = mem_Data[i];
    /*释放旧内存使用新内存*/
    delete[] mem_Data;
    mem_Data = new_mem_Data;
    /*容量调整*/
    capacity_ = capacity;
    return true;
}

/*排序*/
template<typename T>
inline void SeqList<T>::Sort()
{
    int length = Length();
    for (int i = 1; i < length; i++)
    {
        for (int j = 1; j <= length - i; j++)
        {
            T j_data;
            GetData(j, j_data);
            T j_next_data;
            GetData(j + 1, j_next_data);
            if (j_data > j_next_data)
            {
                SetData(j, j_next_data);
                SetData(j + 1, j_data);
            }
        }
    }
}

/*打印顺序表*/
template<typename T>
inline void SeqList<T>::Print()
{
    if (last_index_ == -1)
    {
        std::cout << "顺序表为空表\n";
        return;
    }
    for (int i = 0; i <= last_index_; i++)
    {
        std::cout << "位置(非数组索引)" << i + 1 << "  数据:" << mem_Data[i] << "\n";
    }
}

/*顺序表求并集*/
template<typename T>
inline void SeqListUnion(SeqList<T>& seq_list_a, SeqList<T>& seq_list_b)
{
    int a_length = seq_list_a.Length();
    int b_length = seq_list_b.Length();

    for (int i = 1; i <= b_length; i++)
    {
        T list_b_item;
        seq_list_b.GetData(i, list_b_item);  //在a顺序表中找到当前位置的数据
        int pos = seq_list_a.Search(list_b_item);  //在b顺序表中查找该数据
        if (pos == 0)  /*如果没找到该数据*/
        {
            seq_list_a.Insert(a_length, list_b_item);  /*在a表中插入该数据*/
            a_length++;
        }
    }
}

/*顺序表求交集*/
template<typename T>
inline void SeqListIntersection(SeqList<T>& seq_list_a, SeqList<T>& seq_list_b)
{
    int a_length = seq_list_a.Length();

    int iter_pos = 1;
    while (iter_pos <= a_length)
    {
        T list_a_item;
        seq_list_a.GetData(iter_pos, list_a_item);  //在a顺序表中找到当前位置的数据
        int pos = seq_list_b.Search(list_a_item);  //在b顺序表中查找该数据
        if (pos == 0)  /*如果没找到该数据*/
        {
            seq_list_a.Remove(iter_pos, list_a_item);  //则删除该数据
            a_length--;  /*a表长度--*/
        }
        else
        {
            iter_pos++;
        }
    }
}

