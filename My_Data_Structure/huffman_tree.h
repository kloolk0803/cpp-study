#pragma once

#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

template<typename TKey, typename TWeight>
struct HuffmanTreeNode
{
	HuffmanTreeNode() :key(TKey()), weight(TWeight()), left_child(nullptr), right_child(nullptr), parent(nullptr) {};
	HuffmanTreeNode(TKey key, TWeight weight, HuffmanTreeNode* left = nullptr, HuffmanTreeNode* right = nullptr, HuffmanTreeNode* parent = nullptr)
		:key(key), weight(weight), left_child(left), right_child(right), parent(parent) {};

	TKey key;  //关键字
	TWeight weight;  //权值
	HuffmanTreeNode* left_child;  //左孩子
	HuffmanTreeNode* right_child;  //右孩子
	HuffmanTreeNode* parent;  //父节点
};

template<typename TKey, typename TWeight>
struct Compare
{
	bool operator()(HuffmanTreeNode<TKey, TWeight>* node1, HuffmanTreeNode<TKey, TWeight>* node2) {
		return node1->weight > node2->weight;
	}
};

template<typename TKey, typename TWeight>
class HuffmanTree
{
public:
	HuffmanTree(const TKey keys[], const TWeight weights[], int count);
	~HuffmanTree()
	{
		ClearSubTreeRecursive_(root_);
		root_ = nullptr;
	}

	//生成哈夫曼编码
	std::unordered_map<TKey, std::string>GenerateHuffmanCodes();
	void PrintTree() { PrintSubTreeRecursive_(root_); std::cout << '\n'; }

protected:
	HuffmanTreeNode<TKey, TWeight>* root_;  //根节点
	//子树清空
	void ClearSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* subtree_root);
	//合并子树
	void MergeSubTree_(HuffmanTreeNode<TKey, TWeight>* subtree_root_1,
					   HuffmanTreeNode<TKey, TWeight>* subtree_root_2,
					   HuffmanTreeNode<TKey, TWeight>*& new_subtree_root);
	//打印子树
	void PrintSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* subtree_root);
	//子树生成哈夫曼编码
	void GenerateHuffmanCodeOfSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* node,
												const std::string& current_prefix_code,
												std::unordered_map<TKey, std::string>& huffman_codes);
};

template<typename TKey, typename TWeight>
inline HuffmanTree<TKey, TWeight>::HuffmanTree(const TKey keys[], const TWeight weights[], int count)
{
	/*初始化优先队列*/
	std::priority_queue<HuffmanTreeNode<TKey, TWeight>*, std::vector<HuffmanTreeNode<TKey, TWeight>*>, Compare<TKey, TWeight>>min_priority_queue;
	for (int i = 0; i < count; i++)
	{
		HuffmanTreeNode<TKey, TWeight>* node = new HuffmanTreeNode<TKey, TWeight>(keys[i], weights[i], nullptr, nullptr, nullptr);
		min_priority_queue.push(node); 
	}
	/*使用最小优先队列构造哈夫曼树*/
	HuffmanTreeNode<TKey, TWeight>* cur_parent = nullptr;
	for (int i = 0; i < count - 1; i++)
	{
		HuffmanTreeNode<TKey, TWeight>* first = min_priority_queue.top();
		min_priority_queue.pop();  //对头出队
		HuffmanTreeNode<TKey, TWeight>* second = min_priority_queue.top();
		min_priority_queue.pop();  //对头出队
		MergeSubTree_(first, second, cur_parent);
		min_priority_queue.push(cur_parent);
	}
	root_ = cur_parent;
}

template<typename TKey, typename TWeight>
inline std::unordered_map<TKey, std::string> HuffmanTree<TKey, TWeight>::GenerateHuffmanCodes()
{
	unordered_map<TKey, string> huffman_codes;  // 声明huffman_codes

	string current_prefix_code;
	// 调用GenerateHuffmanCodeOfSubTreeRecursive_, 生成哈夫曼编码
	GenerateHuffmanCodeOfSubTreeRecursive_(root_, current_prefix_code, huffman_codes);

	return huffman_codes;
}

template<typename TKey, typename TWeight>
inline void HuffmanTree<TKey, TWeight>::ClearSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* subtree_root)
{
	if (subtree_root == nullptr)return;
	/*递归*/
	ClearSubTreeRecursive_(subtree_root->left_child);
	ClearSubTreeRecursive_(subtree_root->right_child);
	/*释放根节点*/
	delete subtree_root;
	subtree_root = nullptr;
}

template<typename TKey, typename TWeight>
inline void HuffmanTree<TKey, TWeight>::MergeSubTree_(HuffmanTreeNode<TKey, TWeight>* subtree_root_1, HuffmanTreeNode<TKey, TWeight>* subtree_root_2, HuffmanTreeNode<TKey, TWeight>*& new_subtree_root)
{
	TKey key;
	new_subtree_root = new HuffmanTreeNode<TKey, TWeight>(key, subtree_root_1->weight + subtree_root_2->weight, subtree_root_1, subtree_root_2, nullptr);
	//两个子树根节点的parent指向新子树根节点
	subtree_root_1->parent = new_subtree_root;
	subtree_root_2->parent = new_subtree_root;
}

template<typename TKey, typename TWeight>
inline void HuffmanTree<TKey, TWeight>::PrintSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* subtree_root)
{
	if (subtree_root == nullptr)return;
	/*递归*/
	std::cout << subtree_root->weight;
	std::cout << "(";
	PrintSubTreeRecursive_(subtree_root->left_child);
	std::cout << ",";
	PrintSubTreeRecursive_(subtree_root->right_child);
	std::cout << ")";
}

template<typename TKey, typename TWeight>
inline void HuffmanTree<TKey, TWeight>::GenerateHuffmanCodeOfSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* node, const std::string& current_prefix_code, std::unordered_map<TKey, std::string>& huffman_codes)
{
	if (node == NULL) {                                                                                         // if node == NULL
		return;                                                                                                 // 退出函数
	}

	// ---------- 2 叶子结点处理 ----------

	if (node->left_child == NULL && node->right_child == NULL) {                                                // if node为叶子结点
		huffman_codes[node->key] = current_prefix_code;                                                         // current_prefix_code即为node->key的哈夫曼编码
		return;                                                                                                 // 退出函数
	}

	// ---------- 3 非叶子结点处理 ----------

	string str_zero("0");                                                                                       // current_prefix_code扩展0
	GenerateHuffmanCodeOfSubTreeRecursive_(node->left_child, current_prefix_code + str_zero, huffman_codes);    // 向左子树递归执行GenerateHuffmanCodeOfSubTreeRecursive_

	string str_one("1");                                                                                        // current_prefix_code扩展1
	GenerateHuffmanCodeOfSubTreeRecursive_(node->right_child, current_prefix_code + str_one, huffman_codes);    // 向右子树递归执行GenerateHuffmanCodeOfSubTreeRecursive_
}


