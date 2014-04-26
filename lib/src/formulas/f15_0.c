
// term1 = (a - b) * (a - b - 1) * sum_delta_in_B + b * (b - 1) * sum_delta_in_B_complement

term1 = sbplus(sbtimes(sbtimes(sbminus(a, b), sbminus(sbminus(a, b), one)), sum_delta_in_B), sbtimes(sbtimes(b, sbminus(b, one)), sum_delta_in_B_complement));




// answer = (z - 1) * term1 + (a - 1) * (a - 2) * (y * (z - y) * b_1 - (z - 1) * b_w)

answer = sbplus(sbtimes(sbminus(z, one), term1), sbtimes(sbtimes(sbminus(a, one), sbminus(a, two)), sbminus(sbtimes(sbtimes(y, sbminus(z, y)), b_1), sbtimes(sbminus(z, one), b_w))));



