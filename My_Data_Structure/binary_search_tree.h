#pragma once

#include <iostream>
#include <exception>

template<typename TKey, typename TValue>
struct BstNode
{
public:
	BstNode() :left_child_(nullptr), right_child_(nullptr) {};
	BstNode(TKey key, TValue value) :value_(value), key_(key), left_child_(nullptr), right_child_(nullptr) {};
	BstNode(TKey key, TValue value, BstNode<TKey, TValue>* left_child, BstNode<TKey, TValue>* right_child) :
		value_(value), key_(key), left_child_(left_child), right_child_(right_child) {};
	/*��ȡ����*/
	BstNode<TKey, TValue>*& LeftChild() { return this->left_child_; }
	/*��ȡ�Һ���*/
	BstNode<TKey, TValue>*& RightChild() { return this->right_child_; }
	/*��������*/
	void SetLeftChild(BstNode<TKey, TValue>* node) { this->left_child_ = node; }
	/*�����Һ���*/
	void SetRightChild(BstNode<TKey, TValue>* node) { this->right_child_ = node; }
	/*��ȡ�ؼ���*/
	virtual TKey Key() { return this->key_; }
	/*���ùؼ���*/
	virtual void SetKey(const TKey& key) { this->key_ = key; }
	/*��ȡֵ*/
	virtual TValue Value() { return this->value_; }
	/*����ֵ*/
	virtual void SetValue(const TValue& value) { this->value_ = value; }

protected:
	BstNode<TKey, TValue>* left_child_;  //����ָ��
	BstNode<TKey, TValue>* right_child_;  //�Һ���ָ��
	TKey key_;  //�ؼ���
	TValue value_;  //ֵ
};

template<typename TKey, typename TValue>
class BinarySearchTree
{
public:
	BinarySearchTree() :root_(nullptr) {};
	BinarySearchTree(TKey key, TValue value) { this->InsertRecursive(key, value); }
	virtual ~BinarySearchTree() { delete this->root_; }
	/*������*/
	virtual bool InsertRecursive(TKey key, TValue value) { return InsertInSubTree_(key, value, root_); }
	/*ɾ�����*/
	virtual bool RemoveRecursive(const TKey& key) { return RemoveInSubTree_(root_, key); }
	/*���������õݹ飩*/
	virtual BstNode<TKey, TValue>* Search(TKey key) { return SearchInSubTree_(root_, key); }
	/*��ȡ�߶�*/
	virtual int Height() { return HeightOfSubtreeRecursive_(root_); }
	/*��ȡ��С�ؼ��ֶ�Ӧ��ֵ*/
	virtual bool Min(TValue& min_value);
	/*��ȡ���ؼ��ֶ�Ӧ��ֵ*/
	virtual bool Max(TValue& max_value);
	/*��ȡ���ڵ�*/
	BstNode<TKey, TValue>*& Root() { return root_; }
	/*���*/
	virtual void Clear() { ClearSubTree_(root_); }
	/*��ӡ(����)*/
	void Print(void(*NodePrint)(BstNode<TKey, TValue>*)) { PrintSubTreeRecursive_(root_, NodePrint); }

	/*����=*/
	BinarySearchTree<TKey, TValue>& operator=(const BinarySearchTree<TKey, TValue>& src_bst);

protected:
	//����������(�ݹ�)
	bool InsertInSubTree_(TKey key, TValue value, BstNode<TKey, TValue>*& subtree_root);
	//����ɾ�����(�ݹ�)
	bool RemoveInSubTree_(BstNode<TKey, TValue>*& subtree_root, TKey key);
	//��������(�ݹ�)
	BstNode<TKey, TValue>* SearchInSubTree_(BstNode<TKey, TValue>* subtree_root, TKey key);
	//�����߶�
	int HeightOfSubtreeRecursive_(BstNode<TKey, TValue>* subtree_root);
	//�������(�ݹ�)
	void ClearSubTree_(BstNode<TKey, TValue>*& subtree_root);
	//������ӡ(�ݹ�)
	void PrintSubTreeRecursive_(BstNode<TKey, TValue>* subtree_root, void(*NodePrint)(BstNode<TKey, TValue>*)) const;
	//��������(�ݹ�)
	BstNode<TKey, TValue>* CopySubTreeRecursive_(const BstNode<TKey, TValue>* src_bst_root);
	//�����йؼ�����С��
	BstNode<TKey, TValue>* MinInSubTree_(BstNode<TKey, TValue>* subtree_root) const;
	//�����йؼ��������
	BstNode<TKey, TValue>* MaxInSubTree_(BstNode<TKey, TValue>* subtree_root) const;
	//��ȡ����(����)��һ���
	BstNode<TKey, TValue>* NextNode_(BstNode<TKey, TValue>* node);

