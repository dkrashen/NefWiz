
// term1 = (a + z - 1) * (a + z - 2)

term1 = sbtimes(sbminus(sbplus(a, z), one), sbminus(sbplus(a, z), two));





// term5 = (a + z - y - b) * (a + z - y - b - 1)

term5 = sbtimes(sbminus(sbminus(sbplus(a, z), y), b), sbminus(sbminus(sbminus(sbplus(a, z), y), b), one));





// term6 = (b + y) * (b + y - 1)

term6 = sbtimes(sbplus(b, y), sbminus(sbplus(b, y), one));





// term2 = term5 * y + term6 * (z - y)

term2 = sbplus(sbtimes(term5, y), sbtimes(term6, sbminus(z, y)));





// term3 = (z - y) * (a - b) * sum_delta_in_B + y * b * sum_delta_in_B_complement

term3 = sbplus(sbtimes(sbtimes(sbminus(z, y), sbminus(a, b)), sum_delta_in_B), sbtimes(sbtimes(y, b), sum_delta_in_B_complement));





// term4 = (a - 1) * z

term4 = sbtimes(sbminus(a, one), z);





// pNum_alpha = term1 * (2 * (a - 1) - b * (a - b)) - (a - 1) * term2

pNum_alpha = sbminus(sbtimes(term1, sbminus(sbtimes(two, sbminus(a, one)), sbtimes(b, sbminus(a, b)))), sbtimes(sbminus(a, one), term2));





// pDen_alpha = (a - 1) * term1

pDen_alpha = sbtimes(sbminus(a, one), term1);





// pDen_beta = term1 * term4

pDen_beta = sbtimes(term1, term4);





// pNum_beta = term1 * term3 + b_1 * term2 * term4

pNum_beta = sbplus(sbtimes(term1, term3), sbtimes(sbtimes(b_1, term2), term4));




