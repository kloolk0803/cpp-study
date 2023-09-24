#pragma once

#include <iostream>
#include <exception>

const int CHILD_POINTER = 0;  //�ӽڵ�ָ������
const int THREADED_NODE_POINTER = 1;  //�������ָ������

template<typename T>
struct ThreadNode
{
	int left_tag;
	int right_tag;

	ThreadNode<T>* left_child;  //����
	ThreadNode<T>* right_child;  //�Һ���
	T data;  //������

	explicit ThreadNode(const T& data) :data(data), left_child(nullptr), right_child(nullptr), left_tag(CHILD_POINTER), right_tag(CHILD_POINTER) {};
};

template<typename T>
class InorderThreadedBinaryTree
{
public:
	InorderThreadedBinaryTree() :root_(nullptr) {};
	//��ȡ���ڵ�
	ThreadNode<T>* Root() { return root_; }
	//������
	bool InsertRecursive(const T& data) { return InsertInSubTreeRecursive_(root_, data); }
	/*������������*/
	void CreateThreadRecursive();
	/*����������һ���������*/
	ThreadNode<T>* First(ThreadNode<T>* subtree_root);
	/*��ȡ�������һ���������*/
	ThreadNode<T>* Last(ThreadNode<T>* subtree_root);
	/*��ȡ��һ���������*/
	ThreadNode<T>* Next(ThreadNode<T>* node);
	/*��ȡǰһ���������*/
	ThreadNode<T>* Pre(ThreadNode<T>* node);
	//��ȡ���ڵ�
	ThreadNode<T>* Parent(ThreadNode<T>* node);
	//���������������������
	void InorderTraverse(void(*visit)(ThreadNode<T>*));
	//��������������ǰ�����
	void PreorderTraverse(void(*visit)(ThreadNode<T>*));
	//���������������������
	void PostorderTraverse(void(*visit)(ThreadNode<T>*));
	//������ȡ���������׸��������
	ThreadNode<T>* GetFirstNodeForPostorder(ThreadNode<T>* subtree_root);

protected:
	ThreadNode<T>* root_;  //���ڵ�
	//����������������
	void CreateThreadInSubtreeRecursive_(ThreadNode<T>*& subtree_root, ThreadNode<T>*& pre_node);
	//��������
	bool InsertInSubTreeRecursive_(ThreadNode<T>*& subtree_root, const T& data);
};

template<typename T>
inline void InorderThreadedBinaryTree<T>::CreateThreadRecursive()
{
	if (root_ == nullptr)return;
	/*ִ�еݹ�*/
	ThreadNode<T>* pre_node = nullptr;
	CreateThreadInSubtreeRecursive_(root_, pre_node);
	/*���һ�����������β����*/
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
	/*ͨ��ǰ��Ѱ�Ҹ��ڵ�*/
	ThreadNode<T>* cur = node;
	while (cur->left_tag == CHILD_POINTER) cur = cur->left_child;
	ThreadNode<T>* upper_level_pre_node = cur->left_child;  //��ʼ���ϲ�ǰ�����
	if (upper_level_pre_node != nullptr)  //��ʱ����ǰ��
	{
		if (upper_level_pre_node->right_child != node) upper_level_pre_node = upper_level_pre_node->right_child;
		if (upper_level_pre_node != nullptr && (upper_level_pre_node->left_child == node || upper_level_pre_node->right_child == node))
			return upper_level_pre_node;
	}
	/*ͨ�����Ѱ�Ҹ��ڵ�*/
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
			//ʹ������������������1�����Һ��ӵĽ��
			while (cur != nullptr && cur->right_tag == THREADED_NODE_POINTER) cur = cur->right_child;
			//cur�ƶ�
			if (cur != nullptr)cur = cur->right_child;
		}
	}
}

template<typename T>
inline void InorderThreadedBinaryTree<T>::PostorderTraverse(void(*visit)(ThreadNode<T>*))
{
	if (!root_) return;
	/*���ʺ�������ĵ�1�����*/
	ThreadNode<T>* cur = this->GetFirstNodeForPostorder(root_);
	ThreadNode<T>* cur_parent = Parent(cur);
	visit(cur);
	/*�ݹ�*/
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
	/*�������ݹ�*/
	CreateThreadInSubtreeRecursive_(subtree_root->left_child, pre_node);
	/*��������*/
	if (subtree_root->left_child == NULL) {                                 // if subtree_root->left_childΪNULL :
		subtree_root->left_child = pre_node;                                // subtree_root->left_childָ��pre_node
		subtree_root->left_tag = THREADED_NODE_POINTER;                     // subtree_root->left_tag����, ����ΪTHREADED_NODE_POINTER(�������ָ��)
	}

	if (pre_node != NULL && pre_node->right_child == NULL) {                // if pre_node���� && pre_node->right_childΪNULL :
		pre_node->right_child = subtree_root;                               // pre_node->right_childָ��subtree_root
		pre_node->right_tag = THREADED_NODE_POINTER;                        // pre_node->left_tag����, ����ΪTHREADED_NODE_POINTER(�������ָ��)
	}
	/*����pre_node*/
	pre_node = subtree_root;
	/*�������ݹ�*/
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