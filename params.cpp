#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

int N = 4096;           // division
double L = 8;           // length of range
int diff_precision = 6; // error: o(h^m) (h = L / N, m = diff_precision)

#define BOHR_TO_METOR 5.29177210903e-11  // bohr to m (length)
#define U_TO_E 1822.888486209            // m_u to m_e (mass)
#define HARTREE_TO_CMREV 219474.63136320 // hartree to cm^-1 (energy)

#define __MORSE__

#ifdef __MORSE__ // direct input constants of morse potential

double r_e = 2.0;
double mu = 12800;
double D_e = 0.45;
double a = 1.25;

double om = a * sqrt(2.0 * D_e / mu);
double omx = om * om / (4.0 * D_e);

#else // input measured values

double om = 2358.57 / HARTREE_TO_CMREV;    // hatree
double omx = 14.324109 / HARTREE_TO_CMREV; // hatree
double r_e = 1.09768e-10 / BOHR_TO_METOR;  // bohr
double mu = (28.0134 / 4) * U_TO_E;        // m_e

double D_e = om * om / (4 * omx);   // hatree
double a = om / sqrt(2 * D_e / mu); // bohr^-1

#endif

// export params & exaxt values of energy
void export_params(std::string path_name, int pot_type, int vals_prec)
{
    // output params
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

    // output exact values
    std::ofstream out_vals(path_name + "ex_vals.txt");
    out_vals << std::setprecision(vals_prec) << std::fixed;
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
