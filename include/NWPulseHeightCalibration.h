#ifndef NWPULSEHEIGHTCALIBRATION_H
#define NWPULSEHEIGHTCALIBRATION_H

#include <string>
#include <fstream>
#include <sstream>
#include <TRandom3.h>

class NWPulseHeightCalibration
{
public :
  NWPulseHeightCalibration(int TotNumBars);
  ~NWPulseHeightCalibration();

  int LoadMatching(const char *);
  int LoadCalibration(const char *);
  int LoadPulseHeightCalibration(const char *);//KZ

  double GetLeftMatched(double ch, int numbar) const;
  double GetRightMatched(double ch, int numbar) const;
  double GetPulseHeightCalibrated(double ch, double NW_fXcm, int numbar) const;//KZ

private :
  int fNumBars;
  double * fRightMatchingParameters;
  double * fLeftMatchingParameters;
  double * fPulseHeightCalibrationParameters_a;//KZ
  double * fPulseHeightCalibrationParameters_b;//KZ
  double * fPulseHeightCalibrationParameters_c;//KZ
  double * fPulseHeightCalibrationParameters_d;//KZ
  double * fPulseHeightCalibrationParameters_e;//KZ

  bool fMatchingLoaded;
  bool fCalibrationLoaded;
  bool fPositionCorrectionLoaded;
  bool fPulseHeightCalibrationLoaded;//KZ

};

#endif
