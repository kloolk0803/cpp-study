#pragma once

#include <iostream>
#include <stack>
#include <queue>

template<typename T>
struct BinaryTreeNode
{
	BinaryTreeNode() :left_child(nullptr), right_child(nullptr) {};
	explicit BinaryTreeNode(T data, BinaryTreeNode<T>* left_child = nullptr, BinaryTreeNode<T>* right_child = nullptr) :
		data(data), left_child(left_child), right_child(right_child) {};

	T data;  /*数据项*/
	BinaryTreeNode<T>* left_child;  /*左孩子结点*/
	BinaryTreeNode<T>* right_child;  /*右孩子结点*/
};

template<typename T>  //后序遍历回溯栈结点模版
struct PostorderBacktrackStackNode
{
	explicit PostorderBacktrackStackNode(BinaryTreeNode<T>* node = nullptr) :node(node), tag(LEFT_BACK_TRACKING) {};

	BinaryTreeNode<T>* node;  /*二叉树结点指针*/
	enum 
	{
		LEFT_BACK_TRACKING = 0,
		RIGHT_BACK_TRACKING
	}tag;
};

template<typename T>class BinaryTree;
/*判断两棵树相同*/
template<typename T>
bool operator==(const BinaryTree<T>& binary_tree_1, const BinaryTree<T>& binary_tree_2);
/*输出二叉树*/
template<typename T>
std::ostream& operator<<(std::ostream& out, BinaryTree<T>& binary_tree);

template<typename T>
class BinaryTree
{
public:
	BinaryTree() :root_(nullptr) {};
	explicit BinaryTree(const T& data) { this->InsertInSubtreeRecursive_(this->root_, data); }
	BinaryTree(const BinaryTree<T>& src__binary_tree);
	~BinaryTree() { this->DeleteSubtreeRecursive_(this->root_); }

	/*获取根节点*/
	BinaryTreeNode<T>* Root()const { return this->root_; }
	/*判断是否是空树*/
	bool IsEmpty() { return this->root_ == nullptr; }
	/*获取父节点*/
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* node) const {
		return (this->root_ == nullptr) || (this->root_ == node) ? nullptr : this->GetParentInSubtreeRecursive_(this->root_, node);
	}
	/*获取高度*/
	int Height() { return this->HeightOfSubtreeRecursive_(this->root_); }
	/*获取结点数*/
	int Size() { return this->SizeOfSubTreeRecursive_(this->root_); }
	/*插入结点（递归）*/
	bool InsertRecursive(const T& data) { return this->InsertInSubtreeRecursive_(this->root_, data); }
	/*是否存在数据*/
	bool Exist(T data) { return this->ExistInSubTree_(this->root_, data); }
	/*前序遍历（递归）*/
	void PreorderTraversalRecursive(void(*visit)(BinaryTreeNode<T>*)) { this->PreorderTraversalOfSubtreeRecursive_(this->root_, visit); }
	/*前序遍历*/
	void PreorderTraversal(void(*visit)(BinaryTreeNode<T>*)) { this->PreorderTraversalOfSubtree_(this->root_, visit); }
	/*中序遍历（递归）*/
	void InorderTraversalRecursive(void(*visit)(BinaryTreeNode<T>*)) { this->InorderTraversalOfSubtreeRecursive_(this->root_, visit); }
	/*中序遍历*/
	void InorderTraversal(void(*visit)(BinaryTreeNode<T>*)) { this->InorderTraversalOfSubtree_(this->root_, visit); }
	/*后序遍历（递归）*/
	void PostorderTraversalRecursive(void(*visit)(BinaryTreeNode<T>*)) { this->PostorderTraversalOfSubtreeRecursive_(this->root_, visit); }
	/*后序遍历*/
	void PostorderTraversal(void(*visit)(BinaryTreeNode<T>*)) { this->PostorderTraversalOfSubtree_(this->root_, visit); }
	/*层序遍历*/
	void LevelOrderTraversal(void(*visit)(BinaryTreeNode<T>*)) { this->LevelOrderTraversalOfSubtree_(this->root_, visit); }
	/*建树*/
	bool CreateByPreorderAndInorderList(T* preorder_list, T* inorder_list, int length){
		return this->CreateSubtreeByPreorderAndInorderList_(preorder_list, inorder_list, length, this->root_);
	}
	/*打印*/
	void Print() { this->PrintSubTreeRecursive_(this->root_); }

	/*判断两棵树是否相同（递归）*/
	static bool Equal(BinaryTreeNode<T>* root1, BinaryTreeNode<T>* root2);

