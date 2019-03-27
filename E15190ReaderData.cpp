#include <E15190Reader.h>

//____________________________________________________
void E15190Reader::BuildCalibratedEvent()
{
  if(fIsNWA) {
    HTNeutronWallData * NWA = fNWA->Get();
    //Filling calibrated data structures
    fNWACalibratedData.fmulti=0;
    for(int i=0; i<NWA->fmulti; i++)
    {
      if(1) {
        fNWACalibratedData.fnumbar[fNWACalibratedData.fmulti]      =NWA->fnumbar[i];
        fNWACalibratedData.fLeft[fNWACalibratedData.fmulti]        =NWA->fLeft[i];
        fNWACalibratedData.fRight[fNWACalibratedData.fmulti]       =NWA->fRight[i];
        fNWACalibratedData.ffastLeft[fNWACalibratedData.fmulti]    =NWA->ffastLeft[i];
        fNWACalibratedData.ffastRight[fNWACalibratedData.fmulti]   =NWA->ffastRight[i];
        fNWACalibratedData.fTimeLeft[fNWACalibratedData.fmulti]    =NWA->fTimeLeft[i];
        fNWACalibratedData.fTimeRight[fNWACalibratedData.fmulti]   =NWA->fTimeRight[i];
        fNWACalibratedData.fGeoMean[fNWACalibratedData.fmulti]     =NWA->fGeoMean[i];
        fNWACalibratedData.ffastGeoMean[fNWACalibratedData.fmulti] =NWA->ffastGeoMean[i];
        fNWACalibratedData.fTimeMean[fNWACalibratedData.fmulti]    =GetNWATimeMean(NWA->fnumbar[i],NWA->fTimeLeft[i],NWA->fTimeRight[i]);
        fNWACalibratedData.fMatchedLeft[fNWACalibratedData.fmulti] =GetNWALeftMatched(NWA->fLeft[i], NWA->fnumbar[i]);
        fNWACalibratedData.fMatchedRight[fNWACalibratedData.fmulti]=GetNWARightMatched(NWA->fRight[i], NWA->fnumbar[i]);
        fNWACalibratedData.fMatchedGeoMean[fNWACalibratedData.fmulti]=sqrt(fNWACalibratedData.fMatchedLeft[fNWACalibratedData.fmulti]*fNWACalibratedData.fMatchedRight[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]         =GetNWAXcm(NWA->fnumbar[i],NWA->fTimeLeft[i],NWA->fTimeRight[i]);
        fNWACalibratedData.fCalGeoMean[fNWACalibratedData.fmulti]  =GetNWAPulseHeightCalibrated(NWA->fGeoMean[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti],NWA->fnumbar[i]);
        fNWACalibratedData.fFlattenedGeoMean[fNWACalibratedData.fmulti]  =GetNWAPSDFlattened(NWA->fGeoMean[i],NWA->ffastGeoMean[i],NWA->fnumbar[i]);
        fNWACalibratedData.fTheta[fNWACalibratedData.fmulti]       =GetNWATheta(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fPhi[fNWACalibratedData.fmulti]         =GetNWAPhi(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fThetaRan[fNWACalibratedData.fmulti]    =GetNWAThetaRan(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fPhiRan[fNWACalibratedData.fmulti]      =GetNWAPhiRan(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fDistcm[fNWACalibratedData.fmulti]      =GetNWADistance(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fDistRancm[fNWACalibratedData.fmulti]   =GetNWADistanceRan(NWA->fnumbar[i],fNWACalibratedData.fXcm[fNWACalibratedData.fmulti]);
        fNWACalibratedData.fIsGamma[fNWACalibratedData.fmulti]     =IsNWAGamma(NWA->fGeoMean[i],NWA->ffastGeoMean[i],NWA->fnumbar[i]);
        fNWACalibratedData.fmulti++;
      }
    }
  }

  if(fIsNWB) {
    HTNeutronWallData * NWB = fNWB->Get();
    fNWBCalibratedData.fmulti=0;
    for(int i=0; i<NWB->fmulti; i++)
    {
      if(1) {
        fNWBCalibratedData.fnumbar[fNWBCalibratedData.fmulti]      =NWB->fnumbar[i];
        fNWBCalibratedData.fLeft[fNWBCalibratedData.fmulti]        =NWB->fLeft[i];
        fNWBCalibratedData.fRight[fNWBCalibratedData.fmulti]       =NWB->fRight[i];
        fNWBCalibratedData.ffastLeft[fNWBCalibratedData.fmulti]    =NWB->ffastLeft[i];
        fNWBCalibratedData.ffastRight[fNWBCalibratedData.fmulti]   =NWB->ffastRight[i];
        fNWBCalibratedData.fTimeLeft[fNWBCalibratedData.fmulti]    =NWB->fTimeLeft[i];
        fNWBCalibratedData.fTimeRight[fNWBCalibratedData.fmulti]   =NWB->fTimeRight[i];
        fNWBCalibratedData.fGeoMean[fNWBCalibratedData.fmulti]     =NWB->fGeoMean[i];
        fNWBCalibratedData.ffastGeoMean[fNWBCalibratedData.fmulti] =NWB->ffastGeoMean[i];
        fNWBCalibratedData.fTimeMean[fNWBCalibratedData.fmulti]    =GetNWBTimeMean(NWB->fnumbar[i],NWB->fTimeLeft[i],NWB->fTimeRight[i]);
        fNWBCalibratedData.fMatchedLeft[fNWBCalibratedData.fmulti] =GetNWBLeftMatched(NWB->fLeft[i], NWB->fnumbar[i]);
        fNWBCalibratedData.fMatchedRight[fNWBCalibratedData.fmulti]=GetNWBRightMatched(NWB->fRight[i], NWB->fnumbar[i]);
        fNWBCalibratedData.fMatchedGeoMean[fNWBCalibratedData.fmulti]=sqrt(fNWBCalibratedData.fMatchedLeft[fNWBCalibratedData.fmulti]*fNWBCalibratedData.fMatchedRight[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]         =GetNWBXcm(NWB->fnumbar[i],NWB->fTimeLeft[i],NWB->fTimeRight[i]);
        fNWBCalibratedData.fCalGeoMean[fNWBCalibratedData.fmulti]  =GetNWBPulseHeightCalibrated(NWB->fGeoMean[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti],NWB->fnumbar[i]);
        fNWBCalibratedData.fFlattenedGeoMean[fNWBCalibratedData.fmulti]  =GetNWBPSDFlattened(NWB->fGeoMean[i],NWB->ffastGeoMean[i],NWB->fnumbar[i]);
        fNWBCalibratedData.fTheta[fNWBCalibratedData.fmulti]       =GetNWBTheta(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fPhi[fNWBCalibratedData.fmulti]         =GetNWBPhi(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fThetaRan[fNWBCalibratedData.fmulti]    =GetNWBThetaRan(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fPhiRan[fNWBCalibratedData.fmulti]      =GetNWBPhiRan(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fDistcm[fNWBCalibratedData.fmulti]      =GetNWBDistance(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fDistRancm[fNWBCalibratedData.fmulti]   =GetNWBDistanceRan(NWB->fnumbar[i],fNWBCalibratedData.fXcm[fNWBCalibratedData.fmulti]);
        fNWBCalibratedData.fIsGamma[fNWBCalibratedData.fmulti]     =IsNWBGamma(NWB->fGeoMean[i],NWB->ffastGeoMean[i],NWB->fnumbar[i]);
        fNWBCalibratedData.fmulti++;
      }
    }
  }

  if(fIsFA) {
    HTForwardArrayData * ForwardArray = fForwardArray->Get();
    fForwardArrayCalibratedData.fmulti=0;
    for(int i=0; i<ForwardArray->fmulti; i++)
    {
      if(1) {
        fForwardArrayCalibratedData.fnumdet[fForwardArrayCalibratedData.fmulti]    = ForwardArray->fnumdet[i];
        fForwardArrayCalibratedData.fE[fForwardArrayCalibratedData.fmulti]         = ForwardArray->fE[i];
        fForwardArrayCalibratedData.fTime[fForwardArrayCalibratedData.fmulti]      = ForwardArray->fTime[i]-GetFATimeOffset(ForwardArray->fnumdet[i])+GetFATimePulseHeightCorrection(ForwardArray->fnumdet[i], ForwardArray->fE[i]);
        fForwardArrayCalibratedData.fmulti++;
      }
    }
    //FA tmean and tmin are here calculated. They correspond, respectively to the minimum FA time of the matched times and the
    //time average between any other time which differs for less than 3ns with the minumum
    fForwardArrayCalibratedData.fTimeMin = *std::min_element(fForwardArrayCalibratedData.fTime, fForwardArrayCalibratedData.fTime+fForwardArrayCalibratedData.fmulti);
    double ttolerance=3; //time mean is found within the elements that differ for less than 3 ns from the minimum
    int tgood=0; //number of FA elements giving a time within the tolerance limit
    fForwardArrayCalibratedData.fTimeMean=0;
    for(int i=0; i<fForwardArrayCalibratedData.fmulti; i++) {
      if(fabs(fForwardArrayCalibratedData.fTime[i]-fForwardArrayCalibratedData.fTimeMin) < ttolerance) {
        fForwardArrayCalibratedData.fTimeMean+=fForwardArrayCalibratedData.fTime[i];
        tgood++;
      }
    }
    fForwardArrayCalibratedData.fTimeMean/=tgood;
  }

  if(fIsVW) {
    HTVetoWallData * VetoWall = fVetoWall->Get();
    fVetoWallCalibratedData.fmulti=0;
    for(int i=0; i<VetoWall->fmulti; i++)
    {
      if(1) {
        fVetoWallCalibratedData.fnumbar[fVetoWallCalibratedData.fmulti]     =VetoWall->fnumbar[i];
        fVetoWallCalibratedData.fTop[fVetoWallCalibratedData.fmulti]        =VetoWall->fTop[i];
        fVetoWallCalibratedData.fBottom[fVetoWallCalibratedData.fmulti]     =VetoWall->fBottom[i];
        fVetoWallCalibratedData.fTimeTop[fVetoWallCalibratedData.fmulti]    =VetoWall->fTimeTop[i];
        fVetoWallCalibratedData.fTimeBottom[fVetoWallCalibratedData.fmulti] =VetoWall->fTimeBottom[i];
        fVetoWallCalibratedData.fGeoMean[fVetoWallCalibratedData.fmulti]    =VetoWall->fGeoMean[i];
	fVetoWallCalibratedData.fYcm[fVetoWallCalibratedData.fmulti]        =GetVWYcm(VetoWall->fnumbar[i], VetoWall->fTimeBottom[i], VetoWall->fTimeTop[i]);
        fVetoWallCalibratedData.fGeoMeanMatched[fVetoWallCalibratedData.fmulti] =GetVWGeoMeanMatched(VetoWall->fGeoMean[i], VetoWall->fnumbar[i]);
	fVetoWallCalibratedData.fCalGeoMean[fVetoWallCalibratedData.fmulti] =GetVWPulseHeightCalibrated(VetoWall->fGeoMean[i],fVetoWallCalibratedData.fYcm[fNWACalibratedData.fmulti],VetoWall->fnumbar[i]);
        fVetoWallCalibratedData.fTheta[fVetoWallCalibratedData.fmulti]      =GetVWTheta(VetoWall->fnumbar[i], fVetoWallCalibratedData.fYcm[fVetoWallCalibratedData.fmulti]);
        fVetoWallCalibratedData.fPhi[fVetoWallCalibratedData.fmulti]        =GetVWPhi(VetoWall->fnumbar[i], fVetoWallCalibratedData.fYcm[fVetoWallCalibratedData.fmulti]);
        fVetoWallCalibratedData.fThetaRan[fVetoWallCalibratedData.fmulti]   =GetVWThetaRan(VetoWall->fnumbar[i], fVetoWallCalibratedData.fYcm[fVetoWallCalibratedData.fmulti]);
        fVetoWallCalibratedData.fPhiRan[fVetoWallCalibratedData.fmulti]     =GetVWPhiRan(VetoWall->fnumbar[i], fVetoWallCalibratedData.fYcm[fVetoWallCalibratedData.fmulti]);
        fVetoWallCalibratedData.fDistcm[fVetoWallCalibratedData.fmulti]     =GetVWDistance(VetoWall->fnumbar[i], fVetoWallCalibratedData.fYcm[fVetoWallCalibratedData.fmulti]);
        fVetoWallCalibratedData.fDistRancm[fVetoWallCalibratedData.fmulti]  =GetVWDistanceRan(VetoWall->fnumbar[i], fVetoWallCalibratedData.fYcm[fVetoWallCalibratedData.fmulti]);
        fVetoWallCalibratedData.fmulti++;
      }
    }
  }

  if(fIsHiRA) {
    //Analysis of the HiRA detector
    fHiRACalibratedData.fmulti=0;

    //Creation of a buffer of calibrated data for the event
    for(int i=0; i<NUM_TEL; i++)
    {
      fHiRACalibratedDataBuffer.fmultistripf=0;
      fHiRACalibratedDataBuffer.fmultistripb=0;
      fHiRACalibratedDataBuffer.fmulticsi=0;
      HTHiRAData * HiRA = fHiRA[i]->Get();
      for(int j=0; j<HiRA->fEF.fmulti; j++) {
        if(IsStripfBad(i,HiRA->fEF.fnumstrip[j])) continue;
        fHiRACalibratedDataBuffer.fnumstripf[fHiRACalibratedDataBuffer.fmultistripf]=HiRA->fEF.fnumstrip[j];
        fHiRACalibratedDataBuffer.fEnergySifHi[fHiRACalibratedDataBuffer.fmultistripf]=HiRA->fEF.fEnergyHi[j];
        fHiRACalibratedDataBuffer.fEnergySifLo[fHiRACalibratedDataBuffer.fmultistripf]=HiRA->fEF.fEnergyLo[j];
        fHiRACalibratedDataBuffer.fTimeSif[fHiRACalibratedDataBuffer.fmultistripf]=HiRA->fEF.fTime[j];
        fHiRACalibratedDataBuffer.fEnergySifMatched[fHiRACalibratedDataBuffer.fmultistripf]=GetSifHiLowMatched(HiRA->fEF.fEnergyHi[j], HiRA->fEF.fEnergyLo[j], i, HiRA->fEF.fnumstrip[j]);
        fHiRACalibratedDataBuffer.fEnergySifCal[fHiRACalibratedDataBuffer.fmultistripf]=GetSifHiLowMatchedEMeV(HiRA->fEF.fEnergyHi[j], HiRA->fEF.fEnergyLo[j], i, HiRA->fEF.fnumstrip[j]);
        fHiRACalibratedDataBuffer.fmultistripf++;
      }
      for(int j=0; j<HiRA->fEB.fmulti; j++) {
        if(IsStripbBad(i,HiRA->fEB.fnumstrip[j])) continue;
        fHiRACalibratedDataBuffer.fnumstripb[fHiRACalibratedDataBuffer.fmultistripb]=HiRA->fEB.fnumstrip[j];
        fHiRACalibratedDataBuffer.fEnergySibHi[fHiRACalibratedDataBuffer.fmultistripb]=HiRA->fEB.fEnergyHi[j];
        fHiRACalibratedDataBuffer.fEnergySibLo[fHiRACalibratedDataBuffer.fmultistripb]=HiRA->fEB.fEnergyLo[j];
        fHiRACalibratedDataBuffer.fTimeSib[fHiRACalibratedDataBuffer.fmultistripb]=HiRA->fEB.fTime[j];
        fHiRACalibratedDataBuffer.fEnergySibMatched[fHiRACalibratedDataBuffer.fmultistripb]=GetSibHiLowMatched(HiRA->fEB.fEnergyHi[j], HiRA->fEB.fEnergyLo[j], i, HiRA->fEB.fnumstrip[j]);
        fHiRACalibratedDataBuffer.fEnergySibCal[fHiRACalibratedDataBuffer.fmultistripb]=GetSibHiLowMatchedEMeV(HiRA->fEB.fEnergyHi[j], HiRA->fEB.fEnergyLo[j], i, HiRA->fEB.fnumstrip[j]);
        fHiRACalibratedDataBuffer.fmultistripb++;
      }
      for(int j=0; j<HiRA->fCsI.fmulti; j++) {
        fHiRACalibratedDataBuffer.fnumcsi[fHiRACalibratedDataBuffer.fmulticsi]=HiRA->fCsI.fnumcsi[j];
        fHiRACalibratedDataBuffer.fEnergycsi[fHiRACalibratedDataBuffer.fmulticsi]=HiRA->fCsI.fEnergy[j];
        fHiRACalibratedDataBuffer.fTimecsi[fHiRACalibratedDataBuffer.fmulticsi]=HiRA->fCsI.fTime[j];
        fHiRACalibratedDataBuffer.fEnergycsiCalProtons[fHiRACalibratedDataBuffer.fmulticsi]=GetCsIEMeV(HiRA->fCsI.fEnergy[j], i, HiRA->fCsI.fnumcsi[j]); //CsI Proton-equivalent Energy
        fHiRACalibratedDataBuffer.fEnergycsiVolt[fHiRACalibratedDataBuffer.fmulticsi]=GetCsIVoltage(HiRA->fCsI.fEnergy[j], i, HiRA->fCsI.fnumcsi[j]); //CsI voltage from pulser calibration

        fHiRACalibratedDataBuffer.fmulticsi++;
      }

      //Pixelization for the current telescope
      fHiRAPixelizationModule->Pixelization(i,&fHiRACalibratedDataBuffer,&fHiRACalibratedData);
    }

    //Particle Identification
    if(fHiRAIdentificationLoaded) {
      fHiRAIdentifiationModule->PerformIdentification(&fHiRACalibratedData);
    }

    //Geometry and Energy
    for(int i=0; i<fHiRACalibratedData.fmulti; i++) {
      fHiRACalibratedData.fTheta[i]=GetThetaPixel(fHiRACalibratedData.fnumtel[i], fHiRACalibratedData.fnumstripf[i], fHiRACalibratedData.fnumstripb[i]);
      fHiRACalibratedData.fPhi[i]=GetPhiPixel(fHiRACalibratedData.fnumtel[i], fHiRACalibratedData.fnumstripf[i], fHiRACalibratedData.fnumstripb[i]);
      fHiRACalibratedData.fEnergycsiCal[i]=GetCsIEMeV(fHiRACalibratedData.fEnergycsi[i],fHiRACalibratedData.fnumtel[i],fHiRACalibratedData.fnumcsi[i],fHiRACalibratedData.fZId[i],fHiRACalibratedData.fAId[i]); //Energy in the CsI
      fHiRACalibratedData.fKinEnergy[i]=fHiRACalibratedData.fEnergycsiCal[i]>0 ? GetHiRAKineticEnergy(fHiRACalibratedData.fnumtel[i], fHiRACalibratedData.fZId[i], fHiRACalibratedData.fAId[i], fHiRACalibratedData.fEnergySifCal[i]+fHiRACalibratedData.fEnergycsiCal[i], fHiRACalibratedData.fTheta[i]) : -9999; //Total kinetic energy as the sum of DE (front) and E + the energy loss in the absorbers
      fHiRACalibratedData.fBeta[i]=fHiRACalibratedData.fKinEnergy[i]>0 ? -9999 : -9999;
      fHiRACalibratedData.fMomentum[i]=fHiRACalibratedData.fKinEnergy[i]>0 ? -9999 : -9999;
    }
  }

  if(fIsMB) {
    HTMicroballData * Microball = fMicroball->Get();
    //Filling calibrated data structures
    fMicroballCalibratedData.fmulti=0;
    for(int i=0; i<Microball->fmulti; i++)
    {
      if(!IsMBDetectorBad(Microball->fnumring[i], Microball->fnumdet[i]) && IsMBHit(Microball->fnumring[i], Microball->fnumdet[i],Microball->fFast[i],Microball->fTail[i],Microball->fTime[i])) {
        fMicroballCalibratedData.fnumring[fMicroballCalibratedData.fmulti] =Microball->fnumring[i];
        fMicroballCalibratedData.fnumdet[fMicroballCalibratedData.fmulti]  =Microball->fnumdet[i];
        fMicroballCalibratedData.fTail[fMicroballCalibratedData.fmulti]    =Microball->fTail[i];
        fMicroballCalibratedData.fFast[fMicroballCalibratedData.fmulti]    =Microball->fFast[i];
        fMicroballCalibratedData.fTime[fMicroballCalibratedData.fmulti]    =Microball->fTime[i];

        fMicroballCalibratedData.fTheta[fMicroballCalibratedData.fmulti]   =GetMBTheta(Microball->fnumring[i], Microball->fnumdet[i]);
        fMicroballCalibratedData.fPhi[fMicroballCalibratedData.fmulti]     =GetMBPhi(Microball->fnumring[i], Microball->fnumdet[i]);
        fMicroballCalibratedData.fThetaRan[fMicroballCalibratedData.fmulti]=GetMBThetaRandom(Microball->fnumring[i], Microball->fnumdet[i]);
        fMicroballCalibratedData.fPhiRan[fMicroballCalibratedData.fmulti]  =GetMBPhiRandom(Microball->fnumring[i], Microball->fnumdet[i]);

        fMicroballCalibratedData.fmulti++;
      }
      //Microball Event Varaibles
      fMicroballCalibratedData.fb     =GetMBImpactParameter(fMicroballCalibratedData.fmulti);
      fMicroballCalibratedData.fbhat  =GetMBbhat(fMicroballCalibratedData.fmulti);
    }
  }

  if(fIsTDC) {
    fTDCAdditionalChannels->FillOutputBranches();
  }

  if(fIsTS) {
    fTimestampChannels->FillOutputBranches();
  }
}

//____________________________________________________
void E15190Reader::BuildCalibratedTree(const char * file_name, Long64_t evt_amount)
{
  // this method constructs a calibrated data tree

  TFile * FileOut = new TFile(file_name, "RECREATE");
  if(FileOut->IsZombie()) {
    printf("Error: Cannot create file %s\n", file_name);
    return;
  }
  // Initializing output TTree
  TTree * TreeOut = new TTree ("E15190", "Calibrated Data");
  if(fIsNWA) TreeOut->Branch("NWA.","NeutronWallCalibratedData",&fNWACalibratedData,32000,2);
  if(fIsNWB) TreeOut->Branch("NWB.","NeutronWallCalibratedData",&fNWBCalibratedData,32000,2);
  if(fIsVW) TreeOut->Branch("VetoWall.","VetoWallCalibratedData",&fVetoWallCalibratedData,32000,2);
  if(fIsFA) TreeOut->Branch("ForwardArray.","ForwardArrayCalibratedData",&fForwardArrayCalibratedData,32000,2);
  if(fIsMB) TreeOut->Branch("uBall.","MicroballCalibratedData",&fMicroballCalibratedData,32000,2);
  if(fIsHiRA) TreeOut->Branch("HiRA.","HiRACalibratedData",&fHiRACalibratedData,32000,2);
  if(fIsTDC) fTDCAdditionalChannels->SetOutputTree(TreeOut);
  if(fIsTS) fTimestampChannels->SetOutputTree(TreeOut);

  TreeOut->GetUserInfo()->Add(fBeam);
  TreeOut->GetUserInfo()->Add(fBeamEnergy);
  TreeOut->GetUserInfo()->Add(fTarget);

  TreeOut->SetDirectory(FileOut);
  TreeOut->SetAutoSave(5000000);

  Long64_t nentries=fChain->GetEntries();
  if(evt_amount!=0) {
    nentries=evt_amount;
  }
  Long64_t jentry=0;
  std::cout << "found " << nentries << " entries\n";
  fStartTime = clock(); // initializing start time
  for(;fE15190Reader->Next() && jentry<nentries; jentry++)
  {
    if(jentry%100000==0) {
      PrintPercentage(jentry,nentries);
    }

    BuildCalibratedEvent();

    TreeOut->Fill();
  }

  //Save Output Tree to file
  TreeOut->AutoSave();

  // closing output file
  FileOut->Close();
}

//____________________________________________________
int E15190Reader::Next()
{
  int value = fE15190Reader->Next();
  if(!fIsDataCalibrated && value) BuildCalibratedEvent();
  return value;
}

//____________________________________________________
void * E15190Reader::GetData(const char * det_name)
{
  if(fIsDataCalibrated) {
    if(strcmp(det_name, "HiRA")==0 && fIsHiRA) {
      return (void *)fHiRACal->Get();
    } else if(strcmp(det_name, "NWA")==0 && fIsNWA) {
      return (void *)fNWACal->Get();
    } else if(strcmp(det_name, "NWB")==0 && fIsNWB) {
      return (void *)fNWBCal->Get();
    } else if(strcmp(det_name, "VW")==0 && fIsVW) {
      return (void *)fVetoWallCal->Get();
    } else if(strcmp(det_name, "FA")==0 && fIsFA) {
      return (void *)fForwardArrayCal->Get();
    } else if(strcmp(det_name, "uBall")==0 && fIsMB) {
      return (void *)fMicroballCal->Get();
    }
  } else {
    if(strcmp(det_name, "HiRA")==0 && fIsHiRA) {
      return (void *)&fHiRACalibratedData;
    } else if(strcmp(det_name, "NWA")==0 && fIsNWA) {
      return (void *)&fNWACalibratedData;
    } else if(strcmp(det_name, "NWB")==0 && fIsNWB) {
      return (void *)&fNWACalibratedData;
    } else if(strcmp(det_name, "VW")==0 && fIsVW) {
      return (void *)&fVetoWallCalibratedData;
    } else if(strcmp(det_name, "FA")==0 && fIsFA) {
      return (void *)&fForwardArrayCalibratedData;
    } else if(strcmp(det_name, "uBall")==0 && fIsMB) {
      return (void *)&fMicroballCalibratedData;
    }
  }
}
