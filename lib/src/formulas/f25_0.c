
// term1 = (z - y) * (a - b) * sum_delta_in_B + y * b * sum_delta_in_B_complement

term1 = sbplus(sbtimes(sbtimes(sbminus(z, y), sbminus(a, b)), sum_delta_in_B), sbtimes(sbtimes(y, b), sum_delta_in_B_complement));




// answer = (z - 1) * term1 + z * (a - 1) * (b_1 * y * (z - y) - (z - 1) * b_w)

answer = sbplus(sbtimes(sbminus(z, one), term1), sbtimes(sbtimes(z, sbminus(a, one)), sbminus(sbtimes(sbtimes(b_1, y), sbminus(z, y)), sbtimes(sbminus(z, one), b_w))));


