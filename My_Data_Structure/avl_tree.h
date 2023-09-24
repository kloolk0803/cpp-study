#pragma once

#include "binary_search_tree.h"
#include <stack>

template<typename TKey, typename TValue>
class AvlNode :public BstNode<TKey, TValue>
{
public:
	AvlNode() :left_child_(nullptr), right_child_(nullptr), height_(1), balance_factor_(BALANCED) {};
	AvlNode(const TKey& key, const TValue& value) :
		value_(value), key_(key), left_child_(nullptr), right_child_(nullptr), height_(1), balance_factor_(BALANCED) {};
	AvlNode(TKey key, TValue value, AvlNode<TKey, TValue>* left_child, AvlNode<TKey, TValue>* right_child) :
		value_(value), key_(key), left_child_(left_child), right_child_(right_child), height_(1), balance_factor_(BALANCED) {};

	/*��ȡ���ӽ��*/
	AvlNode<TKey, TValue>*& LeftChild() { return left_child_; }
	/*�������ӽ��*/
	void SetLeftChild(AvlNode<TKey, TValue>* node) { left_child_ = node; }
	/*��ȡ�Һ��ӽ��*/
	AvlNode<TKey, TValue>*& RightChild() { return right_child_; }
	/*�����Һ��ӽ��*/
	void SetRightChild(AvlNode<TKey, TValue>* node) { right_child_ = node; }
	/*��ȡ�ؼ���*/
	TKey key() { return key_; }
	/*���ùؼ���*/
	void SetKey(const TKey& key) { key_ = key; }
	/*��ȡֵ*/
	TValue Value() { return value_; }
	/*����ֵ*/
	void SetValue(const TValue& value) { value_ = value; }
	/*��ȡ�߶�*/
	int Height() { return height_; }
	/*���ø߶�*/
	void SetHeight(int height) { height_ = height; }
	/*��ȡƽ������*/
	int BalanceFactor() { return balance_factor_; }
	/*����ƽ������*/
	void SetBalanceFactor(int balance_factor) { balance_factor_ = balance_factor; }
	/*���¸߶�*/
	void UpdateHeight()
	{
		int left_height = LeftChild() ? LeftChild()->Height() : 0;  //��ȡ�������߶�
		int right_height = RightChild() > RightChild()->Height() :0;  //��ȡ�������߶�
		height_ = (left_height > right_height ? left_height : right_height) + 1;  //ȡ�����߶����ֵ
	}
	/*����ƽ������*/
	void UpdateBanlanceFactor()
	{
		int left_height = LeftChild() ? LeftChild()->Height() : 0;  //��ȡ�������߶�
		int right_height = RightChild() > RightChild()->Height() :0;  //��ȡ�������߶�
		balance_factor_ = right_height - left_height;
	}

	static constexpr int RIGHT_HIGHER_2 = 2;  //����������������2
	static constexpr int RIGHT_HIGHER_1 = 1;  //����������������1
	static constexpr int BALANCED = 0;  //����ƽ��
	static constexpr int LEFT_HIGHER_1 = -1;  //����������������1
	static constexpr int LEFT_HIGHER_2 = -2;  //����������������2

protected:
	TKey key_;  //�ؼ���
	TValue value_;  //ֵ
	AvlNode<TKey, TValue>* left_child_;  //���ӽ��(ָ��)
	AvlNode<TKey, TValue>* right_child_;  //�Һ��ӽ��(ָ��)
	int height_;  //�߶�
	int balance_factor_;  //ƽ������
};

