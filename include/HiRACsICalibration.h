#ifndef HIRACSICalibRATION_h
#define HIRACSICalibRATION_h

#include <Math/Interpolator.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TSpline.h>
#include <math.h>
#include <cmath>

#include <shared.h>

/* HiRACsICalibration class
 * created by Daniele Dell'Aquila
 * v1.0 - April 2018
 * v2.0 - Nov 1st 2018
 *  Improved to handle the most recent calibration with an arbitrary formula for each isotope
 *  Since the calibrations are given in E -> Light a new method for fast inverse function is
 *  implemented to rapidly convert a light output into energy Light -> E
 *  The latter process is handled by the class TF1Fast
 */

 /* HiRACsICalibratioNManager class
  * created by Daniele Dell'Aquila
  * v1.0 - April 2018
  * v2.0 - Nov 1st 2018
  *  This class handles HiRA CsI calibrations for all isotopes and all crystals
  *
  */

// MAX Z DETECTED
const int Z_MAX=20;
// MAX A DETECTED
const int A_MAX=20;
// NUMBER OF CRYSTALS SUBJECT TO CALIBRATION
const int NUM_CRYSTALS=48;

class TF1Fast
{
public :
  TF1Fast(double precision=0.2);
  TF1Fast(const char * name, const char * formula, double xmin, double max, double precision=0.2);
  ~TF1Fast();

  void InitInverseFunction();

  double Eval(double);
  double EvalInverse(double);
  TF1 * GetFunction();

  void SetFunction(TF1 *);
  void SetParameters(double *);
  void SetParameter(int, double);

private :
  bool fFunctionSet;
  std::string fName;
  TF1 * fTheRootFunction;
  double fInversePrecision;
  ROOT::Math::Interpolator * fTheRootInverseFunction;
  std::vector<double> fInterpolatedEnergy;
  std::vector<double> fInterpolatedLight;
  double fymin;
  double fymax;
};

class HiRACsICalibration
{
public:
  HiRACsICalibration(int Z=1, int A=1);
  ~HiRACsICalibration();

  void SetNumParameters(int);
  void SetParameter(int, double);
  void InitCalibration(const char *);

  double GetEnergy(double V) const;

private:
  int fNumParameters;
  double * fParameters;
  TF1Fast * fCalibrationFunc;
  bool fCalibrationInitialized;
  int fZ;
  int fA;
};

class HiRACsICalibrationManager
{
public:
  HiRACsICalibrationManager();
  ~HiRACsICalibrationManager();

  int LoadPulserInfo(const char *);
  int LoadEnergyCalibration(const char *);
  void Clear();

  double GetVoltageValue(double ch, int numtel, int numcsi) const;
  double GetEnergyValue(double ch, int numtel, int numcsi, int Z=1, int A=1) const;
  HiRACsICalibration * GetCalibration(int numtel, int numcsi, int Z=1, int A=1) const;

  void DrawChVoltage (int numtel, int numcsi) const;

private:

  std::vector<double> fChValues [NUM_CRYSTALS];
  std::vector<double> fVoltageValues [NUM_CRYSTALS];
  TGraph * fCsIChToVExtrapolated [NUM_CRYSTALS];
  TSpline3 * fCsIChToVInterpolated [NUM_CRYSTALS];

  HiRACsICalibration * fCalib[Z_MAX][A_MAX][NUM_CRYSTALS];

  bool fPulserLoaded;

};

#endif
