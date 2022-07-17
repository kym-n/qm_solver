extern int N;              // division
extern double L;           // length of range
extern int diff_precision; // error: o(h^m) (h = L / N, m = diff_precision)
extern double om, omx, omy, r_e, mu;
extern double D_e, a;
void export_params(std::string path_name, int pot_type, int vals_prec);
