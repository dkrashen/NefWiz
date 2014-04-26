
// term1 = a * (a - 1)

term1 = sbtimes(a, sbminus(a, one));





// term2 = (a + z - 1) * (a + z - 2)

term2 = sbtimes(sbminus(sbplus(a, z), one), sbminus(sbplus(a, z), two));





// term3 = (a + z - b - y) * (a + z - b - y - 1)

term3 = sbtimes(sbminus(sbminus(sbplus(a, z), b), y), sbminus(sbminus(sbminus(sbplus(a, z), b), y), one));





// term4 = (y + b) * (y + b - 1)

term4 = sbtimes(sbplus(y, b), sbminus(sbplus(y, b), one));





// term5 = (a - b) * (a - b - 1) * y + b * (b - 1) * (z - y)

term5 = sbplus(sbtimes(sbtimes(sbminus(a, b), sbminus(sbminus(a, b), one)), y), sbtimes(sbtimes(b, sbminus(b, one)), sbminus(z, y)));





// pNum_alpha = 2 * term1 * term2 - term1 * (term3 * b + term4 * (a - b)) - term2 * term5

pNum_alpha = sbminus(sbminus(sbtimes(sbtimes(two, term1), term2), sbtimes(term1, sbplus(sbtimes(term3, b), sbtimes(term4, sbminus(a, b))))), sbtimes(term2, term5));





// pDen_alpha = term1 * term2

pDen_alpha = sbtimes(term1, term2);





// pDen_beta = term1 * term2

pDen_beta = sbtimes(term1, term2);





// pNum_beta = term1 * (term3 * sum_delta_in_B + term4 * sum_delta_in_B_complement) + term2 * (b_1 * term5 - b_w * term1)

pNum_beta = sbplus(sbtimes(term1, sbplus(sbtimes(term3, sum_delta_in_B), sbtimes(term4, sum_delta_in_B_complement))), sbtimes(term2, sbminus(sbtimes(b_1, term5), sbtimes(b_w, term1))));




