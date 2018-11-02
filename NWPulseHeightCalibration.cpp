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
fMatchingLoaded(false),
fCalibrationLoaded(false),
fPositionCorrectionLoaded(false),
fPulseHeightCalibrationLoaded(false)//KZ
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

    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.empty()) continue;
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

    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.empty()) continue;
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
double NWPulseHeightCalibration::GetPulseHeightCalibrated(double ch, double NW_fXcm, int numbar) const
{
  return fPulseHeightCalibrationLoaded ? fPulseHeightCalibrationParameters_d[numbar]+gRandom->Uniform(ch-0.5, ch+0.5)/(fPulseHeightCalibrationParameters_a[numbar]+fPulseHeightCalibrationParameters_b[numbar]*NW_fXcm+fPulseHeightCalibrationParameters_c[numbar]*NW_fXcm*NW_fXcm)*4.196*fPulseHeightCalibrationParameters_e[numbar] : -9999;
}