protected:
	BinaryTreeNode<T>* root_;  /*根节点*/

	/*子树插入节点（递归）*/
	bool InsertInSubtreeRecursive_(BinaryTreeNode<T>*& subtree_root, const T& data);
	/*子树删除*/
	void DeleteSubtreeRecursive_(BinaryTreeNode<T>*& subtree_root);
	/*子树是否存在数据（递归）*/
	bool ExistInSubTree_(BinaryTreeNode<T>* subtree_root, T data) const;
	/*复制（递归）*/
	bool DuplicateSubTreeRecursive_(BinaryTreeNode<T>* src_subtree_root, BinaryTreeNode<T>*& target_subtree_root);
	/*求子树的高度（递归）*/
	int HeightOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root) const;
	/*求子树的Size（递归）*/
	int SizeOfSubTreeRecursive_(BinaryTreeNode<T>* subtree_root) const;
	/*子树获取结点的父节点*/
	BinaryTreeNode<T>* GetParentInSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, BinaryTreeNode<T>* node) const;

	/*子树前序遍历（递归）*/
	void PreorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*子树前序遍历*/
	void PreorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*子树中序遍历（递归）*/
	void InorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*子树中序遍历*/
	void InorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*子树后序遍历（递归）*/
	void PostorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*子树后序遍历*/
	void PostorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*子树层序遍历*/
	void LevelOrderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*子树打印*/
	void PrintSubTreeRecursive_(BinaryTreeNode<T>* subtree_root);

	/*使用前序遍历和中序遍历结果，创建子树（递归）*/
	bool CreateSubtreeByPreorderAndInorderList_(T* preorder_sub_list, T* inorder_sub_list, int length, BinaryTreeNode<T>*& subtree_root);

	/*判断两棵树是否相同*/
	friend bool operator== <>(const BinaryTree<T>& binary_tree_1, const BinaryTree<T>& binary_tree_2);
	/*输出二叉树*/
	friend std::ostream& operator<< <>(std::ostream& out, BinaryTree<T>& binary_tree);
};

template<typename T>
inline BinaryTree<T>::BinaryTree(const BinaryTree<T>& src__binary_tree)
{
	if (!DuplicateSubTreeRecursive_(src__binary_tree.Root(), this->root_))
		throw std::logic_error("DuplicateSubTreeRecursive_error");
}

template<typename T>
inline bool BinaryTree<T>::Equal(BinaryTreeNode<T>* root1, BinaryTreeNode<T>* root2)
{
	if (root1 == nullptr && root2 == nullptr) return true;
	/*递归*/
	if (root1 != nullptr && root2 != nullptr && root1->data == root2->data 
		&& BinaryTree<T>::Equal(root1->left_child, root2->left_child)
		&& BinaryTree<T>::Equal(root1->right_child, root2->right_child))
	{
		return true;
	}
	return false;
}

template<typename T>
inline bool BinaryTree<T>::InsertInSubtreeRecursive_(BinaryTreeNode<T>*& subtree_root, const T& data)
{
	/*空子树处理*/
	if (subtree_root == nullptr)
	{
		subtree_root = new BinaryTreeNode<T>(data);
		if (!subtree_root)throw std::bad_alloc();
		return true;
	}
	/*分治递归*/
	int left_subtree_height = HeightOfSubtreeRecursive_(subtree_root->left_child);  /*计算left_subtree_height（左子树高度）*/
	int rigth_subtree_height = HeightOfSubtreeRecursive_(subtree_root->right_child);  /*计算rigth_subtree_height（右子树高度）*/
	if (left_subtree_height > rigth_subtree_height)  /*如果left_subtree_height > rigth_subtree_height*/
	{
		if (!(InsertInSubtreeRecursive_(subtree_root->right_child, data)))   /*递归调用InsertInSubtreeRecursive_*/
			return false;
	}
	else   /*如果left_subtree_height < rigth_subtree_height*/
	{
		if (!(InsertInSubtreeRecursive_(subtree_root->left_child, data)))    /*递归调用InsertInSubtreeRecursive_*/
			return false;
	}
	return true;
}

