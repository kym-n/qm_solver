#include "Eigen/Eigen"
using namespace Eigen;

long factorial(int k)
{
    long ans = 1;
    for (int i = 1; i <= k; i++)
    {
        ans *= i;
    }
    return ans;
}

// returns matrix of -d^2/dr^2 with precision of o(h^m)
SparseMatrix<double> diff(int m, int N)
{
    int n = m / 2;
    MatrixXd A(n + 1, n + 1);
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            A(j, i) = pow(i, j * 2) * (factorial(n * 2) / factorial(j * 2));
        }
    }
    VectorXd b = VectorXd::Zero(n + 1);
    b(1) = factorial(n * 2);
    VectorXd x = A.fullPivLu().solve(b);

    SparseMatrix<double> T(N, N);
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
