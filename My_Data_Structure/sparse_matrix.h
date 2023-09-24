#pragma once

#include <iostream>
#include <exception>
#include <algorithm>

template<typename T>
struct TriTuple
{
	int row;  /*������*/
	int col;  /*������*/
	T value;  /*ֵ*/

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

	/*��ȡ����*/
	int Rows() const { return rows_; }
	/*��������*/
	void SetRows(int rows) { rows_ = rows; }
	/*��ȡ����*/
	int Cols() const { return cols_; }
	/*��������*/
	void SetCols(int cols) { cols_ = cols; }
	/*��ȡԪ����*/
	int Size() const { return size_; }
	/*����Ԫ����*/
	void SetSize(int size) { size_ = size; }
	/*��ȡ����*/
	int Capacity() const { return capacity_; }
	/*�������Ԫ����*/
	void SetCapacity(int capacity) { capacity_ = capacity; }
	/*��ȡԪ��*/
	bool Element(int row, int col, T& value);
	/*��ӣ��滻��Ԫ��*/
	bool SetElement(int row, int col, T& value);
	/*ת������*/
	SparseMatrix<T>* Transpose();
	/*����ת������*/
	SparseMatrix<T>* FastTranspose();
	//��ǰ������sparse_matrix���
	SparseMatrix<T> Add(SparseMatrix<T>& sparse_matrix);
	//��ǰ������sparse_matrix���
	SparseMatrix<T> Multiply(SparseMatrix<T>& sparse_matrix);

	/*��ӡϡ�����*/
	friend std::ostream& operator<< <>(std::ostream& out, SparseMatrix<T>& sparse_matrix);
	/*����ϡ�����*/
	friend std::istream& operator>> <>(std::istream& in, SparseMatrix<T>& sparse_matrix);
	
private:
	int rows_;  /*����*/
	int cols_;  /*����*/
	int size_;  /*��ǰԪ����*/
	int capacity_;  /*���Ԫ����*/
	TriTuple<T>* elements;  /*Ԫ������*/
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
	/*��ȡ��λ����elements_�����ж�Ӧ������*/
	int index = -1;
	for (int i = 0; i < this->Size(); i++)
	{
		if ((this->elements[i].row > row) || (this->elements[i].row == row && this->elements[i].col >= col))
		{
			index = i;
			break;
		}
	}
	/*���·�0Ԫ�ص��������*/
	if (index != -1 && this->elements[index].row == row && this->elements[index].col == col)
	{
		this->elements[index].value = value;
		return true;
	}
	/*������Ԫ�ص��������*/
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

	/*ת��*/
	int cur_elements_index = 0;
	for (int row = 0; row < this->Cols(); row++)  /*����������cols����Ϊת���������row*/
	{
		for (int i = 0; i < this->Size(); i++)  /*����������elements*/
		{
			if (this->elements[i].col == row)  /*��������鵱ǰelementsԪ�ص��к� == row*/
			{
				trans_sparse_matrix->elements[cur_elements_index].row = row;  /*����ת�þ���ǰelementsԪ�ص��к�*/
				trans_sparse_matrix->elements[cur_elements_index].col = this->elements[i].row;  /*����ת�þ���ǰelementsԪ�ص��к�*/
				trans_sparse_matrix->elements[cur_elements_index].value = this->elements[i].value;  /*����ת�þ���ǰelementsԪ�ص�value*/
				cur_elements_index++;
			}
		}
	}

	return trans_sparse_matrix;
}

template<typename T>
inline SparseMatrix<T>* SparseMatrix<T>::FastTranspose()
{
	/*��ʼ����������*/
	int* row_size = new int(this->Cols());  /*ת�þ������Ԫ������*/
	int* iterator_positions = new int(this->Cols());  /*ת�þ��������elements����ı���λ��*/

	/*ת�þ�������ڴ�*/
	SparseMatrix<T>* trans_sparse_matrix = new SparseMatrix<T>(this->Capacity());
	if (!trans_sparse_matrix) throw std::bad_alloc();
	trans_sparse_matrix->SetRows(this->Cols());
	trans_sparse_matrix->SetCols(this->Rows());
	trans_sparse_matrix->SetSize(this->Size());

	/*sizeΪ0�������*/
	if (this->Size() == 0) return trans_sparse_matrix;

	/*����row_sizes*/
	for (int i = 0; i < this->Cols(); i++) row_size[i] = 0;
	for (int i = 0; i < this->Size(); i++)
	{
		int cur_row = this->elements[i].col;
		row_size[cur_row]++;
	}

	/*����iterator_positions*/
	iterator_positions[0] = 0;
	for (int row = 1; row < this->Cols(); row++)
		iterator_positions[row] = iterator_positions[row - 1] + row_size[row - 1];

	/*����ת��*/
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
	std::cout << "����rows, cols��size\n";
	int rows = 0, cols = 0, size = 0;
	in >> rows >> cols >> size;
	if (size > sparse_matrix.Capacity()) throw std::length_error("size wrong");
	sparse_matrix.SetRows(rows);
	sparse_matrix.SetCols(cols);
	sparse_matrix.SetSize(size);

	for (int i = 0; i < sparse_matrix.Size(); i++)
	{
		std::cout << "�����" << i << "��row, column��term��ֵ\n";
		in >> sparse_matrix.elements[i].row > sparse_matrix.elements[i].col >> sparse_matrix.elements[i].value;
	}
	std::cout << sparse_matrix << '\n';
	return in;
}