//------------------------------------------------------------------------------------------------
// Solves for u, v, and w in a set of linear equations
//       Du + Ev + Fw + G = 0
//       Hu + Iv + Jw + K = 0
//       Lu + Mv + Nw + P = 0
//
// Linear Solver.cpp
//------------------------------------------------------------------------------------------------



#ifndef _LINEARSOLVER_H
#define _LINEARSOLVER_H

#include "STVector3.h"




class LinearSolver {

public:

                                        LinearSolver                            (void);
                                        ~LinearSolver                           (void);

    bool                                Run_method1                              (double D, double E, double F, double G,
                                                                                 double H, double I, double J, double K,
                                                                                 double L, double M, double N, double P,
                                                                                 double &u, double &v, double &w);



    bool                                Run_method2                             ( double a, double b, double c, double d,
                                                                                  double l, double m, double n, double k,
                                                                                  double p, double q, double r, double s,
                                                                                  double &x, double &y, double &z);
};


#endif //_LINEARSOLVER_H