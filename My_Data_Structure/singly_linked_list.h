#include <iostream>
#include <cstddef>
#include "linear_list.h"

template<typename T>
struct LinkedNode {
    explicit LinkedNode(LinkedNode<T>* node = NULL) : next(node) {}
    LinkedNode(const T& data, LinkedNode<T>* node = NULL) : data(data), next(node) {}

    T data;                 //!< ����������
    LinkedNode<T>* next;    //!< ��һ���
};

template<typename T>
class SinglyLinkedList : public Linear_list<T> {
public:
    // Ĭ�Ϲ��캯��
    SinglyLinkedList();
    // ���ƹ��캯��
    SinglyLinkedList(const SinglyLinkedList<T>& src_linked_list);
    // ��������
    ~SinglyLinkedList();

    // �������
    void Clear();
    /*������*/
    int Length() const override{ return this->length_; }
    /*��ȡ����ͷ���*/
    LinkedNode<T>* Head() const { return this->head_; }
    // ����
    LinkedNode<T>* Search(T data);
    // ��ȡ���
    LinkedNode<T>* GetDataNode(int pos);
    // ��ȡ�������
    bool GetData(int pos, T& data) const override;
    // ���ý������
    bool SetData(int pos, const T& data) override;
    // ����(����)
    bool Insert(int prev_pos, const T& data) override;
    // ����(���)
    bool Insert(int prev_pos, LinkedNode<T>* node);
    // ɾ��(���)Ԫ��
    bool Remove(int tarGetData_pos, T& data) override;
    // �ж��Ƿ�Ϊ������
    bool IsEmpty() const override;
    // ��ӡ����
    void Print();

private:
    LinkedNode<T>* head_;     //!< **����ͷ���**
    int length_;              //!< **������**
};

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : length_(0) {
    this->head_ = new LinkedNode<T>();                                  // head_(ͷ���)�����ڴ�, length_(����)����Ϊ0
    if (!this->head_) {                                                     // if head_�ڴ����ʧ��
        throw std::bad_alloc();                                                  // �׳�bad_alloc()
    }
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& src_linked_list) : length_(0) {

    // ---------- 1 ͷ����ʼ�� ----------

    this->head_ = new LinkedNode<T>();                                  // head_(ͷ���)�����ڴ沢��ʼ��
    if (this->head_ == NULL) {                                              // if �ڴ����ʧ��
        throw std::bad_alloc();                                                  // �׳�bad_alloc()
    }

    // ---------- 2 ��ʼ��ָ�������������ͷ���ı���ָ�� ----------

    LinkedNode<T>* src_list_cur = src_linked_list.Head();               // src_list_curָ��Դ����head_
    LinkedNode<T>* cur = this->Head();                                  // curָ����������head_

    // ---------- 3 ѭ�����ƽ�� ----------

    while (src_list_cur->next != NULL) {                                    // while src_list_cur->next��ΪNULL:

        T data = src_list_cur->next->data;
        cur->next = new LinkedNode<T>(data);                            // ʹ��src_list_cur->next����������½��, ����cur->nextָ����½ڵ�(������������½ڵ�)

        cur = cur->next;                                                    // cur����ƶ�1λ
        src_list_cur = src_list_cur->next;                                  // src_list_cur����ƶ�1λ

        this->length_++;                                                    // �����ȼ�1
    }

    cur->next = NULL;                                                       // cur->next��ΪNULL
}

template<typename T>
inline SinglyLinkedList<T>::~SinglyLinkedList()
{
    this->Clear();  /*�������*/

    delete this->head_;
    this->head_ = nullptr;  /*�ͷ�head_���ÿ�*/
}

template<typename T>
inline void SinglyLinkedList<T>::Clear()
{
	while (this->head_->next != nullptr)
    {
        LinkedNode<T>* cur = this->head_->next;
        this->head_->next = cur->next;

        delete cur;  /*�ͷ�curָ��Ľ��*/

        this->length_--;  /*�����ȼ�1*/
    }
}

