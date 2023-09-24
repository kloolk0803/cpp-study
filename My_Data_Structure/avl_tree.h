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

	/*获取左孩子结点*/
	AvlNode<TKey, TValue>*& LeftChild() { return left_child_; }
	/*设置左孩子结点*/
	void SetLeftChild(AvlNode<TKey, TValue>* node) { left_child_ = node; }
	/*获取右孩子结点*/
	AvlNode<TKey, TValue>*& RightChild() { return right_child_; }
	/*设置右孩子结点*/
	void SetRightChild(AvlNode<TKey, TValue>* node) { right_child_ = node; }
	/*获取关键字*/
	TKey key() { return key_; }
	/*设置关键字*/
	void SetKey(const TKey& key) { key_ = key; }
	/*获取值*/
	TValue Value() { return value_; }
	/*设置值*/
	void SetValue(const TValue& value) { value_ = value; }
	/*获取高度*/
	int Height() { return height_; }
	/*设置高度*/
	void SetHeight(int height) { height_ = height; }
	/*获取平衡因子*/
	int BalanceFactor() { return balance_factor_; }
	/*设置平衡因子*/
	void SetBalanceFactor(int balance_factor) { balance_factor_ = balance_factor; }
	/*更新高度*/
	void UpdateHeight()
	{
		int left_height = LeftChild() ? LeftChild()->Height() : 0;  //获取左子树高度
		int right_height = RightChild() > RightChild()->Height() :0;  //获取右子树高度
		height_ = (left_height > right_height ? left_height : right_height) + 1;  //取子树高度最大值
	}
	/*更新平衡因子*/
	void UpdateBanlanceFactor()
	{
		int left_height = LeftChild() ? LeftChild()->Height() : 0;  //获取左子树高度
		int right_height = RightChild() > RightChild()->Height() :0;  //获取右子树高度
		balance_factor_ = right_height - left_height;
	}

	static constexpr int RIGHT_HIGHER_2 = 2;  //左子树比右子树矮2
	static constexpr int RIGHT_HIGHER_1 = 1;  //左子树比右子树矮1
	static constexpr int BALANCED = 0;  //左右平衡
	static constexpr int LEFT_HIGHER_1 = -1;  //左子树比右子树高1
	static constexpr int LEFT_HIGHER_2 = -2;  //左子树比右子树高2

protected:
	TKey key_;  //关键字
	TValue value_;  //值
	AvlNode<TKey, TValue>* left_child_;  //左孩子结点(指针)
	AvlNode<TKey, TValue>* right_child_;  //右孩子结点(指针)
	int height_;  //高度
	int balance_factor_;  //平衡因子
};

template<typename TKey, typename TValue>
class AvlTree :public BinarySearchTree<TKey, TValue>
{
public:
	AvlTree() :root_(nullptr) {};
	/*获取根节点*/
	AvlNode<TKey, TValue>*& Root() { return root_; }
	/*设置根节点*/
	void SetRoot(AvlNode<TKey, TValue>* node) { root_ = node; }
	/*插入结点*/
	bool Insert(TKey key, TValue value);
	/*插入结点（递归）*/
	bool InsertRecursive(TKey key, TValue value);
	/*删除结点*/
	bool Remove(TKey key);
	/*删除结点（递归）*/
	bool RemoveRecursive(TKey key);
	/*获取高度*/
	int Height() { return root_->Height(); }
	/*获取高度（递归）*/
	int HeightRecursive() { return HeightOfSubtreeRecursive_(this->root_); }
	/*获取最大关键字对应的值*/
	bool Max(TValue& max_value);
	/*获取最小关键字对应的值*/
	bool Min(TValue& min_value);
	/*搜索*/
	AvlNode<TKey, TValue>* Search(TKey key) { return this->SearchInSubTree_(this->root_, key); }
	/*打印*/
	void Print(void(*visit)(AvlNode<TKey, TValue>*));

protected:
	/*子树插入结点(递归)*/
	bool InsertInSubTreeRecursive_(AvlNode<TKey, TValue>*& subtree_root, TKey key, TValue value);
	/*子树插入结点*/
	bool InsertSubTree_(AvlNode<TKey, TValue>*& subtree_root, TKey key, TValue value);
	/*子树删除结点(递归)*/
	bool RemoveInSubTreeRecursive_(AvlNode<TKey, TValue>*& subtree_root, TKey key);
	/*子树删除结点*/
	bool RemoveInSubTree_(AvlNode<TKey, TValue>*& subtree_root, TKey key);
	/*插入动作平衡(by回溯栈)*/
	AvlNode<TKey, TValue>* InsertionBalanceByStack_(std::stack<AvlNode<TKey, TValue>*>& backtrack_stack);
	/*删除动作平衡(by回溯栈)*/
	AvlNode<TKey, TValue>* RemovalBalanceByStack_(std::stack<AvlNode<TKey, TValue>*>& backtrack_stack);
	/*平衡*/
	void Balance_(AvlNode<TKey, TValue>*& node);
	 
