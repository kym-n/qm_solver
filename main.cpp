#include <fstream>
#include <iomanip>
#include <iostream>
#include "Eigen/Eigen"
using namespace Eigen;

#include "params.h"
SelfAdjointEigenSolver<SparseMatrix<double>> solve(int pot_type, int l, int diff_precision);

int main(int argc, char **argv) // pot_type min_l max_l name (N (diff_precision))
{
    // input
    int pot_type = atoi(argv[1]);
    int min_l = atoi(argv[2]), max_l = atoi(argv[3]); // pot_type 0: well, 1: harmo, 2: morse
    std::string path_name = "results/" + (std::string)argv[4] + "/";
    if (argc >= 6)
        N = atoi(argv[5]);
    if (argc >= 7)
        diff_precision = atoi(argv[6]);

    std::cout << "output path: " << path_name << std::endl;
    std::cout << "length: " << L << std::endl;
    std::cout << "divide: " << N << std::endl;

    // output params
    {
        std::ofstream out_params(path_name + "params.txt");
        out_params << "diff_precision: " << diff_precision << std::endl;
        out_params << "L = " << L << std::endl;
        out_params << "N = " << N << std::endl;
        out_params << "om = " << om << ", omx = " << omx << std::endl;
        out_params << "mu = " << mu << std::endl;
        out_params << "r_e = " << r_e << std::endl;
        out_params << "a = " << a << std::endl;
        out_params << "D_e = " << D_e << std::endl;
        out_params.close();
    }

    // output exact values
    {
        std::ofstream out_vals(path_name + "ex_vals.txt");
        out_vals << std::setprecision(10) << std::fixed;
        switch (pot_type)
        {
        case 1:
            for (int i = 0; i < N; i++)
            {
                double num = 0.5 + i;
                out_vals << om * num << std::endl;
            }
            break;

        case 2:
        default:
            for (int i = 0;; i++)
            {
                double num = 0.5 + i;
                out_vals << om * num - omx * num * num - D_e << std::endl;
                if (num >= om / (2.0 * omx))
                    break;
            }
            break;
        }
        out_vals.close();
    }

    // solve & output for l = 0...max_l
    clock_t start = clock();
    for (int l = min_l; l <= max_l; l++)
    {
        std::cout << "solve on l = " << l << "." << std::endl;
        SelfAdjointEigenSolver<SparseMatrix<double>> es = solve(pot_type, l, diff_precision);

        std::cout << "writing..." << std::endl;
        std::ofstream out_vals(path_name + std::to_string(l) + "_vals.txt"), out_vecs(path_name + std::to_string(l) + "_vecs.txt");
        out_vals << std::setprecision(10) << std::fixed << es.eigenvalues() << std::endl;
        out_vecs << std::setprecision(6) << std::fixed << es.eigenvectors() << std::endl;
        out_vals.close();
        out_vecs.close();
    }
    clock_t end = clock();
    std::cout << "total time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}
