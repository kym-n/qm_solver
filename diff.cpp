#include "Eigen/Eigen"
using namespace Eigen;
#include "opts.h"
#include <cmath>
#ifdef __DEBUG__
#include <iostream>
#include <iomanip>
#endif

long factorial(int k)
{
    long ans = 1;
    for (int i = 1; i <= k; i++)
    {
        ans *= i;
    }
    return ans;
}

typedef Vector<ldouble, Dynamic> VectorXld;
typedef Matrix<ldouble, Dynamic, Dynamic> MatrixXld;

// returns matrix of -d^2/dr^2 with precision of o(h^m)
SparseMatrix<ldouble> diff(int m, int N)
{
    int n = m / 2;
    MatrixXld A(n + 1, n + 1);
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            A(j, i) = pow(i, j * 2) * (factorial(n * 2) / factorial(j * 2));
        }
    }
    VectorXld b = VectorXld::Zero(n + 1);
    b(1) = factorial(n * 2);
    VectorXld x = A.fullPivLu().solve(b);
#ifdef __DEBUG__
    std::cout << std::fixed << std::setprecision(20) << A << std::endl;
    std::cout << x << std::endl;
    ldouble a = 0;
#endif
    for (int i = 0; i <= n; i++)
    {
        x(i) = round(x(i) * factorial(n * 2));
        x(i) /= factorial(n * 2);
#ifdef __DEBUG__
        a -= x(i);
    }
    std::cout << a << std::endl;
    std::cout << x << std::endl;
#else
    }
#endif

    SparseMatrix<ldouble>
        T(N, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= n && j <= i; j++)
        {
            if (j == 0)
            {
                T.insert(i, i) = x(0);
            }
            else
            {
                T.insert(i, i - j) = x(j) / 2;
                T.insert(i - j, i) = x(j) / 2;
            }
        }
    }
    return T;
}
