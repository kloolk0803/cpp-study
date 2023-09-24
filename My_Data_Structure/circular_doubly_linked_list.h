#pragma once

#include "linear_list.h"

template <typename T>
struct CircularDoublyLinkedNode {
    explicit CircularDoublyLinkedNode(CircularDoublyLinkedNode<T>* next = NULL,
        CircularDoublyLinkedNode<T>* prev = NULL)
        : next(next), prev(prev) {}

    explicit CircularDoublyLinkedNode(const T& data,
        CircularDoublyLinkedNode<T>* next = NULL,
        CircularDoublyLinkedNode<T>* prev = NULL)
        : data(data), next(next), prev(prev) {}

    T data;                               //!< 数据项
    CircularDoublyLinkedNode<T>* next;    //!< 下一结点
    CircularDoublyLinkedNode<T>* prev;    //!< 上一结点
};

template<typename T>
class CircularDoublyLinkedList : public Linear_list<T> {
public:
    /*! @brief **默认构造函数** */
    CircularDoublyLinkedList() : first_(NULL), length_(0) {}

    // 析构函数
    ~CircularDoublyLinkedList() { this->Clear(); }

    /*! @brief **长度** */
    int Length() const { return this->length_; }

    /*! @brief **判断是否为空链表** */
    bool IsEmpty() const { return this->first_ == NULL; }

    // 清空
    void Clear();

    /*! @brief **获取链表首结点** */
    CircularDoublyLinkedNode<T>* First() const { return this->first_; }

    // 搜索
    CircularDoublyLinkedNode<T>* Search(const T& data);

    // 获取结点(按方向)
    CircularDoublyLinkedNode<T>* GetDataNodeByDirection(int step, int direction);

    // 获取结点
    CircularDoublyLinkedNode<T>* GetDataNode(int pos);

    // 插入结点
    bool Insert(int prev_pos, const T& data);  /*在prev_pos后面插入一个结点*/

    // 删除结点(按方向)
    bool RemoveByDirection(int step, T& data, int direction);

    // 删除结点
    bool Remove(int tarGetData_pos, T& data);

    // 获取结点数据
    bool GetData(int pos, T& data) const;

    // 设置结点数据
    bool SetData(int pos, const T& data);

    // 打印
    void Print();

    static const int BACKWARD_DIRECTION = 0;    //!< **prev方向**
    static const int FORWARD_DIRECTION = 1;     //!< **next方向**

private:
    CircularDoublyLinkedNode<T>* first_;    //!< **首元素结点(指针)**
    int length_;                                //!< **长度**
};

template<typename T>
inline void CircularDoublyLinkedList<T>::Clear()
{
	while (first_ != nullptr)
    {
        /*删除当前首结点*/
        CircularDoublyLinkedNode<T>* cur_tarGetData_node = first_;  /*声明cur_tarGetData_node(本轮删除的结点)，指向first_*/
        first_ = cur_tarGetData_node->next;  /*first_指向cur_tarGetData_node->next*/

        delete cur_tarGetData_node;
        cur_tarGetData_node = nullptr;
    }
    this->length_ = 0;
}

template<typename T>
inline CircularDoublyLinkedNode<T>* CircularDoublyLinkedList<T>::Search(const T& data)
{
    CircularDoublyLinkedNode<T>* cur = this->first_;
    for (int pos = 1; pos <= Length(); pos++, cur = cur->next)
        if (cur->data == data)return cur;
    return nullptr;
}

template<typename T>
inline CircularDoublyLinkedNode<T>* CircularDoublyLinkedList<T>::GetDataNodeByDirection(int step, int direction)
{
    if ((step < 0) || (step >= length_)) return nullptr;
    CircularDoublyLinkedNode<T>* cur = first_;
    for (int i = 1; i <= step; i++)
    {
        if (direction == BACKWARD_DIRECTION)cur = cur->prev;
        else cur = cur->next;
    }
    return cur;
}

