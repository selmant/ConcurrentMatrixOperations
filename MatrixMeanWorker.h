//
// Created by selmant on 20.12.2020.
//

#ifndef MATRIX_MATRIXMEANWORKER_H
#define MATRIX_MATRIXMEANWORKER_H

#include <thread>
#include "Matrix.h"

class MatrixMeanWorker
{
public:

    /**
     * Wait worker until it finishes.
     */
    void waitForFinish();
    /**
     * Create MatrixMeanWorker and start thread immediately.
     * @param input_matrix Input matrix to calculate mean from.
     * @param output_matrix Output matrix to assign mean values.
     * @param chunk_start Start point of thread's workspace. calculate as ( row_count * row ) + column
     * @param chunk_end End point of thread's workspace. calculate as ( row_count * row ) + column
     */
    MatrixMeanWorker(const Matrix &input_matrix, Matrix& output_matrix, int chunk_start, int chunk_end);

    //delete copy and move
    MatrixMeanWorker(const MatrixMeanWorker&) = delete;
    MatrixMeanWorker& operator=(const MatrixMeanWorker&) = delete;
private:

    /**
     * Entry point of thread.
     */
    void start();
    const Matrix& m_input_matrix;
    Matrix& m_output_matrix;
    int m_start_row, m_start_column, m_end_row, m_end_column;
    std::thread m_thread;

    /**
     * Calculate mean of neighbours for given row and column.
     */
    int calculateMean(int row, int column);
};


#endif //MATRIX_MATRIXMEANWORKER_H
