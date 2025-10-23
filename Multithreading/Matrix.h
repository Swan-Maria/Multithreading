#pragma once
#include <vector>

class Matrix
{
public:
	Matrix(size_t rows, size_t cols);

	size_t cols() const;
	size_t rows() const;
	int& at(size_t row, size_t col);
	int at(size_t row, size_t col) const;

	void print() const;

private:
	void RandomFill();
	std::vector<std::vector<int>> _matrix;
	size_t rows_;
	size_t cols_;
};
