#ifndef HIRAEDFIDENTIFICATIONPARAMETERS_H
#define HIRAEDFIDENTIFICATIONPARAMETERS_H

#include <iostream>
#include <math.h>
#include <HiRAEdFMPart.h>

#include <shared.h>

class HiRAEdFIdentificationParameters
{
public :
  HiRAEdFIdentificationParameters();
  ~HiRAEdFIdentificationParameters();

  void SetNumParameters(int);
  void SetParameter(int, double);
  void SetParameters(double *);

  double func14(MPart &p) const;
  int Get_Charge(double de, double fast, int *iter, double *zeta);
  double Get_Mass(int charge, double de, double fast, int *iter);

private :
  int fNumParameters;
  double * fParameters;

  double GetMassCharity(double Z) const;
};

#endif
