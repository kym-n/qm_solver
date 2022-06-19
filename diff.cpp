#include "Eigen/Eigen"
using namespace Eigen;

// returns matrix of -d^2/dr^2 with precision of o(h^m)
SparseMatrix<double> diff(int m, int N)
{
    SparseMatrix<double> T(N, N);
    switch (m)
    {
    case 2: // error: o(h^2)
        for (size_t i = 0; i < N; i++)
        {
            T.insert(i, i) = 2.0;
            if (i >= 1)
            {
                T.insert(i, i - 1) = -1.0;
                T.insert(i - 1, i) = -1.0;
            }
        }
        return T;

    case 4: // error: o(h^4)
        for (size_t i = 0; i < N; i++)
        {
            T.insert(i, i) = 2.5;
            if (i >= 1)
            {
                T.insert(i, i - 1) = -4.0 / 3;
                T.insert(i - 1, i) = -4.0 / 3;
            }
            if (i >= 2)
            {
                T.insert(i, i - 2) = 1.0 / 12;
                T.insert(i - 2, i) = 1.0 / 12;
            }
        }
        return T;

    case 6: // error: o(h^6)
    default:
        for (size_t i = 0; i < N; i++)
        {
            T.insert(i, i) = 21.0 / 8;
            if (i >= 1)
            {
                T.insert(i, i - 1) = -64.0 / 45;
                T.insert(i - 1, i) = -64.0 / 45;
            }
            if (i >= 2)
            {
                T.insert(i, i - 2) = 1.0 / 9;
                T.insert(i - 2, i) = 1.0 / 9;
            }
            if (i >= 4)
            {
                T.insert(i, i - 4) = -1.0 / 720;
                T.insert(i - 4, i) = -1.0 / 720;
            }
        }
        return T;
    }
}
