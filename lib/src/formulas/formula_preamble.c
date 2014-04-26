bfunctiontype *pFormula;
baseint w, base_b, base_sum_of_A;
bz_t *pNum_alpha, *pDen_alpha, *pNum_beta, *pDen_beta;
bz_t *y, *b, *a, *g, *sum_of_A, *z, *sum_delta_in_B; 
bz_t *sum_delta_in_B_complement, *b_w, *b_1, *one, *two, *four;
bz_t *term0, *term1, *term2, *term3, *term4, *term5, *term6, *term7;
bz_t *answer, *return_value;
bq_t *pAlpha, *pBeta;

start_garbage;

one = base2sbig(1);
two = base2sbig(2);
four = base2sbig(4);
y = base2sbig(triple_y(pT));
base_b = list_length(triple_B(pT));
b = base2sbig(base_b);
a = base2sbig(base_b + list_length(triple_Bc(pT)));
g = base2sbig(div_genus(pDiv));

base_sum_of_A = medint_list_sum(triple_B(pT)) + 
medint_list_sum(triple_Bc(pT));

sum_of_A = base2sbig(base_sum_of_A);

z = base2sbig(div_genus(pDiv) - base_sum_of_A);

sum_delta_in_B = 
base2sbig(div_sum_delta_in_list(pDiv, triple_B(pT)));

sum_delta_in_B_complement = 
base2sbig(div_sum_delta_in_list(pDiv, triple_Bc(pT)));

w = triple_y(pT) + medint_list_sum(triple_B(pT));
b_w = base2sbig(div_delta(pDiv, w));
b_1 = base2sbig(div_delta(pDiv, 1));

