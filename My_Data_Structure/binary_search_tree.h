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
	/*获取左孩子*/
	BstNode<TKey, TValue>*& LeftChild() { return this->left_child_; }
	/*获取右孩子*/
	BstNode<TKey, TValue>*& RightChild() { return this->right_child_; }
	/*设置左孩子*/
	void SetLeftChild(BstNode<TKey, TValue>* node) { this->left_child_ = node; }
	/*设置右孩子*/
	void SetRightChild(BstNode<TKey, TValue>* node) { this->right_child_ = node; }
	/*获取关键字*/
	virtual TKey Key() { return this->key_; }
	/*设置关键字*/
	virtual void SetKey(const TKey& key) { this->key_ = key; }
	/*获取值*/
	virtual TValue Value() { return this->value_; }
	/*设置值*/
	virtual void SetValue(const TValue& value) { this->value_ = value; }

protected:
	BstNode<TKey, TValue>* left_child_;  //左孩子指针
	BstNode<TKey, TValue>* right_child_;  //右孩子指针
	TKey key_;  //关键字
	TValue value_;  //值
};

template<typename TKey, typename TValue>
class BinarySearchTree
{
public:
	BinarySearchTree() :root_(nullptr) {};
	BinarySearchTree(TKey key, TValue value) { this->InsertRecursive(key, value); }
	virtual ~BinarySearchTree() { delete this->root_; }
	/*插入结点*/
	virtual bool InsertRecursive(TKey key, TValue value) { return InsertInSubTree_(key, value, root_); }
	/*删除结点*/
	virtual bool RemoveRecursive(const TKey& key) { return RemoveInSubTree_(root_, key); }
	/*搜索（调用递归）*/
	virtual BstNode<TKey, TValue>* Search(TKey key) { return SearchInSubTree_(root_, key); }
	/*获取高度*/
	virtual int Height() { return HeightOfSubtreeRecursive_(root_); }
	/*获取最小关键字对应的值*/
	virtual bool Min(TValue& min_value);
	/*获取最大关键字对应的值*/
	virtual bool Max(TValue& max_value);
	/*获取根节点*/
	BstNode<TKey, TValue>*& Root() { return root_; }
	/*清空*/
	virtual void Clear() { ClearSubTree_(root_); }
	/*打印(中序)*/
	void Print(void(*NodePrint)(BstNode<TKey, TValue>*)) { PrintSubTreeRecursive_(root_, NodePrint); }

	/*重载=*/
	BinarySearchTree<TKey, TValue>& operator=(const BinarySearchTree<TKey, TValue>& src_bst);

protected:
	//子树插入结点(递归)
	bool InsertInSubTree_(TKey key, TValue value, BstNode<TKey, TValue>*& subtree_root);
	//子树删除结点(递归)
	bool RemoveInSubTree_(BstNode<TKey, TValue>*& subtree_root, TKey key);
	//子树搜索(递归)
	BstNode<TKey, TValue>* SearchInSubTree_(BstNode<TKey, TValue>* subtree_root, TKey key);
	//子树高度
	int HeightOfSubtreeRecursive_(BstNode<TKey, TValue>* subtree_root);
	//子树清空(递归)
	void ClearSubTree_(BstNode<TKey, TValue>*& subtree_root);
	//子树打印(递归)
	void PrintSubTreeRecursive_(BstNode<TKey, TValue>* subtree_root, void(*NodePrint)(BstNode<TKey, TValue>*)) const;
	//子树复制(递归)
	BstNode<TKey, TValue>* CopySubTreeRecursive_(const BstNode<TKey, TValue>* src_bst_root);
	//子树中关键码最小项
	BstNode<TKey, TValue>* MinInSubTree_(BstNode<TKey, TValue>* subtree_root) const;
	//子树中关键码最大项
	BstNode<TKey, TValue>* MaxInSubTree_(BstNode<TKey, TValue>* subtree_root) const;
	//获取结点的(中序)下一结点
	BstNode<TKey, TValue>* NextNode_(BstNode<TKey, TValue>* node);

	BstNode<TKey, TValue>* root_;  //根节点
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
	/*复制*/
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
	/*分治递归*/
	if (key < subtree_root->Key()) return InsertInSubTree_(key, value, subtree_root->LeftChild());  //如果key < 子树根节点key，对根节点左孩子递归调用
	if (key > subtree_root->Key()) return InsertInSubTree_(key, value, subtree_root->RightChild());  //如果key > 子树根节点key，对根节点右孩子递归调用
	return false;
}

