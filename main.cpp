#include <iostream>
#include <fstream>
#include <random>
#include <thread>

#include "Matrix.h"

int main()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    int row_count, column_count, thread_count;
    std::ifstream input_reader("input.txt");
    input_reader >> row_count >> column_count >> thread_count;

    Matrix matrix1(row_count, column_count);
    for (int i = 0; i < matrix1.getRowCount(); i++)
    {
        for (int j = 0; j < matrix1.getColumnCount(); j++)
        {
            matrix1.setData(i, j, dist(mt));
        }
    }

    Matrix matrix2 = matrix1.getMeanOfAllCell(thread_count);
    std::ofstream output("matrix2.txt");
    for (int i = 0; i < matrix1.getRowCount(); i++)
    {
        for (int j = 0; j < matrix1.getColumnCount(); j++)
        {
            output << matrix2.getData(i, j) << ' ';
        }
        output << '\n';
    }


    std::cout << "Done!" << std::endl;
    return 0;
}

