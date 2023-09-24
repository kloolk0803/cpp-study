#pragma once

#include <iostream>
#include <exception>

const int CHILD_POINTER = 0;  //子节点指针类型
const int THREADED_NODE_POINTER = 1;  //线索结点指针类型

template<typename T>
struct ThreadNode
{
	int left_tag;
	int right_tag;

	ThreadNode<T>* left_child;  //左孩子
	ThreadNode<T>* right_child;  //右孩子
	T data;  //数据项

	explicit ThreadNode(const T& data) :data(data), left_child(nullptr), right_child(nullptr), left_tag(CHILD_POINTER), right_tag(CHILD_POINTER) {};
};

template<typename T>
class InorderThreadedBinaryTree
{
public:
	InorderThreadedBinaryTree() :root_(nullptr) {};
	//获取根节点
	ThreadNode<T>* Root() { return root_; }
	//插入结点
	bool InsertRecursive(const T& data) { return InsertInSubTreeRecursive_(root_, data); }
	/*创建中序线索*/
	void CreateThreadRecursive();
	/*中序线索第一个线索结点*/
	ThreadNode<T>* First(ThreadNode<T>* subtree_root);
	/*获取子树最后一个线索结点*/
	ThreadNode<T>* Last(ThreadNode<T>* subtree_root);
	/*获取下一个线索结点*/
	ThreadNode<T>* Next(ThreadNode<T>* node);
	/*获取前一个线索结点*/
	ThreadNode<T>* Pre(ThreadNode<T>* node);
	//获取父节点
	ThreadNode<T>* Parent(ThreadNode<T>* node);
	//中序线索二叉树中序遍历
	void InorderTraverse(void(*visit)(ThreadNode<T>*));
	//中序线索二叉树前序遍历
	void PreorderTraverse(void(*visit)(ThreadNode<T>*));
	//中序线索二叉树后序遍历
	void PostorderTraverse(void(*visit)(ThreadNode<T>*));
	//子树获取后续遍历首个遍历结点
	ThreadNode<T>* GetFirstNodeForPostorder(ThreadNode<T>* subtree_root);

protected:
	ThreadNode<T>* root_;  //根节点
	//子树创建中序线索
	void CreateThreadInSubtreeRecursive_(ThreadNode<T>*& subtree_root, ThreadNode<T>*& pre_node);
	//子树插入
	bool InsertInSubTreeRecursive_(ThreadNode<T>*& subtree_root, const T& data);
};

template<typename T>
inline void InorderThreadedBinaryTree<T>::CreateThreadRecursive()
{
	if (root_ == nullptr)return;
	/*执行递归*/
	ThreadNode<T>* pre_node = nullptr;
	CreateThreadInSubtreeRecursive_(root_, pre_node);
	/*最后一个线索结点首尾工作*/
	pre_node->right_child = nullptr;
	pre_node->right_tag = THREADED_NODE_POINTER;
}

template<typename T>
inline ThreadNode<T>* InorderThreadedBinaryTree<T>::First(ThreadNode<T>* subtree_root)
{
	if (!subtree_root) throw std::invalid_argument("NULL pointer");
	ThreadNode<T>* cur = subtree_root;
	while (cur->left_child != nullptr && cur->left_tag == CHILD_POINTER) cur = cur->left_child;
	return cur;
}

template<typename T>
inline ThreadNode<T>* InorderThreadedBinaryTree<T>::Last(ThreadNode<T>* subtree_root)
{
	if (!subtree_root) throw std::invalid_argument("null pointer");
	ThreadNode<T>* cur = subtree_root;
	while (cur->right_child != nullptr && cur->right_tag == CHILD_POINTER) cur = cur->right_child;
	return cur;
}

template<typename T>
inline ThreadNode<T>* InorderThreadedBinaryTree<T>::Next(ThreadNode<T>* node)
{
	if (node->right_tag == THREADED_NODE_POINTER) return node->right_child;
	return First(node->right_child);                                                 
}

template<typename T>
inline ThreadNode<T>* InorderThreadedBinaryTree<T>::Pre(ThreadNode<T>* node)
{
	if (node->left_tag == THREADED_NODE_POINTER) return node->left_child;
	return Last(node->left_child);
}

template<typename T>
inline ThreadNode<T>* InorderThreadedBinaryTree<T>::Parent(ThreadNode<T>* node)
{
	if (!node) throw std::invalid_argument("null pointer");
	if (node == root_)return nullptr;
	/*通过前驱寻找父节点*/
	ThreadNode<T>* cur = node;
	while (cur->left_tag == CHILD_POINTER) cur = cur->left_child;
	ThreadNode<T>* upper_level_pre_node = cur->left_child;  //初始化上层前驱结点
	if (upper_level_pre_node != nullptr)  //此时存在前驱
	{
		if (upper_level_pre_node->right_child != node) upper_level_pre_node = upper_level_pre_node->right_child;
		if (upper_level_pre_node != nullptr && (upper_level_pre_node->left_child == node || upper_level_pre_node->right_child == node))
			return upper_level_pre_node;
	}
	/*通过后继寻找父节点*/
	cur = node;
	while (cur->right_tag == CHILD_POINTER) cur = cur->right_child;
	ThreadNode<T>* upper_level_post_node = cur->right_child;
	return upper_level_post_node;
}

