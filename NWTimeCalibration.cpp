#include "include/NWTimeCalibration.h"

//____________________________________________________
NWTimeCalibration::NWTimeCalibration(int num_bars) :
fNumBars(num_bars),
fTimeOffset(0),
fCalibrationLoaded(false)
{
  fTimeOffset=new double[fNumBars];
}

//____________________________________________________
NWTimeCalibration::~NWTimeCalibration()
{
  if(fTimeOffset) delete [] fTimeOffset;
}

//____________________________________________________
int NWTimeCalibration::LoadCalibration(const char * file_name)
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
    double offset;

    LineStream>>DetName>>offset;
    int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));
    fTimeOffset[NumBar]=offset;

    NRead++;
  }

  NRead>0 ? fCalibrationLoaded=true : fCalibrationLoaded=false;
  return NRead;
}

//____________________________________________________
double NWTimeCalibration::GetTimeOffset(int num_bar) const
{
  return fCalibrationLoaded ? fTimeOffset[num_bar] : 0;
}
