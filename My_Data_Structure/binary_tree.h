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

	T data;  /*������*/
	BinaryTreeNode<T>* left_child;  /*���ӽ��*/
	BinaryTreeNode<T>* right_child;  /*�Һ��ӽ��*/
};

template<typename T>  //�����������ջ���ģ��
struct PostorderBacktrackStackNode
{
	explicit PostorderBacktrackStackNode(BinaryTreeNode<T>* node = nullptr) :node(node), tag(LEFT_BACK_TRACKING) {};

	BinaryTreeNode<T>* node;  /*���������ָ��*/
	enum 
	{
		LEFT_BACK_TRACKING = 0,
		RIGHT_BACK_TRACKING
	}tag;
};

template<typename T>class BinaryTree;
/*�ж���������ͬ*/
template<typename T>
bool operator==(const BinaryTree<T>& binary_tree_1, const BinaryTree<T>& binary_tree_2);
/*���������*/
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

	/*��ȡ���ڵ�*/
	BinaryTreeNode<T>* Root()const { return this->root_; }
	/*�ж��Ƿ��ǿ���*/
	bool IsEmpty() { return this->root_ == nullptr; }
	/*��ȡ���ڵ�*/
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* node) const {
		return (this->root_ == nullptr) || (this->root_ == node) ? nullptr : this->GetParentInSubtreeRecursive_(this->root_, node);
	}
	/*��ȡ�߶�*/
	int Height() { return this->HeightOfSubtreeRecursive_(this->root_); }
	/*��ȡ�����*/
	int Size() { return this->SizeOfSubTreeRecursive_(this->root_); }
	/*�����㣨�ݹ飩*/
	bool InsertRecursive(const T& data) { return this->InsertInSubtreeRecursive_(this->root_, data); }
	/*�Ƿ��������*/
	bool Exist(T data) { return this->ExistInSubTree_(this->root_, data); }
	/*ǰ��������ݹ飩*/
	void PreorderTraversalRecursive(void(*visit)(BinaryTreeNode<T>*)) { this->PreorderTraversalOfSubtreeRecursive_(this->root_, visit); }
	/*ǰ�����*/
	void PreorderTraversal(void(*visit)(BinaryTreeNode<T>*)) { this->PreorderTraversalOfSubtree_(this->root_, visit); }
	/*����������ݹ飩*/
	void InorderTraversalRecursive(void(*visit)(BinaryTreeNode<T>*)) { this->InorderTraversalOfSubtreeRecursive_(this->root_, visit); }
	/*�������*/
	void InorderTraversal(void(*visit)(BinaryTreeNode<T>*)) { this->InorderTraversalOfSubtree_(this->root_, visit); }
	/*����������ݹ飩*/
	void PostorderTraversalRecursive(void(*visit)(BinaryTreeNode<T>*)) { this->PostorderTraversalOfSubtreeRecursive_(this->root_, visit); }
	/*�������*/
	void PostorderTraversal(void(*visit)(BinaryTreeNode<T>*)) { this->PostorderTraversalOfSubtree_(this->root_, visit); }
	/*�������*/
	void LevelOrderTraversal(void(*visit)(BinaryTreeNode<T>*)) { this->LevelOrderTraversalOfSubtree_(this->root_, visit); }
	/*����*/
	bool CreateByPreorderAndInorderList(T* preorder_list, T* inorder_list, int length){
		return this->CreateSubtreeByPreorderAndInorderList_(preorder_list, inorder_list, length, this->root_);
	}
	/*��ӡ*/
	void Print() { this->PrintSubTreeRecursive_(this->root_); }

	/*�ж��������Ƿ���ͬ���ݹ飩*/
	static bool Equal(BinaryTreeNode<T>* root1, BinaryTreeNode<T>* root2);

