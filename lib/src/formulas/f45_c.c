// term1 = (a + z - 1) * (a + z - 2)

term1 = sbtimes(sbminus(sbplus(a, z), one), sbminus(sbplus(a, z), two));





// term2 = (z - 1)

term2 = sbminus(z, one);





// term5 = (a + z - y - b) * (a + z - y - b - 1)

term5 = sbtimes(sbminus(sbminus(sbplus(a, z), y), b), sbminus(sbminus(sbminus(sbplus(a, z), y), b), one));





// term6 = (y + b) * (y + b - 1)

term6 = sbtimes(sbplus(y, b), sbminus(sbplus(y, b), one));





// term3 = term5 * b + term6 * (a - b)

term3 = sbplus(sbtimes(term5, b), sbtimes(term6, sbminus(a, b)));





// term4 = term5 * sum_delta_in_B + term6 * sum_delta_in_B_complement

term4 = sbplus(sbtimes(term5, sum_delta_in_B), sbtimes(term6, sum_delta_in_B_complement));





// pNum_alpha = 2 * term1 * term2 - (z - 1) * term3 - term1 * y * (z - y)

pNum_alpha = sbminus(sbminus(sbtimes(sbtimes(two, term1), term2), sbtimes(sbminus(z, one), term3)), sbtimes(sbtimes(term1, y), sbminus(z, y)));





// pDen_alpha = term1 * term2

pDen_alpha = sbtimes(term1, term2);





// pDen_beta = term1 * term2

pDen_beta = sbtimes(term1, term2);





// pNum_beta = term2 * term4 + term1 * (b_1 * y * (z - y) - term2 * b_w)

pNum_beta = sbplus(sbtimes(term2, term4), sbtimes(term1, sbminus(sbtimes(sbtimes(b_1, y), sbminus(z, y)), sbtimes(term2, b_w))));




