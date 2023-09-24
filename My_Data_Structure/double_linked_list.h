#pragma once

#include "Linear_list.h"

template <typename T>
struct DoublyLinkedNode {
    explicit DoublyLinkedNode(DoublyLinkedNode<T>* next = NULL, DoublyLinkedNode<T>* prev = NULL) :
        next(next), prev(prev) {}
    explicit DoublyLinkedNode(const T& data, DoublyLinkedNode<T>* next = NULL, DoublyLinkedNode<T>* prev = NULL) :
        data(data), next(next), prev(prev) {}

    T data;                       //!< **数据项**
    DoublyLinkedNode<T>* next;    //!< **下一结点**
    DoublyLinkedNode<T>* prev;    //!< **上一结点**
};

template<typename T>
class DoublyLinkedList : public Linear_list<T> {
public:
    // 默认构造函数
    DoublyLinkedList();
    // 析构函数
    ~DoublyLinkedList() { this->Clear(); }

    /*判断是否为空链表*/
    bool IsEmpty() const { return this->head_->next == head_; }
    // 插入结点
    bool Insert(int pos, const T& data);
    // 获取结点
    DoublyLinkedNode<T>* GetDataNode(int pos) const;
    // 搜索
    DoublyLinkedNode<T>* Search(const T& data) const;
    // 搜索(递归)
    DoublyLinkedNode<T>* SearchRecursive(const T& data) const;
    // 获取结点数据项
    bool GetData(int pos, T& data) const;
    // 设置结点数据项
    bool SetData(int pos, const T& data);
    // 删除结点
    bool Remove(int pos, T& data);
    // 清空
    void Clear();
    // 打印
    void Print();
    /*! @brief **长度** */
    int Length() const { return this->length_; }

private:
    // 子链表搜索(递归)
    DoublyLinkedNode<T>* SearchInSubListRecursive_(DoublyLinkedNode<T>* sub_list_first_element, const T& data) const;

    DoublyLinkedNode<T>* head_;     //!< **头结点**
    DoublyLinkedNode<T>* tail_;     //!< **尾结点**
    int length_;                        //!< **长度**
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
    /*非法位置处理*/
    if (prev_pos > length_ || prev_pos < 0) return false;
    /*构造插入结点*/
    DoublyLinkedNode<T>* new_node = new DoublyLinkedNode<T>(data);
    if (!new_node) std::bad_alloc();
    /*插入*/
    DoublyLinkedNode<T>* prev_node = this->GetDataNode(prev_pos);
    new_node->next = prev_node->next;  /*新结点的next，指向新结点的前一结点的next*/
    prev_node->next = new_node;  /*新结点的前一结点的next，指向新结点*/

    new_node->next->prev = new_node;  /*新节点的下一节点的prev，指向新结点*/
    new_node->prev = prev_node;  /*新节点的prev，指向新结点的前一结点*/
    /*调整长度*/
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
    std::cout << "打印双向链表：{ ";
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
    /*空链表处理*/
    if (sub_list_first_element == nullptr) return nullptr;
    /*子链表首个元素结点既是搜索结点的处理*/
    if (sub_list_first_element->data == data) return sub_list_first_element;
    /*递归搜索*/
    return SearchInSubListRecursive_(sub_list_first_element->next, data);
}