protected:
	BinaryTreeNode<T>* root_;  /*���ڵ�*/

	/*��������ڵ㣨�ݹ飩*/
	bool InsertInSubtreeRecursive_(BinaryTreeNode<T>*& subtree_root, const T& data);
	/*����ɾ��*/
	void DeleteSubtreeRecursive_(BinaryTreeNode<T>*& subtree_root);
	/*�����Ƿ�������ݣ��ݹ飩*/
	bool ExistInSubTree_(BinaryTreeNode<T>* subtree_root, T data) const;
	/*���ƣ��ݹ飩*/
	bool DuplicateSubTreeRecursive_(BinaryTreeNode<T>* src_subtree_root, BinaryTreeNode<T>*& target_subtree_root);
	/*�������ĸ߶ȣ��ݹ飩*/
	int HeightOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root) const;
	/*��������Size���ݹ飩*/
	int SizeOfSubTreeRecursive_(BinaryTreeNode<T>* subtree_root) const;
	/*������ȡ���ĸ��ڵ�*/
	BinaryTreeNode<T>* GetParentInSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, BinaryTreeNode<T>* node) const;

	/*����ǰ��������ݹ飩*/
	void PreorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*����ǰ�����*/
	void PreorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*��������������ݹ飩*/
	void InorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*�����������*/
	void InorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*��������������ݹ飩*/
	void PostorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*�����������*/
	void PostorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*�����������*/
	void LevelOrderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*));
	/*������ӡ*/
	void PrintSubTreeRecursive_(BinaryTreeNode<T>* subtree_root);

	/*ʹ��ǰ������������������������������ݹ飩*/
	bool CreateSubtreeByPreorderAndInorderList_(T* preorder_sub_list, T* inorder_sub_list, int length, BinaryTreeNode<T>*& subtree_root);

	/*�ж��������Ƿ���ͬ*/
	friend bool operator== <>(const BinaryTree<T>& binary_tree_1, const BinaryTree<T>& binary_tree_2);
	/*���������*/
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
	/*�ݹ�*/
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
	/*����������*/
	if (subtree_root == nullptr)
	{
		subtree_root = new BinaryTreeNode<T>(data);
		if (!subtree_root)throw std::bad_alloc();
		return true;
	}
	/*���εݹ�*/
	int left_subtree_height = HeightOfSubtreeRecursive_(subtree_root->left_child);  /*����left_subtree_height���������߶ȣ�*/
	int rigth_subtree_height = HeightOfSubtreeRecursive_(subtree_root->right_child);  /*����rigth_subtree_height���������߶ȣ�*/
	if (left_subtree_height > rigth_subtree_height)  /*���left_subtree_height > rigth_subtree_height*/
	{
		if (!(InsertInSubtreeRecursive_(subtree_root->right_child, data)))   /*�ݹ����InsertInSubtreeRecursive_*/
			return false;
	}
	else   /*���left_subtree_height < rigth_subtree_height*/
	{
		if (!(InsertInSubtreeRecursive_(subtree_root->left_child, data)))    /*�ݹ����InsertInSubtreeRecursive_*/
			return false;
	}
	return true;
}

template<typename T>
inline void BinaryTree<T>::DeleteSubtreeRecursive_(BinaryTreeNode<T>*& subtree_root)
{
	if (subtree_root == nullptr)return;
	/*���εݹ�*/
	this->DeleteSubtreeRecursive_(subtree_root->left_child);   /*�������ݹ�ɾ��*/
	this->DeleteSubtreeRecursive_(subtree_root->right_child);  /*�������ݹ�ɾ��*/
	/*ɾ���������ڵ�*/
	delete subtree_root;
	subtree_root = nullptr;
}

template<typename T>
inline bool BinaryTree<T>::ExistInSubTree_(BinaryTreeNode<T>* subtree_root, T data) const
{
	/*��������*/
	if (subtree_root == nullptr) return false;
	/*������������*/
	if (subtree_root->data == data) return true;
	/*���εݹ�*/
	if (ExistInSubTree_(subtree_root->left_child, data)) return true;   /*�������ݹ�*/
	if (ExistInSubTree_(subtree_root->right_child, data)) return true;  /*�������ݹ�*/
	return false;
}

template<typename T>
inline bool BinaryTree<T>::DuplicateSubTreeRecursive_(BinaryTreeNode<T>* src_subtree_root, BinaryTreeNode<T>*& target_subtree_root)
{
	/*��������*/
	if (src_subtree_root == nullptr)
	{
		target_subtree_root = nullptr;
		return true;
	}
	/*Ŀ���������ڵ㴦��*/
	target_subtree_root = new BinaryTreeNode<T>(src_subtree_root->data);
	if (!target_subtree_root)return false;
	/*���εݹ�*/
	if (!DuplicateSubTreeRecursive_(src_subtree_root->left_child, target_subtree_root->left_child)) return false;    /*�������ݹ鸴��*/
	if (!DuplicateSubTreeRecursive_(src_subtree_root->right_child, target_subtree_root->right_child)) return false;  /*�������ݹ鸴��*/
	return true;
}

