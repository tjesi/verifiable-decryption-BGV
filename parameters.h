
#ifndef HEADER_P
#define HEADER_P

#include <math.h>

const long N           = 2048;
const double q         = pow(2,44) + pow(2,17) + 1;
const long p           = 2;
const long tau         = 2048;
const long lambda      = 128;
const long B           = 1;
const double MLinInv   = 1/sqrt(3);
const double MAInv     = 1/3.0;
const double Sigma_A   = 268435456;
const double Bound_A   = 81;    // # bits * 2
const double TwoSigmaA2 = 2*Sigma_A*Sigma_A;
const double Sigma_C   = 61147;
const double Bound_C   = 44.8;  // # bits * 2
const double TwoSigmaC2 = 2*Sigma_C*Sigma_C;

#endif
