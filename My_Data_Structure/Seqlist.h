#pragma once

#include "linear_list.h"

template<typename T>
class SeqList : public Linear_list<T> {

public:
    /*Ĭ�Ϲ��캯��*/
    SeqList() : mem_Data(NULL), capacity_(0), last_index_(-1) {}
    /*���캯��(����)*/
    explicit SeqList(int capacity = 100);
    /*���ƹ��캯��*/
    SeqList(const SeqList<T>& seq_list);
    /*��ֵ��������غ���*/
    SeqList<T>& operator =(const SeqList<T>& seq_list);
    /*��������*/
    ~SeqList() { delete[] mem_Data; }

    /*��ȡ����*/
    int Capacity() const { return capacity_; }
    /*��ȡ��ǰ����*/
    int Length() const override{ return last_index_ + 1; }
    /*�������ݵ�λ��*/
    int Search(const T& data) const;
    /*��ȡ�������*/
    bool GetData(int pos, T& data) const override; 
    /*���ý������*/
    bool SetData(int pos, const T& data) override;
    /*������*/
    bool Insert(int prev_pos, const T& data) override;
    /*ɾ�����*/
    bool Remove(int tarGetData_pos, T& data) override;
    /*�Ƿ�Ϊ��*/
    bool IsEmpty() const override;
    /*�Ƿ���*/
    bool IsFull() const;
    /*��������*/
    bool ReSetDataCapacity(int capacity);
    /*����*/
    void Sort();
    /*��ӡ˳���*/
    void Print() override;

private:
    T* mem_Data;        /*���������� �±��0��ʼ*/
    int capacity_;           /*����*/
    int last_index_;         /*���һ�����������*/
};

/*���캯��(����)*/
template<typename T>
inline SeqList<T>::SeqList(int capacity) :capacity_(capacity), last_index_(-1)
{
    if (capacity_ < 0)
    {
        throw std::out_of_range("capacity < 0");  /*���������ͼ�ܶ��巶Χ���Ԫ���������Ĵ���*/
    }
    this->mem_Data = new T[capacity];
    if (!this->mem_Data)
    {
        throw std::bad_alloc();  /*�ڴ����ʧ���׳��쳣*/
    }
}

/*���ƹ��캯��*/
template<typename T>
inline SeqList<T>::SeqList(const SeqList<T>& seq_list)
{
    /*��ʼ��*/
    capacity_ = seq_list.Capacity();
    last_index_ = seq_list.Length() - 1;
    if (capacity_ == 0)
        return;
    /*mem_Data�����ڴ�*/
    mem_Data = new T[Capacity()];
    if (!mem_Data) {
        std::bad_alloc();
    }
    /*mem_Data�ڴ渳ֵ*/
    for (int pos = 1; pos <= seq_list.Length(); pos++)
    {
        T cur_data;
        seq_list.GetData(pos, cur_data);  /*seq_listλ��pos�ı�������cur_data*/
        mem_Data[pos - 1] = cur_data;    /*cur_data����mem_Data[pos - 1]*/
    }
}

/*��ֵ��������غ���*/
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

/*�������ݵ�λ��*/
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

/*��ȡ�������*/
template<typename T>
inline bool SeqList<T>::GetData(int pos, T& data) const
{
    if ((pos <= 0) || (pos > last_index_ + 1))
        return false;
    data = mem_Data[pos - 1];
    return true;
}

/*���ý������*/
template<typename T>
inline bool SeqList<T>::SetData(int pos, const T& data)
{
    if ((pos <= 0) || (pos > last_index_ + 1))  //λ��Խ��
        return false;
    mem_Data[pos - 1] = data;
    return true;
}

