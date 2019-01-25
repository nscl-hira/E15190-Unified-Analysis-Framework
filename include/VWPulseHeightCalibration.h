#ifndef VWPULSEHEIGHTCALIBRATION_H
#define VWPULSEHEIGHTCALIBRATION_H

#include <fstream>
#include <sstream>
#include <string>

class VWPulseHeightCalibration
{
public :
  VWPulseHeightCalibration(int num_bars);
  ~VWPulseHeightCalibration();

  int LoadGainMatching(const char *);
  int LoadPulseHeightCalibration(const char *);

  double GetGeoMeanMatched(double ch, int num_bar) const;
  double GetPulseHeightCalibrated(double ch, double Ycm, int num_bar) const;

private :
  int fNumBars;
  double * fGeoMeanScalingFactors;
  double * fPulseHeightCalibration_a;
  double * fPulseHeightCalibration_b;
  double * fPulseHeightCalibration_c;

  bool fGainMatched;
  bool fPulseHeightCalibrated;

};

#endif
