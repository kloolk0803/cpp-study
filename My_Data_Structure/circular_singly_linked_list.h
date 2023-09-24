#pragma once

#include "linear_list.h"

using namespace std;

template <typename T>
struct CircularSinglyLinkedNode {

    explicit CircularSinglyLinkedNode(CircularSinglyLinkedNode<T>* next = nullptr) :
        next(next) {}

    explicit CircularSinglyLinkedNode(const T& data, CircularSinglyLinkedNode<T>* next = nullptr) :
        data(data), next(next) {}

    T data;                               //!< **数据项**
    CircularSinglyLinkedNode<T>* next;    //!< **下一结点**
};

template<typename T>
class CircularSinglyLinkedList : public Linear_list<T> {  /*无头结点*/
public:
    /*! @brief 默认构造函数 */
    CircularSinglyLinkedList() : first_(nullptr), last_(nullptr), length_(0) {}

    // 析构函数
    ~CircularSinglyLinkedList();

    /*! @brief **长度** */
    int Length() const { return this->length_; }

    /*! @brief **链表是否为空** */
    bool IsEmpty() const { return this->first_ == nullptr; }

    // 清空链表
    void Clear();

    // 搜索
    CircularSinglyLinkedNode<T>* Search(const T& data);

    // 获取结点
    CircularSinglyLinkedNode<T>* GetDataNode(int pos);

    // 插入结点
    bool Insert(int prev_pos, const T& data);

    // 删除结点
    bool Remove(int tarGetData_pos, T& data);

    // 获取结点数据
    bool GetData(int pos, T& data) const;

    // 设置结点数据
    bool SetData(int pos, const T& data);

    // 打印
    void Print();

private:
    CircularSinglyLinkedNode<T>* first_;            //!< **首结点(指针)**  指向链表首元素
    CircularSinglyLinkedNode<T>* last_;             //!< **末结点(指针)**  指向链表尾元素
    int length_;                                        //!< **长度**
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
    /*第一个结点插入*/
    if (length_ == 0)
    {
        first_ = new_node;   /*first_指向new_node*/
        first_->next = first_;  /*first_->next指向first_*/
        last_ = first_;  /*last_指向first_*/
        length_ = 1; 
        return true;
    }
    /*非首结点插入*/
    CircularSinglyLinkedNode<T>* prev_node = this->GetDataNode(prev_pos);
    new_node->next = prev_node->next;  /*new_node->next指向prev_node->next*/
    prev_node->next = new_node;  /*prev_node->next指向new_node*/

    if (prev_pos == 0)first_ = new_node;  /*插入链表首位置*/
    if (new_node->next == first_)last_ = new_node;  /*如果新插入的节点的next指向first_，则last_指向new_node*/

    this->length_++;
    return true;
}

template<typename T>
inline bool CircularSinglyLinkedList<T>::Remove(int tarGetData_pos, T& data)
{
    if ((tarGetData_pos < 1) || (tarGetData_pos > length_)) return false;
    /*链表长度为1的情况*/
    if (Length() == -1)
    {
        data = first_->data;
        delete first_;
        first_ = nullptr;
        last_ = nullptr;
        length_ = 0;
        return true;
    }
    /*删除first_结点的情况*/
    if (tarGetData_pos == 1)
    {
        data = first_->data;
        CircularSinglyLinkedNode<T>* tarGetData_node = first_;

        last_->next = first_->next;  /*last_->next指向first_->next*/
        first_ = first_->next;  /*first_指向first_->next*/

        delete tarGetData_node;
        tarGetData_node = nullptr;
        length_--;
        return true;
    }
    /*其他情况*/
    CircularSinglyLinkedNode<T>* prev_node = this->GetDataNode(tarGetData_pos - 1);
    CircularSinglyLinkedNode<T>* tarGetData_node = prev_node->next;
    if (tarGetData_node == last_)last_ = prev_node;  /*如果删除last_结点，last_ = prev_node*/
    data = tarGetData_node->data;
    prev_node->next = tarGetData_node->next;  /*prev_node->next指向tarGetData_node->next*/
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
    for (int i = 1; i < pos; i++)cur = cur->next;  /*循环pos-1次，因为没有头结点*/
    data = cur->data;
    return true;
}

template<typename T>
inline bool CircularSinglyLinkedList<T>::SetData(int pos, const T& data)
{
    if ((pos < 1) || (pos > Length())) return false;
    CircularSinglyLinkedNode<T>* cur = first_;
    for (int i = 1; i < pos; i++)cur = cur->next;  /*循环pos-1次，因为没有头结点*/
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

    std::cout << "打印循环单链表：{ ";
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


