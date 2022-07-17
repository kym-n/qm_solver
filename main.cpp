#include <fstream>
#include <iomanip>
#include <iostream>
#include "Eigen/Eigen"
using namespace Eigen;

#include "params.h"
SelfAdjointEigenSolver<SparseMatrix<double>> solve(int pot_type, int l, int diff_precision);

#define __MPI__

#ifdef __MPI__
#include <mpi.h>
#endif

const int vals_prec = 12;
const int vecs_prec = 6;

int main(int argc, char **argv) // pot_type min_l max_l name (N (diff_precision))
{
    /* input */
    int pot_type = atoi(argv[1]);
    int min_l = atoi(argv[2]), max_l = atoi(argv[3]); // pot_type 0: well, 1: harmo, 2: morse
    std::string path_name = "results/" + (std::string)argv[4] + "/";
    if (argc >= 6)
        N = atoi(argv[5]);
    if (argc >= 7)
        diff_precision = atoi(argv[6]);

#ifdef __MPI__
    /* mpi init */
    int myid, procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    if (myid == 0)
#endif
    {
        // output params
        std::cout << "output path: " << path_name << std::endl;
        std::cout << "length: " << L << std::endl;
        std::cout << "divide: " << N << std::endl;
        export_params(path_name, pot_type, vals_prec);
    }

    /* exec */
    clock_t start = clock();
    std::string id_str = "";
#ifdef __MPI__
    // display process id (ex. #000)
    id_str = std::to_string(myid);
    while (id_str.length < 3)
        id_str = '0' + id_str;
    id_str = '#' + id_str + "  ";

    // solve & output for l = min_l...max_l
    for (int l = min_l + myid; l <= max_l; l += procs)
#else
    for (int l = min_l; l <= max_l; l++)
#endif
    {
        // solve
        std::cout << id_str << "solving...(l = " << l << ")" << std::endl;
        SelfAdjointEigenSolver<SparseMatrix<double>> es = solve(pot_type, l, diff_precision);

        // write
        std::cout << id_str << "writing...(l = " << l << ")" << std::endl;
        // eigenvalues to "{l}_vals.txt"
        std::ofstream out_vals(path_name + std::to_string(l) + "_vals.txt");
        out_vals << std::setprecision(vals_prec) << std::fixed << es.eigenvalues() << std::endl;
        out_vals.close();
        // eigenvectors to "{l}_vecs.txt"
        if (N <= 4096)
        {
            std::ofstream out_vecs(path_name + std::to_string(l) + "_vecs.txt");
            out_vecs << std::setprecision(vecs_prec) << std::fixed << es.eigenvectors() << std::endl;
            out_vecs.close();
        }
    }
    clock_t end = clock();
    std::cout << id_str << "total time: " << (double)(end - start) / CLOCKS_PER_SEC << "s." << std::endl;

#ifdef __MPI__
    MPI_Finalize();
#endif
    return 0;
}