template<typename T>
inline void InorderThreadedBinaryTree<T>::InorderTraverse(void(*visit)(ThreadNode<T>*))
{
	for (ThreadNode<T>* cur = First(root_); cur != nullptr; cur = Next(cur)) visit(cur);
}

template<typename T>
inline void InorderThreadedBinaryTree<T>::PreorderTraverse(void(*visit)(ThreadNode<T>*))
{
	ThreadNode<T>* cur = root_;
	while (cur != nullptr)
	{
		visit(cur);
		if (cur->left_tag == CHILD_POINTER) cur = cur->left_child;
		else if (cur->right_tag == CHILD_POINTER) cur = cur->right_child;
		else
		{
			//使用中序线索回溯至第1个有右孩子的结点
			while (cur != nullptr && cur->right_tag == THREADED_NODE_POINTER) cur = cur->right_child;
			//cur移动
			if (cur != nullptr)cur = cur->right_child;
		}
	}
}

template<typename T>
inline void InorderThreadedBinaryTree<T>::PostorderTraverse(void(*visit)(ThreadNode<T>*))
{
	if (!root_) return;
	/*访问后序遍历的第1个结点*/
	ThreadNode<T>* cur = this->GetFirstNodeForPostorder(root_);
	ThreadNode<T>* cur_parent = Parent(cur);
	visit(cur);
	/*递归*/
	while (cur_parent != nullptr)
	{
		if (cur_parent->right_child == cur || cur_parent->right_tag == THREADED_NODE_POINTER) cur = cur_parent;
		else cur = this->GetFirstNodeForPostorder(cur_parent->right_child);
		visit(cur);
		cur_parent = Parent(cur);
	}
}

template<typename T>
inline ThreadNode<T>* InorderThreadedBinaryTree<T>::GetFirstNodeForPostorder(ThreadNode<T>* subtree_root)
{
	ThreadNode<T>* cur = subtree_root;
	while (cur->left_tag == CHILD_POINTER || cur->right_tag == CHILD_POINTER)
	{
		if (cur->left_tag == CHILD_POINTER) cur = cur->left_child;
		else if (cur->right_tag == CHILD_POINTER) cur = cur->right_child;
	}
	return cur;
}

template<typename T>
inline void InorderThreadedBinaryTree<T>::CreateThreadInSubtreeRecursive_(ThreadNode<T>*& subtree_root, ThreadNode<T>*& pre_node)
{
	if (subtree_root == NULL)return;
	/*左子树递归*/
	CreateThreadInSubtreeRecursive_(subtree_root->left_child, pre_node);
	/*创建线索*/
	if (subtree_root->left_child == NULL) {                                 // if subtree_root->left_child为NULL :
		subtree_root->left_child = pre_node;                                // subtree_root->left_child指向pre_node
		subtree_root->left_tag = THREADED_NODE_POINTER;                     // subtree_root->left_tag属性, 设置为THREADED_NODE_POINTER(线索结点指针)
	}

	if (pre_node != NULL && pre_node->right_child == NULL) {                // if pre_node存在 && pre_node->right_child为NULL :
		pre_node->right_child = subtree_root;                               // pre_node->right_child指向subtree_root
		pre_node->right_tag = THREADED_NODE_POINTER;                        // pre_node->left_tag属性, 设置为THREADED_NODE_POINTER(线索结点指针)
	}
	/*更新pre_node*/
	pre_node = subtree_root;
	/*右子树递归*/
	CreateThreadInSubtreeRecursive_(subtree_root->right_child, pre_node);
}

template<typename T>
inline bool InorderThreadedBinaryTree<T>::InsertInSubTreeRecursive_(ThreadNode<T>*& subtree_root, const T& data)
{
	if (subtree_root == nullptr)
	{
		subtree_root = new ThreadNode<T>(data);
		if (!subtree_root) throw std::bad_alloc();
		return true;
	}
	int left_subtree_height = HeightOfSubTree(subtree_root->left_child);
	int right_subtree_height = HeightOfSubTree(subtree_root->right_child);
	if (left_subtree_height > right_subtree_height)
		return InsertInSubTreeRecursive_(subtree_root->right_child, data);
	else
		return InsertInSubTreeRecursive_(subtree_root->left_child, data);
}


template<typename T>
int HeightOfSubTree(ThreadNode<T>* subtree_root)
{
	if (subtree_root == nullptr) return 0;
	int left_subtree_height = HeightOfSubTree(subtree_root->left_child);
	int right_subtree_height = HeightOfSubTree(subtree_root->right_child);
	return (left_subtree_height < right_subtree_height ? right_subtree_height : left_subtree_height) + 1;
}