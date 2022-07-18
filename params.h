#include <string>
extern int N;              // division
extern ldouble L;          // length of range
extern int diff_precision; // error: o(h^m) (h = L / N, m = diff_precision)
extern ldouble om, omx, r_e, mu;
extern ldouble D_e, a;
void export_params(std::string path_name, int pot_type, int vals_prec);
