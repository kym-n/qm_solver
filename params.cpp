#include <cmath>

int N = 4096;           // division
double L = 8;           // length of range
int diff_precision = 6; // error: o(h^m) (h = L / N, m = diff_precision)

#define BOHR_TO_METOR 5.29177210903e-11  // bohr to m (length)
#define U_TO_E 1822.888486209            // m_u to m_e (mass)
#define HARTREE_TO_CMREV 219474.63136320 // hartree to cm^-1 (energy)

double om = 2358.57 / HARTREE_TO_CMREV;    // hatree
double omx = 14.324109 / HARTREE_TO_CMREV; // hatree
double omy = -2.26e-3 / HARTREE_TO_CMREV;  // hatree
double r_e = 1.09768e-10 / BOHR_TO_METOR;  // bohr
double mu = (28.0134 / 4) * U_TO_E;        // m_e

double D_e = om * om / (4 * omx);   // hatree
double a = om / sqrt(2 * D_e / mu); // bohr^-1
