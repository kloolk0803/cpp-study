#pragma once

#include <iostream>
#include <vector>

template<typename TVertex, typename TWeight>
class Edge {
public:
    Edge() : starting_vertex(TVertex()), ending_vertex(TVertex()), weight(TWeight()) {}
    Edge(const TVertex& starting_vertex, const TVertex& ending_vertex, const TWeight& weight) :
        weight(weight), starting_vertex(starting_vertex), ending_vertex(ending_vertex) {}

    bool operator<=(const Edge<TVertex, TWeight>& edge) { return weight <= edge.weight; }
    bool operator>=(const Edge<TVertex, TWeight>& edge) { return weight >= edge.weight; }
    bool operator>(const Edge<TVertex, TWeight>& edge) { return weight > edge.weight; }
    bool operator<(const Edge<TVertex, TWeight>& edge) { return weight < edge.weight; }

    TVertex starting_vertex;  //!< **起点**
    TVertex ending_vertex;    //!< **终点**
    TWeight weight;           //!< **边权重**
};

/*路径模版类*/
template<typename TVertex, typename TWeight>
class Path : public Edge<TVertex, TWeight> {
public:
	Path() : starting_vertex(TVertex()), ending_vertex(TVertex()), weight(TWeight()) {};
	Path(TVertex starting_vertex, TVertex ending_vertex, TWeight weight) :
		starting_vertex(starting_vertex), ending_vertex(ending_vertex), weight(weight) {}

	TWeight weight;             //!< **路径权值**
	TVertex starting_vertex;    //!< **起点**
	TVertex ending_vertex;      //!< **终点**
};

/*图抽象模版类*/
template<typename TVertex,typename TWeight>
class Graph
{
public:
	/*获取图类型*/
	int Type() const { return this->type_; }
	/*获取结点数量*/
	unsigned int VertexCount() const { return this->vertex_count_; }
	/*获取边数量*/
	unsigned int EdgeCount() const { return this->edge_count_; }
	/*获取边权值上限*/
	virtual TWeight MaxWeight() const { return this->max_weight_; }
	/*获取边vector*/
	virtual const std::vector<Edge<TVertex, TWeight>>& Edge() const { return this->edges_; }
	/*获取点vector*/
	virtual const std::vector<TVertex>& Vertices() const { return this->vertices_; }
	/*获取边(by边索引)*/
	virtual const ::Edge<TVertex, TWeight>& GetEdge(int index) const { return this->edges_[index]; }
	/*获取结点(by边索引)*/
	virtual bool GetVertexByIndex(int vertex_index, TVertex& vertex) const = 0;
	/*获取边权值(by结点)*/
	virtual bool GetWeight(const TVertex& starting_vertex, const TVertex& ending_vertex, TWeight& weight) const = 0;
	/*获取边权值(by边索引)*/
	virtual bool GetWeightByVertexIndex(int starting_vertex_index, int ending_vertex_index, TWeight& weight) const = 0;
	/*获取结点的第一个相邻结点*/
	virtual bool GetFirstNeighborVertex(const TVertex& vertex, TVertex& first_neighbor) const = 0;
	/*获取结点的下一个相邻结点*/
	virtual bool GetNextNeighborVertex(const TVertex& vertex, const TVertex& neighbor_vertex, TVertex& next_neighbor) const = 0;
	/*获取结点的度*/
	int GetVertexDegree(TVertex& vertex)
	{
		if (this->type_ == DIRECTED) return -1;  //如果是有向图，返回-1（有向图应获取出入度）
		int vertex_index = GetVertexIndex(vertex);  //获取结点索引
		return this->degrees_[vertex_index];
	}
	/*获取结点的入度*/
	int GetVertexInDegree(const TVertex& vertex)
	{
		if (this->type_ == UNDIRECTED) return -1;  //如果是无向图，返回-1（无向图应获取度）
		int vertex_index = GetVertexIndex(vertex);  //获取结点索引
		return this->in_degrees_[vertex_index];
	}
	/*获取结点的出度*/
	int GetVertexOutDegree(TVertex vertex)
	{
		if (this->type_ == UNDIRECTED) return -1;  //如果是无向图，返回-1（无向图应获取度）
		int vertex_index = GetVertexIndex(vertex);  //获取结点索引
		return this->out_degrees_[vertex_index];
	}
	/*插入结点*/
	virtual bool InsertVertex(const TVertex& vertex) = 0;
	/*插入边*/
	virtual bool InsertEdge(const TVertex& starting_vertex, const TVertex& ending_vertex, const TWeight& weight) = 0;
	/*删除结点*/
	virtual bool RemoveVertex(const TVertex& vertex) = 0;
	/*删除边*/
	virtual bool RemoveEdge(const TVertex& starting_vertex, const TVertex& ending_vertex) = 0;
	/*获取结点索引*/
	virtual int GetVertexIndex(const TVertex& vertex) const = 0;

	static constexpr int DIRECTED = 1;    //有向
	static constexpr int UNDIRECTED = 2;  //无向

protected:
	int max_vertex_count_;                    //!< **图结点数量上限**
	TWeight max_weight_;                      //!< **边权值上限**
	int edge_count_;                          //!< **边数量**
	int vertex_count_;                        //!< **结点数量**
	int type_;                                //!< **类型(1:有向, 2:无向)**

	std::vector<TVertex> vertices_;                //!< **结点vector**
	std::vector<::Edge<TVertex, TWeight> > edges_;   //!< **边vector**
	std::vector<int> degrees_;                     //!< **度vector(无向图使用)**
	std::vector<int> in_degrees_;                  //!< **入度vector(有向图使用)**
	std::vector<int> out_degrees_;                 //!< **出度vector(有向图使用)**
};