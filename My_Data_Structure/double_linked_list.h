#pragma once

#include "Linear_list.h"

template <typename T>
struct DoublyLinkedNode {
    explicit DoublyLinkedNode(DoublyLinkedNode<T>* next = NULL, DoublyLinkedNode<T>* prev = NULL) :
        next(next), prev(prev) {}
    explicit DoublyLinkedNode(const T& data, DoublyLinkedNode<T>* next = NULL, DoublyLinkedNode<T>* prev = NULL) :
        data(data), next(next), prev(prev) {}

    T data;                       //!< **������**
    DoublyLinkedNode<T>* next;    //!< **��һ���**
    DoublyLinkedNode<T>* prev;    //!< **��һ���**
};

template<typename T>
class DoublyLinkedList : public Linear_list<T> {
public:
    // Ĭ�Ϲ��캯��
    DoublyLinkedList();
    // ��������
    ~DoublyLinkedList() { this->Clear(); }

    /*�ж��Ƿ�Ϊ������*/
    bool IsEmpty() const { return this->head_->next == head_; }
    // ������
    bool Insert(int pos, const T& data);
    // ��ȡ���
    DoublyLinkedNode<T>* GetDataNode(int pos) const;
    // ����
    DoublyLinkedNode<T>* Search(const T& data) const;
    // ����(�ݹ�)
    DoublyLinkedNode<T>* SearchRecursive(const T& data) const;
    // ��ȡ���������
    bool GetData(int pos, T& data) const;
    // ���ý��������
    bool SetData(int pos, const T& data);
    // ɾ�����
    bool Remove(int pos, T& data);
    // ���
    void Clear();
    // ��ӡ
    void Print();
    /*! @brief **����** */
    int Length() const { return this->length_; }

private:
    // ����������(�ݹ�)
    DoublyLinkedNode<T>* SearchInSubListRecursive_(DoublyLinkedNode<T>* sub_list_first_element, const T& data) const;

    DoublyLinkedNode<T>* head_;     //!< **ͷ���**
    DoublyLinkedNode<T>* tail_;     //!< **β���**
    int length_;                        //!< **����**
};

template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList()
{
    head_ = new DoublyLinkedNode<T>();
    tail_ = new DoublyLinkedNode<T>();
    if (head_ == nullptr || tail_ == nullptr)
        std::bad_alloc();

    head_->next = tail_;
    head_->prev = nullptr;

    tail_->next = nullptr;
    tail_->prev = head_;

    length_ = 0;
}

template<typename T>
inline bool DoublyLinkedList<T>::Insert(int prev_pos, const T& data)
{
    /*�Ƿ�λ�ô���*/
    if (prev_pos > length_ || prev_pos < 0) return false;
    /*���������*/
    DoublyLinkedNode<T>* new_node = new DoublyLinkedNode<T>(data);
    if (!new_node) std::bad_alloc();
    /*����*/
    DoublyLinkedNode<T>* prev_node = this->GetDataNode(prev_pos);
    new_node->next = prev_node->next;  /*�½���next��ָ���½���ǰһ����next*/
    prev_node->next = new_node;  /*�½���ǰһ����next��ָ���½��*/

    new_node->next->prev = new_node;  /*�½ڵ����һ�ڵ��prev��ָ���½��*/
    new_node->prev = prev_node;  /*�½ڵ��prev��ָ���½���ǰһ���*/
    /*��������*/
    length_++;
    return true;
}

template<typename T>
inline DoublyLinkedNode<T>* DoublyLinkedList<T>::GetDataNode(int pos) const
{
    if (pos < 0 || pos > length_) return nullptr;

    DoublyLinkedNode<T>* cur = head_;
    for (int i = 0; i < pos; i++) cur = cur->next;

    return cur;
}

template<typename T>
inline DoublyLinkedNode<T>* DoublyLinkedList<T>::Search(const T& data) const
{
    for (DoublyLinkedNode<T>* cur = head_->next; cur != nullptr; cur = cur->next)
    {
        if (cur->data == data)
            return cur;
    }
    return nullptr;
}

template<typename T>
inline DoublyLinkedNode<T>* DoublyLinkedList<T>::SearchRecursive(const T& data) const
{
    DoublyLinkedNode<T>* node = SearchInSubListRecursive_(head_, data);
    return node;
}

template<typename T>
inline bool DoublyLinkedList<T>::GetData(int pos, T& data) const
{
    if (pos < 0 || pos > length_) return false;

    DoublyLinkedNode<T>* cur = head_;
    for (int i = 0; i < pos; i++) cur = cur->next;

    data = cur->data;
    return true;
}

template<typename T>
inline bool DoublyLinkedList<T>::SetData(int pos, const T& data)
{
    if (pos < 0 || pos > length_) return false;

    DoublyLinkedNode<T>* cur = head_;
    for (int i = 0; i < pos; i++) cur = cur->next;

    cur->data = data;
    return true;
}

template<typename T>
inline bool DoublyLinkedList<T>::Remove(int tarGetData_pos, T& data)
{
    if (tarGetData_pos > Length() || tarGetData_pos < 1) return false;
    DoublyLinkedNode<T>* tarGetData_node = this->GetDataNode(tarGetData_pos);
    tarGetData_node->next->prev = tarGetData_node->prev;
    tarGetData_node->prev->next = tarGetData_node->next;

    data = tarGetData_node->data;
    delete tarGetData_node;
    tarGetData_node = nullptr;
    length_--;
    return true;
}

template<typename T>
inline void DoublyLinkedList<T>::Clear()
{
    int length = this->length_;
    for (int i = 1; i <= length; i++)
    {
        T tarGetData_data;
        this->Remove(1, tarGetData_data);
    }
}

template<typename T>
inline void DoublyLinkedList<T>::Print()
{
    if (this->length_ == 0)
    {
        std::cout << "Empty list\n";
        return;
    }
    std::cout << "��ӡ˫������{ ";
    DoublyLinkedNode<T>* cur = this->head_->next;
    for (int pos = 1; pos <= Length(); pos++)
    {
        std::cout << cur->data;
        if (pos != Length())std::cout << " <--> ";
        cur = cur->next;
    }
    std::cout << " }\n";
    std::cout << "--------------------------------------------------------------------------\n";
}

template<typename T>
inline DoublyLinkedNode<T>* DoublyLinkedList<T>::SearchInSubListRecursive_(DoublyLinkedNode<T>* sub_list_first_element, const T& data) const
{ 
    /*��������*/
    if (sub_list_first_element == nullptr) return nullptr;
    /*�������׸�Ԫ�ؽ������������Ĵ���*/
    if (sub_list_first_element->data == data) return sub_list_first_element;
    /*�ݹ�����*/
    return SearchInSubListRecursive_(sub_list_first_element->next, data);
}


