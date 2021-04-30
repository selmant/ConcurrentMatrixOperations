//
// Created by selmant on 19.12.2020.
//

#include "Matrix.h"

#include <stdexcept>
#include <vector>
#include <deque>

#include "MatrixMeanWorker.h"

Matrix::Matrix(int row_count, int column_count) :
        m_column_count(column_count),
        m_row_count(row_count)
{
    m_data = new int[row_count * column_count];
}

Matrix::~Matrix()
{
    delete[] m_data;
}

int Matrix::getData(int row, int column) const
{
    if (row >= 0 && column >= 0 && row < m_row_count && column < m_column_count)
        return m_data[row * m_column_count + column];
    else
        throw std::invalid_argument("invalid indexes");
}

void Matrix::setData(int row, int column, int value)
{
    if (row >= 0 && column >= 0 && row < m_row_count && column < m_column_count)
        m_data[row * m_column_count + column] = value;
    else
        throw std::invalid_argument("invalid indexes");
}

int Matrix::getRowCount() const
{
    return m_row_count;
}

int Matrix::getColumnCount() const
{
    return m_column_count;
}

Matrix Matrix::getMeanOfAllCell(int thread_count /* Default 4*/)
{
    Matrix new_matrix(m_row_count, m_column_count);
    std::deque<MatrixMeanWorker> workers;

    int cell_count = m_column_count * m_row_count;
    for (int thread = 0; thread < thread_count; thread++)
    {
        int chunk_start = cell_count / thread_count * thread;
        int chunk_end = cell_count / thread_count * (thread + 1);
        workers.emplace_back(*this, new_matrix, chunk_start, chunk_end);
    }

    // Wait for all threads in workers.
    for (MatrixMeanWorker &worker : workers)
    {
        worker.waitForFinish();
    }

    return new_matrix;

}
