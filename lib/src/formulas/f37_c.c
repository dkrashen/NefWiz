
// term1 = z * (z - 1)

term1 = sbtimes(z, sbminus(z, one));





// term2 = a * (a - 1)

term2 = sbtimes(a, sbminus(a, one));





// term3 = (z - y) * (z - y - 1)

term3 = sbtimes(sbminus(z, y), sbminus(sbminus(z, y), one));





// term4 = y * (y - 1)

term4 = sbtimes(y, sbminus(y, one));





// term5 = (a - b) * (a - b - 1) * y + b * (b - 1) * (z - y)

term5 = sbplus(sbtimes(sbtimes(sbminus(a, b), sbminus(sbminus(a, b), one)), y), sbtimes(sbtimes(b, sbminus(b, one)), sbminus(z, y)));





// pNum_alpha = 2 * term1 * term2 - term2 * (term3 * b + term4 * (a - b)) - term1 * term5

pNum_alpha = sbminus(sbminus(sbtimes(sbtimes(two, term1), term2), sbtimes(term2, sbplus(sbtimes(term3, b), sbtimes(term4, sbminus(a, b))))), sbtimes(term1, term5));





// pDen_alpha = term1 * term2

pDen_alpha = sbtimes(term1, term2);





// pDen_beta = term1 * term2

pDen_beta = sbtimes(term1, term2);





// pNum_beta = term2 * (term3 * sum_delta_in_B + term4 * sum_delta_in_B_complement) + term1 * (b_1 * term5 - b_w * term2)

pNum_beta = sbplus(sbtimes(term2, sbplus(sbtimes(term3, sum_delta_in_B), sbtimes(term4, sum_delta_in_B_complement))), sbtimes(term1, sbminus(sbtimes(b_1, term5), sbtimes(b_w, term2))));




