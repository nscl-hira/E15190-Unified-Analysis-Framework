#include "include/NWPositionCalibration.h"

//____________________________________________________
NWPositionCalibration::NWPositionCalibration(int num_bars) :
fNumBars(num_bars),
fOffset(0),
fSpeedLightBar(0),
fCalibrationLoaded(false)
{
  fOffset=new double[fNumBars];
  fSpeedLightBar=new double[fNumBars];
}

//____________________________________________________
NWPositionCalibration::~NWPositionCalibration()
{
  if(fOffset) delete [] fOffset;
  if(fSpeedLightBar) delete [] fSpeedLightBar;
}

//____________________________________________________
int NWPositionCalibration::LoadCalibration(const char * file_name)
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
    double offset;
    double cprime;

    LineStream>>DetName>>offset>>cprime;
    int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));
    fOffset[NumBar]=offset;
    fSpeedLightBar[NumBar]=cprime;

    NRead++;
  }

  NRead>0 ? fCalibrationLoaded=true : fCalibrationLoaded=false;
  return NRead;
}

//____________________________________________________
double NWPositionCalibration::GetPosition(int num_bar, double tleft, double tright) const
{
  return fCalibrationLoaded ? (tleft-tright)*fSpeedLightBar[num_bar]-fOffset[num_bar] : -9999;
}
