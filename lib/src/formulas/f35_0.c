
// term1 = (z - y) * (z - y - 1)

term1 = sbtimes(sbminus(z, y), sbminus(sbminus(z, y), one));





// term2 = y * (y - 1)

term2 = sbtimes(y, sbminus(y, one));




// answer = term1 * sum_delta_in_B + term2 * sum_delta_in_B_complement + z * (y * (z - y) * b_1 - (z - 1) * b_w)

answer = sbplus(sbplus(sbtimes(term1, sum_delta_in_B), sbtimes(term2, sum_delta_in_B_complement)), sbtimes(z, sbminus(sbtimes(sbtimes(y, sbminus(z, y)), b_1), sbtimes(sbminus(z, one), b_w))));




