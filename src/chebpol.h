#ifndef _CHEBPOL
#define _CHEBPOL

#include <float.h>
#include <math.h>

#ifndef  USE_FC_LEN_T
# define USE_FC_LEN_T
#endif
#include <Rconfig.h>
#include <R_ext/BLAS.h>
#include <R_ext/Lapack.h>
#ifndef FCONE
# define FCONE
#endif

#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <R_ext/Applic.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

#include "config.h"

SEXP R_makerbf(SEXP, SEXP, SEXP, SEXP);
SEXP R_evalrbf(SEXP, SEXP, SEXP);
SEXP R_evalstalker(SEXP, SEXP, SEXP, SEXP, SEXP);
SEXP R_makehyp(SEXP, SEXP);
SEXP R_evalhyp(SEXP, SEXP, SEXP, SEXP);
SEXP R_makestalk(SEXP, SEXP);
SEXP R_evalstalk(SEXP, SEXP, SEXP, SEXP);
SEXP R_havealglib();
SEXP havegsl();

static R_INLINE double blendfun(double w,int blend) {
  switch(blend) {
  case 0:
    // Linear, nothing to do here
    break;
  case 1:
    w = w<0.5 ? 0.5*exp(2-1/w) : 1-0.5*exp(2-1/(1-w));  // smooth sigmoid blending
    break;
  case 2:
    w = w<0.5 ? 0.5*exp(4-1/(w*w)) : 1-0.5*exp(4-1/((1-w)*(1-w)));  // parodic sigmoid blending
    break;
  case 3:
    w = (-2*w + 3)*w*w; // cubic blending
    break;
  case 4:
    w = (w < 0.5) ? 0 : 1;  // discontinuous blending
  break;
  case 5:
    w = 0.5; // mean blending
  }        
  return w;
}
#endif