template<typename T>
inline int BinaryTree<T>::HeightOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root) const
{
	/*��������*/
	if (subtree_root == nullptr) return 0;
	/*���εݹ�*/
	int left_subtree_height = HeightOfSubtreeRecursive_(subtree_root->left_child);  /*�������ݹ飬�õ�left_subtree_height(�������߶�)*/
	int right_subtree_height = HeightOfSubtreeRecursive_(subtree_root->right_child);  /*�������ݹ飬�õ�right_subtree_height(�������߶�)*/
	int subtree_height = (left_subtree_height < right_subtree_height ? right_subtree_height : left_subtree_height) + 1;
	return subtree_height;
}

template<typename T>
inline int BinaryTree<T>::SizeOfSubTreeRecursive_(BinaryTreeNode<T>* subtree_root) const
{
	/*��������*/
	if (subtree_root == nullptr) return 0;
	/*���εݹ�*/
	int left_subtree_size = SizeOfSubTreeRecursive_(subtree_root->left_child);  /*�������ݹ飬�õ�left_subtree_height(�������߶�)*/
	int right_subtree_size = SizeOfSubTreeRecursive_(subtree_root->right_child);  /*�������ݹ飬�õ�right_subtree_height(�������߶�)*/
	int subtree_size = 1 + left_subtree_size + right_subtree_size;
	return subtree_size;
}

template<typename T>
inline BinaryTreeNode<T>* BinaryTree<T>::GetParentInSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, BinaryTreeNode<T>* node) const
{
	/*��������*/
	if (subtree_root == nullptr) return 0;
	/*�ҵ����ڵ��������*/
	if (subtree_root->left_child == node || subtree_root->right_child == node) return subtree_root;
	/*���εݹ�*/
	BinaryTreeNode<T>* parent = GetParentInSubtreeRecursive_(subtree_root->left_child, node);  /*�������ݹ����GetParentInSubtreeRecursive_*/
	if (parent == nullptr) parent = GetParentInSubtreeRecursive_(subtree_root->right_child, node);  /*���δ�ҵ����ڵ㣬�������ݹ����GetParentInSubtreeRecursive_*/
	return parent;
}

template<typename T>
inline void BinaryTree<T>::PreorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	/*��������*/
	if (subtree_root == nullptr) return;
	/*���εݹ�*/
	visit(subtree_root);  /*����subtree_root*/
	PreorderTraversalOfSubtreeRecursive_(subtree_root->left_child, visit);   //�������ݹ�
	PreorderTraversalOfSubtreeRecursive_(subtree_root->right_child, visit);  //�������ݹ�
}

template<typename T>
inline void BinaryTree<T>::PreorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	std::stack<BinaryTreeNode<T>*>backtrack_stack;  /*����ջ*/
	backtrack_stack.push(subtree_root);  /*subtree_root(�������ڵ�)��ջ*/

	while (!backtrack_stack.empty())
	{
		BinaryTreeNode<T>* cur = backtrack_stack.top();  /*ȡ��ջ��*/
		backtrack_stack.pop();  /*ջ����ջ*/

		visit(cur);
		if (cur->right_child != nullptr)backtrack_stack.push(cur->right_child);  /*���cur�����Һ��ӣ�cur�Һ�����ջ*/
		if (cur->left_child != nullptr)backtrack_stack.push(cur->left_child);  /*���cur�������ӣ�cur������ջ*/
	}
}

template<typename T>
inline void BinaryTree<T>::InorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	/*��������*/
	if (subtree_root == nullptr) return;
	/*���εݹ�*/
	InorderTraversalOfSubtreeRecursive_(subtree_root->left_child, visit);
	visit(subtree_root);
	InorderTraversalOfSubtreeRecursive_(subtree_root->right_child, visit);
}

template<typename T>
inline void BinaryTree<T>::InorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	std::stack<BinaryTreeNode<T>*> backtrack_stack;  /*����ջ*/
	BinaryTreeNode<T>* cur = subtree_root;

	while (cur != nullptr || !backtrack_stack.empty())
	{
		//һֱ���������������������������������DFS
		while (cur != nullptr)
		{
			backtrack_stack.push(cur);   /*cur��ջ*/
			cur = cur->left_child;  /*curָ�����������*/
		}

		if (!backtrack_stack.empty())
		{
			cur = backtrack_stack.top();  /*ȡ��ջ��*/
			backtrack_stack.pop();  /*ջ����ջ*/
			visit(cur);
			cur = cur->right_child;  /*curָ��������Һ���*/
		}
	}
}

