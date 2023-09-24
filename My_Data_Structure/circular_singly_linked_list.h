#pragma once

#include "linear_list.h"

using namespace std;

template <typename T>
struct CircularSinglyLinkedNode {

    explicit CircularSinglyLinkedNode(CircularSinglyLinkedNode<T>* next = nullptr) :
        next(next) {}

    explicit CircularSinglyLinkedNode(const T& data, CircularSinglyLinkedNode<T>* next = nullptr) :
        data(data), next(next) {}

    T data;                               //!< **������**
    CircularSinglyLinkedNode<T>* next;    //!< **��һ���**
};

template<typename T>
class CircularSinglyLinkedList : public Linear_list<T> {  /*��ͷ���*/
public:
    /*! @brief Ĭ�Ϲ��캯�� */
    CircularSinglyLinkedList() : first_(nullptr), last_(nullptr), length_(0) {}

    // ��������
    ~CircularSinglyLinkedList();

    /*! @brief **����** */
    int Length() const { return this->length_; }

    /*! @brief **�����Ƿ�Ϊ��** */
    bool IsEmpty() const { return this->first_ == nullptr; }

    // �������
    void Clear();

    // ����
    CircularSinglyLinkedNode<T>* Search(const T& data);

    // ��ȡ���
    CircularSinglyLinkedNode<T>* GetDataNode(int pos);

    // ������
    bool Insert(int prev_pos, const T& data);

    // ɾ�����
    bool Remove(int tarGetData_pos, T& data);

    // ��ȡ�������
    bool GetData(int pos, T& data) const;

    // ���ý������
    bool SetData(int pos, const T& data);

    // ��ӡ
    void Print();

private:
    CircularSinglyLinkedNode<T>* first_;            //!< **�׽��(ָ��)**  ָ��������Ԫ��
    CircularSinglyLinkedNode<T>* last_;             //!< **ĩ���(ָ��)**  ָ������βԪ��
    int length_;                                        //!< **����**
};

template<typename T>
inline CircularSinglyLinkedList<T>::~CircularSinglyLinkedList()
{
    this->Clear();
}

template<typename T>
inline void CircularSinglyLinkedList<T>::Clear()
{
    if (this->first_ == nullptr) return;
    for (int i = 1; i <= length_; i++)
    {
        CircularSinglyLinkedNode<T>* tarGetData_node = this->first_; 
        this->first_ = tarGetData_node->next;

        delete tarGetData_node;
        tarGetData_node = nullptr;
    }

    this->first_ = nullptr;
    this->last_ = nullptr;
    this->length_ = 0;
}

template<typename T>
inline CircularSinglyLinkedNode<T>* CircularSinglyLinkedList<T>::Search(const T& data)
{
    CircularSinglyLinkedNode<T>* cur = first_;
    for (int i = 1; i <= length_; i++)
    {
        if (cur->data == data)return cur;
        cur = cur->next;
    }
    return nullptr;
}

template<typename T>
inline CircularSinglyLinkedNode<T>* CircularSinglyLinkedList<T>::GetDataNode(int pos)
{
    if (pos < 0 || pos > length_)return nullptr;
    if (pos == 0)return last_;
    CircularSinglyLinkedNode<T>* cur = first_;
    for (int i = 1; i < pos; i++)cur = cur->next;
    return cur;
}

template<typename T>
inline bool CircularSinglyLinkedList<T>::Insert(int prev_pos, const T& data)
{
    if ((prev_pos > Length()) || (prev_pos < 0))return false;
    CircularSinglyLinkedNode<T>* new_node = new CircularSinglyLinkedNode<T>(data);
    if (new_node == nullptr)return false;
    /*��һ��������*/
    if (length_ == 0)
    {
        first_ = new_node;   /*first_ָ��new_node*/
        first_->next = first_;  /*first_->nextָ��first_*/
        last_ = first_;  /*last_ָ��first_*/
        length_ = 1; 
        return true;
    }
    /*���׽�����*/
    CircularSinglyLinkedNode<T>* prev_node = this->GetDataNode(prev_pos);
    new_node->next = prev_node->next;  /*new_node->nextָ��prev_node->next*/
    prev_node->next = new_node;  /*prev_node->nextָ��new_node*/

    if (prev_pos == 0)first_ = new_node;  /*����������λ��*/
    if (new_node->next == first_)last_ = new_node;  /*����²���Ľڵ��nextָ��first_����last_ָ��new_node*/

    this->length_++;
    return true;
}

template<typename T>
inline bool CircularSinglyLinkedList<T>::Remove(int tarGetData_pos, T& data)
{
    if ((tarGetData_pos < 1) || (tarGetData_pos > length_)) return false;
    /*������Ϊ1�����*/
    if (Length() == -1)
    {
        data = first_->data;
        delete first_;
        first_ = nullptr;
        last_ = nullptr;
        length_ = 0;
        return true;
    }
    /*ɾ��first_�������*/
    if (tarGetData_pos == 1)
    {
        data = first_->data;
        CircularSinglyLinkedNode<T>* tarGetData_node = first_;

        last_->next = first_->next;  /*last_->nextָ��first_->next*/
        first_ = first_->next;  /*first_ָ��first_->next*/

        delete tarGetData_node;
        tarGetData_node = nullptr;
        length_--;
        return true;
    }
    /*�������*/
    CircularSinglyLinkedNode<T>* prev_node = this->GetDataNode(tarGetData_pos - 1);
    CircularSinglyLinkedNode<T>* tarGetData_node = prev_node->next;
    if (tarGetData_node == last_)last_ = prev_node;  /*���ɾ��last_��㣬last_ = prev_node*/
    data = tarGetData_node->data;
    prev_node->next = tarGetData_node->next;  /*prev_node->nextָ��tarGetData_node->next*/
    delete tarGetData_node;
    tarGetData_node = nullptr;
    length_--;
    return true;
}

template<typename T>
inline bool CircularSinglyLinkedList<T>::GetData(int pos, T& data) const
{
    if ((pos < 1) || (pos > Length()) || (length_ == 0)) return false;
    CircularSinglyLinkedNode<T>* cur = first_;
    for (int i = 1; i < pos; i++)cur = cur->next;  /*ѭ��pos-1�Σ���Ϊû��ͷ���*/
    data = cur->data;
    return true;
}

template<typename T>
inline bool CircularSinglyLinkedList<T>::SetData(int pos, const T& data)
{
    if ((pos < 1) || (pos > Length())) return false;
    CircularSinglyLinkedNode<T>* cur = first_;
    for (int i = 1; i < pos; i++)cur = cur->next;  /*ѭ��pos-1�Σ���Ϊû��ͷ���*/
    cur->data = data;
    return true;
}

template<typename T>
inline void CircularSinglyLinkedList<T>::Print()
{
    if (this->first_ == nullptr)
    {
        std::cout << "Empty list\n";
        return;
    }

    std::cout << "��ӡѭ��������{ ";
    CircularSinglyLinkedNode<T>* cur = this->first_;
    for (int pos = 1; pos <= Length(); pos++)
    {
        std::cout << cur->data;
        if (pos != Length())std::cout << " <--> ";
        cur = cur->next;
    }
    std::cout << " }\n";
    std::cout << "--------------------------------------------------------------------------\n";
}


