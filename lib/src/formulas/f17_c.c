
// term1 = (a - b) * (a - b - 1)

term1 = sbtimes(sbminus(a, b), sbminus(sbminus(a, b), one));





// term2 = b * (b - 1)

term2 = sbtimes(b, sbminus(b, one));





// term3 = a * (a - 1)

term3 = sbtimes(a, sbminus(a, one));





// term4 = term1 * y + term2 * (z - y)

term4 = sbplus(sbtimes(term1, y), sbtimes(term2, sbminus(z, y)));





// pNum_alpha = a * (2 * (a - 1) - b * (a - b)) - (term1 * y + term2 * (z - y))

pNum_alpha = sbminus(sbtimes(a, sbminus(sbtimes(two, sbminus(a, one)), sbtimes(b, sbminus(a, b)))), sbplus(sbtimes(term1, y), sbtimes(term2, sbminus(z, y))));





// pDen_alpha = term3

pDen_alpha = term3;





// pDen_beta = term3 * (a - 2)

pDen_beta = sbtimes(term3, sbminus(a, two));





// pNum_beta = a * (term1 * sum_delta_in_B + term2 * sum_delta_in_B_complement) + (a - 2) * (b_1 * term4 - term3 * b_w)

pNum_beta = sbplus(sbtimes(a, sbplus(sbtimes(term1, sum_delta_in_B), sbtimes(term2, sum_delta_in_B_complement))), sbtimes(sbminus(a, two), sbminus(sbtimes(b_1, term4), sbtimes(term3, b_w))));