	/*左单旋转(left Rotation)*/
	int LeftRotate_(AvlNode<TKey, TValue>*& node);
	/*右单旋转(left Rotation)*/
	int RightRotate_(AvlNode<TKey, TValue>*& node);
	/*先左后右双旋转(left right Rotation)*/
	int LeftRightRotate_(AvlNode<TKey, TValue>*& node);
	/*先右后左双旋转(right left Rotation)*/
	int RightLeftRotate_(AvlNode<TKey, TValue>*& node);

	/*子树搜索(递归)*/
	AvlNode<TKey, TValue>* SearchInSubTree_(AvlNode<TKey, TValue>* subtree_root, TKey key);

	/*获取(子树中)关键字最小结点*/
	AvlNode<TKey, TValue>* MinInSubTree_(AvlNode<TKey, TValue>* subtree_root) const;
	/*获取(子树中)关键字最大结点*/
	AvlNode<TKey, TValue>* MaxInSubTree_(AvlNode<TKey, TValue>* subtree_root) const;
	
	/*获取结点的(中序)前一结点*/
	AvlNode<TKey, TValue>* PreviousNode_(AvlNode<TKey, TValue>* node);

	/*子树高度*/
	int HeightOfSubtreeRecursive_(AvlNode<TKey, TValue>* subtree_root);

	/*子树打印(递归)*/
	void PrintSubTreeRecursive_(AvlNode<TKey, TValue>* subtree_root, void(*Print)(AvlNode<TKey, TValue>*));

	/*检查插入合法性并初始化回溯栈*/
	bool CheckInsertLegalAndInitStack_(TKey key, AvlNode<TKey, TValue>* subtree_root, std::stack<AvlNode<TKey, TValue>*>& backtrack_stack);

	/*定位删除结点并初始化回溯栈*/
	AvlNode<TKey, TValue>* FindRemoveNodeAndInitStack_(AvlNode<TKey, TValue>* subtree_root, TKey key, std::stack<AvlNode<TKey, TValue>*>& backtrack_stack);