template<typename TKey, typename TValue>
inline bool BinarySearchTree<TKey, TValue>::RemoveInSubTree_(BstNode<TKey, TValue>*& subtree_root, TKey key)
{
	if (subtree_root == nullptr) return false;
	/*执行递归*/
	if (key < subtree_root->Key()) return RemoveInSubTree_(subtree_root->LeftChild(), key);  //如果待删除结点在左子树，对左孩子递归调用
	if (key > subtree_root->Key()) return RemoveInSubTree_(subtree_root->RightChild(), key);  //如果待删除结点在右子树，对右孩子递归调用
	/*删除结点为子树根节点的情况*/
	if (subtree_root->LeftChild() != nullptr && subtree_root->RightChild() != nullptr)  //如果subtree_root同时存在左右孩子
	{
		BstNode<TKey, TValue>* next_node = NextNode_(subtree_root);  //初始化next_node,指向根结点中序的下一个结点(在右子树内)，作为替换结点
		subtree_root->SetValue(next_node->Value());
		subtree_root->SetKey(next_node->Key());
		return RemoveInSubTree_(subtree_root->RightChild(), next_node->Key());  
	}
	else
	{
		BstNode<TKey, TValue>* remove_node = subtree_root;
		if (subtree_root->LeftChild() == nullptr) subtree_root = subtree_root->RightChild();  //如果左孩子为空，则右孩子代替
		else subtree_root = subtree_root->LeftChild();  //如果右孩子为空，则左孩子代替
		delete remove_node;
		remove_node = nullptr;
		return true;
	}
}

template<typename TKey, typename TValue>
inline BstNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::SearchInSubTree_(BstNode<TKey, TValue>* subtree_root, TKey key)
{
	if (subtree_root == nullptr) return nullptr;
	/*分治递归*/
	TKey subtree_root_key = subtree_root->Key();
	if (key < subtree_root_key) return SearchInSubTree_(subtree_root->LeftChild(), key);  //如果搜索关键字 < 子树根节点关键字，递归搜索左子树
	else if (key > subtree_root_key) return SearchInSubTree_(subtree_root->RightChild(), key);  //如果搜索关键字 > 子树根节点关键字，递归搜索右子树
	return subtree_root;
}

template<typename TKey, typename TValue>
inline int BinarySearchTree<TKey, TValue>::HeightOfSubtreeRecursive_(BstNode<TKey, TValue>* subtree_root)
{
	if (!subtree_root) return 0;
	/*分治递归*/
	int left_subtree_height = HeightOfSubtreeRecursive_(subtree_root->LeftChild());
	int right_subtree_height = HeightOfSubtreeRecursive_(subtree_root->RightChild());
	if (left_subtree_height < right_subtree_height) return right_subtree_height + 1;
	else return left_subtree_height + 1;
}

template<typename TKey, typename TValue>
inline void BinarySearchTree<TKey, TValue>::ClearSubTree_(BstNode<TKey, TValue>*& subtree_root)
{
	if (subtree_root == nullptr) return;
	/*分治递归*/
	ClearSubTree_(subtree_root->LeftChild());
	ClearSubTree_(subtree_root->RightChild());
	/*重置根节点*/
	delete subtree_root;
	subtree_root = nullptr;
}

template<typename TKey, typename TValue>
inline void BinarySearchTree<TKey, TValue>::PrintSubTreeRecursive_(BstNode<TKey, TValue>* subtree_root, void(*NodePrint)(BstNode<TKey, TValue>*)) const
{
	if (subtree_root == nullptr) return;
	/*分治递归*/
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
	/*生成新树根结点*/
	BstNode<TKey, TValue>* new_bst_root = new BstNode<TKey, TValue>(src_bst_root->Value(), src_bst_root->Key());
	if (new_bst_root == nullptr) throw std::bad_alloc();
	/*左右子树分治递归复制*/
	new_bst_root->SetLeftChild(CopySubTreeRecursive_(src_bst_root->left_child_));
	new_bst_root->SetRightChild(CopySubTreeRecursive_(src_bst_root->right_child_));
	return new_bst_root;
}

template<typename TKey, typename TValue>
inline BstNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::MinInSubTree_(BstNode<TKey, TValue>* subtree_root) const
{
	if (subtree_root == nullptr) return nullptr;
	/*向左遍历*/
	BstNode<TKey, TValue>* cur = subtree_root;
	while (cur && cur->LeftChild() != nullptr) cur = cur->LeftChild();
	return cur;
}

template<typename TKey, typename TValue>
inline BstNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::MaxInSubTree_(BstNode<TKey, TValue>* subtree_root) const
{
	if (subtree_root == nullptr) return nullptr;
	/*向右遍历*/
	BstNode<TKey, TValue>* cur = subtree_root;
	while (cur && cur->RightChild() != nullptr) cur = cur->RightChild();
	return cur;
}

template<typename TKey, typename TValue>
inline BstNode<TKey, TValue>* BinarySearchTree<TKey, TValue>::NextNode_(BstNode<TKey, TValue>* node)
{
	if (!node) return nullptr;
	/*查找结点*/
	BstNode<TKey, TValue>* cur = node->RightChild();
	while (cur && cur->LeftChild())cur = cur->LeftChild(); 
	return cur;
}
