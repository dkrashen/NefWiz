
// term1 = z * (z - 1)

term1 = sbtimes(z, sbminus(z, one));





// term2 = (a + z - 1) * (a + z - 2)

term2 = sbtimes(sbminus(sbplus(a, z), one), sbminus(sbplus(a, z), two));





// term6 = (a + z - b - y) * (a + z - b - y - 1)

term6 = sbtimes(sbminus(sbminus(sbplus(a, z), b), y), sbminus(sbminus(sbminus(sbplus(a, z), b), y), one));





// term7 = (b + y) * (b + y - 1)

term7 = sbtimes(sbplus(b, y), sbminus(sbplus(b, y), one));





// term3 = term6 * y + term7 * (z - y)

term3 = sbplus(sbtimes(term6, y), sbtimes(term7, sbminus(z, y)));





// term4 = (z - y) * (z - y - 1) * b + y * (y - 1) * (a - b)

term4 = sbplus(sbtimes(sbtimes(sbminus(z, y), sbminus(sbminus(z, y), one)), b), sbtimes(sbtimes(y, sbminus(y, one)), sbminus(a, b)));





// term5 = (z - y) * (z - y - 1) * sum_delta_in_B + y * (y - 1) * sum_delta_in_B_complement

term5 = sbplus(sbtimes(sbtimes(sbminus(z, y), sbminus(sbminus(z, y), one)), sum_delta_in_B), sbtimes(sbtimes(y, sbminus(y, one)), sum_delta_in_B_complement));





// answer = term2 * term5 + term1 * (b_1 * term3 - b_w * term2)

answer = sbplus(sbtimes(term2, term5), sbtimes(term1, sbminus(sbtimes(b_1, term3), sbtimes(b_w, term2))));



