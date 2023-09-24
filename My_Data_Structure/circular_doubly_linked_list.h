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

    T data;                               //!< ������
    CircularDoublyLinkedNode<T>* next;    //!< ��һ���
    CircularDoublyLinkedNode<T>* prev;    //!< ��һ���
};

template<typename T>
class CircularDoublyLinkedList : public Linear_list<T> {
public:
    /*! @brief **Ĭ�Ϲ��캯��** */
    CircularDoublyLinkedList() : first_(NULL), length_(0) {}

    // ��������
    ~CircularDoublyLinkedList() { this->Clear(); }

    /*! @brief **����** */
    int Length() const { return this->length_; }

    /*! @brief **�ж��Ƿ�Ϊ������** */
    bool IsEmpty() const { return this->first_ == NULL; }

    // ���
    void Clear();

    /*! @brief **��ȡ�����׽��** */
    CircularDoublyLinkedNode<T>* First() const { return this->first_; }

    // ����
    CircularDoublyLinkedNode<T>* Search(const T& data);

    // ��ȡ���(������)
    CircularDoublyLinkedNode<T>* GetDataNodeByDirection(int step, int direction);

    // ��ȡ���
    CircularDoublyLinkedNode<T>* GetDataNode(int pos);

    // ������
    bool Insert(int prev_pos, const T& data);  /*��prev_pos�������һ�����*/

    // ɾ�����(������)
    bool RemoveByDirection(int step, T& data, int direction);

    // ɾ�����
    bool Remove(int tarGetData_pos, T& data);

    // ��ȡ�������
    bool GetData(int pos, T& data) const;

    // ���ý������
    bool SetData(int pos, const T& data);

    // ��ӡ
    void Print();

    static const int BACKWARD_DIRECTION = 0;    //!< **prev����**
    static const int FORWARD_DIRECTION = 1;     //!< **next����**

private:
    CircularDoublyLinkedNode<T>* first_;    //!< **��Ԫ�ؽ��(ָ��)**
    int length_;                                //!< **����**
};

template<typename T>
inline void CircularDoublyLinkedList<T>::Clear()
{
	while (first_ != nullptr)
    {
        /*ɾ����ǰ�׽��*/
        CircularDoublyLinkedNode<T>* cur_tarGetData_node = first_;  /*����cur_tarGetData_node(����ɾ���Ľ��)��ָ��first_*/
        first_ = cur_tarGetData_node->next;  /*first_ָ��cur_tarGetData_node->next*/

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

    /*���������*/
    if (first_ == nullptr)
    {
        first_ = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        length_ = 1;
        return true;
    }
    /*����*/
    CircularDoublyLinkedNode<T>* prev_node = this->GetDataNode(prev_pos);
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    new_node->next->prev = new_node;
    new_node->prev = prev_node;
    if (prev_pos == 0)first_ = new_node;  /*�����������Ϊ�׽�㣬��first_ָ��new_node*/

    length_++;
    return true;
}

template<typename T>
inline bool CircularDoublyLinkedList<T>::RemoveByDirection(int step, T& data, int direction)
{
    if (first_ == nullptr) return false;
    CircularDoublyLinkedNode<T>* tarGetData_node = GetDataNodeByDirection(step, direction);
    if (tarGetData_node == nullptr)return false;
    /*ֻ��һ���������*/
    if (length_ == 1)
    {
        data = tarGetData_node->data;
        delete tarGetData_node;
        tarGetData_node = nullptr;
        length_ = 0;
        return true;
    }
    /*ɾ��*/
    if (tarGetData_node == first_)  /*���ɾ���׽�㣬first_����*/
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
    /*��������*/
    if (this->first_ == nullptr)
    {
        std::cout << "Empty list\n";
        return;
    }
    /*forward�����ӡ*/
    std::cout << "next����(forward)������ӡ��\n";
    CircularDoublyLinkedNode<T>* cur = this->First();

    for (int pos = 1; pos <= Length(); pos++)
    {
        std::cout << cur->data << ";";
        cur = cur->next;
    }
    std::cout << '\n';

    std::cout << "prev����(backward)������ӡ��\n";
    for (int pos = 1; pos <= Length(); pos++)
    {
        std::cout << cur->data << ";";
        cur = cur->prev;
    }
    std::cout << '\n';
    std::cout << "--------------------------------------------------------------------------\n";
}


