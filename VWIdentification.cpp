#include <VWIdentification.h>

//____________________________________________________
VWIdentification::VWIdentification() :
fFileCuts(0),
fCutsLoaded(false)
{
  fIdentificationCuts= (TCutG ***) new TCutG ** [dVWIdentificationZMAX];
  for(int i=0; i<dVWIdentificationZMAX; i++) {
    fIdentificationCuts[i]= (TCutG **) new TCutG *[dVWIdentificationAMAX];
    for(int j=0; j<dVWIdentificationAMAX; j++) {
      fIdentificationCuts[i][j]=0;
    }
  }
}

//____________________________________________________
VWIdentification::~VWIdentification()
{
  for(int i=0; i<dVWIdentificationZMAX; i++) {
    delete [] fIdentificationCuts[i];
  }
  delete [] fIdentificationCuts;
  if(fFileCuts) {
    fFileCuts->Close();
    delete fFileCuts;
  }
}

//____________________________________________________
int VWIdentification::LoadIdentificationCuts(const char * file_name)
{
  int NCuts=0;

  fFileCuts = new TFile(file_name);
  if(fFileCuts->IsZombie()) {
    return -1;
  }

  for(int i=0; i<dVWIdentificationZMAX; i++) {
    for(int j=0; j<dVWIdentificationAMAX; j++) {
      fIdentificationCuts[i][j]=(TCutG*)fFileCuts->Get(Form("VW_DETOF_Z%02d_A%02d", i+1, j+1));
      if(fIdentificationCuts[i][j]) NCuts++;
    }
  }

  if(NCuts>0) fCutsLoaded=true;
  return NCuts;
}

//____________________________________________________
bool VWIdentification::IsChargedParticle(double DE, double TOF) const
{
  for(int i=0; i<dVWIdentificationZMAX; i++) {
    for(int j=0; j<dVWIdentificationAMAX; j++) {
      if(fIdentificationCuts[i][j] && fIdentificationCuts[i][j]->IsInside(TOF,DE)) return true;
    }
  }
  return false;
}

//____________________________________________________
int VWIdentification::GetZ(double DE, double TOF) const
{
  for(int i=0; i<dVWIdentificationZMAX; i++) {
    for(int j=0; j<dVWIdentificationAMAX; j++) {
      if(fIdentificationCuts[i][j] && fIdentificationCuts[i][j]->IsInside(TOF,DE)) return i+1;
    }
  }
  return -1;
}

//____________________________________________________
int VWIdentification::GetA(double DE, double TOF) const
{
  for(int i=0; i<dVWIdentificationZMAX; i++) {
    for(int j=0; j<dVWIdentificationAMAX; j++) {
      if(fIdentificationCuts[i][j] && fIdentificationCuts[i][j]->IsInside(TOF,DE)) return j+1;
    }
  }
  return -1;
}