template<typename T>
inline void BinaryTree<T>::DeleteSubtreeRecursive_(BinaryTreeNode<T>*& subtree_root)
{
	if (subtree_root == nullptr)return;
	/*分治递归*/
	this->DeleteSubtreeRecursive_(subtree_root->left_child);   /*左子树递归删除*/
	this->DeleteSubtreeRecursive_(subtree_root->right_child);  /*右子树递归删除*/
	/*删除子树根节点*/
	delete subtree_root;
	subtree_root = nullptr;
}

template<typename T>
inline bool BinaryTree<T>::ExistInSubTree_(BinaryTreeNode<T>* subtree_root, T data) const
{
	/*空树处理*/
	if (subtree_root == nullptr) return false;
	/*存在条件处理*/
	if (subtree_root->data == data) return true;
	/*分治递归*/
	if (ExistInSubTree_(subtree_root->left_child, data)) return true;   /*左子树递归*/
	if (ExistInSubTree_(subtree_root->right_child, data)) return true;  /*右子树递归*/
	return false;
}

template<typename T>
inline bool BinaryTree<T>::DuplicateSubTreeRecursive_(BinaryTreeNode<T>* src_subtree_root, BinaryTreeNode<T>*& target_subtree_root)
{
	/*空树处理*/
	if (src_subtree_root == nullptr)
	{
		target_subtree_root = nullptr;
		return true;
	}
	/*目标子树根节点处理*/
	target_subtree_root = new BinaryTreeNode<T>(src_subtree_root->data);
	if (!target_subtree_root)return false;
	/*分治递归*/
	if (!DuplicateSubTreeRecursive_(src_subtree_root->left_child, target_subtree_root->left_child)) return false;    /*左子树递归复制*/
	if (!DuplicateSubTreeRecursive_(src_subtree_root->right_child, target_subtree_root->right_child)) return false;  /*右子树递归复制*/
	return true;
}

template<typename T>
inline int BinaryTree<T>::HeightOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root) const
{
	/*空树处理*/
	if (subtree_root == nullptr) return 0;
	/*分治递归*/
	int left_subtree_height = HeightOfSubtreeRecursive_(subtree_root->left_child);  /*左子树递归，得到left_subtree_height(左子树高度)*/
	int right_subtree_height = HeightOfSubtreeRecursive_(subtree_root->right_child);  /*右子树递归，得到right_subtree_height(右子树高度)*/
	int subtree_height = (left_subtree_height < right_subtree_height ? right_subtree_height : left_subtree_height) + 1;
	return subtree_height;
}

template<typename T>
inline int BinaryTree<T>::SizeOfSubTreeRecursive_(BinaryTreeNode<T>* subtree_root) const
{
	/*空树处理*/
	if (subtree_root == nullptr) return 0;
	/*分治递归*/
	int left_subtree_size = SizeOfSubTreeRecursive_(subtree_root->left_child);  /*左子树递归，得到left_subtree_height(左子树高度)*/
	int right_subtree_size = SizeOfSubTreeRecursive_(subtree_root->right_child);  /*右子树递归，得到right_subtree_height(右子树高度)*/
	int subtree_size = 1 + left_subtree_size + right_subtree_size;
	return subtree_size;
}

template<typename T>
inline BinaryTreeNode<T>* BinaryTree<T>::GetParentInSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, BinaryTreeNode<T>* node) const
{
	/*空树处理*/
	if (subtree_root == nullptr) return 0;
	/*找到父节点情况处理*/
	if (subtree_root->left_child == node || subtree_root->right_child == node) return subtree_root;
	/*分治递归*/
	BinaryTreeNode<T>* parent = GetParentInSubtreeRecursive_(subtree_root->left_child, node);  /*左子树递归调用GetParentInSubtreeRecursive_*/
	if (parent == nullptr) parent = GetParentInSubtreeRecursive_(subtree_root->right_child, node);  /*如果未找到父节点，右子树递归调用GetParentInSubtreeRecursive_*/
	return parent;
}

