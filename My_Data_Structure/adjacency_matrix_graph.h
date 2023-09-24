#pragma once

#include "graph.h"
#include <map>
#include <iomanip> 

template<typename Tvertex, typename TWeight> class MatrixGraph;
//���� >>
template<typename Tvertex, typename TWeight>
std::istream& operator>>(std::istream& in, MatrixGraph<Tvertex, TWeight>& graph);
//���� <<
template<typename Tvertex, typename TWeight>
std::ostream& operator<<(std::ostream& in, MatrixGraph<Tvertex, TWeight>& graph);

/*�ڽӾ���ͼģ����*/
template<typename Tvertex, typename TWeight>
class MatrixGraph : public Graph<Tvertex, TWeight>
{
public:
	/*���캯��(���������/��Ȩֵ����)*/
	MatrixGraph(int max_vertex_count, TWeight max_weight);
	/*���캯��(ͼ����/���������/��Ȩֵ����)*/
	MatrixGraph(int type, int max_vertex_count, TWeight max_weight);
	/*���캯��(���������/��Ȩֵ����/��vector/���vector)*/
	MatrixGraph(int max_vertex_count, TWeight max_weight, const std::vector<::Edge<Tvertex, TWeight>>& edges, const std::vector<Tvertex>& vertices);
	/*���캯��(ͼ����/���������/��Ȩֵ����/��vector/���vector)*/
	MatrixGraph(int type, 
		int max_vertex_count, 
		TWeight max_weight, 
		const std::vector<::Edge<Tvertex, TWeight>>& edges, 
		const std::vector<Tvertex>& vertices);
	~MatrixGraph();

	/*��ȡ���(by�������)*/
	bool GetVertexByIndex(int vertex_index, Tvertex& vertex) const;
	/*��ȡ��Ȩֵ(by���)*/
	bool GetWeight(const Tvertex& starting_vertex, const Tvertex& ending_vertex, TWeight& weight) const;
	/*��ȡ��Ȩֵ(by�������)*/
	bool GetWeightByVertexIndex(int starting_vertex_index, int ending_vertex_index, TWeight& weight) const;
	/*��ȡ���ĵ�һ�����ڽ��*/
	bool GetFirstNeighborVertex(const Tvertex& vertex, Tvertex& first_neighbor) const;
	/*��ȡ������һ�����ڽ��*/
	bool GetNextNeighborVertex(const Tvertex& vertex, const Tvertex& neighbor_vertex, Tvertex& next_neighbor) const;
	/*������*/
	bool InsertVertex(const Tvertex& vertex);
	/*�����*/
	bool InsertEdge(const Tvertex& starting_vertex, const Tvertex& ending_vertex, const TWeight& weight);
	/*ɾ�����*/
	bool RemoveVertex(const Tvertex& vertex);
	/*ɾ����*/
	bool RemoveEdge(const Tvertex& starting_vertex, const Tvertex& ending_vertex);
	/*��ȡ�������*/
	int GetVertexIndex(const Tvertex& vertex) const;

	/*����>>*/
	friend std::istream& operator>> <>(std::istream& in, MatrixGraph<Tvertex, TWeight>& graph);
	/*����<<*/
	friend std::ostream& operator<< <>(std::ostream& out, MatrixGraph<Tvertex, TWeight>& graph);

	/*��ӡ�ڽӾ���*/
	void PrintMatrix();

private:
	TWeight** adjacency_matrix_;  /*�ڽӾ���*/
};

template<typename Tvertex, typename TWeight>
inline MatrixGraph<Tvertex, TWeight>::MatrixGraph(int max_vertex_count, TWeight max_weight)
{

}
