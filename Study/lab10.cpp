#include <vector>
#include <iostream>

std::vector<std::vector<int>> create2DVector(int row, int col) {
    std::vector<std::vector<int>> matrix(row, std::vector<int>(col, 0));
    return matrix;
}

void Print2DVector(const std::vector<std::vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void FillWithIndices(std::vector<std::vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            matrix[i][j] = i + j;
        }
    }
}

void DoubleElements(std::vector<std::vector<int>> *matrix) {
    for (int i = 0; i < (*matrix).size(); ++i) {
        for (int j = 0; j < (*matrix).at(i).size(); ++j) {
            (*matrix).at(i).at(j) *= 2;
        }
    }
}