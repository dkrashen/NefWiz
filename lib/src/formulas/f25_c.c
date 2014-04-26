
// term1 = (z - y) * (a - b) * sum_delta_in_B + y * b * sum_delta_in_B_complement

term1 = sbplus(sbtimes(sbtimes(sbminus(z, y), sbminus(a, b)), sum_delta_in_B), sbtimes(sbtimes(y, b), sum_delta_in_B_complement));





// pNum_alpha = (z - 1) * (2 * (a - 1) - b * (a - b)) - (a - 1) * y * (z - y)

pNum_alpha = sbminus(sbtimes(sbminus(z, one), sbminus(sbtimes(two, sbminus(a, one)), sbtimes(b, sbminus(a, b)))), sbtimes(sbtimes(sbminus(a, one), y), sbminus(z, y)));





// pDen_alpha = (a - 1) * (z - 1)

pDen_alpha = sbtimes(sbminus(a, one), sbminus(z, one));





// pDen_beta = (a - 1) * (z - 1) * z

pDen_beta = sbtimes(sbtimes(sbminus(a, one), sbminus(z, one)), z);





// pNum_beta = (z - 1) * term1 + z * (a - 1) * (b_1 * y * (z - y) - (z - 1) * b_w)

pNum_beta = sbplus(sbtimes(sbminus(z, one), term1), sbtimes(sbtimes(z, sbminus(a, one)), sbminus(sbtimes(sbtimes(b_1, y), sbminus(z, y)), sbtimes(sbminus(z, one), b_w))));