template<typename TKey, typename TValue>
class AvlTree :public BinarySearchTree<TKey, TValue>
{
public:
	AvlTree() :root_(nullptr) {};
	/*��ȡ���ڵ�*/
	AvlNode<TKey, TValue>*& Root() { return root_; }
	/*���ø��ڵ�*/
	void SetRoot(AvlNode<TKey, TValue>* node) { root_ = node; }
	/*������*/
	bool Insert(TKey key, TValue value);
	/*�����㣨�ݹ飩*/
	bool InsertRecursive(TKey key, TValue value);
	/*ɾ�����*/
	bool Remove(TKey key);
	/*ɾ����㣨�ݹ飩*/
	bool RemoveRecursive(TKey key);
	/*��ȡ�߶�*/
	int Height() { return root_->Height(); }
	/*��ȡ�߶ȣ��ݹ飩*/
	int HeightRecursive() { return HeightOfSubtreeRecursive_(this->root_); }
	/*��ȡ���ؼ��ֶ�Ӧ��ֵ*/
	bool Max(TValue& max_value);
	/*��ȡ��С�ؼ��ֶ�Ӧ��ֵ*/
	bool Min(TValue& min_value);
	/*����*/
	AvlNode<TKey, TValue>* Search(TKey key) { return this->SearchInSubTree_(this->root_, key); }
	/*��ӡ*/
	void Print(void(*visit)(AvlNode<TKey, TValue>*));

protected:
	/*����������(�ݹ�)*/
	bool InsertInSubTreeRecursive_(AvlNode<TKey, TValue>*& subtree_root, TKey key, TValue value);
	/*����������*/
	bool InsertSubTree_(AvlNode<TKey, TValue>*& subtree_root, TKey key, TValue value);
	/*����ɾ�����(�ݹ�)*/
	bool RemoveInSubTreeRecursive_(AvlNode<TKey, TValue>*& subtree_root, TKey key);
	/*����ɾ�����*/
	bool RemoveInSubTree_(AvlNode<TKey, TValue>*& subtree_root, TKey key);
	/*���붯��ƽ��(by����ջ)*/
	AvlNode<TKey, TValue>* InsertionBalanceByStack_(std::stack<AvlNode<TKey, TValue>*>& backtrack_stack);
	/*ɾ������ƽ��(by����ջ)*/
	AvlNode<TKey, TValue>* RemovalBalanceByStack_(std::stack<AvlNode<TKey, TValue>*>& backtrack_stack);
	/*ƽ��*/
	void Balance_(AvlNode<TKey, TValue>*& node);
	 
	/*����ת(left Rotation)*/
	int LeftRotate_(AvlNode<TKey, TValue>*& node);
	/*�ҵ���ת(left Rotation)*/
	int RightRotate_(AvlNode<TKey, TValue>*& node);
	/*�������˫��ת(left right Rotation)*/
	int LeftRightRotate_(AvlNode<TKey, TValue>*& node);
	/*���Һ���˫��ת(right left Rotation)*/
	int RightLeftRotate_(AvlNode<TKey, TValue>*& node);

	/*��������(�ݹ�)*/
	AvlNode<TKey, TValue>* SearchInSubTree_(AvlNode<TKey, TValue>* subtree_root, TKey key);

	/*��ȡ(������)�ؼ�����С���*/
	AvlNode<TKey, TValue>* MinInSubTree_(AvlNode<TKey, TValue>* subtree_root) const;
	/*��ȡ(������)�ؼ��������*/
	AvlNode<TKey, TValue>* MaxInSubTree_(AvlNode<TKey, TValue>* subtree_root) const;
	
	/*��ȡ����(����)ǰһ���*/
	AvlNode<TKey, TValue>* PreviousNode_(AvlNode<TKey, TValue>* node);

	/*�����߶�*/
	int HeightOfSubtreeRecursive_(AvlNode<TKey, TValue>* subtree_root);

	/*������ӡ(�ݹ�)*/
	void PrintSubTreeRecursive_(AvlNode<TKey, TValue>* subtree_root, void(*Print)(AvlNode<TKey, TValue>*));

	/*������Ϸ��Բ���ʼ������ջ*/
	bool CheckInsertLegalAndInitStack_(TKey key, AvlNode<TKey, TValue>* subtree_root, std::stack<AvlNode<TKey, TValue>*>& backtrack_stack);

	/*��λɾ����㲢��ʼ������ջ*/
	AvlNode<TKey, TValue>* FindRemoveNodeAndInitStack_(AvlNode<TKey, TValue>* subtree_root, TKey key, std::stack<AvlNode<TKey, TValue>*>& backtrack_stack);