template<typename T>
inline void BinaryTree<T>::PostorderTraversalOfSubtreeRecursive_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	/*��������*/
	if (subtree_root == nullptr) return;
	/*���εݹ�*/
	PostorderTraversalOfSubtreeRecursive_(subtree_root->left_child, visit);
	PostorderTraversalOfSubtreeRecursive_(subtree_root->right_child, visit);
	visit(subtree_root);
}

template<typename T>
inline void BinaryTree<T>::PostorderTraversalOfSubtree_(BinaryTreeNode<T>* subtree_root, void(*visit)(BinaryTreeNode<T>*))
{
	stack<PostorderBacktrackStackNode<T> > backtrack_stack;                                     // ����backtrack_stack(����ջ)

	BinaryTreeNode<T>* cur_tree_node = subtree_root;                                            // ��ʼ��cur_tree_node(��ǰ���������), ָ��subtree_root(���������)

	do
	{
		//һֱ�������������������������������������DFS
		while (cur_tree_node != NULL) {                                                             // while loop cur_tree_node��ΪNULL
			PostorderBacktrackStackNode<T> stack_node(cur_tree_node);                           // ʹ��cur_tree_node��ʼ��ջ���stack_node(Ĭ��tagΪLEFT_BACK_TRACKING)
			backtrack_stack.push(stack_node);                                                       // stack_node��ջ
			cur_tree_node = cur_tree_node->left_child;                                              // cur_tree_nodeָ�����������
		}

		bool cur_tree_node_backtrack_unfinished = true;
		while (cur_tree_node_backtrack_unfinished && !backtrack_stack.empty())
		{
			PostorderBacktrackStackNode<T> cur_backtrack_node = backtrack_stack.top();          // ȡ����ջջ��, ����cur_backtrack_node(��ǰ���ݽ��)
			backtrack_stack.pop();                                                                  // ����ջջ����ջ

			cur_tree_node = cur_backtrack_node.node;

			if (cur_backtrack_node.tag == PostorderBacktrackStackNode<T>::LEFT_BACK_TRACKING)  /*�����ǰtagΪLEFT_BACK_TRACKING*/
			{
				cur_backtrack_node.tag = PostorderBacktrackStackNode<T>::RIGHT_BACK_TRACKING;  /*��ǰtag��ΪRIGHT_BACK_TRACKING*/
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
	/*��ʼ����������*/
	std::queue<BinaryTreeNode<T>*> traversal_queue;  
	traversal_queue.push(subtree_root);
	/*����*/
	while (!traversal_queue.empty())
	{
		BinaryTreeNode<T>* cur = traversal_queue.front();  //ȡ��ͷ
		traversal_queue.pop();  //��ͷ����

		visit(cur);

		if (cur->left_child != nullptr) traversal_queue.push(cur->left_child);    /*���cur�����Ӳ�Ϊ�գ���cur->left_child���*/
		if (cur->right_child != nullptr) traversal_queue.push(cur->right_child);  /*���cur���Һ��Ӳ�Ϊ�գ���cur->right_child���*/
	}
}

template<typename T>
inline void BinaryTree<T>::PrintSubTreeRecursive_(BinaryTreeNode<T>* subtree_root)
{
	/*����������*/
	if (subtree_root == nullptr)return;
	std::cout << subtree_root->data;
	/*�ݹ鴦����������*/
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
	/*�������д���*/
	if (length == 0) {                                                              // if length == 0
		return true;                                                                // ����true
	}

	int inorder_sub_list_pivot = 0;                                                 // ��ʼ��inorder_sub_list_pivot(���������������)Ϊ0
	T cur_subtree_root_data = *preorder_sub_list;
	while (cur_subtree_root_data != inorder_sub_list[inorder_sub_list_pivot]) {     // while loop cur_subtree_root_data != inorder_sub_list[inorder_sub_list_pivot]
		inorder_sub_list_pivot++;                                                   // inorder_sub_list_pivot����ƶ�1��λ��
	}
	subtree_root = new BinaryTreeNode<T>(cur_subtree_root_data);                // ʹ��cur_subtree_root_data, �����ڴ沢��ʼ��subtree_root
	if (subtree_root == NULL) {                                                     // if �ڴ����ʧ��
		return false;                                                               // ����false
	}

	/*�ݹ鹹����������������*/
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