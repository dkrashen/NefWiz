
// term1 = (a - b) * (a - b - 1) * y + b * (b - 1) * (z - y)

term1 = sbplus(sbtimes(sbtimes(sbminus(a, b), sbminus(sbminus(a, b), one)), y), sbtimes(sbtimes(b, sbminus(b, one)), sbminus(z, y)));





// term2 = a * (a - 1)

term2 = sbtimes(a, sbminus(a, one));





// term3 = (z - y) * (a - b) * sum_delta_in_B + y * b * sum_delta_in_B_complement

term3 = sbplus(sbtimes(sbtimes(sbminus(z, y), sbminus(a, b)), sum_delta_in_B), sbtimes(sbtimes(y, b), sum_delta_in_B_complement));





// pNum_alpha = a * (2 * (a - 1) - b * (a - b)) - term1

pNum_alpha = sbminus(sbtimes(a, sbminus(sbtimes(two, sbminus(a, one)), sbtimes(b, sbminus(a, b)))), term1);





// pDen_alpha = term2

pDen_alpha = term2;





// pDen_beta = term2 * z

pDen_beta = sbtimes(term2, z);





// pNum_beta = a * term3 + z * b_1 * term1 - term2 * z * b_w

pNum_beta = sbminus(sbplus(sbtimes(a, term3), sbtimes(sbtimes(z, b_1), term1)), sbtimes(sbtimes(term2, z), b_w));




