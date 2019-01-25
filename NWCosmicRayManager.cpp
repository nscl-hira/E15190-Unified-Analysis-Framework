#include "include/NWCosmicRayManager.h"

//____________________________________________________
NWCosmicRayManager::NWCosmicRayManager(int num_bars) :
fNumBars(num_bars),
fCenter(0),
fSigma(0),
fPositionLoaded(false)
{
  fCenter=new double[fNumBars];
  fSigma=new double[fNumBars];
}

//____________________________________________________
NWCosmicRayManager::~NWCosmicRayManager()
{
  if(fCenter) delete [] fCenter;
  if(fSigma) delete [] fSigma;
}

//____________________________________________________
int NWCosmicRayManager::LoadPeakPositions(const char * file_name)
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
    double center;
    double sigma;

    LineStream>>DetName>>center>>sigma;

    int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));
    fCenter[NumBar]=center;
    fSigma[NumBar]=sigma;

    NRead++;
  }

  NRead>0 ? fPositionLoaded=true : fPositionLoaded=false;
  return NRead;
}

//____________________________________________________
double NWCosmicRayManager::GetCosmicRayCenter(int num_bar) const
{
  return fPositionLoaded ? fCenter[num_bar] : -9999;
}

//____________________________________________________
double NWCosmicRayManager::GetCosmicRayStartingPoint(int num_bar) const
{
  return fPositionLoaded ? fCenter[num_bar]-2*fSigma[num_bar] : -9999;
}
