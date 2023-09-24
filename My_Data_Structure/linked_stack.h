#pragma once

#include "stack.h"

template<typename T>
struct LinkedStackNode
{
	explicit LinkedStackNode(LinkedStackNode<T>* next = nullptr) :next(next) {};
	explicit LinkedStackNode(const T& data, LinkedStackNode<T>* next = nullptr) :data(data), next(next) {};

	T data;  /*������*/
	LinkedStackNode<T>* next;  /*��һ���*/
};

template<typename T>class LinkedStack;
template<typename T>
std::ostream& operator<<(std::ostream& os, const LinkedStack<T>& stack);

template<typename T>
class LinkedStack :public Stack<T>
{
public:
	LinkedStack() :top_(nullptr) {};
	~LinkedStack() { Clear(); }

    // ��ջ
    bool Push(const T& data);
    // ��ջ(��������)
    bool Pop(T& data);
    // ��ջ(����������)
    bool Pop();
    // ��ȡջ������
    bool Top(T& data) const;
    // �ж�ջ�Ƿ�Ϊ��
    bool IsEmpty() const;
    // ��ȡջ��С
    int Length() const;
	/*���*/
	void Clear();

    /*����*/
    friend std::ostream& operator << <>(std::ostream& os, const LinkedStack<T>& stack);

private:
	LinkedStackNode<T>* top_;
};

template<typename T>
inline bool LinkedStack<T>::Push(const T& data)
{
    LinkedStackNode<T>* node = new LinkedStackNode<T>(data);
    if (!node)throw std::bad_alloc();
    
    node->next = this->top_;
    this->top_ = node;

    return true;
}

template<typename T>
inline bool LinkedStack<T>::Pop(T& data)
{
    if (IsEmpty()) return false;

    LinkedStackNode<T>* temp = this->top_;
    this->top_ = this->top_->next;
    data = temp->data;

    delete temp;
    temp = nullptr;

    return true;
}

template<typename T>
inline bool LinkedStack<T>::Pop()
{
    if (IsEmpty()) return false;

    LinkedStackNode<T>* temp = this->top_;
    this->top_ = this->top_->next;

    delete temp;
    temp = nullptr;

    return true;
}

template<typename T>
inline bool LinkedStack<T>::Top(T& data) const
{
    if (IsEmpty()) return false;

    data = this->top_->data;
    return true;
}

template<typename T>
inline bool LinkedStack<T>::IsEmpty() const
{
    if (this->top_ == nullptr) return true;
    else return false;
}

template<typename T>
inline int LinkedStack<T>::Length() const
{
    int length = 0;
    LinkedStackNode<T>* cur = this->top_;

    while (cur != NULL)
    {
        length++; 
        cur = cur->next;
    }
    return length;
}

template<typename T>
inline void LinkedStack<T>::Clear()
{
	while (this->top_ != nullptr)
    {
        LinkedStackNode<T>* tarGetData = this->top_;
        top_ = top_->next;
        delete tarGetData;
        tarGetData = nullptr;
    }
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const LinkedStack<T>& stack)
{
    os << "ջ��Ԫ�ظ�����" << stack.Length() << '\n';

    LinkedStackNode<T>* cur = stack.top_;
    for (int i = 1; cur != nullptr; i++)
    {
        os << cur->data << '\n';
        cur = cur->next;
    }

    return os;
}