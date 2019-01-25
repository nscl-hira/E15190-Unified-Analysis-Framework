#include "include/FATimeCalibration.h"

//____________________________________________________
FATimeCalibration::FATimeCalibration(int num_dets) :
fNumDetectors(num_dets),
fTimeOffset(0),
fPulseHeightCorrectionFunc(0),
fCalibrationLoaded(false),
fPulseHeightCorrectionLoaded(false)
{
  fTimeOffset=new double[fNumDetectors];
  fPulseHeightCorrectionFunc = new TF1*[fNumDetectors];
  for(int i=0; i<fNumDetectors; i++) {
    fPulseHeightCorrectionFunc[i] = new TF1(Form("PulseHeightCorrectionFunc_%02d", i+1), "[0]-[1]*exp(-[2]*x)", 0, 4096);
  }
}

//____________________________________________________
FATimeCalibration::~FATimeCalibration()
{
  if(fTimeOffset) delete [] fTimeOffset;
  for(int i=0; i<fNumDetectors; i++) {
    if(fPulseHeightCorrectionFunc[i]) delete fPulseHeightCorrectionFunc[i];
  }
  if(fPulseHeightCorrectionFunc) delete [] fPulseHeightCorrectionFunc;
}

//____________________________________________________
int FATimeCalibration::LoadCalibration(const char * file_name)
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

    int det_num;
    double offset;

    LineStream>>det_num>>offset;

    fTimeOffset[det_num-1]=offset;

    NRead++;
  }

  NRead>0 ? fCalibrationLoaded=true : fCalibrationLoaded=false;
  return NRead;
}

//____________________________________________________
int FATimeCalibration::LoadPulseHeightCorrection(const char * file_name)
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

    int det_num;
    double a0;
    double a1;
    double a2;

    LineStream>>det_num>>a0>>a1>>a2;

    fPulseHeightCorrectionFunc[det_num-1]->SetParameters(a0,a1,a2);

    NRead++;
  }

  NRead>0 ? fPulseHeightCorrectionLoaded=true : fPulseHeightCorrectionLoaded=false;
  return NRead;
}

//____________________________________________________
double FATimeCalibration::GetTimeOffset(int num_det) const
{
  return fCalibrationLoaded ? fTimeOffset[num_det-1] : 0;
}

//____________________________________________________
double FATimeCalibration::GetTimePulseHeightCorrection(int num_det, double pulse_height) const
{
  return fPulseHeightCorrectionLoaded ? fPulseHeightCorrectionFunc[num_det-1]->Eval(pulse_height) : 0;
}
