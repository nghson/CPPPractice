#ifndef MATRIX_MULT_H
#define MATRIX_MULT_H

#include <vector>

void mult_recur(const std::vector<float>& A, int A_x, int A_y,
                const std::vector<float>& B, int B_x, int B_y,
                std::vector<float>& C, int C_x, int C_y,
                int n, int sz);

#endif
