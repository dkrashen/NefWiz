
// term1 = (a + z - 1) * (a + z - 2)

term1 = sbtimes(sbminus(sbplus(a, z), one), sbminus(sbplus(a, z), two));





// term2 = (a + z - y - b) * (a + z - y - b - 1)

term2 = sbtimes(sbminus(sbminus(sbplus(a, z), y), b), sbminus(sbminus(sbminus(sbplus(a, z), y), b), one));





// term3 = (y + b) * (y + b - 1)

term3 = sbtimes(sbplus(y, b), sbminus(sbplus(y, b), one));





// pNum_alpha = term1 * (4 * (z - 1) - y * (z - y)) - (z - 1) * (term2 * (2 * b + y) + term3 * (2 * (a - b) + (z - y)))

pNum_alpha = sbminus(sbtimes(term1, sbminus(sbtimes(four, sbminus(z, one)), sbtimes(y, sbminus(z, y)))), sbtimes(sbminus(z, one), sbplus(sbtimes(term2, sbplus(sbtimes(two, b), y)), sbtimes(term3, sbplus(sbtimes(two, sbminus(a, b)), sbminus(z, y))))));





// pDen_alpha = 2 * (z - 1) * term1

pDen_alpha = sbtimes(sbtimes(two, sbminus(z, one)), term1);





// pDen_beta = 2 * (z - 1) * term1

pDen_beta = sbtimes(sbtimes(two, sbminus(z, one)), term1);





// term4 = 2 * sum_delta_in_B + y * b_1

term4 = sbplus(sbtimes(two, sum_delta_in_B), sbtimes(y, b_1));





// term5 = 2 * sum_delta_in_B_complement + (z - y) * b_1

term5 = sbplus(sbtimes(two, sum_delta_in_B_complement), sbtimes(sbminus(z, y), b_1));





// term6 = y * (z - y) * b_1 - 2 * (z - 1) * b_w

term6 = sbminus(sbtimes(sbtimes(y, sbminus(z, y)), b_1), sbtimes(sbtimes(two, sbminus(z, one)), b_w));





// pNum_beta = (z - 1) * (term2 * term4 + term3 * term5) + term1 * term6

pNum_beta = sbplus(sbtimes(sbminus(z, one), sbplus(sbtimes(term2, term4), sbtimes(term3, term5))), sbtimes(term1, term6));




