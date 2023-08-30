#include <vector>

using std::vector;

inline int ind(int row, int col, int sz)
{
        return row * sz + col;
}

void mult_recur(const vector<float>& A, int A_x, int A_y,
                const vector<float>& B, int B_x, int B_y,
                vector<float>& C, int C_x, int C_y,
                int n, int sz)
{
        if (n == 1) {
                C[ind(C_x, C_y, sz)] += A[ind(A_x, A_y, sz)] * B[ind(B_x, B_y, sz)];
                return;
        }

        // A11, B11, C11
        mult_recur(A, A_x, A_y,
                   B, B_x, B_y,
                   C, C_x, C_y,
                   n / 2, sz);
        // A12, B21, C11
        mult_recur(A, A_x, A_y + n / 2,
                   B, B_x + n / 2, B_y,
                   C, C_x, C_y,
                   n / 2, sz);

        // A11, B12, C12
        mult_recur(A, A_x, A_y,
                   B, B_x, B_y + n / 2,
                   C, C_x, C_y + n / 2,
                   n / 2, sz);
        // A12, B22, C12
        mult_recur(A, A_x, A_y + n / 2,
                   B, B_x + n / 2, B_y + n / 2,
                   C, C_x, C_y + n / 2,
                   n / 2, sz);

        // A21, B11, C21
        mult_recur(A, A_x + n / 2, A_y,
                   B, B_x, B_y,
                   C, C_x + n / 2, C_y,
                   n / 2, sz);
        // A22, B21, C21
        mult_recur(A, A_x + n / 2, A_y + n / 2,
                   B, B_x + n / 2, B_y,
                   C, C_x + n / 2, C_y,
                   n / 2, sz);

        // A21, B12, C22
        mult_recur(A, A_x + n / 2, A_y,
                   B, B_x, B_y + n / 2,
                   C, C_x + n / 2, C_y + n / 2,
                   n / 2, sz);
        // A22, B22, C22
        mult_recur(A, A_x + n / 2, A_y + n / 2,
                   B, B_x + n / 2, B_y + n / 2,
                   C, C_x + n / 2, C_y + n / 2,
                   n / 2, sz);
}
