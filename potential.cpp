#include <cmath>
#include "opts.h"
#include "params.h"

// morse potential
ldouble morse(ldouble r)
{
    ldouble w = 1.0 - exp(-a * (r - r_e));
    return D_e * (w * w - 1);
}

// harmonic oscillator
ldouble harmo(ldouble r)
{
    ldouble w = a * (r - r_e);
    return D_e * w * w;
}

// well potential
ldouble well(ldouble r)
{
    if (1.5 < r && r < 2.5)
        return 0;
    else
        return 100000000;
}

// returns potential as function
ldouble (*get_pot(int type))(ldouble)
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
