//
// Created by selmant on 20.12.2020.
//

#include "MatrixMeanWorker.h"

MatrixMeanWorker::MatrixMeanWorker(const Matrix &input_matrix, Matrix &output_matrix, int chunk_start, int chunk_end)
        : m_output_matrix(output_matrix), m_input_matrix(input_matrix)
{
    m_start_row = chunk_start / input_matrix.getColumnCount();
    m_start_column = chunk_start % input_matrix.getColumnCount();

    m_end_row = chunk_end / input_matrix.getColumnCount();
    m_end_column = chunk_end % input_matrix.getColumnCount();

    if (m_end_column == 0)
        m_end_column = input_matrix.getColumnCount();
    m_thread = std::thread(&MatrixMeanWorker::start, this);
}

void MatrixMeanWorker::waitForFinish()
{
    m_thread.join();
}

void MatrixMeanWorker::start()
{
    //set data for first row.
    for (int column = m_start_column; column < m_input_matrix.getColumnCount(); column++)
    {
        int mean = calculateMean(m_start_row, column);
        m_output_matrix.setData(m_start_row, column, mean);
    }

    //set data for all columns in row range but last and first row.
    for (int row = m_start_row + 1; row < m_end_row - 1; row++)
    {
        for (int column = 0; column < m_input_matrix.getColumnCount(); column++)
        {
            int mean = calculateMean(row, column);
            m_output_matrix.setData(row, column, mean);
        }
    }

    //set data for last row.
    for (int column = 0; column < m_end_column; column++)
    {
        int mean = calculateMean(m_end_row - 1, column);
        m_output_matrix.setData(m_end_row - 1, column, mean);
    }
}

int MatrixMeanWorker::calculateMean(int row, int column)
{
    bool value_on_left = column != 0;
    bool value_on_right = column != m_input_matrix.getColumnCount() - 1;
    bool value_on_top = row != 0;
    bool value_on_bottom = row != m_input_matrix.getRowCount() - 1;

    int sums = 0;
    sums += value_on_left ? m_input_matrix.getData(row, column - 1) : 0;
    sums += value_on_right ? m_input_matrix.getData(row, column + 1) : 0;
    sums += value_on_top ? m_input_matrix.getData(row - 1, column) : 0;
    sums += value_on_bottom ? m_input_matrix.getData(row + 1, column) : 0;

    return sums / 4;
}

