// Copyright (C) 2012 Désiré Nuentsa-Wakam <desire.nuentsa_wakam@inria.fr>
// Copyright (C) 2012 Gael Guennebaud <gael.guennebaud@inria.fr>
// Public License v. 2.0. If a copy of the MPL was not distributed

/* 
 
 * NOTE: This file is the modified version of xcolumn_bmod.c file in SuperLU 
 
 * -- SuperLU routine (version 3.0) --
 * Univ. of California Berkeley, Xerox Palo Alto Research Center,
 * and Lawrence Berkeley National Lab.
 * October 15, 2003
 *
 * Copyright (c) 1994 by Xerox Corporation.  All rights reserved.
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY
 * EXPRESSED OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program for any
 * purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is
 * granted, provided the above notices are retained, and a notice that
 * the code was modified is included with the above copyright notice.
 */
#ifndef SPARSELU_COLUMN_BMOD_H
#define SPARSELU_COLUMN_BMOD_H

namespace Eigen {

namespace internal {
template <typename Scalar, typename Index>
Index SparseLUImpl<Scalar,Index>::column_bmod(const Index jcol, const Index nseg, BlockScalarVector dense, ScalarVector& tempv, BlockIndexVector segrep, BlockIndexVector repfnz, Index fpanelc, GlobalLU_t& glu)
{
  Index  jsupno, k, ksub, krep, ksupno; 
  Index lptr, nrow, isub, irow, nextlu, new_next, ufirst; 
  Index fsupc, nsupc, nsupr, luptr, kfnz, no_zeros; 
  
  jsupno = glu.supno(jcol);
  
  k = nseg - 1; 
  Index d_fsupc; 
               
  Index fst_col; 
  Index segsize; 
  for (ksub = 0; ksub < nseg; ksub++)
  {
    krep = segrep(k); k--; 
    ksupno = glu.supno(krep); 
    if (jsupno != ksupno )
    {
      
      fsupc = glu.xsup(ksupno); 
      fst_col = (std::max)(fsupc, fpanelc); 
      
      
      
      d_fsupc = fst_col - fsupc; 
      
      luptr = glu.xlusup(fst_col) + d_fsupc; 
      lptr = glu.xlsub(fsupc) + d_fsupc; 
      
      kfnz = repfnz(krep); 
      kfnz = (std::max)(kfnz, fpanelc); 
      
      segsize = krep - kfnz + 1; 
      nsupc = krep - fst_col + 1; 
      nsupr = glu.xlsub(fsupc+1) - glu.xlsub(fsupc); 
      nrow = nsupr - d_fsupc - nsupc;
      Index lda = glu.xlusup(fst_col+1) - glu.xlusup(fst_col);
      
      
      
      
      no_zeros = kfnz - fst_col; 
      if(segsize==1)
        LU_kernel_bmod<1>::run(segsize, dense, tempv, glu.lusup, luptr, lda, nrow, glu.lsub, lptr, no_zeros);
      else
        LU_kernel_bmod<Dynamic>::run(segsize, dense, tempv, glu.lusup, luptr, lda, nrow, glu.lsub, lptr, no_zeros);
    } 
  } 
  
  
  nextlu = glu.xlusup(jcol); 
  fsupc = glu.xsup(jsupno);
  
  
  Index mem; 
  new_next = nextlu + glu.xlsub(fsupc + 1) - glu.xlsub(fsupc); 
  Index offset = internal::first_multiple<Index>(new_next, internal::packet_traits<Scalar>::size) - new_next;
  if(offset)
    new_next += offset;
  while (new_next > glu.nzlumax )
  {
    mem = memXpand<ScalarVector>(glu.lusup, glu.nzlumax, nextlu, LUSUP, glu.num_expansions);  
    if (mem) return mem; 
  }
  
  for (isub = glu.xlsub(fsupc); isub < glu.xlsub(fsupc+1); isub++)
  {
    irow = glu.lsub(isub);
    glu.lusup(nextlu) = dense(irow);
    dense(irow) = Scalar(0.0); 
    ++nextlu; 
  }
  
  if(offset)
  {
    glu.lusup.segment(nextlu,offset).setZero();
    nextlu += offset;
  }
  glu.xlusup(jcol + 1) = nextlu;  
  
  fst_col = (std::max)(fsupc, fpanelc); 
  
  if (fst_col  < jcol)
  {
    
    
    d_fsupc = fst_col - fsupc; 
    
    lptr = glu.xlsub(fsupc) + d_fsupc; 
    luptr = glu.xlusup(fst_col) + d_fsupc; 
    nsupr = glu.xlsub(fsupc+1) - glu.xlsub(fsupc); 
    nsupc = jcol - fst_col; 
    nrow = nsupr - d_fsupc - nsupc; 
    
    
    ufirst = glu.xlusup(jcol) + d_fsupc; 
    Index lda = glu.xlusup(jcol+1) - glu.xlusup(jcol);
    Map<Matrix<Scalar,Dynamic,Dynamic>, 0,  OuterStride<> > A( &(glu.lusup.data()[luptr]), nsupc, nsupc, OuterStride<>(lda) ); 
    VectorBlock<ScalarVector> u(glu.lusup, ufirst, nsupc); 
    u = A.template triangularView<UnitLower>().solve(u); 
    
    new (&A) Map<Matrix<Scalar,Dynamic,Dynamic>, 0, OuterStride<> > ( &(glu.lusup.data()[luptr+nsupc]), nrow, nsupc, OuterStride<>(lda) ); 
    VectorBlock<ScalarVector> l(glu.lusup, ufirst+nsupc, nrow); 
    l.noalias() -= A * u;
    
  } 
  return 0; 
}

} 
} 

#endif 
