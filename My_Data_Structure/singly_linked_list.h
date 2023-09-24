#include <iostream>
#include <cstddef>
#include "linear_list.h"

template<typename T>
struct LinkedNode {
    explicit LinkedNode(LinkedNode<T>* node = NULL) : next(node) {}
    LinkedNode(const T& data, LinkedNode<T>* node = NULL) : data(data), next(node) {}

    T data;                 //!< 链表数据项
    LinkedNode<T>* next;    //!< 下一结点
};

template<typename T>
class SinglyLinkedList : public Linear_list<T> {
public:
    // 默认构造函数
    SinglyLinkedList();
    // 复制构造函数
    SinglyLinkedList(const SinglyLinkedList<T>& src_linked_list);
    // 析构函数
    ~SinglyLinkedList();

    // 清空链表
    void Clear();
    /*链表长度*/
    int Length() const override{ return this->length_; }
    /*获取链表头结点*/
    LinkedNode<T>* Head() const { return this->head_; }
    // 搜索
    LinkedNode<T>* Search(T data);
    // 获取结点
    LinkedNode<T>* GetDataNode(int pos);
    // 获取结点数据
    bool GetData(int pos, T& data) const override;
    // 设置结点数据
    bool SetData(int pos, const T& data) override;
    // 插入(数据)
    bool Insert(int prev_pos, const T& data) override;
    // 插入(结点)
    bool Insert(int prev_pos, LinkedNode<T>* node);
    // 删除(结点)元素
    bool Remove(int tarGetData_pos, T& data) override;
    // 判断是否为空链表
    bool IsEmpty() const override;
    // 打印链表
    void Print();

private:
    LinkedNode<T>* head_;     //!< **链表头结点**
    int length_;              //!< **链表长度**
};

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : length_(0) {
    this->head_ = new LinkedNode<T>();                                  // head_(头结点)分配内存, length_(长度)设置为0
    if (!this->head_) {                                                     // if head_内存分配失败
        throw std::bad_alloc();                                                  // 抛出bad_alloc()
    }
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& src_linked_list) : length_(0) {

    // ---------- 1 头结点初始化 ----------

    this->head_ = new LinkedNode<T>();                                  // head_(头结点)分配内存并初始化
    if (this->head_ == NULL) {                                              // if 内存分配失败
        throw std::bad_alloc();                                                  // 抛出bad_alloc()
    }

    // ---------- 2 初始化指向两个链表各自头结点的遍历指针 ----------

    LinkedNode<T>* src_list_cur = src_linked_list.Head();               // src_list_cur指向源链表head_
    LinkedNode<T>* cur = this->Head();                                  // cur指向自身链表head_

    // ---------- 3 循环复制结点 ----------

    while (src_list_cur->next != NULL) {                                    // while src_list_cur->next不为NULL:

        T data = src_list_cur->next->data;
        cur->next = new LinkedNode<T>(data);                            // 使用src_list_cur->next的数据项构造新结点, 赋给cur->next指向该新节点(自身链表插入新节点)

        cur = cur->next;                                                    // cur向后移动1位
        src_list_cur = src_list_cur->next;                                  // src_list_cur向后移动1位

        this->length_++;                                                    // 链表长度加1
    }

    cur->next = NULL;                                                       // cur->next置为NULL
}

template<typename T>
inline SinglyLinkedList<T>::~SinglyLinkedList()
{
    this->Clear();  /*清空链表*/

    delete this->head_;
    this->head_ = nullptr;  /*释放head_并置空*/
}

template<typename T>
inline void SinglyLinkedList<T>::Clear()
{
	while (this->head_->next != nullptr)
    {
        LinkedNode<T>* cur = this->head_->next;
        this->head_->next = cur->next;

        delete cur;  /*释放cur指向的结点*/

        this->length_--;  /*链表长度减1*/
    }
}

template<typename T>
inline LinkedNode<T>* SinglyLinkedList<T>::Search(T data)
{
    /*初始化遍历指针*/
    LinkedNode<T>* cur = this->head_->next;
    if (cur == nullptr)return nullptr;

    /*遍历链表进行搜索*/
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
    if ((pos < 1) || (pos > this->length_))  /*访问位置越界*/
        return nullptr;
    /*遍历至pos位置的结点*/
    LinkedNode<T>* cur = this->Head();

    for (int i = 1; i <= pos; i++)cur = cur->next;

    return cur;
}

template<typename T>
inline bool SinglyLinkedList<T>::GetData(int pos, T& data) const
{
    if ((pos < 1) || (pos > this->length_))  /*访问位置越界*/
        return false;
    /*遍历至pos位置的结点*/
    LinkedNode<T>* cur = this->Head();

    for (int i = 1; i <= pos; i++)cur = cur->next;
    data = cur->data;

    return true;
}

template<typename T>
inline bool SinglyLinkedList<T>::SetData(int pos, const T& data)
{
    if ((pos < 1) || (pos > this->length_))  /*访问位置越界*/
        return false;
    /*遍历至插入的位置*/
    LinkedNode<T>* cur = this->Head();

    for (int i = 1; i <= pos; i++)cur = cur->next;
    cur->data = data;

    return true;
}

template<typename T>
inline bool SinglyLinkedList<T>::Insert(int prev_pos, const T& data)
{
	if ((prev_pos < 0) || (prev_pos>Length()))  /*访问位置越界*/
        return false;

    LinkedNode<T>* node = new LinkedNode<T>(data);  /*构造插入结点*/
    if (node == nullptr)return false;

    LinkedNode<T>* cur = this->head_;  /*遍历至插入位置*/
	while (prev_pos > 0)
    {
        cur = cur->next;
        prev_pos--;
    }

    node->next = cur->next;  /*执行插入*/
    cur->next = node;

    this->length_++;  /*链表长度+1*/
    return true;
}

template<typename T>
inline bool SinglyLinkedList<T>::Insert(int prev_pos, LinkedNode<T>* node)
{
    if ((prev_pos < 0) || (prev_pos > Length()) || node == nullptr)  /*访问位置越界*/
        return false;

    LinkedNode<T>* cur = this->head_;  /*遍历至插入位置*/
    while (prev_pos > 0)
    {
        cur = cur->next;
        prev_pos--;
    }

    node->next = cur->next;  /*执行插入*/
    cur->next = node;

    this->length_++;  /*链表长度+1*/
    return true;
}

template<typename T>
inline bool SinglyLinkedList<T>::Remove(int tarGetData_pos, T& data)
{
    if ((this->Length() == 0) || (tarGetData_pos < 1) || (tarGetData_pos > this->Length()))   /*访问位置越界*/
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

