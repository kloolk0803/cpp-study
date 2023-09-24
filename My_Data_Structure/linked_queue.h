#pragma once

#include "queue.h"

template<typename T>
class LinkedNode_Queue
{
public:
	LinkedNode_Queue() :next_(nullptr) {};
	explicit LinkedNode_Queue(LinkedNode_Queue<T>* node = nullptr) :next_(node) {};
	explicit LinkedNode_Queue(const T& data, LinkedNode_Queue<T>* node = nullptr) :data_(data), next_(node) {};
	T GetData() { return data_; }
	void SetData(const T& data) { data_ = data; }
	LinkedNode_Queue<T>* Next() { return next_; }
	void SetNext(LinkedNode_Queue<T>* const& node) { next_ = node; }

private:
	T data_;  /*������*/
	LinkedNode_Queue<T>* next_;  /*��һ���*/
};

template<typename T>class LinkedQueue;
template<typename T>
std::ostream& operator<<(std::ostream& os, const LinkedQueue<T>& lined_queue);

template<typename T>
class LinkedQueue : public Queue<T> {

public:
    LinkedQueue() : front_(NULL), rear_(NULL) {}
    ~LinkedQueue() { Clear(); }

    // ���
    bool EnQueue(const T& data);

    // ����(��������)
    bool DeQueue(T& data);

    // ����(����������)
    bool DeQueue();

    // ��ȡ��ͷ����
    bool Front(T& data) const;

    // ��ȡ��β����
    bool Rear(T& data) const;

    // �ж϶����Ƿ�Ϊ��
    bool IsEmpty() const;

    // ��ȡ���г���
    int Length() const;

    // ��ն���
    void Clear();

    // ����<<(��ӡ����)
    friend ostream& operator<< <>(ostream& os, const LinkedQueue<T>& linked_queue);

private:
    LinkedNode_Queue<T>* FrontNode_() const { return this->front_; }
    LinkedNode_Queue<T>* RearNode_() const { return this->rear_; }

    LinkedNode_Queue<T>* front_;    //!< **��ͷ**
    LinkedNode_Queue<T>* rear_;     //!< **��β**
};

template<typename T>
inline bool LinkedQueue<T>::EnQueue(const T& data)
{
    LinkedNode_Queue<T>* node = new LinkedNode_Queue<T>(data);
    if (node == nullptr) throw std::bad_alloc();

    if (IsEmpty())
    {
        this->front_ = this->rear_ = node;
    }
    else
    {
        this->rear_->SetNext(node);
        this->rear_ = node;
    }

    return true;
}

template<typename T>
inline bool LinkedQueue<T>::DeQueue(T& data)
{
    if (IsEmpty()) return false;
    LinkedNode_Queue<T>* temp = front_;
    data = temp->GetData();
    this->front_ = this->front_->Next();
    delete temp;
    temp = nullptr;
    return true;
}

template<typename T>
inline bool LinkedQueue<T>::DeQueue()
{
    if (IsEmpty()) return false;
    LinkedNode_Queue<T>* temp = front_;
    this->front_ = this->front_->Next();
    delete temp;
    temp = nullptr;
    return true;
}

template<typename T>
inline bool LinkedQueue<T>::Front(T& data) const
{
    if (IsEmpty()) return false;
    data = front_->GetData();
    return true;
}

template<typename T>
inline bool LinkedQueue<T>::Rear(T& data) const
{
    if (IsEmpty()) return false;
    data = rear_->GetData();
    return true;
}

template<typename T>
inline bool LinkedQueue<T>::IsEmpty() const
{
    return front_ == nullptr;
}

template<typename T>
inline int LinkedQueue<T>::Length() const
{
    int count = 0;
    for (LinkedNode_Queue<T>* cur = front_; cur != nullptr; cur = cur->Next(), count++);
    return count;
}

template<typename T>
inline void LinkedQueue<T>::Clear()
{
    while (!IsEmpty()) this->LinkedQueue<T>::DeQueue();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const LinkedQueue<T>& linked_queue)
{
    os << "The size of link queue: " << linked_queue.Length() << '\n';   // ��ӡ���г���
    LinkedNode_Queue<T>* cur = linked_queue.FrontNode_();
    os << "___________________________________________\n";
    for (int i = 1; cur != nullptr; i++, cur = cur->Next()) os << i << ":" << cur->GetData() << " ";
    os << "\n___________________________________________\n";
    return os;
}