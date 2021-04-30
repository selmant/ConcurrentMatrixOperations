//
// Created by selmant on 19.12.2020.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H


class Matrix {
public:
    Matrix(int row_count, int column_count);
    ~Matrix();

    /**
     * Get value of matrix with given row and count. Throws std::invalid_argument.
     * @param row Nth row of matrix. Must be more than zero and less than matrix's row size
     * @param column Nth column of matrix. Must be more than zero and less than matrix's column size
     */
    int getData(int row, int column) const;

    /**
     * Set value of matrix with given row and count. Throws std::invalid_argument.
     * @param row Nth row of matrix. Must be more than zero and less than matrix's row size
     * @param column Nth column of matrix. Must be more than zero and less than matrix's column size
     * @param value Value to be set.
     */
    void setData(int row, int column, int value);

    int getRowCount() const;

    int getColumnCount() const;

    /**
     * Calculate all mean value of cells neighbours with multi thread.
     * @param thread_count Thread count to use. Default thread count is .
     * @return New matrix with calculated values.
     */
    Matrix getMeanOfAllCell(int thread_count = 4);

private:
    int m_row_count;
    int m_column_count;
    int* m_data;
};


#endif //MATRIX_MATRIX_H