	AvlNode<TKey, TValue>* root_;  //���ڵ�
};

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::InsertInSubTreeRecursive_(AvlNode<TKey, TValue>*& subtree_root, TKey key, TValue value)
{
	/*������������*/
	if (!subtree_root)
	{
		subtree_root = new AvlNode<TKey, TValue>(key, value);  
		if (!subtree_root) throw std::bad_alloc(); 
		return true;
	}
	/*�ظ��������*/
	if (key == subtree_root->key()) return false;
	/*���εݹ�*/
	if (key < subtree_root->key())  //�������ؼ��� < �������ڵ�ؼ���
	{
		bool res = InsertInSubTreeRecursive_(subtree_root->LeftChild(), key, value);  //���������ڵ�����ӽ��ִ�еݹ����
		if (!res) return res;
	}
	else if (key > subtree_root->key())  //�������ؼ��� > �������ڵ�ؼ���
	{
		bool res = InsertInSubTreeRecursive_(subtree_root->RightChild(), key, value);  //���������ڵ���Һ��ӽ��ִ�еݹ����
		if (!res) return res;
	}
	/*����ƽ��*/
	subtree_root->UpdateHeight();  //�����������ڵ�ĸ߶�
	subtree_root->UpdateBanlanceFactor();  //�����������ڵ��ƽ������
	Balance_(subtree_root);  //���������ڵ����ƽ��
	return true;
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::InsertSubTree_(AvlNode<TKey, TValue>*& subtree_root, TKey key, TValue value)
{
	/*�ظ�����������ݳ�ʼ��*/
	std::stack<AvlTree<TKey, TValue>*> backtrack_stack;
	bool res = CheckInsertLegalAndInitStack_(key, subtree_root, backtrack_stack);  //����Ƿ��ظ����룬������;���ĸ�����ջ
	if (!res)return res;
	/*��ʼ��������*/
	AvlNode<TKey, TValue>* new_node = new AvlNode<TKey, TValue>(key, value);
	if (!new_node) throw std::bad_alloc();
	/*������������*/
	if (backtrack_stack.empty())
	{
		subtree_root = new_node;
		return true;
	}
	/*�ǿ�����������*/
	AvlNode<TKey, TValue>* parent_node = backtrack_stack.top();  //ȡջ������Ϊ������ĸ��ڵ�(parent_node)
	if (key < parent_node->key()) parent_node->SetLeftChild(new_node);  //���������key < ���ڵ�key��������Ϊ���ڵ������
	else parent_node->SetRightChild(new_node);  //������Ϊ���ڵ���Һ���
	AvlNode<TKey, TValue>* balanced_node = this->InsertionBalanceByStack_(backtrack_stack);  //�Ի���ջ�ڵĽ����ƽ�⣬�������յ�ƽ����balanced_node
	/*����ջ���������Ĳ��䴦��*/
	if (backtrack_stack.empty()) subtree_root = balanced_node;  //�������ջΪ�գ���balanced_nodeΪ���µ��������ڵ�
	else
	{
		AvlNode<TKey, TValue>* stack_top_node = backtrack_stack.top();  //ȡ����ջջ��
		if (stack_top_node->key() > balanced_node->key()) stack_top_node->SetLeftChild(balanced_node);  //���ջ�����key > ƽ���key����ƽ���Ϊջ����������
		else stack_top_node->SetRightChild(balanced_node);  //���ջ�����key < ƽ���key����ƽ���Ϊջ�������Һ���
	}
	return true;
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::RemoveInSubTreeRecursive_(AvlNode<TKey, TValue>*& subtree_root, TKey key)
{
	/*����������*/
	if (!subtree_root) return false;
	/*ִ�еݹ�*/
	if (key < subtree_root->key())  //�����ɾ��key < �������ڵ�key
	{
		bool res = RemoveInSubTreeRecursive_(subtree_root->LeftChild(), key);  //�������ڵ����ӣ��ݹ�ִ��
		if (!res) return false;
	}
	else if (key > subtree_root->key())  //�����ɾ��key > �������ڵ�key
	{
		bool res = RemoveInSubTreeRecursive_(subtree_root->RightChild(), key);  //�������ڵ��Һ��ӣ��ݹ�ִ��
		if (!res) return false;
	}
	else  //�����ɾ��key = �������ڵ�key
	{ 
		if (!subtree_root->LeftChild() && !subtree_root->RightChild())  //������ڵ�û�����Һ���
		{
			delete subtree_root;
			subtree_root = nullptr;
			return true;
		}
		else if (!subtree_root->LeftChild())  //�������Ϊ��
		{
			AvlNode<TKey, TValue>* temp = subtree_root;
			subtree_root = subtree_root->RightChild();  //���ڵ�ָ���Һ���
			delete temp;
		}
		else if (!subtree_root->RightChild())  //����Һ���Ϊ��
		{
			AvlNode<TKey, TValue>* temp = subtree_root;
			subtree_root = subtree_root->LeftChild();  //���ڵ�ָ������
			delete temp;
		}
		else  //���ڵ�ͬʱ�������Һ���
		{
			AvlNode<TKey, TValue>* prev_node = this->PreviousNode_(subtree_root);  //prev_nodeָ�����������ǰһ�����(����������)
			subtree_root->SetKey(prev_node->key());  //prev_node�����ݸ����������ڵ�
			subtree_root->SetValue(prev_node->Value());
			bool res = RemoveInSubTreeRecursive_(subtree_root->LeftChild(), prev_node->key());
			if (!res) return false;
		}
	}
	/*ƽ��*/
	subtree_root->UpdateHeight();  
	subtree_root->UpdateBanlanceFactor();
	Balance_(subtree_root);
	return true;
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::RemoveInSubTree_(AvlNode<TKey, TValue>*& subtree_root, TKey key)
{
	/*�ҵ���ɾ����㲢��ʼ������ջ*/
	std::stack<AvlNode<TKey, TValue>*>backtrack_stack;
	AvlNode<TKey, TValue>* remove_node = FindRemoveNodeAndInitStack_(subtree_root, key, backtrack_stack);  //�ҵ���ɾ������ָ��
	if (remove_node == nullptr) return false;
	/*�滻��ɾ����㲢����;�����ջ*/
	if (remove_node->LeftChild() != nullptr && remove_node->RightChild() != nullptr)  //�����ɾ�����ͬʱ�������Һ���
	{
		backtrack_stack.push(remove_node);  //��ɾ�������ջ
		AvlNode<TKey, TValue>* cur = remove_node->LeftChild();  //��ʼ������ָ��cur��ָ���ɾ���������
		while (cur->RightChild() != nullptr)
		{
			backtrack_stack.push(cur);  //curָ��Ľ����ջ
			cur = cur->RightChild();    //curָ�������Һ���
		}
		remove_node->SetKey(cur->key());  //(��ʱcurָ�����滻���)
		remove_node->SetValue(cur->Value());  //��curָ�����key_��value_������ɾ�����
		remove_node = cur;  //remove_nodeָ��cur
	}
	else if (remove_node->LeftChild() != nullptr && remove_node->RightChild() == nullptr)  //��ɾ�����������ӣ��������Һ���
	{
		backtrack_stack.push(remove_node);  //��ɾ�������ջ
		AvlNode<TKey, TValue>* replace_node = remove_node->LeftChild();  //��ʼ������ָ��replace_node��ָ���ɾ���������
		remove_node->SetKey(replace_node->key());  //��replace_nodeָ�����key_��value_������ɾ�����
		remove_node->SetValue(replace_node->Value());
		remove_node = replace_node;  //remove_nodeָ��replace_node
	}
	else if (remove_node->LeftChild() == nullptr && remove_node->RightChild() != nullptr)  //��ɾ����㲻�������ӣ������Һ���
	{
		backtrack_stack.push(remove_node);  //��ɾ�������ջ
		AvlNode<TKey, TValue>* replace_node = remove_node->RightChild();  //��ʼ������ָ��replace_node��ָ���ɾ������Һ���
		remove_node->SetKey(replace_node->key());  //��replace_nodeָ�����key_��value_������ɾ�����
		remove_node->SetValue(replace_node->Value());
		remove_node = replace_node;  //remove_nodeָ��replace_node
	}
	else {}  //Ҷ�ӽ��
	/*����ΪҶ������Ĵ���*/
	if (backtrack_stack.empty())
	{
		subtree_root = nullptr;
		delete remove_node;
		remove_node = nullptr;
		return true;
	}
	/*ɾ���滻���remove_node*/
	AvlNode<TKey, TValue>* remove_node_parent = backtrack_stack.top();
	if (remove_node_parent->LeftChild() == remove_node)  //�����ɾ�������remove_node_parent������
	{
		if (remove_node->RightChild() != nullptr)  //�����ɾ���������Һ���
			remove_node_parent->SetLeftChild(remove_node->RightChild());   //remove_node_parent�����ӽ�㣬��Ϊremove_node���Һ���
		else   //�����ɾ����㲻�����Һ���
			remove_node_parent->SetLeftChild(remove_node->LeftChild());   //remove_node_parent�����ӽ�㣬��Ϊremove_node������
	}
	else if (remove_node_parent->RightChild() == remove_node)  //�����ɾ�������remove_node_parent���Һ���
	{
		if (remove_node->RightChild() != nullptr)  //�����ɾ���������Һ���
			remove_node_parent->SetRightChild(remove_node->RightChild());   //remove_node_parent���Һ��ӽ�㣬��Ϊremove_node���Һ���
		else   //�����ɾ����㲻�����Һ���
			remove_node_parent->SetRightChild(remove_node->LeftChild());   //remove_node_parent���Һ��ӽ�㣬��Ϊremove_node������
	}
	delete remove_node;
	remove_node = nullptr;
	/*ƽ��*/
	AvlNode<TKey, TValue>* balanced_node = RemovalBalanceByStack_(backtrack_stack);  //��backtrack_stack�еĸ�������ƽ�⣬����balanced_node���յ�ƽ���
	if (backtrack_stack.empty() == true) subtree_root = balanced_node;
	else
	{
		AvlNode<TKey, TValue>* balanced_node_parent = backtrack_stack.top();
		if (balanced_node_parent->key() > balanced_node->key())
			balanced_node_parent->SetLeftChild(balanced_node);
		else balanced_node_parent->SetRightChild(balanced_node);
	}
	return true;
}


template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::InsertionBalanceByStack_(std::stack<AvlNode<TKey, TValue>*>& backtrack_stack)
{
	AvlNode<TKey, TValue>* cur_parent_node = nullptr;  // ��������ʼ��cur_parent_node(��ǰ���ڵ�)ΪNULL

	while (!backtrack_stack.empty())
	{
		cur_parent_node = backtrack_stack.top();  //ȡջ��, ����cur_parent_node
		backtrack_stack.pop();  //ջ����ջ

		cur_parent_node->UpdateBanlanceFactor();  //����ƽ������
		if (cur_parent_node->BalanceFactor() == AvlNode<TKey, TValue>::BALANCED) break;
		if (cur_parent_node->BalanceFactor() == AvlNode<TKey, TValue>::RIGHT_HIGHER_1 || cur_parent_node->BalanceFactor() == AvlNode<TKey, TValue>::LEFT_HIGHER_1) {}
		else
		{
			this->Balance_(cur_parent_node);
			break;
		}
		cur_parent_node->UpdateHeight();  
	}
	return cur_parent_node;
}

template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::RemovalBalanceByStack_(std::stack<AvlNode<TKey, TValue>*>& backtrack_stack)
{
	AvlNode<TKey, TValue>* cur_parent_node = nullptr;  // ��������ʼ��cur_parent_node(��ǰ���ڵ�)ΪNULL

	while (!backtrack_stack.empty())
	{ 
		cur_parent_node = backtrack_stack.top();
		backtrack_stack.pop();

		int grand_parent_direction;   //����grand_parent_direction(�游����븸�ڵ�Ĺ�ϵ)
		if (!backtrack_stack.empty())
		{
			AvlNode<TKey, TValue>* cur_grand_node = backtrack_stack.top();  // ȡջ��, ����cur_grand_node(�游���)
			if (cur_grand_node->LeftChild() == cur_parent_node) grand_parent_direction = -1;  //if���ڵ����游�������ӣ�grand_parent_direction���ó�-1(��)
			else if(cur_grand_node->RightChild() == cur_parent_node) grand_parent_direction = 1;  //else if ���ڵ����游�������ӣ�grand_parent_direction���ó�1(��)
		}
		cur_parent_node->UpdateHeight();  //cur_parent_node���¸߶�
		cur_parent_node->UpdateBanlanceFactor();  //cur_parent_node����ƽ������
		this->Balance_(cur_parent_node);  //cur_parent_node����ƽ��
		if (!backtrack_stack.empty())
		{
			AvlNode<TKey, TValue>* cur_grand_node = backtrack_stack.top();
			if (grand_parent_direction == -1) cur_grand_node->SetLeftChild(cur_parent_node); //������ڵ����游�ڵ�����ӣ��Ѹ��ڵ����ó��游�ڵ������
			else cur_grand_node->SetRightChild(cur_parent_node);  //�Ѹ��ڵ����ó��游�ڵ������
		}
	}
	return cur_parent_node;
}

template<typename TKey, typename TValue>
inline void AvlTree<TKey, TValue>::Balance_(AvlNode<TKey, TValue>*& node)
{
	if (node->BalanceFactor() == AvlNode<TKey, TValue>::RIGHT_HIGHER_2)  //����������߶� > �������߶� 2�����
	{
		//����������࣬(�������߶�==�������߶�) or (�������߶� < �������߶� 1�����)
		if (node->RightChild()->BalanceFactor() != AvlNode<TKey, TValue>::LEFT_HIGHER_1)  this->LeftRotate_(node);  //����ת
		else this->RightLeftRotate_(node);  //�������࣬(�������߶� > �������߶� 1�����)��������ת
	}
	else if (node->BalanceFactor() == AvlNode<TKey, TValue>::LEFT_HIGHER_2)  //����������߶� > �������߶� 2�����
	{
		//����������࣬(�������߶�==�������߶�) or (�������߶� > �������߶� 1�����)
		if (node->LeftChild()->BalanceFactor() != AvlNode<TKey, TValue>::RIGHT_HIGHER_1)  this->RightRotate_(node);  //�ҵ���ת
		else this->LeftRightRotate_(node);  //�������࣬(�������߶� < �������߶� 1�����)��������ת
	}
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::LeftRotate_(AvlNode<TKey, TValue>*& node)
{
	/*ָ��pivot(��ת��)*/
	AvlNode<TKey, TValue>* pivot = node->RightChild();  //ȡ����Һ���Ϊpivot(��ת��)
	/*��ת*/
	node->SetRightChild(pivot->LeftChild());  //pivot�����ӣ���Ϊnode���Һ���
	pivot->SetLeftChild(node);  //node��Ϊpivot������
	/*�����߶�*/
	node->UpdateHeight();  //node���¸߶�
	pivot->UpdateHeight();  //pivot���¸߶�
	/*����ƽ������*/
	node->UpdateBanlanceFactor();  //node����ƽ������
	pivot->UpdateBanlanceFactor();  //pivot����ƽ������
	/*�޸�node*/
	node = pivot;

	return node->BalanceFactor();
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::RightRotate_(AvlNode<TKey, TValue>*& node)
{
	/*ָ��pivot(��ת��)*/
	AvlNode<TKey, TValue>* pivot = node->LeftChild();  //ȡ�������Ϊpivot(��ת��)
	/*��ת*/
	node->SetLeftChild(pivot->RightChild());  //pivot�ĺ��ӣ���Ϊnode������
	pivot->SetRightChild(node);  //node��Ϊpivot���Һ���
	/*�����߶�*/
	node->UpdateHeight();  //node���¸߶�
	pivot->UpdateHeight();  //pivot���¸߶�
	/*����ƽ������*/
	node->UpdateBanlanceFactor();  //node����ƽ������
	pivot->UpdateBanlanceFactor();  //pivot����ƽ������
	/*�޸�node*/
	node = pivot;

	return node->BalanceFactor();
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::LeftRightRotate_(AvlNode<TKey, TValue>*& node)
{
	this->LeftRotate_(node->LeftChild());  //��node������ִ��Left Rotate��������
	this->RightRotate_(node);  //��nodeִ��Right Rotate(����)
	return node->BalanceFactor();  //�������µ�ƽ������
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::RightLeftRotate_(AvlNode<TKey, TValue>*& node)
{
	this->RightRotate_(node->RightChild());  //��node������ִ��Right Rotate��������
	this->LeftRotate_(node);  //��nodeִ��Left Rotate(����)
	return node->BalanceFactor();  //�������µ�ƽ������
}

template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::SearchInSubTree_(AvlNode<TKey, TValue>* subtree_root, TKey key)
{
	if (subtree_root == nullptr) return nullptr;
	/*���εݹ�*/
	if (key < subtree_root->key()) return SearchInSubTree_(subtree_root->LeftChild(), key);
	else return SearchInSubTree_(subtree_root->RightChild(), key);
	return subtree_root;
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::Insert(TKey key, TValue value)
{  
	return this->InsertSubTree_(this->Root(), key, value);  // �Ը�������InsertInSubTree_, ���ؽ��
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::InsertRecursive(TKey key, TValue value)
{
	return this->InsertInSubTreeRecursive_(this->Root(), key, value);
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::Remove(TKey key)
{
	return this->RemoveInSubTree_(this->Root(), key);
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::RemoveRecursive(TKey key)
{
	return this->RemoveInSubTreeRecursive_(this->Root(), key);
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::Max(TValue& max_value)
{
	AvlNode<TKey, TValue>* node = this->MaxInSubTree_(this->Root());
	if(!node) return false;
	max_value = node->Value();
	return true;
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::Min(TValue& min_value)
{
	AvlNode<TKey, TValue>* node = this->MinInSubTree_(this->Root());
	if (!node) return false;
	min_value = node->Value();
	return true;
}

template<typename TKey, typename TValue>
inline void AvlTree<TKey, TValue>::Print(void(*visit)(AvlNode<TKey, TValue>*))
{
	this->PrintSubTreeRecursive_(this->root_, visit);
	std::cout << '\n';
}

template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::MinInSubTree_(AvlNode<TKey, TValue>* subtree_root) const
{
	if (subtree_root == nullptr) return nullptr;
	/*���ұ���*/
	AvlNode<TKey, TValue>* cur = subtree_root;
	while (cur && cur->LeftChild() != nullptr) cur = cur->LeftChild();
	return cur;
}

template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::MaxInSubTree_(AvlNode<TKey, TValue>* subtree_root) const
{
	if (subtree_root == nullptr) return nullptr;
	/*���ұ���*/
	AvlNode<TKey, TValue>* cur = subtree_root;
	while (cur && cur->RightChild() != nullptr) cur = cur->RightChild();
	return cur;
}

template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::PreviousNode_(AvlNode<TKey, TValue>* node)
{
	if (!node) return nullptr;
	/*���ҽ��*/
	AvlNode<TKey, TValue>* cur = node->LeftChild();
	while (cur && cur->RightChild()) cur = cur->RightChild();
	return cur;
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::HeightOfSubtreeRecursive_(AvlNode<TKey, TValue>* subtree_root)
{
	if (!subtree_root) return 0;
	/*���εݹ�*/
	int left_subtree_height = HeightOfSubtreeRecursive_(subtree_root->LeftChild());
	int right_subtree_height = HeightOfSubtreeRecursive_(subtree_root->RightChild());
	if (left_subtree_height < right_subtree_height) return right_subtree_height + 1;
	else return left_subtree_height + 1;
}

template<typename TKey, typename TValue>
inline void AvlTree<TKey, TValue>::PrintSubTreeRecursive_(AvlNode<TKey, TValue>* subtree_root, void(*Print)(AvlNode<TKey, TValue>*))
{
	if (subtree_root == nullptr) return;
	/*���εݹ�*/
	Print(subtree_root);
	if (subtree_root->LeftChild() == nullptr && subtree_root->RightChild() == nullptr) return;
	std::cout << "(";
	PrintSubTreeRecursive_(subtree_root->LeftChild(), Print);
	std::cout << ",";
	PrintSubTreeRecursive_(subtree_root->RightChild(), Print);
	std::cout << ")";
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::CheckInsertLegalAndInitStack_(TKey key, AvlNode<TKey, TValue>* subtree_root, std::stack<AvlNode<TKey, TValue>*>& backtrack_stack)
{
	AvlNode<TKey, TValue>* cur = subtree_root;
	while (cur != nullptr)
	{
		if (key == cur->key())return false;
		backtrack_stack.push(cur);
		if (key < cur->key) cur = cur->LeftChild();
		else cur = cur->RightChild();
	}
	return true;
}

template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::FindRemoveNodeAndInitStack_(AvlNode<TKey, TValue>* subtree_root, TKey key, std::stack<AvlNode<TKey, TValue>*>& backtrack_stack)
{
	AvlNode<TKey, TValue>* cur = subtree_root;
	while (cur != nullptr)
	{
		if (key == cur->key())break;
		backtrack_stack.push(cur);
		if (key < cur->key) cur = cur->LeftChild();
		else cur = cur->RightChild();
	}
	return cur;
}
