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

	TKey key;  //�ؼ���
	TWeight weight;  //Ȩֵ
	HuffmanTreeNode* left_child;  //����
	HuffmanTreeNode* right_child;  //�Һ���
	HuffmanTreeNode* parent;  //���ڵ�
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

	//���ɹ���������
	std::unordered_map<TKey, std::string>GenerateHuffmanCodes();
	void PrintTree() { PrintSubTreeRecursive_(root_); std::cout << '\n'; }

protected:
	HuffmanTreeNode<TKey, TWeight>* root_;  //���ڵ�
	//�������
	void ClearSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* subtree_root);
	//�ϲ�����
	void MergeSubTree_(HuffmanTreeNode<TKey, TWeight>* subtree_root_1,
					   HuffmanTreeNode<TKey, TWeight>* subtree_root_2,
					   HuffmanTreeNode<TKey, TWeight>*& new_subtree_root);
	//��ӡ����
	void PrintSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* subtree_root);
	//�������ɹ���������
	void GenerateHuffmanCodeOfSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* node,
												const std::string& current_prefix_code,
												std::unordered_map<TKey, std::string>& huffman_codes);
};

template<typename TKey, typename TWeight>
inline HuffmanTree<TKey, TWeight>::HuffmanTree(const TKey keys[], const TWeight weights[], int count)
{
	/*��ʼ�����ȶ���*/
	std::priority_queue<HuffmanTreeNode<TKey, TWeight>*, std::vector<HuffmanTreeNode<TKey, TWeight>*>, Compare<TKey, TWeight>>min_priority_queue;
	for (int i = 0; i < count; i++)
	{
		HuffmanTreeNode<TKey, TWeight>* node = new HuffmanTreeNode<TKey, TWeight>(keys[i], weights[i], nullptr, nullptr, nullptr);
		min_priority_queue.push(node); 
	}
	/*ʹ����С���ȶ��й����������*/
	HuffmanTreeNode<TKey, TWeight>* cur_parent = nullptr;
	for (int i = 0; i < count - 1; i++)
	{
		HuffmanTreeNode<TKey, TWeight>* first = min_priority_queue.top();
		min_priority_queue.pop();  //��ͷ����
		HuffmanTreeNode<TKey, TWeight>* second = min_priority_queue.top();
		min_priority_queue.pop();  //��ͷ����
		MergeSubTree_(first, second, cur_parent);
		min_priority_queue.push(cur_parent);
	}
	root_ = cur_parent;
}

template<typename TKey, typename TWeight>
inline std::unordered_map<TKey, std::string> HuffmanTree<TKey, TWeight>::GenerateHuffmanCodes()
{
	unordered_map<TKey, string> huffman_codes;  // ����huffman_codes

	string current_prefix_code;
	// ����GenerateHuffmanCodeOfSubTreeRecursive_, ���ɹ���������
	GenerateHuffmanCodeOfSubTreeRecursive_(root_, current_prefix_code, huffman_codes);

	return huffman_codes;
}

template<typename TKey, typename TWeight>
inline void HuffmanTree<TKey, TWeight>::ClearSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* subtree_root)
{
	if (subtree_root == nullptr)return;
	/*�ݹ�*/
	ClearSubTreeRecursive_(subtree_root->left_child);
	ClearSubTreeRecursive_(subtree_root->right_child);
	/*�ͷŸ��ڵ�*/
	delete subtree_root;
	subtree_root = nullptr;
}

template<typename TKey, typename TWeight>
inline void HuffmanTree<TKey, TWeight>::MergeSubTree_(HuffmanTreeNode<TKey, TWeight>* subtree_root_1, HuffmanTreeNode<TKey, TWeight>* subtree_root_2, HuffmanTreeNode<TKey, TWeight>*& new_subtree_root)
{
	TKey key;
	new_subtree_root = new HuffmanTreeNode<TKey, TWeight>(key, subtree_root_1->weight + subtree_root_2->weight, subtree_root_1, subtree_root_2, nullptr);
	//�����������ڵ��parentָ�����������ڵ�
	subtree_root_1->parent = new_subtree_root;
	subtree_root_2->parent = new_subtree_root;
}

template<typename TKey, typename TWeight>
inline void HuffmanTree<TKey, TWeight>::PrintSubTreeRecursive_(HuffmanTreeNode<TKey, TWeight>* subtree_root)
{
	if (subtree_root == nullptr)return;
	/*�ݹ�*/
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
		return;                                                                                                 // �˳�����
	}

	// ---------- 2 Ҷ�ӽ�㴦�� ----------

	if (node->left_child == NULL && node->right_child == NULL) {                                                // if nodeΪҶ�ӽ��
		huffman_codes[node->key] = current_prefix_code;                                                         // current_prefix_code��Ϊnode->key�Ĺ���������
		return;                                                                                                 // �˳�����
	}

	// ---------- 3 ��Ҷ�ӽ�㴦�� ----------

	string str_zero("0");                                                                                       // current_prefix_code��չ0
	GenerateHuffmanCodeOfSubTreeRecursive_(node->left_child, current_prefix_code + str_zero, huffman_codes);    // ���������ݹ�ִ��GenerateHuffmanCodeOfSubTreeRecursive_

	string str_one("1");                                                                                        // current_prefix_code��չ1
	GenerateHuffmanCodeOfSubTreeRecursive_(node->right_child, current_prefix_code + str_one, huffman_codes);    // ���������ݹ�ִ��GenerateHuffmanCodeOfSubTreeRecursive_
}


