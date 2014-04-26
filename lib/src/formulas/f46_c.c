
// term1 = (a + z - 1) * (a + z - 2)

term1 = sbtimes(sbminus(sbplus(a, z), one), sbminus(sbplus(a, z), two));


// term2 = (a + z - y - b) * (a + z - y - b - 1)

term2 = sbtimes(sbminus(sbminus(sbplus(a, z), y), b), sbminus(sbminus(sbminus(sbplus(a, z), y), b), one));


// term3 = (y + b) * (y + b - 1)

term3 = sbtimes(sbplus(y, b), sbminus(sbplus(y, b), one));



// pNum_alpha = 2 * term1 - term2 * (b + y) - term3 * (a + z - b - y)

pNum_alpha = sbminus(sbminus(sbtimes(two, term1), sbtimes(term2, sbplus(b, y))), sbtimes(term3, sbminus(sbminus(sbplus(a, z), b), y)));



// pDen_alpha = term1

pDen_alpha = term1;



// pNum_beta = term2 * (sum_delta_in_B + y * b_1) + term3 * (sum_delta_in_B_complement + (z - y) * b_1) - term1 * b_w

pNum_beta = sbminus(sbplus(sbtimes(term2, sbplus(sum_delta_in_B, sbtimes(y, b_1))), sbtimes(term3, sbplus(sum_delta_in_B_complement, sbtimes(sbminus(z, y), b_1)))), sbtimes(term1, b_w));


// pDen_beta = term1

pDen_beta = term1;



