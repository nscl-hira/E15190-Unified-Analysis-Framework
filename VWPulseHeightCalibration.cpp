#include <VWPulseHeightCalibration.h>

//____________________________________________________
VWPulseHeightCalibration::VWPulseHeightCalibration(int num_bars) :
fNumBars(num_bars),
fGeoMeanScalingFactors(new double [fNumBars]),
fGainMatched(false)
{}

//____________________________________________________
VWPulseHeightCalibration::~VWPulseHeightCalibration()
{
  delete [] fGeoMeanScalingFactors;
}

//____________________________________________________
int VWPulseHeightCalibration::LoadGainMatching(const char * file_name)
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

    int numbar;
    double fraction;

    LineStream >> numbar >> fraction;

    fGeoMeanScalingFactors[numbar]=fraction;

    NRead++;
  }

  fGainMatched=true;
  return NRead;
}

//____________________________________________________
double VWPulseHeightCalibration::GetGeoMeanMatched(double ch, int num_bar) const
{
  return fGainMatched ? ch*fGeoMeanScalingFactors[num_bar] : -9999;
}