	BstNode<TKey, TValue>* root_;  //���ڵ�
};

template<typename TKey, typename TValue>
inline bool BinarySearchTree<TKey, TValue>::Min(TValue& min_value)
{
	BstNode<TKey, TValue>* node = MinInSubTree_(Root());
	if (!node)return false;
	min_value = node->Value();
	return true;
}

template<typename TKey, typename TValue>
inline bool BinarySearchTree<TKey, TValue>::Max(TValue& max_value)
{
	BstNode<TKey, TValue>* node = MaxInSubTree_(Root());
	if (!node)return false;
	max_value = node->Value();
	return true;
}

template<typename TKey, typename TValue>
inline BinarySearchTree<TKey, TValue>& BinarySearchTree<TKey, TValue>::operator=(const BinarySearchTree<TKey, TValue>& src_bst)
{
	if (this == &src_bst) return *this;
	/*����*/
	root_ = CopySubTreeRecursive_(src_bst.root_);
	return *this;
}

template<typename TKey, typename TValue>
inline bool BinarySearchTree<TKey, TValue>::InsertInSubTree_(TKey key, TValue value, BstNode<TKey, TValue>*& subtree_root)
{
	if (subtree_root == nullptr)
	{
		subtree_root = new BstNode<TKey, TValue>(key, value);
		if (!subtree_root) throw std::bad_alloc();
		return true;
	}
	/*���εݹ�*/
	if (key < subtree_root->Key()) return InsertInSubTree_(key, value, subtree_root->LeftChild());  //���key < �������ڵ�key���Ը��ڵ����ӵݹ����
	if (key > subtree_root->Key()) return InsertInSubTree_(key, value, subtree_root->RightChild());  //���key > �������ڵ�key���Ը��ڵ��Һ��ӵݹ����
	return false;
}

template<typename TKey, typename TValue>
inline bool BinarySearchTree<TKey, TValue>::RemoveInSubTree_(BstNode<TKey, TValue>*& subtree_root, TKey key)
{
	if (subtree_root == nullptr) return false;
	/*ִ�еݹ�*/
	if (key < subtree_root->Key()) return RemoveInSubTree_(subtree_root->LeftChild(), key);  //�����ɾ��������������������ӵݹ����
	if (key > subtree_root->Key()) return RemoveInSubTree_(subtree_root->RightChild(), key);  //�����ɾ������������������Һ��ӵݹ����
	/*ɾ�����Ϊ�������ڵ�����*/
	if (subtree_root->LeftChild() != nullptr && subtree_root->RightChild() != nullptr)  //���subtree_rootͬʱ�������Һ���
	{
		BstNode<TKey, TValue>* next_node = NextNode_(subtree_root);  //��ʼ��next_node,ָ�������������һ�����(����������)����Ϊ�滻���
		subtree_root->SetValue(next_node->Value());
		subtree_root->SetKey(next_node->Key());
		return RemoveInSubTree_(subtree_root->RightChild(), next_node->Key());  
	}
	else
	{
		BstNode<TKey, TValue>* remove_node = subtree_root;
		if (subtree_root->LeftChild() == nullptr) subtree_root = subtree_root->RightChild();  //�������Ϊ�գ����Һ��Ӵ���
		else subtree_root = subtree_root->LeftChild();  //����Һ���Ϊ�գ������Ӵ���
		delete remove_node;
		remove_node = nullptr;
		return true;
	}
}