/*������*/
template<typename T>
inline bool SeqList<T>::Insert(int prev_pos, const T& data)
{
    if (last_index_ == capacity_ - 1)  //˳����Ѿ�����
        return false;
    if ((prev_pos < 0) || (prev_pos > last_index_ + 1))
        return false;
    for (int i = last_index_; i >= prev_pos; i--)  //prev_pos�����Ԫ�������ƶ�һλ
        mem_Data[i + 1] = mem_Data[i];
    mem_Data[prev_pos] = data;
    last_index_++;  //����++
    return true;
}

/*ɾ�����*/
template<typename T>
inline bool SeqList<T>::Remove(int tarGetData_pos, T& data)
{
    if (last_index_ == -1)  //˳���Ϊ��
        return false;
    if ((tarGetData_pos < 1) || (tarGetData_pos > Length()))
        return false;
    data = mem_Data[tarGetData_pos - 1];
    for (int i = tarGetData_pos; i <= last_index_; i++)  //tarGetData_pos�����Ԫ����ǰ�ƶ�һλ
        mem_Data[i - 1] = mem_Data[i];
    last_index_--;
    return true;
}

/*�Ƿ�Ϊ��*/
template<typename T>
inline bool SeqList<T>::IsEmpty() const
{
    if(last_index_ == -1)
        return true;
    return false;
}

/*�Ƿ���*/
template<typename T>
inline bool SeqList<T>::IsFull() const
{
    if (last_index_ == capacity_ - 1)
        return true;
    return false;
}

/*��������*/
template<typename T>
inline bool SeqList<T>::ReSetDataCapacity(int capacity)
{
    if(capacity < Length())
        return false;
    /*���·����ڴ�*/
    T* new_mem_Data = new T[capacity];  
    if (new_mem_Data == nullptr)
        throw std::bad_alloc();
    /*�����е����ݸ�ֵ�����ڴ�*/
    for (int i = 0; i < Length(); i++)
        new_mem_Data[i] = mem_Data[i];
    /*�ͷž��ڴ�ʹ�����ڴ�*/
    delete[] mem_Data;
    mem_Data = new_mem_Data;
    /*��������*/
    capacity_ = capacity;
    return true;
}

/*����*/
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

/*��ӡ˳���*/
template<typename T>
inline void SeqList<T>::Print()
{
    if (last_index_ == -1)
    {
        std::cout << "˳���Ϊ�ձ�\n";
        return;
    }
    for (int i = 0; i <= last_index_; i++)
    {
        std::cout << "λ��(����������)" << i + 1 << "  ����:" << mem_Data[i] << "\n";
    }
}

/*˳����󲢼�*/
template<typename T>
inline void SeqListUnion(SeqList<T>& seq_list_a, SeqList<T>& seq_list_b)
{
    int a_length = seq_list_a.Length();
    int b_length = seq_list_b.Length();

    for (int i = 1; i <= b_length; i++)
    {
        T list_b_item;
        seq_list_b.GetData(i, list_b_item);  //��a˳������ҵ���ǰλ�õ�����
        int pos = seq_list_a.Search(list_b_item);  //��b˳����в��Ҹ�����
        if (pos == 0)  /*���û�ҵ�������*/
        {
            seq_list_a.Insert(a_length, list_b_item);  /*��a���в��������*/
            a_length++;
        }
    }
}

/*˳����󽻼�*/
template<typename T>
inline void SeqListIntersection(SeqList<T>& seq_list_a, SeqList<T>& seq_list_b)
{
    int a_length = seq_list_a.Length();

    int iter_pos = 1;
    while (iter_pos <= a_length)
    {
        T list_a_item;
        seq_list_a.GetData(iter_pos, list_a_item);  //��a˳������ҵ���ǰλ�õ�����
        int pos = seq_list_b.Search(list_a_item);  //��b˳����в��Ҹ�����
        if (pos == 0)  /*���û�ҵ�������*/
        {
            seq_list_a.Remove(iter_pos, list_a_item);  //��ɾ��������
            a_length--;  /*a����--*/
        }
        else
        {
            iter_pos++;
        }
    }
}

