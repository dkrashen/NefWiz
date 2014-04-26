
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




// answer = term1 * term3 + b_1 * term2 * term4

answer = sbplus(sbtimes(term1, term3), sbtimes(sbtimes(b_1, term2), term4));




