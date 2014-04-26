
// term1 = (z - y) * (z - y - 1)

term1 = sbtimes(sbminus(z, y), sbminus(sbminus(z, y), one));





// term2 = y * (y - 1)

term2 = sbtimes(y, sbminus(y, one));





// pNum_alpha = z * (2 * (z - 1) - y * (z - y)) - (term1 * b + term2 * (a - b))

pNum_alpha = sbminus(sbtimes(z, sbminus(sbtimes(two, sbminus(z, one)), sbtimes(y, sbminus(z, y)))), sbplus(sbtimes(term1, b), sbtimes(term2, sbminus(a, b))));





// pDen_alpha = z * (z - 1)

pDen_alpha = sbtimes(z, sbminus(z, one));





// pDen_beta = z * (z - 1)

pDen_beta = sbtimes(z, sbminus(z, one));





// pNum_beta = term1 * sum_delta_in_B + term2 * sum_delta_in_B_complement + z * (y * (z - y) * b_1 - (z - 1) * b_w)

pNum_beta = sbplus(sbplus(sbtimes(term1, sum_delta_in_B), sbtimes(term2, sum_delta_in_B_complement)), sbtimes(z, sbminus(sbtimes(sbtimes(y, sbminus(z, y)), b_1), sbtimes(sbminus(z, one), b_w))));




