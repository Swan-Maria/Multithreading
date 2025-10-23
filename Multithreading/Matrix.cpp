#include "Matrix.h"
#include <time.h>
#include <iostream>

Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols)
{
	_matrix.resize(rows_);
	for (auto& row : _matrix)
	{
		row.resize(cols_);
	}
	RandomFill();
}

size_t Matrix::cols() const
{
	return cols_;
}

size_t Matrix::rows() const
{
	return rows_;
}

int& Matrix::at(size_t row, size_t col)
{
	return _matrix[row][col];
}

int Matrix::at(size_t row, size_t col) const
{
	return _matrix[row][col];
}

void Matrix::print() const
{
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			std::cout << _matrix[i][j] << "  ";
		}
		std::cout << '\n';
	}
}

void Matrix::RandomFill()
{
	for (auto& line : _matrix)
	{
		for (auto& elem : line)
		{
			elem = rand() % 100 + 1;
		}
	}
}