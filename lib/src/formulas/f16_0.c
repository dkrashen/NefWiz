
// term1 = (a + z - 1) * (a + z - 2)

term1 = sbtimes(sbminus(sbplus(a, z), one), sbminus(sbplus(a, z), two));





// term5 = (a + z - y - b) * (a + z - y - b - 1)

term5 = sbtimes(sbminus(sbminus(sbplus(a, z), y), b), sbminus(sbminus(sbminus(sbplus(a, z), y), b), one));





// term6 = (y + b) * (y + b - 1)

term6 = sbtimes(sbplus(y, b), sbminus(sbplus(y, b), one));





// term2 = term5 * y + term6 * (z - y)

term2 = sbplus(sbtimes(term5, y), sbtimes(term6, sbminus(z, y)));





// term3 = (a - b) * (a - b - 1) * sum_delta_in_B + b * (b - 1) * sum_delta_in_B_complement

term3 = sbplus(sbtimes(sbtimes(sbminus(a, b), sbminus(sbminus(a, b), one)), sum_delta_in_B), sbtimes(sbtimes(b, sbminus(b, one)), sum_delta_in_B_complement));





// term4 = (a - 1) * (a - 2)

term4 = sbtimes(sbminus(a, one), sbminus(a, two));



// answer = term1 * (term3 - term4 * b_w) + term4 * term2 * b_1

answer = sbplus(sbtimes(term1, sbminus(term3, sbtimes(term4, b_w))), sbtimes(sbtimes(term4, term2), b_1));






