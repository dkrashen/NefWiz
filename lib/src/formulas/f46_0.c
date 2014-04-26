
// term1 = (a + z - 1) * (a + z - 2)

term1 = sbtimes(sbminus(sbplus(a, z), one), sbminus(sbplus(a, z), two));




// term2 = (a + z - y - b) * (a + z - y - b - 1)

term2 = sbtimes(sbminus(sbminus(sbplus(a, z), y), b), sbminus(sbminus(sbminus(sbplus(a, z), y), b), one));




// term3 = (y + b) * (y + b - 1)

term3 = sbtimes(sbplus(y, b), sbminus(sbplus(y, b), one));






// answer = term2 * (sum_delta_in_B + y * b_1) + term3 * (sum_delta_in_B_complement + (z - y) * b_1) - term1 * b_w

answer = sbminus(sbplus(sbtimes(term2, sbplus(sum_delta_in_B, sbtimes(y, b_1))), sbtimes(term3, sbplus(sum_delta_in_B_complement, sbtimes(sbminus(z, y), b_1)))), sbtimes(term1, b_w));