template<typename T>
inline CircularDoublyLinkedNode<T>* CircularDoublyLinkedList<T>::GetDataNode(int pos)
{
    if (pos == 0)return first_->prev;

    int step = pos - 1;
    return this->GetDataNodeByDirection(step, CircularDoublyLinkedList::FORWARD_DIRECTION);
}

template<typename T>
inline bool CircularDoublyLinkedList<T>::Insert(int prev_pos, const T& data)  
{
    if ((prev_pos < 0) || (prev_pos > length_)) return false;

    CircularDoublyLinkedNode<T>* new_node = new CircularDoublyLinkedNode<T>(data);
    if (new_node == nullptr)throw std::bad_alloc();

    /*空链表插入*/
    if (first_ == nullptr)
    {
        first_ = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        length_ = 1;
        return true;
    }
    /*插入*/
    CircularDoublyLinkedNode<T>* prev_node = this->GetDataNode(prev_pos);
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    new_node->next->prev = new_node;
    new_node->prev = prev_node;
    if (prev_pos == 0)first_ = new_node;  /*如果插入结点作为首结点，则first_指向new_node*/

    length_++;
    return true;
}

template<typename T>
inline bool CircularDoublyLinkedList<T>::RemoveByDirection(int step, T& data, int direction)
{
    if (first_ == nullptr) return false;
    CircularDoublyLinkedNode<T>* tarGetData_node = GetDataNodeByDirection(step, direction);
    if (tarGetData_node == nullptr)return false;
    /*只有一个结点的情况*/
    if (length_ == 1)
    {
        data = tarGetData_node->data;
        delete tarGetData_node;
        tarGetData_node = nullptr;
        length_ = 0;
        return true;
    }
    /*删除*/
    if (tarGetData_node == first_)  /*如果删除首结点，first_调整*/
    {
        if (direction == FORWARD_DIRECTION) first_ = tarGetData_node->next;
        else if (direction == BACKWARD_DIRECTION) first_ = tarGetData_node->prev;
    }
    tarGetData_node->next->prev = tarGetData_node->prev;
    tarGetData_node->prev->next = tarGetData_node->next;

    delete tarGetData_node;
    tarGetData_node = nullptr;
    length_--;
    return true;
}

template<typename T>
inline bool CircularDoublyLinkedList<T>::Remove(int tarGetData_pos, T& data)
{
    int step = tarGetData_pos - 1;
    return this->RemoveByDirection(step, data, CircularDoublyLinkedList::FORWARD_DIRECTION);
}

template<typename T>
inline bool CircularDoublyLinkedList<T>::GetData(int pos, T& data) const
{
    if ((pos < 0) || (pos > length_) || (length_ == 0)) return false;
    if (pos == 0)
    {
        data = first_->prev->data;
        return true;
    }
    CircularDoublyLinkedNode<T>* cur = this->first_;
    for (int i = 1; i < pos; i++)cur = cur->next;
    data = cur->data;
    return true;
}

template<typename T>
inline bool CircularDoublyLinkedList<T>::SetData(int pos, const T& data)
{
    if ((pos < 1) || (pos > Length())) return false;
    CircularDoublyLinkedNode<T>* cur = this->first_;
    for (int i = 1; i < pos; i++)cur = cur->next;
    cur->data = data;
    return true;
}

template<typename T>
inline void CircularDoublyLinkedList<T>::Print()
{
    /*空链表处理*/
    if (this->first_ == nullptr)
    {
        std::cout << "Empty list\n";
        return;
    }
    /*forward方向打印*/
    std::cout << "next方向(forward)遍历打印：\n";
    CircularDoublyLinkedNode<T>* cur = this->First();

    for (int pos = 1; pos <= Length(); pos++)
    {
        std::cout << cur->data << ";";
        cur = cur->next;
    }
    std::cout << '\n';

    std::cout << "prev方向(backward)遍历打印：\n";
    for (int pos = 1; pos <= Length(); pos++)
    {
        std::cout << cur->data << ";";
        cur = cur->prev;
    }
    std::cout << '\n';
    std::cout << "--------------------------------------------------------------------------\n";
}


