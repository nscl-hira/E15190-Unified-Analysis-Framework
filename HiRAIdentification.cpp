#include <HiRAIdentification.h>

//________________________________________________
HiRAIdentification::HiRAIdentification(int tot_num_tel, int num_csi_tel) :
fNumTel(tot_num_tel),
fNumCsITel(num_csi_tel),
fNumCsITot(fNumTel*fNumCsITel),
fEdFTool(new HiRAEdFIdentificationParameters[fNumCsITot]),
fIdentificationLoaded(false)
{}

//________________________________________________
HiRAIdentification::~HiRAIdentification()
{
  delete [] fEdFTool;
}

//________________________________________________
int HiRAIdentification::LoadIdentification(const char * file_name)
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

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int numtel;
    int mf;
    int numpar;
    double TheParameter;

    LineStream >> numtel >> mf >> numpar;

    fEdFTool[numtel].SetNumParameters(numpar);

    for(int i=0; i<numpar; i++) {
      LineStream>>TheParameter;
      fEdFTool[numtel].SetParameter(i, TheParameter);
    }

    NRead++;
  }

  if(NRead>0) fIdentificationLoaded=true;
  return NRead;
}

//________________________________________________
int HiRAIdentification::PerformIdentification(HiRACalibratedData * pCalibratedEvent)
{
  int NIdParticles=0;

  for(int i=0; i<pCalibratedEvent->fmulti; i++)
  {
    int NumTel=pCalibratedEvent->fnumtel[i];
    int NumCsI=pCalibratedEvent->fnumcsi[i];
    double DE = pCalibratedEvent->fEnergySifCal[i];
    double ERes_ch = pCalibratedEvent->fEnergycsi[i];

    int iter;
    double zeta;

    int IdentifiedZ = fIdentificationLoaded ? fEdFTool[NumTel*NUM_CSI_TEL+NumCsI].Get_Charge(DE, ERes_ch, &iter, &zeta) : 0;

    if(IdentifiedZ>0) { //The particle is identified
      pCalibratedEvent->fZ[i]=zeta;
      pCalibratedEvent->fZId[i]=IdentifiedZ;
      pCalibratedEvent->fA[i]=fEdFTool[NumTel*NUM_CSI_TEL+NumCsI].Get_Mass(pCalibratedEvent->fZId[i], DE, ERes_ch, &iter);
      pCalibratedEvent->fAId[i]=int(round(pCalibratedEvent->fA[i]));
      pCalibratedEvent->fIdCode[i]=1;
      NIdParticles++;
    } else {
      pCalibratedEvent->fZ[i]=-9999;
      pCalibratedEvent->fA[i]=-9999;
      pCalibratedEvent->fZId[i]=-9999;
      pCalibratedEvent->fAId[i]=-9999;
      pCalibratedEvent->fIdCode[i]=0;
    }
  }

  return NIdParticles;
}
