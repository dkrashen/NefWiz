
// term1 = (a - b) * (a - b - 1)

term1 = sbtimes(sbminus(a, b), sbminus(sbminus(a, b), one));





// term2 = b * (b - 1)

term2 = sbtimes(b, sbminus(b, one));





// term3 = a * (a - 1)

term3 = sbtimes(a, sbminus(a, one));





// term4 = term1 * y + term2 * (z - y)

term4 = sbplus(sbtimes(term1, y), sbtimes(term2, sbminus(z, y)));




// answer = a * (term1 * sum_delta_in_B + term2 * sum_delta_in_B_complement) + (a - 2) * (b_1 * term4 - term3 * b_w)

answer = sbplus(sbtimes(a, sbplus(sbtimes(term1, sum_delta_in_B), sbtimes(term2, sum_delta_in_B_complement))), sbtimes(sbminus(a, two), sbminus(sbtimes(b_1, term4), sbtimes(term3, b_w))));




