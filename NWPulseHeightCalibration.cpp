#include "include/NWPulseHeightCalibration.h"

//____________________________________________________
NWPulseHeightCalibration::NWPulseHeightCalibration(int TotNumBars) :
fNumBars(TotNumBars),
fRightMatchingParameters(new double[fNumBars]),
fLeftMatchingParameters(new double[fNumBars]),
fPulseHeightCalibrationParameters_a(new double[fNumBars]),//KZ
fPulseHeightCalibrationParameters_b(new double[fNumBars]),//KZ
fPulseHeightCalibrationParameters_c(new double[fNumBars]),//KZ
fPulseHeightCalibrationParameters_d(new double[fNumBars]),//KZ
fPulseHeightCalibrationParameters_e(new double[fNumBars]),//KZ
fSaturationCorrectionParameters_a(new double[fNumBars]),//KZ
fSaturationCorrectionParameters_b(new double[fNumBars]),//KZ
fSaturationCorrectionParameters_c(new double[fNumBars]),//KZ
fSaturationCorrectionParameters_d(new double[fNumBars]),//KZ
fSaturationCorrectionParameters_e(new double[fNumBars]),//KZ
fSaturationCorrectionParameters_f(new double[fNumBars]),//KZ
fMatchingLoaded(false),
fCalibrationLoaded(false),
fPositionCorrectionLoaded(false),
fPulseHeightCalibrationLoaded(false),//KZ
fSaturationCorrected(false)//KZ
{}

//____________________________________________________
NWPulseHeightCalibration::~NWPulseHeightCalibration()
{
  delete [] fRightMatchingParameters;
  delete [] fLeftMatchingParameters;
  delete [] fPulseHeightCalibrationParameters_a;//KZ
  delete [] fPulseHeightCalibrationParameters_b;//KZ
  delete [] fPulseHeightCalibrationParameters_c;//KZ
  delete [] fPulseHeightCalibrationParameters_d;//KZ
  delete [] fPulseHeightCalibrationParameters_e;//KZ
  delete [] fSaturationCorrectionParameters_a;//KZ
  delete [] fSaturationCorrectionParameters_b;//KZ
  delete [] fSaturationCorrectionParameters_c;//KZ
  delete [] fSaturationCorrectionParameters_d;//KZ
  delete [] fSaturationCorrectionParameters_e;//KZ
  delete [] fSaturationCorrectionParameters_f;//KZ
}

//____________________________________________________
int NWPulseHeightCalibration::LoadMatching(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    std::string DetName;
    double peakleft;
    double peakright;
    double requiredposition;

    LineStream>>DetName>>peakleft>>peakright>>requiredposition;
    int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));
    fRightMatchingParameters[NumBar]=requiredposition/peakright;
    fLeftMatchingParameters[NumBar]=requiredposition/peakleft;

    NRead++;
  }

  NRead>0 ? fMatchingLoaded=true : fMatchingLoaded=false;
  return NRead;
}

//____________________________________________________
int NWPulseHeightCalibration::LoadPulseHeightCalibration(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    std::string DetName;
    //Please see \projects\hira\zhukuan\E15190\NWcalibration\txt\AmBe_fitting.xlsx for details
    double a;
    double b;
    double c;
    double d;
    double e;

    LineStream>>DetName>>a>>b>>c>>d>>e;
    int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));
    fPulseHeightCalibrationParameters_a[NumBar]= a;
    fPulseHeightCalibrationParameters_b[NumBar]= b;
    fPulseHeightCalibrationParameters_c[NumBar]= c;
    fPulseHeightCalibrationParameters_d[NumBar]= d;
    fPulseHeightCalibrationParameters_e[NumBar]= e;

    NRead++;
  }

  NRead>0 ? fPulseHeightCalibrationLoaded=true : fPulseHeightCalibrationLoaded=false;
  return NRead;
}

//____________________________________________________
int NWPulseHeightCalibration::LoadSaturationCorrection(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    std::string DetName;
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;

    LineStream>>DetName>>a>>b>>c>>d>>e>>f;
    int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));
    fSaturationCorrectionParameters_a[NumBar]= a;
    fSaturationCorrectionParameters_b[NumBar]= b;
    fSaturationCorrectionParameters_c[NumBar]= c;
    fSaturationCorrectionParameters_d[NumBar]= d;
    fSaturationCorrectionParameters_e[NumBar]= e;
    fSaturationCorrectionParameters_f[NumBar]= f;

    NRead++;
  }

  NRead>0 ? fSaturationCorrected=true : fSaturationCorrected=false;
  return NRead;
}

//____________________________________________________
double NWPulseHeightCalibration::GetLeftMatched(double ch, int numbar) const
{
  return fMatchingLoaded ? gRandom->Uniform(ch-0.5, ch+0.5)*fLeftMatchingParameters[numbar-1] : -9999;
}

