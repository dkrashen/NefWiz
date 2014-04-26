
// term1 = (a - b) * (a - b - 1) * sum_delta_in_B + b * (b - 1) * sum_delta_in_B_complement

term1 = sbplus(sbtimes(sbtimes(sbminus(a, b), sbminus(sbminus(a, b), one)), sum_delta_in_B), sbtimes(sbtimes(b, sbminus(b, one)), sum_delta_in_B_complement));





// pNum_alpha = (z - 1) * (2 * (a - 1) - b * (a - b)) - (a - 1) * y * (z - y)

pNum_alpha = sbminus(sbtimes(sbminus(z, one), sbminus(sbtimes(two, sbminus(a, one)), sbtimes(b, sbminus(a, b)))), sbtimes(sbtimes(sbminus(a, one), y), sbminus(z, y)));





// pDen_alpha = (a - 1) * (z - 1)

pDen_alpha = sbtimes(sbminus(a, one), sbminus(z, one));





// pDen_beta = (a - 1) * (a - 2) * (z - 1)

pDen_beta = sbtimes(sbtimes(sbminus(a, one), sbminus(a, two)), sbminus(z, one));





// pNum_beta = (z - 1) * term1 + (a - 1) * (a - 2) * (y * (z - y) * b_1 - (z - 1) * b_w)

pNum_beta = sbplus(sbtimes(sbminus(z, one), term1), sbtimes(sbtimes(sbminus(a, one), sbminus(a, two)), sbminus(sbtimes(sbtimes(y, sbminus(z, y)), b_1), sbtimes(sbminus(z, one), b_w))));




