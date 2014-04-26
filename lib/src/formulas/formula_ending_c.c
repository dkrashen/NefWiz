    pAlpha = bq_make(pNum_alpha, pDen_alpha);

    pBeta = bq_make(pNum_beta, pDen_beta);
    
    pFormula = bform_make(pAlpha, pBeta);
  
    bq_kill(pAlpha);
    bq_kill(pBeta);
    
    empty_garbage;
    return pFormula;
    