template<typename TKey, typename TValue>
inline BstNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::SearchInSubTree_(BstNode<TKey, TValue>* subtree_root, TKey key)
{
	if (subtree_root == nullptr) return nullptr;
	/*���εݹ�*/
	TKey subtree_root_key = subtree_root->Key();
	if (key < subtree_root_key) return SearchInSubTree_(subtree_root->LeftChild(), key);  //��������ؼ��� < �������ڵ�ؼ��֣��ݹ�����������
	else if (key > subtree_root_key) return SearchInSubTree_(subtree_root->RightChild(), key);  //��������ؼ��� > �������ڵ�ؼ��֣��ݹ�����������
	return subtree_root;
}

template<typename TKey, typename TValue>
inline int BinarySearchTree<TKey, TValue>::HeightOfSubtreeRecursive_(BstNode<TKey, TValue>* subtree_root)
{
	if (!subtree_root) return 0;
	/*���εݹ�*/
	int left_subtree_height = HeightOfSubtreeRecursive_(subtree_root->LeftChild());
	int right_subtree_height = HeightOfSubtreeRecursive_(subtree_root->RightChild());
	if (left_subtree_height < right_subtree_height) return right_subtree_height + 1;
	else return left_subtree_height + 1;
}

template<typename TKey, typename TValue>
inline void BinarySearchTree<TKey, TValue>::ClearSubTree_(BstNode<TKey, TValue>*& subtree_root)
{
	if (subtree_root == nullptr) return;
	/*���εݹ�*/
	ClearSubTree_(subtree_root->LeftChild());
	ClearSubTree_(subtree_root->RightChild());
	/*���ø��ڵ�*/
	delete subtree_root;
	subtree_root = nullptr;
}

template<typename TKey, typename TValue>
inline void BinarySearchTree<TKey, TValue>::PrintSubTreeRecursive_(BstNode<TKey, TValue>* subtree_root, void(*NodePrint)(BstNode<TKey, TValue>*)) const
{
	if (subtree_root == nullptr) return;
	/*���εݹ�*/
	NodePrint(subtree_root);
	if (subtree_root->LeftChild() == nullptr && subtree_root->RightChild() == nullptr) return;
	std::cout << "[";
	PrintSubTreeRecursive_(subtree_root->LeftChild(), NodePrint);
	std::cout << ",";
	PrintSubTreeRecursive_(subtree_root->RightChild(), NodePrint);
	std::cout << "]";
}

template<typename TKey, typename TValue>
inline BstNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::CopySubTreeRecursive_(const BstNode<TKey, TValue>* src_bst_root)
{
	if (src_bst_root == nullptr) return nullptr;
	/*�������������*/
	BstNode<TKey, TValue>* new_bst_root = new BstNode<TKey, TValue>(src_bst_root->Value(), src_bst_root->Key());
	if (new_bst_root == nullptr) throw std::bad_alloc();
	/*�����������εݹ鸴��*/
	new_bst_root->SetLeftChild(CopySubTreeRecursive_(src_bst_root->left_child_));
	new_bst_root->SetRightChild(CopySubTreeRecursive_(src_bst_root->right_child_));
	return new_bst_root;
}

template<typename TKey, typename TValue>
inline BstNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::MinInSubTree_(BstNode<TKey, TValue>* subtree_root) const
{
	if (subtree_root == nullptr) return nullptr;
	/*�������*/
	BstNode<TKey, TValue>* cur = subtree_root;
	while (cur && cur->LeftChild() != nullptr) cur = cur->LeftChild();
	return cur;
}

template<typename TKey, typename TValue>
inline BstNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::MaxInSubTree_(BstNode<TKey, TValue>* subtree_root) const
{
	if (subtree_root == nullptr) return nullptr;
	/*���ұ���*/
	BstNode<TKey, TValue>* cur = subtree_root;
	while (cur && cur->RightChild() != nullptr) cur = cur->RightChild();
	return cur;
}

template<typename TKey, typename TValue>
inline BstNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::NextNode_(BstNode<TKey, TValue>* node)
{
	if (!node) return nullptr;
	/*���ҽ��*/
	BstNode<TKey, TValue>* cur = node->RightChild();
	while (cur && cur->LeftChild())cur = cur->LeftChild(); 
	return cur;
}
