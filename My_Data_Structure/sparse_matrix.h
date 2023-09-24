#pragma once

#include <iostream>
#include <exception>
#include <algorithm>

template<typename T>
struct TriTuple
{
	int row;  /*行索引*/
	int col;  /*列索引*/
	T value;  /*值*/

	TriTuple<T>& operator=(const TriTuple<T>& tri_tuple)
	{
		if (this != &tri_tuple)
		{
			row = tri_tuple.row;
			col = tri_tuple.row;
			value = tri_tuple.value;
		}
		return *this;
	}
};

template<typename T> class SparseMatrix;
template<typename T> std::ostream& operator<<(std::ostream& out, const SparseMatrix<T>& sparse_matirx);
template<typename T> std::istream& operator>>(std::istream& in, const SparseMatrix<T>& sparse_matirx);

template<typename T>
class SparseMatrix
{
public:
	explicit SparseMatrix(int capacity = 100);
	SparseMatrix(const SparseMatrix<T>& sparse_matrix);
	~SparseMatrix() { delete[] elements; }

	/*获取行数*/
	int Rows() const { return rows_; }
	/*设置行数*/
	void SetRows(int rows) { rows_ = rows; }
	/*获取行数*/
	int Cols() const { return cols_; }
	/*设置行数*/
	void SetCols(int cols) { cols_ = cols; }
	/*获取元素数*/
	int Size() const { return size_; }
	/*设置元素数*/
	void SetSize(int size) { size_ = size; }
	/*获取容量*/
	int Capacity() const { return capacity_; }
	/*设置最大元素数*/
	void SetCapacity(int capacity) { capacity_ = capacity; }
	/*获取元素*/
	bool Element(int row, int col, T& value);
	/*添加（替换）元素*/
	bool SetElement(int row, int col, T& value);
	/*转置运算*/
	SparseMatrix<T>* Transpose();
	/*快速转置运算*/
	SparseMatrix<T>* FastTranspose();
	//当前矩阵与sparse_matrix相加
	SparseMatrix<T> Add(SparseMatrix<T>& sparse_matrix);
	//当前矩阵与sparse_matrix相乘
	SparseMatrix<T> Multiply(SparseMatrix<T>& sparse_matrix);

	/*打印稀疏矩阵*/
	friend std::ostream& operator<< <>(std::ostream& out, SparseMatrix<T>& sparse_matrix);
	/*输入稀疏矩阵*/
	friend std::istream& operator>> <>(std::istream& in, SparseMatrix<T>& sparse_matrix);
	
private:
	int rows_;  /*行数*/
	int cols_;  /*列数*/
	int size_;  /*当前元素数*/
	int capacity_;  /*最大元素数*/
	TriTuple<T>* elements;  /*元素数组*/
};

template<typename T>
inline SparseMatrix<T>::SparseMatrix(int capacity) :rows_(0), cols_(0), size_(0), capacity_(capacity)
{
	if (capacity <= 0) throw std::length_error("wrong max size");
	elements = new TriTuple<T>[capacity];
	if (!elements) throw std::bad_alloc(); 
}

template<typename T>
inline SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& sparse_matrix):
	rows_(sparse_matrix.Rows()), cols_(sparse_matrix.Cols()), size_(sparse_matrix.Size()), capacity_(sparse_matrix.Capacity())
{
	elements = new SparseMatrix<T>[Capacity()];
	if (!elements) throw std::bad_alloc();
	for (int i = 0; i < size_; i++) elements[i] = sparse_matrix.elements[i];
}

template<typename T>
inline bool SparseMatrix<T>::Element(int row, int col, T& value)
{
	for (int i = 0; i < this->Size(); i++)
	{
		if (elements[i].row == row && elements[i].col == col)
			value = elements[i].value;
		return true;
	}
	return false;
}

template<typename T>
void Swap(TriTuple<T>* a, TriTuple<T>* b)
{
	TriTuple<T> tmp = *a;
	*a = *b;
	*b = tmp;
}

template<typename T>
inline bool SparseMatrix<T>::SetElement(int row, int col, T& value)
{
	if (row > this->Rows() || col >= this->Cols()) return false;
	if (this->Size() == this->Capacity() || this->Size() == this->Rows() * this->Cols()) return false;
	/*获取该位置在elements_数组中对应的索引*/
	int index = -1;
	for (int i = 0; i < this->Size(); i++)
	{
		if ((this->elements[i].row > row) || (this->elements[i].row == row && this->elements[i].col >= col))
		{
			index = i;
			break;
		}
	}
	/*更新非0元素的情况处理*/
	if (index != -1 && this->elements[index].row == row && this->elements[index].col == col)
	{
		this->elements[index].value = value;
		return true;
	}
	/*插入新元素的情况处理*/
	if (index == -1) index = this->Size();
	this->elements[this->size_].row = row;
	this->elements[this->size_].col = col;
	this->elements[this->size_].value = value;
	for (int i = this->Size(); i > index; i--) swap(&this->elements[i], &this->elements[i - 1]);
	this->size_++;
	return true;
}

