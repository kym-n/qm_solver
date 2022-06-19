#include <cmath>
#include "params.h"

// morse potential
double morse(double r)
{
    double w = 1.0 - exp(-a * (r - r_e));
    return D_e * (w * w - 1);
}

// harmonic oscillator
double harmo(double r)
{
    double w = a * (r - r_e);
    return D_e * w * w;
}

// well potential
double well(double r)
{
    if (1.5 < r && r < 2.5)
        return 0;
    else
        return 100000000;
}

// returns potential as function
double (*get_pot(int type))(double)
{
    switch (type)
    {
    case 0:
        return well;
    case 1:
        return harmo;
    case 2:
    default:
        return morse;
    }
}
