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

    TVertex starting_vertex;  //!< **���**
    TVertex ending_vertex;    //!< **�յ�**
    TWeight weight;           //!< **��Ȩ��**
};

/*·��ģ����*/
template<typename TVertex, typename TWeight>
class Path : public Edge<TVertex, TWeight> {
public:
	Path() : starting_vertex(TVertex()), ending_vertex(TVertex()), weight(TWeight()) {};
	Path(TVertex starting_vertex, TVertex ending_vertex, TWeight weight) :
		starting_vertex(starting_vertex), ending_vertex(ending_vertex), weight(weight) {}

	TWeight weight;             //!< **·��Ȩֵ**
	TVertex starting_vertex;    //!< **���**
	TVertex ending_vertex;      //!< **�յ�**
};

/*ͼ����ģ����*/
template<typename TVertex,typename TWeight>
class Graph
{
public:
	/*��ȡͼ����*/
	int Type() const { return this->type_; }
	/*��ȡ�������*/
	unsigned int VertexCount() const { return this->vertex_count_; }
	/*��ȡ������*/
	unsigned int EdgeCount() const { return this->edge_count_; }
	/*��ȡ��Ȩֵ����*/
	virtual TWeight MaxWeight() const { return this->max_weight_; }
	/*��ȡ��vector*/
	virtual const std::vector<Edge<TVertex, TWeight>>& Edge() const { return this->edges_; }
	/*��ȡ��vector*/
	virtual const std::vector<TVertex>& Vertices() const { return this->vertices_; }
	/*��ȡ��(by������)*/
	virtual const ::Edge<TVertex, TWeight>& GetEdge(int index) const { return this->edges_[index]; }
	/*��ȡ���(by������)*/
	virtual bool GetVertexByIndex(int vertex_index, TVertex& vertex) const = 0;
	/*��ȡ��Ȩֵ(by���)*/
	virtual bool GetWeight(const TVertex& starting_vertex, const TVertex& ending_vertex, TWeight& weight) const = 0;
	/*��ȡ��Ȩֵ(by������)*/
	virtual bool GetWeightByVertexIndex(int starting_vertex_index, int ending_vertex_index, TWeight& weight) const = 0;
	/*��ȡ���ĵ�һ�����ڽ��*/
	virtual bool GetFirstNeighborVertex(const TVertex& vertex, TVertex& first_neighbor) const = 0;
	/*��ȡ������һ�����ڽ��*/
	virtual bool GetNextNeighborVertex(const TVertex& vertex, const TVertex& neighbor_vertex, TVertex& next_neighbor) const = 0;
	/*��ȡ���Ķ�*/
	int GetVertexDegree(TVertex& vertex)
	{
		if (this->type_ == DIRECTED) return -1;  //���������ͼ������-1������ͼӦ��ȡ����ȣ�
		int vertex_index = GetVertexIndex(vertex);  //��ȡ�������
		return this->degrees_[vertex_index];
	}
	/*��ȡ�������*/
	int GetVertexInDegree(const TVertex& vertex)
	{
		if (this->type_ == UNDIRECTED) return -1;  //���������ͼ������-1������ͼӦ��ȡ�ȣ�
		int vertex_index = GetVertexIndex(vertex);  //��ȡ�������
		return this->in_degrees_[vertex_index];
	}
	/*��ȡ���ĳ���*/
	int GetVertexOutDegree(TVertex vertex)
	{
		if (this->type_ == UNDIRECTED) return -1;  //���������ͼ������-1������ͼӦ��ȡ�ȣ�
		int vertex_index = GetVertexIndex(vertex);  //��ȡ�������
		return this->out_degrees_[vertex_index];
	}
	/*������*/
	virtual bool InsertVertex(const TVertex& vertex) = 0;
	/*�����*/
	virtual bool InsertEdge(const TVertex& starting_vertex, const TVertex& ending_vertex, const TWeight& weight) = 0;
	/*ɾ�����*/
	virtual bool RemoveVertex(const TVertex& vertex) = 0;
	/*ɾ����*/
	virtual bool RemoveEdge(const TVertex& starting_vertex, const TVertex& ending_vertex) = 0;
	/*��ȡ�������*/
	virtual int GetVertexIndex(const TVertex& vertex) const = 0;

	static constexpr int DIRECTED = 1;    //����
	static constexpr int UNDIRECTED = 2;  //����

protected:
	int max_vertex_count_;                    //!< **ͼ�����������**
	TWeight max_weight_;                      //!< **��Ȩֵ����**
	int edge_count_;                          //!< **������**
	int vertex_count_;                        //!< **�������**
	int type_;                                //!< **����(1:����, 2:����)**

	std::vector<TVertex> vertices_;                //!< **���vector**
	std::vector<::Edge<TVertex, TWeight> > edges_;   //!< **��vector**
	std::vector<int> degrees_;                     //!< **��vector(����ͼʹ��)**
	std::vector<int> in_degrees_;                  //!< **���vector(����ͼʹ��)**
	std::vector<int> out_degrees_;                 //!< **����vector(����ͼʹ��)**
};