template<typename T>
inline SparseMatrix<T>* SparseMatrix<T>::Transpose()
{
	SparseMatrix<T>* trans_sparse_matrix = new SparseMatrix<T>(this->Capacity());
	trans_sparse_matrix->SetRows(this->Cols());
	trans_sparse_matrix->SetCols(this->Rows());
	trans_sparse_matrix->SetSize(this->Size());

	if (this->Size() == 0)return trans_sparse_matrix;

	/*转置*/
	int cur_elements_index = 0;
	for (int row = 0; row < this->Cols(); row++)  /*遍历本数组cols，作为转置数组的行row*/
	{
		for (int i = 0; i < this->Size(); i++)  /*遍历本数组elements*/
		{
			if (this->elements[i].col == row)  /*如果本数组当前elements元素的列号 == row*/
			{
				trans_sparse_matrix->elements[cur_elements_index].row = row;  /*设置转置矩阵当前elements元素的行号*/
				trans_sparse_matrix->elements[cur_elements_index].col = this->elements[i].row;  /*设置转置矩阵当前elements元素的列号*/
				trans_sparse_matrix->elements[cur_elements_index].value = this->elements[i].value;  /*设置转置矩阵当前elements元素的value*/
				cur_elements_index++;
			}
		}
	}

	return trans_sparse_matrix;
}

template<typename T>
inline SparseMatrix<T>* SparseMatrix<T>::FastTranspose()
{
	/*初始化辅助数组*/
	int* row_size = new int(this->Cols());  /*转置矩阵各行元素数量*/
	int* iterator_positions = new int(this->Cols());  /*转置矩阵各行在elements数组的遍历位置*/

	/*转置矩阵分配内存*/
	SparseMatrix<T>* trans_sparse_matrix = new SparseMatrix<T>(this->Capacity());
	if (!trans_sparse_matrix) throw std::bad_alloc();
	trans_sparse_matrix->SetRows(this->Cols());
	trans_sparse_matrix->SetCols(this->Rows());
	trans_sparse_matrix->SetSize(this->Size());

	/*size为0情况处理*/
	if (this->Size() == 0) return trans_sparse_matrix;

	/*构造row_sizes*/
	for (int i = 0; i < this->Cols(); i++) row_size[i] = 0;
	for (int i = 0; i < this->Size(); i++)
	{
		int cur_row = this->elements[i].col;
		row_size[cur_row]++;
	}

	/*构造iterator_positions*/
	iterator_positions[0] = 0;
	for (int row = 1; row < this->Cols(); row++)
		iterator_positions[row] = iterator_positions[row - 1] + row_size[row - 1];

	/*快速转置*/
	for (int i = 0; i < this->Size(); i++)
	{
		int row = this->elements[i].col;
		int cur_elements_index = iterator_positions[row];
		trans_sparse_matrix->elements[cur_elements_index].row = this->elements[i].col;
		trans_sparse_matrix->elements[cur_elements_index].col = this->elements[i].row;
		trans_sparse_matrix->elements[cur_elements_index].value = this->elements[i].value;
		iterator_positions[row]++;
	}

	delete[] iterator_positions;
	delete[] row_size;

	return trans_sparse_matrix;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, SparseMatrix<T>& sparse_matrix)
{
	out << "rows = " << sparse_matrix.Rows() << '\n';
	out << "cols = " << sparse_matrix.Cols() << '\n';

	out << "NonZero element count:" << sparse_matrix.Size() << '\n';

	for (int i = 0; i < sparse_matrix.Size(); i++)
		out << "sparse_matrix[" << sparse_matrix.elements[i].row << "][" 
		<< sparse_matrix.elements[i].col << "] = " 
		<< sparse_matrix.elements[i].value << '\n';

	return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, SparseMatrix<T>& sparse_matrix)
{
	std::cout << "输入rows, cols和size\n";
	int rows = 0, cols = 0, size = 0;
	in >> rows >> cols >> size;
	if (size > sparse_matrix.Capacity()) throw std::length_error("size wrong");
	sparse_matrix.SetRows(rows);
	sparse_matrix.SetCols(cols);
	sparse_matrix.SetSize(size);

	for (int i = 0; i < sparse_matrix.Size(); i++)
	{
		std::cout << "输入第" << i << "个row, column和term的值\n";
		in >> sparse_matrix.elements[i].row > sparse_matrix.elements[i].col >> sparse_matrix.elements[i].value;
	}
	std::cout << sparse_matrix << '\n';
	return in;
}