template<typename T>
inline LinkedNode<T>* SinglyLinkedList<T>::Search(T data)
{
    /*��ʼ������ָ��*/
    LinkedNode<T>* cur = this->head_->next;
    if (cur == nullptr)return nullptr;

    /*���������������*/
	while (cur != nullptr)
    {
        if (cur->data == data)break;
        cur = cur->next;
    }
    return cur;
}

template<typename T>
inline LinkedNode<T>* SinglyLinkedList<T>::GetDataNode(int pos)
{
    if ((pos < 1) || (pos > this->length_))  /*����λ��Խ��*/
        return nullptr;
    /*������posλ�õĽ��*/
    LinkedNode<T>* cur = this->Head();

    for (int i = 1; i <= pos; i++)cur = cur->next;

    return cur;
}

template<typename T>
inline bool SinglyLinkedList<T>::GetData(int pos, T& data) const
{
    if ((pos < 1) || (pos > this->length_))  /*����λ��Խ��*/
        return false;
    /*������posλ�õĽ��*/
    LinkedNode<T>* cur = this->Head();

    for (int i = 1; i <= pos; i++)cur = cur->next;
    data = cur->data;

    return true;
}

template<typename T>
inline bool SinglyLinkedList<T>::SetData(int pos, const T& data)
{
    if ((pos < 1) || (pos > this->length_))  /*����λ��Խ��*/
        return false;
    /*�����������λ��*/
    LinkedNode<T>* cur = this->Head();

    for (int i = 1; i <= pos; i++)cur = cur->next;
    cur->data = data;

    return true;
}

template<typename T>
inline bool SinglyLinkedList<T>::Insert(int prev_pos, const T& data)
{
	if ((prev_pos < 0) || (prev_pos>Length()))  /*����λ��Խ��*/
        return false;

    LinkedNode<T>* node = new LinkedNode<T>(data);  /*���������*/
    if (node == nullptr)return false;

    LinkedNode<T>* cur = this->head_;  /*����������λ��*/
	while (prev_pos > 0)
    {
        cur = cur->next;
        prev_pos--;
    }

    node->next = cur->next;  /*ִ�в���*/
    cur->next = node;

    this->length_++;  /*������+1*/
    return true;
}

template<typename T>
inline bool SinglyLinkedList<T>::Insert(int prev_pos, LinkedNode<T>* node)
{
    if ((prev_pos < 0) || (prev_pos > Length()) || node == nullptr)  /*����λ��Խ��*/
        return false;

    LinkedNode<T>* cur = this->head_;  /*����������λ��*/
    while (prev_pos > 0)
    {
        cur = cur->next;
        prev_pos--;
    }

    node->next = cur->next;  /*ִ�в���*/
    cur->next = node;

    this->length_++;  /*������+1*/
    return true;
}

template<typename T>
inline bool SinglyLinkedList<T>::Remove(int tarGetData_pos, T& data)
{
    if ((this->Length() == 0) || (tarGetData_pos < 1) || (tarGetData_pos > this->Length()))   /*����λ��Խ��*/
        return false;

    LinkedNode<T>* cur = this->head_;
    for (int i = 1; i < tarGetData_pos; i++)cur = cur->next;

    LinkedNode<T>* temp = cur->next;
    cur->next = temp->next;

    delete temp;
    temp = nullptr;

    this->length_--;
    return true;
}

template<typename T>
inline bool SinglyLinkedList<T>::IsEmpty() const
{
    if (this->Head()->next == nullptr)return true;
    else return false;
}

template<typename T>
inline void SinglyLinkedList<T>::Print()
{
    if (this->head_->next == nullptr)
    {
        std::cout << "Empty list\n";
        std::cout << "-------------------------------------\n";
        return;
    }

    LinkedNode<T>* cur = Head()->next;
    while (cur != nullptr)
    {
        std::cout << cur->data << '\n';
        cur = cur->next;
    }   
    std::cout << "-------------------------------------\n";
}