template<typename T>
inline void BinaryTree<T>::PreorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	/*空树处理*/
	if (subtree_root == nullptr) return;
	/*分治递归*/
	visit(subtree_root);  /*访问subtree_root*/
	PreorderTraversalOfSubtreeRecursive_(subtree_root->left_child, visit);   //左子树递归
	PreorderTraversalOfSubtreeRecursive_(subtree_root->right_child, visit);  //右子树递归
}

template<typename T>
inline void BinaryTree<T>::PreorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	std::stack<BinaryTreeNode<T>*>backtrack_stack;  /*回溯栈*/
	backtrack_stack.push(subtree_root);  /*subtree_root(子树根节点)入栈*/

	while (!backtrack_stack.empty())
	{
		BinaryTreeNode<T>* cur = backtrack_stack.top();  /*取出栈顶*/
		backtrack_stack.pop();  /*栈顶出栈*/

		visit(cur);
		if (cur->right_child != nullptr)backtrack_stack.push(cur->right_child);  /*如果cur存在右孩子，cur右孩子入栈*/
		if (cur->left_child != nullptr)backtrack_stack.push(cur->left_child);  /*如果cur存在左孩子，cur左孩子入栈*/
	}
}

template<typename T>
inline void BinaryTree<T>::InorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	/*空树处理*/
	if (subtree_root == nullptr) return;
	/*分治递归*/
	InorderTraversalOfSubtreeRecursive_(subtree_root->left_child, visit);
	visit(subtree_root);
	InorderTraversalOfSubtreeRecursive_(subtree_root->right_child, visit);
}

template<typename T>
inline void BinaryTree<T>::InorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	std::stack<BinaryTreeNode<T>*> backtrack_stack;  /*回溯栈*/
	BinaryTreeNode<T>* cur = subtree_root;

	while (cur != nullptr || !backtrack_stack.empty())
	{
		//一直向左子树搜索，等于在做深度优先搜索DFS
		while (cur != nullptr)
		{
			backtrack_stack.push(cur);   /*cur入栈*/
			cur = cur->left_child;  /*cur指向自身的左孩子*/
		}

		if (!backtrack_stack.empty())
		{
			cur = backtrack_stack.top();  /*取出栈顶*/
			backtrack_stack.pop();  /*栈顶出栈*/
			visit(cur);
			cur = cur->right_child;  /*cur指向自身的右孩子*/
		}
	}
}

template<typename T>
inline void BinaryTree<T>::PostorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	/*空树处理*/
	if (subtree_root == nullptr) return;
	/*分治递归*/
	PostorderTraversalOfSubtreeRecursive_(subtree_root->left_child, visit);
	PostorderTraversalOfSubtreeRecursive_(subtree_root->right_child, visit);
	visit(subtree_root);
}

template<typename T>
inline void BinaryTree<T>::PostorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	stack<PostorderBacktrackStackNode<T> > backtrack_stack;                                     // 声明backtrack_stack(回溯栈)

	BinaryTreeNode<T>* cur_tree_node = subtree_root;                                            // 初始化cur_tree_node(当前二叉树结点), 指向subtree_root(子树根结点)

	do
	{
		//一直向左子树方向搜索，等于在做深度优先搜索DFS
		while (cur_tree_node != NULL) {                                                             // while loop cur_tree_node不为NULL
			PostorderBacktrackStackNode<T> stack_node(cur_tree_node);                           // 使用cur_tree_node初始化栈结点stack_node(默认tag为LEFT_BACK_TRACKING)
			backtrack_stack.push(stack_node);                                                       // stack_node入栈
			cur_tree_node = cur_tree_node->left_child;                                              // cur_tree_node指向自身的左孩子
		}

		bool cur_tree_node_backtrack_unfinished = true;
		while (cur_tree_node_backtrack_unfinished && !backtrack_stack.empty())
		{
			PostorderBacktrackStackNode<T> cur_backtrack_node = backtrack_stack.top();          // 取回溯栈栈顶, 赋给cur_backtrack_node(当前回溯结点)
			backtrack_stack.pop();                                                                  // 回溯栈栈顶出栈

			cur_tree_node = cur_backtrack_node.node;

			if (cur_backtrack_node.tag == PostorderBacktrackStackNode<T>::LEFT_BACK_TRACKING)  /*如果当前tag为LEFT_BACK_TRACKING*/
			{
				cur_backtrack_node.tag = PostorderBacktrackStackNode<T>::RIGHT_BACK_TRACKING;  /*当前tag设为RIGHT_BACK_TRACKING*/
				backtrack_stack.push(cur_backtrack_node);
				cur_tree_node = cur_tree_node->right_child;
				cur_tree_node_backtrack_unfinished = false;
			}
			else visit(cur_tree_node);
		}
	} while (!backtrack_stack.empty());
}

