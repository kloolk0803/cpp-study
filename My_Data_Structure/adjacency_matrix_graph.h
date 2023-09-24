#pragma once

#include "graph.h"
#include <map>
#include <iomanip> 

template<typename Tvertex, typename TWeight> class MatrixGraph;
//重载 >>
template<typename Tvertex, typename TWeight>
std::istream& operator>>(std::istream& in, MatrixGraph<Tvertex, TWeight>& graph);
//重载 <<
template<typename Tvertex, typename TWeight>
std::ostream& operator<<(std::ostream& in, MatrixGraph<Tvertex, TWeight>& graph);

/*邻接矩阵图模版类*/
template<typename Tvertex, typename TWeight>
class MatrixGraph : public Graph<Tvertex, TWeight>
{
public:
	/*构造函数(结点数上限/边权值上限)*/
	MatrixGraph(int max_vertex_count, TWeight max_weight);
	/*构造函数(图类型/结点数上限/边权值上限)*/
	MatrixGraph(int type, int max_vertex_count, TWeight max_weight);
	/*构造函数(结点数上限/边权值上限/边vector/结点vector)*/
	MatrixGraph(int max_vertex_count, TWeight max_weight, const std::vector<::Edge<Tvertex, TWeight>>& edges, const std::vector<Tvertex>& vertices);
	/*构造函数(图类型/结点数上限/边权值上限/边vector/结点vector)*/
	MatrixGraph(int type, 
		int max_vertex_count, 
		TWeight max_weight, 
		const std::vector<::Edge<Tvertex, TWeight>>& edges, 
		const std::vector<Tvertex>& vertices);
	~MatrixGraph();

	/*获取结点(by结点索引)*/
	bool GetVertexByIndex(int vertex_index, Tvertex& vertex) const;
	/*获取边权值(by结点)*/
	bool GetWeight(const Tvertex& starting_vertex, const Tvertex& ending_vertex, TWeight& weight) const;
	/*获取边权值(by结点索引)*/
	bool GetWeightByVertexIndex(int starting_vertex_index, int ending_vertex_index, TWeight& weight) const;
	/*获取结点的第一个相邻结点*/
	bool GetFirstNeighborVertex(const Tvertex& vertex, Tvertex& first_neighbor) const;
	/*获取结点的下一个相邻结点*/
	bool GetNextNeighborVertex(const Tvertex& vertex, const Tvertex& neighbor_vertex, Tvertex& next_neighbor) const;
	/*插入结点*/
	bool InsertVertex(const Tvertex& vertex);
	/*插入边*/
	bool InsertEdge(const Tvertex& starting_vertex, const Tvertex& ending_vertex, const TWeight& weight);
	/*删除结点*/
	bool RemoveVertex(const Tvertex& vertex);
	/*删除边*/
	bool RemoveEdge(const Tvertex& starting_vertex, const Tvertex& ending_vertex);
	/*获取结点索引*/
	int GetVertexIndex(const Tvertex& vertex) const;

	/*重载>>*/
	friend std::istream& operator>> <>(std::istream& in, MatrixGraph<Tvertex, TWeight>& graph);
	/*重载<<*/
	friend std::ostream& operator<< <>(std::ostream& out, MatrixGraph<Tvertex, TWeight>& graph);

	/*打印邻接矩阵*/
	void PrintMatrix();

private:
	TWeight** adjacency_matrix_;  /*邻接矩阵*/
};

template<typename Tvertex, typename TWeight>
inline MatrixGraph<Tvertex, TWeight>::MatrixGraph(int max_vertex_count, TWeight max_weight)
{

}