//____________________________________________________
double NWPulseHeightCalibration::GetRightMatched(double ch, int numbar) const
{
  return fMatchingLoaded ? gRandom->Uniform(ch-0.5, ch+0.5)*fRightMatchingParameters[numbar-1] : -9999;
}

//____________________________________________________
double NWPulseHeightCalibration::GetLeftSaturationCorrected(double ch_left, double ch_right, double NW_fXcm, int numbar) const
{
  if (!fPulseHeightCalibrationLoaded) return -9999;
  if (ch_left<=4090) return ch_left;
  if (ch_left>4090&&ch_right>4090) return ch_left;
  return ch_right/(std::exp(fSaturationCorrectionParameters_e[numbar]*NW_fXcm*NW_fXcm+fSaturationCorrectionParameters_c[numbar]*NW_fXcm+fSaturationCorrectionParameters_a[numbar]));
}

//____________________________________________________
double NWPulseHeightCalibration::GetfastLeftSaturationCorrected(double fast_ch_left, double fast_ch_right, double NW_fXcm, int numbar) const
{
  if (!fPulseHeightCalibrationLoaded) return -9999;
  if (fast_ch_left<=4090) return fast_ch_left;
  if (fast_ch_left>4090&&fast_ch_right>4090) return fast_ch_left;
  return fast_ch_right/(std::exp(fSaturationCorrectionParameters_e[numbar]*NW_fXcm*NW_fXcm+fSaturationCorrectionParameters_c[numbar]*NW_fXcm+fSaturationCorrectionParameters_a[numbar]));
}

//____________________________________________________
double NWPulseHeightCalibration::GetRightSaturationCorrected(double ch_left, double ch_right, double NW_fXcm, int numbar) const
{
  if (!fPulseHeightCalibrationLoaded) return -9999;
  if (ch_right<=4090) return ch_right;
  if (ch_right>4090&&ch_left>4090) return ch_right;
  return ch_left*(std::exp(fSaturationCorrectionParameters_e[numbar]*NW_fXcm*NW_fXcm+fSaturationCorrectionParameters_c[numbar]*NW_fXcm+fSaturationCorrectionParameters_a[numbar]));
}

//____________________________________________________
double NWPulseHeightCalibration::GetfastRightSaturationCorrected(double fast_ch_left, double fast_ch_right, double NW_fXcm, int numbar) const
{
  if (!fPulseHeightCalibrationLoaded) return -9999;
  if (fast_ch_right<=4090) return fast_ch_right;
  if (fast_ch_right>4090&&fast_ch_left>4090) return fast_ch_right;
  return fast_ch_left*(std::exp(fSaturationCorrectionParameters_e[numbar]*NW_fXcm*NW_fXcm+fSaturationCorrectionParameters_c[numbar]*NW_fXcm+fSaturationCorrectionParameters_a[numbar]));
}

//____________________________________________________
double NWPulseHeightCalibration::GetPulseHeightCalibrated(double ch, double NW_fXcm, int numbar) const
{
  return fPulseHeightCalibrationLoaded ? fPulseHeightCalibrationParameters_d[numbar]+gRandom->Uniform(ch-0.5, ch+0.5)/(fPulseHeightCalibrationParameters_a[numbar]+fPulseHeightCalibrationParameters_b[numbar]*NW_fXcm+fPulseHeightCalibrationParameters_c[numbar]*NW_fXcm*NW_fXcm)*4.196*fPulseHeightCalibrationParameters_e[numbar] : -9999;
}

//____________________________________________________
double NWPulseHeightCalibration::GetSaturationCorrected(double ch_left, double ch_right, double NW_fXcm, int numbar) const
{
  if (fSaturationCorrected) {
    int ch_corrected;
    if (ch_left>4090&&ch_right>4090) {
      ch_corrected = std::sqrt(ch_left*ch_right);
    }
    else if (ch_left>4090) {
      ch_corrected = std::sqrt(ch_right*ch_right/(std::exp(fSaturationCorrectionParameters_e[numbar]*NW_fXcm*NW_fXcm+fSaturationCorrectionParameters_c[numbar]*NW_fXcm+fSaturationCorrectionParameters_a[numbar])));
    }
    else if (ch_right>4090) {
      ch_corrected = std::sqrt(ch_left*ch_left*(std::exp(fSaturationCorrectionParameters_e[numbar]*NW_fXcm*NW_fXcm+fSaturationCorrectionParameters_c[numbar]*NW_fXcm+fSaturationCorrectionParameters_a[numbar])));
    }
    else {
      ch_corrected = std::sqrt(ch_left*ch_right);
    }
    return fPulseHeightCalibrationParameters_d[numbar]+gRandom->Uniform(ch_corrected-0.5, ch_corrected+0.5)/(fPulseHeightCalibrationParameters_a[numbar]+fPulseHeightCalibrationParameters_b[numbar]*NW_fXcm+fPulseHeightCalibrationParameters_c[numbar]*NW_fXcm*NW_fXcm)*4.196*fPulseHeightCalibrationParameters_e[numbar];
  }
  else return -9999;
}