template<typename T>
inline void BinaryTree<T>::LevelOrderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	/*初始化遍历队列*/
	std::queue<BinaryTreeNode<T>*> traversal_queue;  
	traversal_queue.push(subtree_root);
	/*遍历*/
	while (!traversal_queue.empty())
	{
		BinaryTreeNode<T>* cur = traversal_queue.front();  //取对头
		traversal_queue.pop();  //对头出队

		visit(cur);

		if (cur->left_child != nullptr) traversal_queue.push(cur->left_child);    /*如果cur的左孩子不为空，则cur->left_child入队*/
		if (cur->right_child != nullptr) traversal_queue.push(cur->right_child);  /*如果cur的右孩子不为空，则cur->right_child入队*/
	}
}

template<typename T>
inline void BinaryTree<T>::PrintSubTreeRecursive_(BinaryTreeNode<T>* subtree_root)
{
	/*空子树处理*/
	if (subtree_root == nullptr)return;
	std::cout << subtree_root->data;
	/*递归处理左右子树*/
	if (subtree_root->left_child != nullptr)
	{
		std::cout << " -> ";
		this->PrintSubTreeRecursive_(subtree_root->left_child);
	}
	if (subtree_root->right_child != nullptr)
	{
		std::cout << " -> ";
		this->PrintSubTreeRecursive_(subtree_root->right_child);
	}
}

template<typename T>
inline bool BinaryTree<T>::CreateSubtreeByPreorderAndInorderList_(T* preorder_sub_list, T* inorder_sub_list, int length, BinaryTreeNode<T>*& subtree_root)
{
	/*空子序列处理*/
	if (length == 0) {                                                              // if length == 0
		return true;                                                                // 返回true
	}

	int inorder_sub_list_pivot = 0;                                                 // 初始化inorder_sub_list_pivot(中序遍历子序列轴)为0
	T cur_subtree_root_data = *preorder_sub_list;
	while (cur_subtree_root_data != inorder_sub_list[inorder_sub_list_pivot]) {     // while loop cur_subtree_root_data != inorder_sub_list[inorder_sub_list_pivot]
		inorder_sub_list_pivot++;                                                   // inorder_sub_list_pivot向后移动1个位置
	}
	subtree_root = new BinaryTreeNode<T>(cur_subtree_root_data);                // 使用cur_subtree_root_data, 分配内存并初始化subtree_root
	if (subtree_root == NULL) {                                                     // if 内存分配失败
		return false;                                                               // 返回false
	}

	/*递归构造左子树和右子树*/
	bool res = CreateSubtreeByPreorderAndInorderList_(preorder_sub_list + 1,
                                                      inorder_sub_list,
                                                      inorder_sub_list_pivot,
                                                      subtree_root->left_child);	
	if (!res)return false;
	res = CreateSubtreeByPreorderAndInorderList_(preorder_sub_list + inorder_sub_list_pivot + 1,
		inorder_sub_list + inorder_sub_list_pivot + 1,
		length - inorder_sub_list_pivot - 1,
		subtree_root->right_child);
	return res;
}

template<typename T>
bool operator==(const BinaryTree<T>& binary_tree_1, const BinaryTree<T>& binary_tree_2)
{
	return BinaryTree<T>::Equal(binary_tree_1.Root(), binary_tree_2.Root());
}

template<typename T>
std::ostream& operator<<(std::ostream& out, BinaryTree<T>& binary_tree)
{
	binary_tree.Print();
	return out;
}