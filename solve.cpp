#include <ctime>
#include <iostream>
#include "Eigen/Eigen"
using namespace Eigen;

#include "params.h"

// -d^2/dr^2
SparseMatrix<double> diff(int m, int N);
// potential at r
double (*get_pot(int type))(double);

SelfAdjointEigenSolver<SparseMatrix<double>> solve(int pot_type, int l, int diff_precision)
{
    // T: kinetic part
    SparseMatrix<double> T = diff(diff_precision, N); // -d^2/dr^2
    T /= (2.0 * mu * pow(L / N, 2));

    // V: potential part
    double (*pot)(double) = get_pot(pot_type); // 0: well, 1: harmo, 2: morse
    SparseMatrix<double> V(N, N);
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            V.insert(i, i) = pot(L * i / N) + ((l == 0) ? 0 : l * (l + 1) / (mu * pow(L / N, 2)));
        }
        else
        {
            V.insert(i, i) = pot(L * i / N) + (l * (l + 1) / (2.0 * mu * pow(L * i / N, 2)));
        }
    }

    // H: Hamiltonian matrix
    SparseMatrix<double> H = T + V;

    // solve eigenvalue problem
    clock_t start = clock();
    SelfAdjointEigenSolver<SparseMatrix<double>> es(H);
    clock_t end = clock();
    std::cout << "time: " << (double)(end - start) / CLOCKS_PER_SEC << "s. (l = " << l << ")" << std::endl;

    return es;
}