	AvlNode<TKey, TValue>* root_;  //根节点
};

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::InsertInSubTreeRecursive_(AvlNode<TKey, TValue>*& subtree_root, TKey key, TValue value)
{
	/*空子树插入结点*/
	if (!subtree_root)
	{
		subtree_root = new AvlNode<TKey, TValue>(key, value);  
		if (!subtree_root) throw std::bad_alloc(); 
		return true;
	}
	/*重复插入操作*/
	if (key == subtree_root->key()) return false;
	/*分治递归*/
	if (key < subtree_root->key())  //如果插入关键字 < 子树根节点关键字
	{
		bool res = InsertInSubTreeRecursive_(subtree_root->LeftChild(), key, value);  //对子树根节点的左孩子结点执行递归插入
		if (!res) return res;
	}
	else if (key > subtree_root->key())  //如果插入关键字 > 子树根节点关键字
	{
		bool res = InsertInSubTreeRecursive_(subtree_root->RightChild(), key, value);  //对子树根节点的右孩子结点执行递归插入
		if (!res) return res;
	}
	/*调整平衡*/
	subtree_root->UpdateHeight();  //更新子树根节点的高度
	subtree_root->UpdateBanlanceFactor();  //更新子树根节点的平衡因子
	Balance_(subtree_root);  //对子树根节点进行平衡
	return true;
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::InsertSubTree_(AvlNode<TKey, TValue>*& subtree_root, TKey key, TValue value)
{
	/*重复插入检查与回溯初始化*/
	std::stack<AvlTree<TKey, TValue>*> backtrack_stack;
	bool res = CheckInsertLegalAndInitStack_(key, subtree_root, backtrack_stack);  //检查是否重复插入，并将沿途检查的各点入栈
	if (!res)return res;
	/*初始化插入结点*/
	AvlNode<TKey, TValue>* new_node = new AvlNode<TKey, TValue>(key, value);
	if (!new_node) throw std::bad_alloc();
	/*空子树插入结点*/
	if (backtrack_stack.empty())
	{
		subtree_root = new_node;
		return true;
	}
	/*非空子树插入结点*/
	AvlNode<TKey, TValue>* parent_node = backtrack_stack.top();  //取栈顶，作为插入结点的父节点(parent_node)
	if (key < parent_node->key()) parent_node->SetLeftChild(new_node);  //如果插入结点key < 父节点key，插入结点为父节点的左孩子
	else parent_node->SetRightChild(new_node);  //插入结点为父节点的右孩子
	AvlNode<TKey, TValue>* balanced_node = this->InsertionBalanceByStack_(backtrack_stack);  //对回溯栈内的结点做平衡，返回最终的平衡结点balanced_node
	/*回溯栈处理结束后的补充处理*/
	if (backtrack_stack.empty()) subtree_root = balanced_node;  //如果回溯栈为空，则balanced_node为最新的子树根节点
	else
	{
		AvlNode<TKey, TValue>* stack_top_node = backtrack_stack.top();  //取回溯栈栈顶
		if (stack_top_node->key() > balanced_node->key()) stack_top_node->SetLeftChild(balanced_node);  //如果栈顶结点key > 平衡点key，则平衡点为栈顶结点的左孩子
		else stack_top_node->SetRightChild(balanced_node);  //如果栈顶结点key < 平衡点key，则平衡点为栈顶结点的右孩子
	}
	return true;
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::RemoveInSubTreeRecursive_(AvlNode<TKey, TValue>*& subtree_root, TKey key)
{
	/*空子树处理*/
	if (!subtree_root) return false;
	/*执行递归*/
	if (key < subtree_root->key())  //如果待删除key < 子树根节点key
	{
		bool res = RemoveInSubTreeRecursive_(subtree_root->LeftChild(), key);  //子树根节点左孩子，递归执行
		if (!res) return false;
	}
	else if (key > subtree_root->key())  //如果待删除key > 子树根节点key
	{
		bool res = RemoveInSubTreeRecursive_(subtree_root->RightChild(), key);  //子树根节点右孩子，递归执行
		if (!res) return false;
	}
	else  //如果待删除key = 子树根节点key
	{ 
		if (!subtree_root->LeftChild() && !subtree_root->RightChild())  //如果根节点没有左右孩子
		{
			delete subtree_root;
			subtree_root = nullptr;
			return true;
		}
		else if (!subtree_root->LeftChild())  //如果左孩子为空
		{
			AvlNode<TKey, TValue>* temp = subtree_root;
			subtree_root = subtree_root->RightChild();  //根节点指向右孩子
			delete temp;
		}
		else if (!subtree_root->RightChild())  //如果右孩子为空
		{
			AvlNode<TKey, TValue>* temp = subtree_root;
			subtree_root = subtree_root->LeftChild();  //根节点指向左孩子
			delete temp;
		}
		else  //根节点同时存在左右孩子
		{
			AvlNode<TKey, TValue>* prev_node = this->PreviousNode_(subtree_root);  //prev_node指向根结点中序的前一个结点(在左子树内)
			subtree_root->SetKey(prev_node->key());  //prev_node的数据赋给子树根节点
			subtree_root->SetValue(prev_node->Value());
			bool res = RemoveInSubTreeRecursive_(subtree_root->LeftChild(), prev_node->key());
			if (!res) return false;
		}
	}
	/*平衡*/
	subtree_root->UpdateHeight();  
	subtree_root->UpdateBanlanceFactor();
	Balance_(subtree_root);
	return true;
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::RemoveInSubTree_(AvlNode<TKey, TValue>*& subtree_root, TKey key)
{
	/*找到待删除结点并初始化回溯栈*/
	std::stack<AvlNode<TKey, TValue>*>backtrack_stack;
	AvlNode<TKey, TValue>* remove_node = FindRemoveNodeAndInitStack_(subtree_root, key, backtrack_stack);  //找到待删除结点的指针
	if (remove_node == nullptr) return false;
	/*替换待删除结点并将沿途结点入栈*/
	if (remove_node->LeftChild() != nullptr && remove_node->RightChild() != nullptr)  //如果待删除结点同时存在左右孩子
	{
		backtrack_stack.push(remove_node);  //待删除结点入栈
		AvlNode<TKey, TValue>* cur = remove_node->LeftChild();  //初始化遍历指针cur，指向待删除结点左孩子
		while (cur->RightChild() != nullptr)
		{
			backtrack_stack.push(cur);  //cur指向的结点入栈
			cur = cur->RightChild();    //cur指向自身右孩子
		}
		remove_node->SetKey(cur->key());  //(此时cur指向了替换结点)
		remove_node->SetValue(cur->Value());  //将cur指向结点的key_和value_赋给待删除结点
		remove_node = cur;  //remove_node指向cur
	}
	else if (remove_node->LeftChild() != nullptr && remove_node->RightChild() == nullptr)  //待删除结点存在左孩子，不存在右孩子
	{
		backtrack_stack.push(remove_node);  //待删除结点入栈
		AvlNode<TKey, TValue>* replace_node = remove_node->LeftChild();  //初始化遍历指针replace_node，指向待删除结点左孩子
		remove_node->SetKey(replace_node->key());  //将replace_node指向结点的key_和value_赋给待删除结点
		remove_node->SetValue(replace_node->Value());
		remove_node = replace_node;  //remove_node指向replace_node
	}
	else if (remove_node->LeftChild() == nullptr && remove_node->RightChild() != nullptr)  //待删除结点不存在左孩子，存在右孩子
	{
		backtrack_stack.push(remove_node);  //待删除结点入栈
		AvlNode<TKey, TValue>* replace_node = remove_node->RightChild();  //初始化遍历指针replace_node，指向待删除结点右孩子
		remove_node->SetKey(replace_node->key());  //将replace_node指向结点的key_和value_赋给待删除结点
		remove_node->SetValue(replace_node->Value());
		remove_node = replace_node;  //remove_node指向replace_node
	}
	else {}  //叶子结点
	/*子树为叶子情况的处理*/
	if (backtrack_stack.empty())
	{
		subtree_root = nullptr;
		delete remove_node;
		remove_node = nullptr;
		return true;
	}
	/*删除替换后的remove_node*/
	AvlNode<TKey, TValue>* remove_node_parent = backtrack_stack.top();
	if (remove_node_parent->LeftChild() == remove_node)  //如果待删除结点是remove_node_parent的左孩子
	{
		if (remove_node->RightChild() != nullptr)  //如果待删除结点存在右孩子
			remove_node_parent->SetLeftChild(remove_node->RightChild());   //remove_node_parent的左孩子结点，设为remove_node的右孩子
		else   //如果待删除结点不存在右孩子
			remove_node_parent->SetLeftChild(remove_node->LeftChild());   //remove_node_parent的左孩子结点，设为remove_node的左孩子
	}
	else if (remove_node_parent->RightChild() == remove_node)  //如果待删除结点是remove_node_parent的右孩子
	{
		if (remove_node->RightChild() != nullptr)  //如果待删除结点存在右孩子
			remove_node_parent->SetRightChild(remove_node->RightChild());   //remove_node_parent的右孩子结点，设为remove_node的右孩子
		else   //如果待删除结点不存在右孩子
			remove_node_parent->SetRightChild(remove_node->LeftChild());   //remove_node_parent的右孩子结点，设为remove_node的左孩子
	}
	delete remove_node;
	remove_node = nullptr;
	/*平衡*/
	AvlNode<TKey, TValue>* balanced_node = RemovalBalanceByStack_(backtrack_stack);  //对backtrack_stack中的各结点进行平衡，返回balanced_node最终的平衡点
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
	AvlNode<TKey, TValue>* cur_parent_node = nullptr;  // 声明并初始化cur_parent_node(当前父节点)为NULL

	while (!backtrack_stack.empty())
	{
		cur_parent_node = backtrack_stack.top();  //取栈顶, 赋给cur_parent_node
		backtrack_stack.pop();  //栈顶出栈

		cur_parent_node->UpdateBanlanceFactor();  //更新平衡因子
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
	AvlNode<TKey, TValue>* cur_parent_node = nullptr;  // 声明并初始化cur_parent_node(当前父节点)为NULL

	while (!backtrack_stack.empty())
	{ 
		cur_parent_node = backtrack_stack.top();
		backtrack_stack.pop();

		int grand_parent_direction;   //声明grand_parent_direction(祖父结点与父节点的关系)
		if (!backtrack_stack.empty())
		{
			AvlNode<TKey, TValue>* cur_grand_node = backtrack_stack.top();  // 取栈顶, 赋给cur_grand_node(祖父结点)
			if (cur_grand_node->LeftChild() == cur_parent_node) grand_parent_direction = -1;  //if父节点是祖父结点的左孩子，grand_parent_direction设置成-1(左)
			else if(cur_grand_node->RightChild() == cur_parent_node) grand_parent_direction = 1;  //else if 父节点是祖父结点的左孩子，grand_parent_direction设置成1(右)
		}
		cur_parent_node->UpdateHeight();  //cur_parent_node更新高度
		cur_parent_node->UpdateBanlanceFactor();  //cur_parent_node更新平衡因子
		this->Balance_(cur_parent_node);  //cur_parent_node进行平衡
		if (!backtrack_stack.empty())
		{
			AvlNode<TKey, TValue>* cur_grand_node = backtrack_stack.top();
			if (grand_parent_direction == -1) cur_grand_node->SetLeftChild(cur_parent_node); //如果父节点是祖父节点的左孩子，把父节点设置成祖父节点的左孩子
			else cur_grand_node->SetRightChild(cur_parent_node);  //把父节点设置成祖父节点的左孩子
		}
	}
	return cur_parent_node;
}

template<typename TKey, typename TValue>
inline void AvlTree<TKey, TValue>::Balance_(AvlNode<TKey, TValue>*& node)
{
	if (node->BalanceFactor() == AvlNode<TKey, TValue>::RIGHT_HIGHER_2)  //如果右子树高度 > 左子树高度 2个结点
	{
		//如果右子树侧，(左子树高度==右子树高度) or (左子树高度 < 右子树高度 1个结点)
		if (node->RightChild()->BalanceFactor() != AvlNode<TKey, TValue>::LEFT_HIGHER_1)  this->LeftRotate_(node);  //左单旋转
		else this->RightLeftRotate_(node);  //右子树侧，(左子树高度 > 右子树高度 1个结点)，右左旋转
	}
	else if (node->BalanceFactor() == AvlNode<TKey, TValue>::LEFT_HIGHER_2)  //如果左子树高度 > 右子树高度 2个结点
	{
		//如果左子树侧，(左子树高度==右子树高度) or (左子树高度 > 右子树高度 1个结点)
		if (node->LeftChild()->BalanceFactor() != AvlNode<TKey, TValue>::RIGHT_HIGHER_1)  this->RightRotate_(node);  //右单旋转
		else this->LeftRightRotate_(node);  //左子树侧，(左子树高度 < 右子树高度 1个结点)，左右旋转
	}
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::LeftRotate_(AvlNode<TKey, TValue>*& node)
{
	/*指定pivot(旋转轴)*/
	AvlNode<TKey, TValue>* pivot = node->RightChild();  //取结点右孩子为pivot(旋转轴)
	/*旋转*/
	node->SetRightChild(pivot->LeftChild());  //pivot的左孩子，改为node的右孩子
	pivot->SetLeftChild(node);  //node改为pivot的左孩子
	/*调整高度*/
	node->UpdateHeight();  //node更新高度
	pivot->UpdateHeight();  //pivot更新高度
	/*调整平衡因子*/
	node->UpdateBanlanceFactor();  //node更新平衡因子
	pivot->UpdateBanlanceFactor();  //pivot更新平衡因子
	/*修改node*/
	node = pivot;

	return node->BalanceFactor();
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::RightRotate_(AvlNode<TKey, TValue>*& node)
{
	/*指定pivot(旋转轴)*/
	AvlNode<TKey, TValue>* pivot = node->LeftChild();  //取结点左孩子为pivot(旋转轴)
	/*旋转*/
	node->SetLeftChild(pivot->RightChild());  //pivot的孩子，改为node的左孩子
	pivot->SetRightChild(node);  //node改为pivot的右孩子
	/*调整高度*/
	node->UpdateHeight();  //node更新高度
	pivot->UpdateHeight();  //pivot更新高度
	/*调整平衡因子*/
	node->UpdateBanlanceFactor();  //node更新平衡因子
	pivot->UpdateBanlanceFactor();  //pivot更新平衡因子
	/*修改node*/
	node = pivot;

	return node->BalanceFactor();
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::LeftRightRotate_(AvlNode<TKey, TValue>*& node)
{
	this->LeftRotate_(node->LeftChild());  //对node的左孩子执行Left Rotate（左旋）
	this->RightRotate_(node);  //对node执行Right Rotate(右旋)
	return node->BalanceFactor();  //返回最新的平衡因子
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::RightLeftRotate_(AvlNode<TKey, TValue>*& node)
{
	this->RightRotate_(node->RightChild());  //对node的左孩子执行Right Rotate（右旋）
	this->LeftRotate_(node);  //对node执行Left Rotate(左旋)
	return node->BalanceFactor();  //返回最新的平衡因子
}

template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::SearchInSubTree_(AvlNode<TKey, TValue>* subtree_root, TKey key)
{
	if (subtree_root == nullptr) return nullptr;
	/*分治递归*/
	if (key < subtree_root->key()) return SearchInSubTree_(subtree_root->LeftChild(), key);
	else return SearchInSubTree_(subtree_root->RightChild(), key);
	return subtree_root;
}

template<typename TKey, typename TValue>
inline bool AvlTree<TKey, TValue>::Insert(TKey key, TValue value)
{  
	return this->InsertSubTree_(this->Root(), key, value);  // 对根结点调用InsertInSubTree_, 返回结果
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
	/*向右遍历*/
	AvlNode<TKey, TValue>* cur = subtree_root;
	while (cur && cur->LeftChild() != nullptr) cur = cur->LeftChild();
	return cur;
}

template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::MaxInSubTree_(AvlNode<TKey, TValue>* subtree_root) const
{
	if (subtree_root == nullptr) return nullptr;
	/*向右遍历*/
	AvlNode<TKey, TValue>* cur = subtree_root;
	while (cur && cur->RightChild() != nullptr) cur = cur->RightChild();
	return cur;
}

template<typename TKey, typename TValue>
inline AvlNode<TKey, TValue>* AvlTree<TKey, TValue>::PreviousNode_(AvlNode<TKey, TValue>* node)
{
	if (!node) return nullptr;
	/*查找结点*/
	AvlNode<TKey, TValue>* cur = node->LeftChild();
	while (cur && cur->RightChild()) cur = cur->RightChild();
	return cur;
}

template<typename TKey, typename TValue>
inline int AvlTree<TKey, TValue>::HeightOfSubtreeRecursive_(AvlNode<TKey, TValue>* subtree_root)
{
	if (!subtree_root) return 0;
	/*分治递归*/
	int left_subtree_height = HeightOfSubtreeRecursive_(subtree_root->LeftChild());
	int right_subtree_height = HeightOfSubtreeRecursive_(subtree_root->RightChild());
	if (left_subtree_height < right_subtree_height) return right_subtree_height + 1;
	else return left_subtree_height + 1;
}

template<typename TKey, typename TValue>
inline void AvlTree<TKey, TValue>::PrintSubTreeRecursive_(AvlNode<TKey, TValue>* subtree_root, void(*Print)(AvlNode<TKey, TValue>*))
{
	if (subtree_root == nullptr) return;
	/*分治递归*/
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
