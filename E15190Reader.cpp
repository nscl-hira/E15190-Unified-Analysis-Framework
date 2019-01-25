#include "include/E15190Reader.h"

//____________________________________________________
E15190Reader::E15190Reader(TChain * Chain, HTRunInfo * CurrRunInfo, const char * DataType, bool IsDataCalibrated) :
fCurrRunInfo(CurrRunInfo),
fHiRA(new TTreeReaderValue<HTHiRAData> *[NUM_TEL]),
fChain(Chain),
fStartTime(clock()),
fDegToRad(TMath::Pi()/180.),
fRadToDeg(180./TMath::Pi()),
fSpeedOfLight(29.9792),
fNWBarLength(200),
fNWBarHigh(7.62),
fNWBarThickness(6.35),
fIsTDC(false),
fIsTS(false),
fIsNWA(false),
fIsNWB(false),
fIsFA(false),
fIsVW(false),
fIsMB(false),
fIsHiRA(false),
fIsDataCalibrated(IsDataCalibrated),
fNWAPositionCalibrated(false),
fNWBPositionCalibrated(false),
fNWTimeCalibrated(false),
fNWPulseHeightCalibrated(false),
fNWACosmicRayPositionLoaded(false),
fNWBCosmicRayPositionLoaded(false),
fNWATimeCalibrated(false),
fNWBTimeCalibrated(false),
fNWAGeometryCalibrated(false),
fNWBGeometryCalibrated(false),
fNWAPulseHeightMatched(false),
fNWBPulseHeightMatched(false),
fNWAPulseHeightCalibrated(false),
fNWBPulseHeightCalibrated(false),
fNWAPSDFlattened(false),
fNWBPSDFlattened(false),
fNWAPSDCutsLoaded(false),
fNWBPSDCutsLoaded(false),
fFATimeCalibrated(false),
fVWPulseHeightMatched(false),
fVWIdentificationLoaded(false),
fVWPositionCalibrated(false),
fVWPulseHeightCalibrated(false),
fMBGeometryLoaded(false),
fMBStatusLoaded(false),
fMBHitConditionLoaded(false),
fMBCentralityLoaded(false),
fHiRACsICalibrated(false),
fHiRACsIPulserCalibrated(false),
fHiRASiCalibrated(false),
fHiRAGeometryCalibrated(false),
fHiRAStripBadLoaded(false),
fHiRASiHiLowMatched(false),
fNWAPositionCalibration(new NWPositionCalibration(NUM_BARS_NWA)),
fNWBPositionCalibration(new NWPositionCalibration(NUM_BARS_NWB)),
fNWACosmicRayInfo(new NWCosmicRayManager(NUM_BARS_NWA)),
fNWBCosmicRayInfo(new NWCosmicRayManager(NUM_BARS_NWB)),
fNWATimeCalibration(new NWTimeCalibration(NUM_BARS_NWA)),
fNWBTimeCalibration(new NWTimeCalibration(NUM_BARS_NWB)),
fNWAGeometry(new NWGeometry(NUM_BARS_NWA)),
fNWBGeometry(new NWGeometry(NUM_BARS_NWB)),
fNWAPulseHeightCalibrationTools(new NWPulseHeightCalibration(NUM_BARS_NWA)),
fNWBPulseHeightCalibrationTools(new NWPulseHeightCalibration(NUM_BARS_NWB)),
fNWAPulseShapeDiscriminationTools(new NWPulseShapeDiscrimination(NUM_BARS_NWA)),
fNWBPulseShapeDiscriminationTools(new NWPulseShapeDiscrimination(NUM_BARS_NWB)),
fFATimeCalibration(new FATimeCalibration(NUM_DETECTORS_FA)),
fVWPulseHeightCalibrationTools(new VWPulseHeightCalibration(NUM_BARS_VW)),
fVWIdentificationModule(new VWIdentification()),
fVWGeometryModule(new VWGeometry(NUM_BARS_VW)),
fVWPositionCalibration(new NWPositionCalibration(NUM_BARS_VW)),
fMicroballStatus(new MBDetectorStatus()),
fMicroballGeometry(new MBGeometry()),
fMicroballHitCondition(new MBHitCondition()),
fMicroballCentrality(new MBImpactParameter()),
fHiRAGeometryTab(new HiRAGeometry(NUM_TEL,NUM_STRIP_F,NUM_STRIP_B)),
fSiCalibrationTools(new HiRASiCalibration(NUM_TEL,NUM_STRIP_F,NUM_STRIP_B)),
fCsICalibrationModule(new HiRACsICalibrationManager()),
fHiRAStatus(new HiRADetectorStatus(NUM_TEL,NUM_STRIP_F,NUM_STRIP_B)),
fHiRAIdentifiationModule(new HiRAIdentification(NUM_TEL,NUM_CSI_TEL)),
fHiRAPixelizationModule(new HiRAPixelization(NUM_TEL))
{
  //Parsing DataType string to allocate specific detectors
  std::string DetectorsIncluded(DataType);
  std::istringstream StreamDetectorsIncluded(DetectorsIncluded);
  std::string DetectorToAdd;
  while(std::getline(StreamDetectorsIncluded, DetectorToAdd, '-')) {
    if(DetectorToAdd.compare("NWA")==0) fIsNWA=true;
    if(DetectorToAdd.compare("NWB")==0) fIsNWB=true;
    if(DetectorToAdd.compare("FA")==0) fIsFA=true;
    if(DetectorToAdd.compare("VW")==0) fIsVW=true;
    if(DetectorToAdd.compare("uBall")==0) fIsMB=true;
    if(DetectorToAdd.compare("HiRA")==0) fIsHiRA=true;
    if(DetectorToAdd.compare("TDC")==0) fIsTDC=true;
    if(DetectorToAdd.compare("TS")==0) fIsTS=true;
  }

  if(fChain!=0) {
    fE15190Reader = new TTreeReader(fChain);
    if(!fIsDataCalibrated) {
      if(fIsNWA) fNWA = new TTreeReaderValue<HTNeutronWallData>(*fE15190Reader, "NWA.");
      if(fIsNWB) fNWB = new TTreeReaderValue<HTNeutronWallData>(*fE15190Reader, "NWB.");
      if(fIsFA) fForwardArray = new TTreeReaderValue<HTForwardArrayData>(*fE15190Reader, "ForwardArray.");
      if(fIsVW) fVetoWall = new TTreeReaderValue<HTVetoWallData>(*fE15190Reader, "VetoWall.");
      if(fIsMB) fMicroball = new TTreeReaderValue<HTMicroballData>(*fE15190Reader, "uBall.");
      if(fIsHiRA) {
        for(int i=0; i<NUM_TEL; i++) fHiRA[i] = new TTreeReaderValue<HTHiRAData>(*fE15190Reader, Form("HiRA.tele%d.",i));
      }
    } else {
      if(fIsNWA) fNWACal = new TTreeReaderValue<NeutronWallCalibratedData>(*fE15190Reader, "NWA.");
      if(fIsNWB) fNWBCal = new TTreeReaderValue<NeutronWallCalibratedData>(*fE15190Reader, "NWB.");
      if(fIsFA) fForwardArrayCal = new TTreeReaderValue<ForwardArrayCalibratedData>(*fE15190Reader, "ForwardArray.");
      if(fIsVW) fVetoWallCal = new TTreeReaderValue<VetoWallCalibratedData>(*fE15190Reader, "VetoWall.");
      if(fIsMB) fMicroballCal = new TTreeReaderValue<MicroballCalibratedData>(*fE15190Reader, "uBall.");
      if(fIsHiRA) fHiRACal = new TTreeReaderValue<HiRACalibratedData>(*fE15190Reader, "HiRA.");
    }

    if(fIsTDC) {
      fTDCAdditionalChannels = new TDCSpareChannels();
      fTDCAdditionalChannels->InitFromMapping(fE15190Reader, fCurrRunInfo->GetMappingFile());
    }

    if(fIsTS) {
      fTimestampChannels = new TimestampChannels();
      fTimestampChannels->InitFromMapping(fE15190Reader, fCurrRunInfo->GetMappingFile());
    }
  }
}

//____________________________________________________
E15190Reader::~E15190Reader()
{
  if(fChain!=0) {
    delete fE15190Reader;
    if(!fIsDataCalibrated) {
      if (fIsNWA) delete fNWA;
      if (fIsNWB) delete fNWB;
      if (fIsFA) delete fForwardArray;
      if (fIsVW) delete fVetoWall;
      if (fIsMB) delete fMicroball;
      if (fIsHiRA) {
        for(int i=0; i<NUM_TEL; i++) delete fHiRA[i];
      }
    } else {
      if (fIsNWA) delete fNWACal;
      if (fIsNWB) delete fNWBCal;
      if (fIsFA) delete fForwardArrayCal;
      if (fIsVW) delete fVetoWallCal;
      if (fIsMB) delete fMicroballCal;
      if (fIsHiRA) delete fHiRACal;
    }

    if(fIsTDC) {
      delete fTDCAdditionalChannels;
    }

    if(fIsTS) {
      delete fTimestampChannels;
    }
  }

  if(fHiRA) delete [] fHiRA;
}

//____________________________________________________
void E15190Reader::InitAllCalibrations()
{
  LoadNWPositionCalibration(fCurrRunInfo->GetNWBPositionCalibrationFileName(), "NWB");
  LoadNWPositionCalibration(fCurrRunInfo->GetNWAPositionCalibrationFileName(), "NWA");
  LoadNWGeometryFiducialPoints(fCurrRunInfo->GetNWBGeometryCalibrationFileName(), "NWB");
  LoadNWGeometryFiducialPoints(fCurrRunInfo->GetNWAGeometryCalibrationFileName(), "NWA");
  LoadNWTimeCalibration(fCurrRunInfo->GetNWBTimeOffsetCalibrationFileName(), "NWB");
  LoadNWPulseHeightMatching(fCurrRunInfo->GetNWBGainMatchingCalibrationFileName(), "NWB");
  LoadNWPulseHeightMatching(fCurrRunInfo->GetNWAGainMatchingCalibrationFileName(), "NWA");
  LoadNWPulseHeightCalibration(fCurrRunInfo->GetNWBPulseHeightCalibrationFileName(), "NWB");//KZ
  LoadNWPulseHeightCalibration(fCurrRunInfo->GetNWAPulseHeightCalibrationFileName(), "NWA");//KZ
  LoadNWPSDFlattening(fCurrRunInfo->GetNWBPSDFlatteningFileName(), "NWB");//KZ
  LoadNWPSDFlattening(fCurrRunInfo->GetNWAPSDFlatteningFileName(), "NWA");//KZ
  LoadNWPSDCuts(fCurrRunInfo->GetNWBPSDCutsFileName(),"NWB"); //KZ
  LoadNWPSDCuts(fCurrRunInfo->GetNWAPSDCutsFileName(),"NWA"); //KZ
  LoadFATimeCalibration(fCurrRunInfo->GetFATimeCalibrationFileName());
  LoadFATimePulseHeightCorrection(fCurrRunInfo->GetFAPulseHeightCorrectionFileName());
  LoadVWGainMatchig(fCurrRunInfo->GetVWGainMatchingCalibrationFileName());
  LoadVWPulseHeightCalibration(fCurrRunInfo->GetVWPulseHeightCalibrationFileName());
  LoadVWIdentificationCuts(fCurrRunInfo->GetVWDETOFPIDCalibrationFileName());
  LoadVWPositionCalibration(fCurrRunInfo->GetVWPositionCalibrationFileName());
  LoadVWGeometryFiducialPoints(fCurrRunInfo->GetVWGeometryFileName());
  LoadMBGeometry(fCurrRunInfo->GetMBGeometryFileName());
  LoadMBDetectorStatus(fCurrRunInfo->GerMBDetectorStatusFileName());
  LoadMBFastSlowHitCondition(fCurrRunInfo->GetMBHitConditionFileName());
  LoadMBCentrality(fCurrRunInfo->GetMBImpactParameterFileName());
  LoadHiRAGeometry(fCurrRunInfo->GetHiRAGeometryFileName());
  LoadHiRASiCalibration(fCurrRunInfo->GetHiRASiEnergyCalibrationFileName());
  LoadHiRAStripBad(fCurrRunInfo->GetHiRADetectorStatusFileName());
  LoadHiRACsIPulserInfo(fCurrRunInfo->GetHiRACsIPulserFileName());
  LoadHiRASiHiLowMatching(fCurrRunInfo->GetHiRASiHiLowMatchingFileName());
  LoadHiRACsICalibration(fCurrRunInfo->GetHiRACsIEnergyCalibrationFileName());
  LoadHiRAIdentification(fCurrRunInfo->GetHiRAPIDFileName());

  fBeam = new TNamed("Beam", fCurrRunInfo->GetBeam());
  fBeamEnergy = new TNamed("Beam Energy (AMeV)", fCurrRunInfo->GetBeamEnergy());
  fTarget = new TNamed("Target", fCurrRunInfo->GetTarget());
}


//____________________________________________________
int E15190Reader::LoadNWPositionCalibration(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    if(!fIsNWA) return 0;
    int NLines=fNWAPositionCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWAPositionCalibrated=true;
      printf("Loaded position calibration for NWA %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWA Position calibration file %s\n", file_name);
    fNWAPositionCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    if(!fIsNWB) return 0;
    int NLines=fNWBPositionCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWBPositionCalibrated=true;
      printf("Loaded position calibration for NWB %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWB Position calibration file %s\n", file_name);
    fNWBPositionCalibrated=false;
  }

  return -1;
}

//____________________________________________________
int E15190Reader::LoadNWCosmicRayPosition(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    if(!fIsNWA) return 0;
    int NLines=fNWACosmicRayInfo->LoadPeakPositions(file_name);
    if(NLines>0) {
      fNWACosmicRayPositionLoaded=true;
      printf("Loaded cosmics calibration for NWA %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWA cosmic ray positions %s\n", file_name);
    fNWACosmicRayPositionLoaded=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    if(!fIsNWB) return 0;
    int NLines=fNWBCosmicRayInfo->LoadPeakPositions(file_name);
    if(NLines>0) {
      fNWBCosmicRayPositionLoaded=true;
      printf("Loaded cosmics calibration for NWB %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWB cosmic ray positions %s\n", file_name);
    fNWBCosmicRayPositionLoaded=false;
  }

  return -1;
}

//____________________________________________________
int E15190Reader::LoadNWTimeCalibration(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    if(!fIsNWA) return 0;
    int NLines=fNWATimeCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWATimeCalibrated=true;
      printf("Loaded time calibration for NWA %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWA time calibration %s\n", file_name);
    fNWATimeCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    if(!fIsNWB) return 0;
    int NLines=fNWBTimeCalibration->LoadCalibration(file_name);
    if(NLines>0) {
      fNWBTimeCalibrated=true;
      printf("Loaded time calibration for NWB %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWB time calibration %s\n", file_name);
    fNWBTimeCalibrated=false;
  }

  return -1;
}

//____________________________________________________
int E15190Reader::LoadNWGeometryFiducialPoints(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    if(!fIsNWA) return 0;
    int NLines=fNWAGeometry->LoadFiducialPoints(file_name);
    if(NLines>0) {
      fNWAGeometryCalibrated=true;
      printf("Loaded geometry fiducial points for NWA %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWA geometry fiducial points %s\n", file_name);
    fNWAGeometryCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    if(!fIsNWB) return 0;
    int NLines=fNWBGeometry->LoadFiducialPoints(file_name);
    if(NLines>0) {
      fNWBGeometryCalibrated=true;
      printf("Loaded geometry fiducial points for NWB %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWB geometry fiducial points %s\n", file_name);
    fNWBGeometryCalibrated=false;
  }

  return -1;
}

//____________________________________________________
int E15190Reader::LoadNWPulseHeightMatching(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    if(!fIsNWA) return 0;
    int NLines=fNWAPulseHeightCalibrationTools->LoadMatching(file_name);
    if(NLines>0) {
      fNWAPulseHeightMatched=true;
      printf("Loaded gain matching for NWA %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWA gain matching %s\n", file_name);
    fNWAPulseHeightMatched=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    if(!fIsNWB) return 0;
    int NLines=fNWBPulseHeightCalibrationTools->LoadMatching(file_name);
    if(NLines>0) {
      fNWBPulseHeightMatched=true;
      printf("Loaded gain matching for NWB %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWB gain matching %s\n", file_name);
    fNWBPulseHeightMatched=false;
  }

  return -1;
}

//K____________________________________________________
int E15190Reader::LoadNWPulseHeightCalibration(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    if(!fIsNWA) return 0;
    int NLines=fNWAPulseHeightCalibrationTools->LoadPulseHeightCalibration(file_name);
    if(NLines>0) {
      fNWAPulseHeightCalibrated=true;
      printf("Loaded pulse height calibration for NWA %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWA pulse height calibration %s\n", file_name);
    fNWAPulseHeightCalibrated=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    if(!fIsNWB) return 0;
    int NLines=fNWBPulseHeightCalibrationTools->LoadPulseHeightCalibration(file_name);
    if(NLines>0) {
      fNWBPulseHeightCalibrated=true;
      printf("Loaded pulse height calibration for NWB %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWB pulse height calibration %s\n", file_name);
    fNWBPulseHeightCalibrated=false;
  }

  return -1;
}

//K____________________________________________________
int E15190Reader::LoadNWPSDFlattening(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    if(!fIsNWA) return 0;
    int NLines=fNWAPulseShapeDiscriminationTools->LoadPSDFlattening(file_name);
    if(NLines>0) {
      fNWAPSDFlattened=true;
      printf("Loaded PSD Flattening info for NWA %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWA PSD flattening info %s\n", file_name);
    fNWAPSDFlattened=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    if(!fIsNWB) return 0;
    int NLines=fNWBPulseShapeDiscriminationTools->LoadPSDFlattening(file_name);
    if(NLines>0) {
      fNWBPSDFlattened=true;
      printf("Loaded PSD Flattening info for NWB %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWB PSD flattening info %s\n", file_name);
    fNWBPSDFlattened=false;
  }

  return -1;
}

//K____________________________________________________
int E15190Reader::LoadNWPSDCuts(const char * file_name, const char * WallToCalibrate)
{
  if(strcmp(WallToCalibrate,"NWA")==0) {
    if(!fIsNWA) return 0;
    int NLines=fNWAPulseShapeDiscriminationTools->LoadIsGammaCuts(file_name);
    if(NLines>0) {
      fNWAPSDCutsLoaded=true;
      printf("Loaded IsGamma Cuts info for NWA %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWA IsGamma Cuts %s\n", file_name);
    fNWAPSDCutsLoaded=false;
  }
  if(strcmp(WallToCalibrate,"NWB")==0) {
    if(!fIsNWB) return 0;
    int NLines=fNWBPulseShapeDiscriminationTools->LoadIsGammaCuts(file_name);
    if(NLines>0) {
      fNWBPSDCutsLoaded=true;
      printf("Loaded IsGamma Cuts info for NWB %s\n", file_name);
      return NLines;
    }
    printf("Error: Error while loading NWB IsGamma Cuts %s\n", file_name);
    fNWBPSDCutsLoaded=false;
  }

  return -1;
}

//____________________________________________________
int E15190Reader::LoadFATimeCalibration(const char * file_name)
{
  if(!fIsFA) return 0;
  int NLines=fFATimeCalibration->LoadCalibration(file_name);
  if(NLines>0) {
    fFATimeCalibrated=true;
    printf("Loaded time calibration for FA %s\n", file_name);
    return NLines;
  } else {
    fFATimeCalibrated=false;
    printf("Error: Error while loading FA time calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadFATimePulseHeightCorrection(const char * file_name)
{
  if(!fIsFA) return 0;
  int NLines=fFATimeCalibration->LoadPulseHeightCorrection(file_name);
  if(NLines>0) {
    fFATimeCalibrated=true;
    printf("Loaded time pulse height correction for FA %s\n", file_name);
    return NLines;
  } else {
    fFATimeCalibrated=false;
    printf("Error: Error while loading FA time calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadVWGainMatchig(const char * file_name)
{
  if(!fIsVW) return 0;
  int NLines=fVWPulseHeightCalibrationTools->LoadGainMatching(file_name);
  if(NLines>0) {
    fVWPulseHeightMatched=true;
    printf("Loaded VW gain matching %s\n", file_name);
    return NLines;
  } else {
    fVWPulseHeightMatched=false;
    printf("Error: Error while loading VW gain matching %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadVWIdentificationCuts(const char * file_name)
{
  if(!fIsVW) return 0;
  int NLines=fVWIdentificationModule->LoadIdentificationCuts(file_name);
  if(NLines>0) {
    fVWIdentificationLoaded=true;
    printf("Loaded VW DETOF identification cuts %s\n", file_name);
    return NLines;
  } else {
    fVWIdentificationLoaded=false;
    printf("Error: Error while loading VW DETOF identification cuts %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadVWPositionCalibration(const char * file_name)
{
  if(!fIsVW) return 0;
  int NLines=fVWPositionCalibration->LoadCalibration(file_name);
  if(NLines>0) {
    fVWPositionCalibrated=true;
    printf("Loaded VW Position Calibration %s\n", file_name);
    return NLines;
  } else {
    fVWPositionCalibrated=false;
    printf("Error: Error while loading VW Position Calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadVWGeometryFiducialPoints(const char * file_name)
{
  if(!fIsVW) return 0;
  int NLines=fVWGeometryModule->LoadFiducialPoints(file_name);
  if(NLines>0) {
    fVWGeometryLoaded=true;
    printf("Loaded VW Geometry %s\n", file_name);
    return NLines;
  } else {
    fVWGeometryLoaded=false;
    printf("Error: Error while loading VW Geometry %s\n", file_name);
    return -1;
  }
}


//____________________________________________________
int E15190Reader::LoadVWPulseHeightCalibration(const char * file_name)
{
  if(!fIsVW) return 0;
  int NLines=fVWPulseHeightCalibrationTools->LoadPulseHeightCalibration(file_name);
  if(NLines>0) {
    fVWPulseHeightCalibrated=true;
    printf("Loaded VW Pulse Height Calibration %s\n", file_name);
    return NLines;
  } else {
    fVWPulseHeightCalibrated=false;
    printf("Error: Error while loading VW Pulse Height Calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
double E15190Reader::GetNWAXcm(int num_bar, double tleft, double tright) const
{
  return fNWAPositionCalibrated ? fNWAPositionCalibration->GetPosition(num_bar, tleft, tright) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBXcm(int num_bar, double tleft, double tright) const
{
  return fNWBPositionCalibrated ? fNWBPositionCalibration->GetPosition(num_bar, tleft, tright) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWACosmicCenter(int num_bar) const
{
  return fNWACosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayCenter(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWACosmicStartingPoint(int num_bar) const
{
  return fNWACosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayStartingPoint(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBCosmicCenter(int num_bar) const
{
  return fNWBCosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayCenter(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBCosmicStartingPoint(int num_bar) const
{
  return fNWBCosmicRayPositionLoaded ? fNWBCosmicRayInfo->GetCosmicRayStartingPoint(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWATimeMean(int num_bar, double tleft, double tright) const
{
  return fNWATimeCalibrated ? 0.5*(tleft+tright)-fNWATimeCalibration->GetTimeOffset(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBTimeMean(int num_bar, double tleft, double tright) const
{
  return fNWBTimeCalibrated ? 0.5*(tleft+tright)-fNWBTimeCalibration->GetTimeOffset(num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetFATimeOffset(int num_det) const
{
  return fFATimeCalibrated ? fFATimeCalibration->GetTimeOffset(num_det) : 0;
}

//____________________________________________________
double E15190Reader::GetNWATheta(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetTheta(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWAPhi(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetPhi(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWAThetaRan(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetThetaRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWAPhiRan(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetPhiRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWADistance(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetR(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWADistanceRan(int num_bar, double Xcm) const
{
  return fNWAGeometryCalibrated ? fNWAGeometry->GetRRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBTheta(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetTheta(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBPhi(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetPhi(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBThetaRan(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetThetaRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBPhiRan(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetPhiRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBDistance(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetR(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBDistanceRan(int num_bar, double Xcm) const
{
  return fNWBGeometryCalibrated ? fNWBGeometry->GetRRan(num_bar, Xcm) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWALeftMatched(double ch, int num_bar) const
{
  return fNWAPulseHeightMatched ? fNWAPulseHeightCalibrationTools->GetLeftMatched(ch, num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWARightMatched(double ch, int num_bar) const
{
  return fNWAPulseHeightMatched ? fNWAPulseHeightCalibrationTools->GetRightMatched(ch, num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBLeftMatched(double ch, int num_bar) const
{
  return fNWBPulseHeightMatched ? fNWBPulseHeightCalibrationTools->GetLeftMatched(ch, num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetNWBRightMatched(double ch, int num_bar) const
{
  return fNWBPulseHeightMatched ? fNWBPulseHeightCalibrationTools->GetRightMatched(ch, num_bar) : -9999;
}

//KZ____________________________________________________
double E15190Reader::GetNWAPulseHeightCalibrated(double ch, double Xcm, int num_bar) const
{
  return fNWAPulseHeightCalibrated ? fNWAPulseHeightCalibrationTools->GetPulseHeightCalibrated(ch, Xcm, num_bar) : -9999;
}

//KZ____________________________________________________
double E15190Reader::GetNWBPulseHeightCalibrated(double ch, double Xcm, int num_bar) const
{
  return fNWBPulseHeightCalibrated ? fNWBPulseHeightCalibrationTools->GetPulseHeightCalibrated(ch, Xcm, num_bar) : -9999;
}

//KZ____________________________________________________
double E15190Reader::GetNWAPSDFlattened(double ch, double ch_fast, int num_bar) const
{
  return fNWAPSDFlattened ? fNWAPulseShapeDiscriminationTools->GetPSDFlattened(ch, ch_fast, num_bar) : -9999;
}

//KZ____________________________________________________
double E15190Reader::GetNWBPSDFlattened(double ch, double ch_fast, int num_bar) const
{
  return fNWBPSDFlattened ? fNWBPulseShapeDiscriminationTools->GetPSDFlattened(ch, ch_fast, num_bar) : -9999;
}

//KZ____________________________________________________
bool E15190Reader::IsNWAGamma(double ch, double ch_fast, int num_bar) const
{
  return fNWAPSDFlattened&&fNWAPSDCutsLoaded ? fNWAPulseShapeDiscriminationTools->IsGamma(ch, ch_fast, num_bar) : true;
}

//KZ____________________________________________________
bool E15190Reader::IsNWBGamma(double ch, double ch_fast, int num_bar) const
{
  return fNWBPSDFlattened&&fNWBPSDCutsLoaded ? fNWBPulseShapeDiscriminationTools->IsGamma(ch, ch_fast, num_bar) : true;
}

//____________________________________________________
double E15190Reader::GetFATimePulseHeightCorrection(int num_det, double pulse_height) const
{
  return fFATimeCalibrated ? fFATimeCalibration->GetTimePulseHeightCorrection(num_det, pulse_height) : 0;
}

//____________________________________________________
double E15190Reader::GetVWGeoMeanMatched(double ch, int num_bar) const
{
  return fVWPulseHeightMatched ? fVWPulseHeightCalibrationTools->GetGeoMeanMatched(ch, num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetVWPulseHeightCalibrated(double ch, double Ycm, int num_bar) const
{
  return fVWPulseHeightCalibrated ? fVWPulseHeightCalibrationTools->GetPulseHeightCalibrated(ch, Ycm, num_bar) : -9999;
}

//____________________________________________________
double E15190Reader::GetVWYcm(int num_bar, double tbottom, double ttop) const
{
  return fVWPositionCalibrated ? fVWPositionCalibration->GetPosition(num_bar, tbottom, ttop) : -9999;
}

//____________________________________________________
double E15190Reader::GetVWTheta(int num_bar, double Ycm) const
{
  return fVWGeometryLoaded ? fVWGeometryModule->GetTheta(num_bar, Ycm) : -9999;
}

//____________________________________________________
double E15190Reader::GetVWPhi(int num_bar, double Ycm) const
{
  return fVWGeometryLoaded ? fVWGeometryModule->GetPhi(num_bar, Ycm) : -9999;
}

//____________________________________________________
double E15190Reader::GetVWThetaRan(int num_bar, double Ycm) const
{
  return fVWGeometryLoaded ? fVWGeometryModule->GetThetaRan(num_bar, Ycm) : -9999;
}

//____________________________________________________
double E15190Reader::GetVWPhiRan(int num_bar, double Ycm) const
{
  return fVWGeometryLoaded ? fVWGeometryModule->GetPhiRan(num_bar, Ycm) : -9999;
}

//____________________________________________________
double E15190Reader::GetVWDistance(int num_bar, double Ycm) const
{
  return fVWGeometryLoaded ? fVWGeometryModule->GetR(num_bar, Ycm) : -9999;
}

//____________________________________________________
double E15190Reader::GetVWDistanceRan(int num_bar, double Ycm) const
{
  return fVWGeometryLoaded ? fVWGeometryModule->GetRRan(num_bar, Ycm) : -9999;
}

//____________________________________________________
bool E15190Reader::IsVWChargedParticle(double DE, double TOF) const
{
  return fVWIdentificationLoaded ? fVWIdentificationModule->IsChargedParticle(DE, TOF) : 0;
}

//____________________________________________________
int E15190Reader::GetVWZ(double DE, double TOF) const
{
  return fVWIdentificationLoaded ? fVWIdentificationModule->GetZ(DE, TOF) : -9999;
}

//____________________________________________________
int E15190Reader::GetVWA(double DE, double TOF) const
{
  return fVWIdentificationLoaded ? fVWIdentificationModule->GetA(DE, TOF) : -9999;
}

//____________________________________________________
int E15190Reader::LoadMBGeometry(const char * file_name)
{
  if(!fIsMB) return 0;
  int NLines=fMicroballGeometry->LoadGeometry(file_name);
  if(NLines>0) {
    fMBGeometryLoaded=true;
    printf("Loaded Microball geometry from file %s\n", file_name);
    return NLines;
  } else {
    fMBGeometryLoaded=false;
    printf("Error: Error while loading Microball geometry %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadMBDetectorStatus(const char * file_name)
{
  if(!fIsMB) return 0;
  int NLines=fMicroballStatus->LoadBadDetectors(file_name);
  if(NLines>0) {
    fMBStatusLoaded=true;
    printf("Loaded Microball status from file %s\n", file_name);
    return NLines;
  } else {
    fMBStatusLoaded=false;
    printf("Error: Error while loading Microball status %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadMBFastSlowHitCondition(const char * file_name)
{
  if(!fIsMB) return 0;
  int NLines=fMicroballHitCondition->LoadFastSlowCuts(file_name);
  if(NLines>0) {
    fMBHitConditionLoaded=true;
    printf("Loaded Microball Fast Slow Hit conditions from file %s\n", file_name);
    return NLines;
  } else {
    fMBHitConditionLoaded=false;
    printf("Error: Error while loading Microball Fast Slow Hit conditions %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadMBCentrality(const char * file_name)
{
  if(!fIsMB) return 0;
  int NLines=fMicroballCentrality->LoadImpactParameter(file_name);
  if(NLines>0) {
    fMBCentralityLoaded=true;
    printf("Loaded Microball centrality conditions from file %s\n", file_name);
    return NLines;
  } else {
    fMBCentralityLoaded=false;
    printf("Error: Error while loading Microball centrality conditions %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
double E15190Reader::GetMBTheta(int num_ring, int num_det) const
{
  return fMBGeometryLoaded ? fMicroballGeometry->GetTheta(num_ring, num_det) : -9999;
}

//____________________________________________________
double E15190Reader::GetMBPhi(int num_ring, int num_det) const
{
  return fMBGeometryLoaded ? fMicroballGeometry->GetPhi(num_ring, num_det) : -9999;
}

//____________________________________________________
double E15190Reader::GetMBThetaRandom(int num_ring, int num_det) const
{
  return fMBGeometryLoaded ? fMicroballGeometry->GetThetaRandom(num_ring, num_det) : -9999;
}

//____________________________________________________
double E15190Reader::GetMBPhiRandom(int num_ring, int num_det) const
{
  return fMBGeometryLoaded ? fMicroballGeometry->GetPhiRandom(num_ring, num_det) : -9999;
}

//____________________________________________________
double E15190Reader::GetMBImpactParameter(int multiplicity) const
{
  return fMBCentralityLoaded ? fMicroballCentrality->GetImpactParameter(multiplicity) : -9999;
}

//____________________________________________________
double E15190Reader::GetMBbhat(int multiplicity) const
{
  return fMBCentralityLoaded ? fMicroballCentrality->Getbhat(multiplicity) : -9999;
}

//____________________________________________________
bool E15190Reader::IsMBDetectorBad (int num_ring, int num_det) const
{
  return fMBStatusLoaded ? fMicroballStatus->IsBad(num_ring,num_det) : false;
}

//____________________________________________________
bool E15190Reader::IsMBHit (int num_ring, int num_det, double fast, double tail, double time) const
{
  return fMBHitConditionLoaded ? fMicroballHitCondition->IsHit(num_ring,num_det,fast,tail,time) : false;
}

//____________________________________________________
int E15190Reader::LoadHiRAGeometry(const char * file_name)
{
  if(!fIsHiRA) return 0;
  int NLines=fHiRAGeometryTab->LoadPixels(file_name);
  if(NLines>0) {
    fHiRAGeometryCalibrated=true;
    printf("Loaded HiRA Geometry from file %s\n", file_name);
    return NLines;
  } else {
    fHiRAGeometryCalibrated=false;
    printf("Error: Error while loading HiRA Geometry %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadHiRAStripBad(const char * file_name)
{
  if(!fIsHiRA) return 0;
  int NLines=fHiRAStatus->LoadStipBad(file_name);
  if(NLines>0) {
    fHiRAStripBadLoaded=true;
    printf("Loaded HiRA Strip bad from file %s\n", file_name);
    return NLines;
  } else {
    fHiRAStripBadLoaded=false;
    printf("Error: Error while loading HiRA Strip bad %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadHiRASiCalibration(const char * file_name)
{
  if(!fIsHiRA) return 0;
  int NLines=fSiCalibrationTools->LoadCalibration(file_name);
  if(NLines>0) {
    fHiRASiCalibrated=true;
    printf("Loaded HiRA Silicon calibration from file %s\n", file_name);
    return NLines;
  } else {
    fHiRASiCalibrated=false;
    printf("Error: Error while loading HiRA Silicon calibration %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadHiRACsICalibration(const char * file_name)
{
  if(!fIsHiRA) return 0;
  int NLines=fCsICalibrationModule->LoadEnergyCalibration(file_name);
  if(NLines>0) {
    fHiRACsICalibrated=true;
    printf("Loaded HiRA CsI calibrations from file %s\n", file_name);
    return NLines;
  } else {
    fHiRACsICalibrated=false;
    printf("Error: Error while loading HiRA CsI calibrations from file %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadHiRASiHiLowMatching(const char * file_name)
{
  if(!fIsHiRA) return 0;
  int NLines=fSiCalibrationTools->LoadMatching(file_name);
  if(NLines>0) {
    fHiRASiHiLowMatched=true;
    printf("Loaded HiRA Silicon Hi Gain Low Gain from file %s\n", file_name);
    return NLines;
  } else {
    fHiRASiHiLowMatched=false;
    printf("Error: Error while loading HiRA Silicon Hi Gain Low Gain %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadHiRACsIPulserInfo(const char * file_name)
{
  if(!fIsHiRA) return 0;
  int NLines=fCsICalibrationModule->LoadPulserInfo(file_name);
  if(NLines>0) {
    fHiRACsIPulserCalibrated=true;
    printf("Loaded HiRA CsI pulser settings from file %s\n", file_name);
    return NLines;
  } else {
    fHiRACsIPulserCalibrated=false;
    printf("Error: Error while loading HiRA CsI pulser settings %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
int E15190Reader::LoadHiRAIdentification(const char * file_name)
{
  if(!fIsHiRA) return 0;
  int NLines=fHiRAIdentifiationModule->LoadIdentification(file_name);
  if(NLines>0) {
    fHiRAIdentificationLoaded=true;
    printf("Loaded HiRA PID from file %s\n", file_name);
    return NLines;
  } else {
    fHiRAIdentificationLoaded=false;
    printf("Error: Error while loading HiRA PID %s\n", file_name);
    return -1;
  }
}

//____________________________________________________
bool E15190Reader::IsStripfBad(int telescope, int strip_front) const
{
  return fHiRAStripBadLoaded ? fHiRAStatus->IsStripfBad(telescope, strip_front) : false;
}

//____________________________________________________
bool E15190Reader::IsStripbBad(int telescope, int strip_back) const
{
  return fHiRAStripBadLoaded ? fHiRAStatus->IsStripbBad(telescope, strip_back) : false;
}

//____________________________________________________
double E15190Reader::GetThetaPixel(int telescope, int strip_front, int strip_back) const
{
  return fHiRAGeometryCalibrated ? fHiRAGeometryTab->GetThetaPixel(telescope,strip_front,strip_back) : -9999;
}

//____________________________________________________
double E15190Reader::GetPhiPixel(int telescope, int strip_front, int strip_back) const
{
  return fHiRAGeometryCalibrated ? fHiRAGeometryTab->GetPhiPixel(telescope,strip_front,strip_back) : -9999;
}

//____________________________________________________
double E15190Reader::GetThetaPixelDeg(int telescope, int strip_front, int strip_back) const
{
  return fHiRAGeometryCalibrated ? fHiRAGeometryTab->GetThetaPixelDeg(telescope,strip_front,strip_back) : -9999;
}

//____________________________________________________
double E15190Reader::GetPhiPixelDeg(int telescope, int strip_front, int strip_back) const
{
  return fHiRAGeometryCalibrated ? fHiRAGeometryTab->GetPhiPixelDeg(telescope,strip_front,strip_back) : -9999;
}

//____________________________________________________
double E15190Reader::GetSifIntercept(int telescope, int numstrip) const
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetIntercept(telescope,numstrip,0) : -9999;
}

//____________________________________________________
double E15190Reader::GetSibIntercept(int telescope, int numstrip) const
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetIntercept(telescope,numstrip,1) : -9999;
}

//____________________________________________________
double E15190Reader::GetSifSlope(int telescope, int numstrip) const
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetSlope(telescope,numstrip,0) : -9999;
}

//____________________________________________________
double E15190Reader::GetSibSlope(int telescope, int numstrip) const
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetSlope(telescope,numstrip,1) : -9999;
}

//____________________________________________________
double E15190Reader::GetSifHiLowMatched(int chHi, int chLow, int telescope, int numstrip) const
{
  return fHiRASiHiLowMatched ? fSiCalibrationTools->GetHiLowMatched(gRandom->Uniform(chHi-0.5,chHi+0.5),gRandom->Uniform(chLow-0.5,chLow+0.5),telescope,numstrip,0) : -9999;
}

//____________________________________________________
double E15190Reader::GetSibHiLowMatched(int chHi, int chLow, int telescope, int numstrip) const
{
  return fHiRASiHiLowMatched ? fSiCalibrationTools->GetHiLowMatched(gRandom->Uniform(chHi-0.5,chHi+0.5),gRandom->Uniform(chLow-0.5,chLow+0.5),telescope,numstrip,1): -9999;
}

//____________________________________________________
double E15190Reader::GetSifHiLowMatchedEMeV(int chHi, int chLow, int telescope, int numstrip) const
{
  return fHiRASiHiLowMatched ? fSiCalibrationTools->GetEnergyHiLowMatched(gRandom->Uniform(chHi-0.5,chHi+0.5),gRandom->Uniform(chLow-0.5,chLow+0.5),telescope,numstrip,0): -9999;
}

//____________________________________________________
double E15190Reader::GetSibHiLowMatchedEMeV(int chHi, int chLow, int telescope, int numstrip) const
{
  return fHiRASiHiLowMatched ? fSiCalibrationTools->GetEnergyHiLowMatched(gRandom->Uniform(chHi-0.5,chHi+0.5),gRandom->Uniform(chLow-0.5,chLow+0.5),telescope,numstrip,1): -9999;
}

//____________________________________________________
double E15190Reader::GetCsIEMeV(double ch, int telescope, int numcsi, int Z, int A) const
{
  return Z>0&&A>0&&fHiRACsICalibrated&&fHiRACsIPulserCalibrated ? fCsICalibrationModule->GetEnergyValue(gRandom->Uniform(ch-0.5,ch+0.5), telescope, numcsi, Z, A) : -9999;
}

//____________________________________________________
double E15190Reader::GetCsIVoltage(double ch, int telescope, int numcsi) const
{
  return fHiRACsIPulserCalibrated ? fCsICalibrationModule->GetVoltageValue(gRandom->Uniform(ch-0.5,ch+0.5), telescope, numcsi) : -9999;
}

//____________________________________________________
double E15190Reader::GetSifEMeV(int ch, int telescope, int numstripf) const
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetEnergy(gRandom->Uniform(ch-0.5,ch+0.5),telescope,numstripf,0) : -9999;
}

//____________________________________________________
double E15190Reader::GetSibEMeV(int ch, int telescope, int numstripb) const
{
  return fHiRASiCalibrated ? fSiCalibrationTools->GetEnergy(gRandom->Uniform(ch-0.5,ch+0.5),telescope,numstripb,1) : -9999;
}

//____________________________________________________
void E15190Reader::PrintPercentage(Long64_t jentry, Long64_t nentries) const
{
  double time_elapsed = (double)(clock() - fStartTime)/CLOCKS_PER_SEC;
  std::cout << "  Percentage = " << std::fixed << std::setprecision(1) << std::setw(5) << (100*double(jentry)/nentries) << " %";
  std::cout << "   [";
  int printindex=0;
  for(; printindex<int(100*double(jentry)/nentries); printindex+=5) std::cout << "=";
  for(; printindex<100; printindex+=5) std::cout << " ";
  std::cout << "]   " << "elapsed time " << std::setprecision(1) <<
  (time_elapsed<60 ? time_elapsed : (time_elapsed<3600 ? time_elapsed/60 : time_elapsed/3600)) <<
  (time_elapsed<60 ? " s; " : (time_elapsed<3600 ? " m; " : " h; "));
  if(jentry>0) {
    double time_remaining = (time_elapsed/jentry)*(nentries-jentry);
    std::cout << " estimated remaining time " << std::setprecision(1) <<
    (time_remaining<60 ? time_remaining : (time_remaining<3600 ? time_remaining/60 : time_remaining/3600)) <<
    (time_remaining<60 ? " s      " : (time_remaining<3600 ? " m      " : " h      "));
  }
  std::cout << "\r";
  std::cout.flush();
}

//____________________________________________________
void E15190Reader::PrintPercentageSimple(Long64_t jentry, Long64_t nentries) const
{
  std::cout << "  Percentage = " << std::fixed << std::setprecision(1) << std::setw(5) << (100*double(jentry)/nentries) << " %";
  std::cout << "   [";
  int printindex=0;
  for(; printindex<int(100*double(jentry)/nentries); printindex+=5) std::cout << "=";
  for(; printindex<100; printindex+=5) std::cout << " ";
  std::cout << "]   \r"; std::cout.flush();
}

//____________________________________________________
void E15190Reader::Loop(const char * file_name, Long64_t evt_amount)
{
  // this method loops on the first "evt_amount" data entries
  // and creates a ROOT otput file named "file_name"
  // where the user can write some ROOT output
  TFile * FileOut = new TFile(file_name, "RECREATE");

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

    if (fIsNWA) {
      HTNeutronWallData * NWA = fNWA->Get();
      //Insert NWA code here
    }
    if (fIsNWB) {
      HTNeutronWallData * NWB = fNWB->Get();
      //Insert NWB code here
    }
    if (fIsFA) {
      HTForwardArrayData * ForwardArray = fForwardArray->Get();
      //Insert ForwardArray code here
    }
    if (fIsVW) {
      HTVetoWallData * VetoWall = fVetoWall->Get();
      //Insert VetoWall code here
    }
    if (fIsMB) {
      HTMicroballData * Microball = fMicroball->Get();
      //Insert Microball code here
    }
    if (fIsHiRA) {
      HTHiRAData * HiRATel[NUM_TEL];
      for(int i=0; i<NUM_TEL; i++) {
        HiRATel[i] = fHiRA[i]->Get();
      }
      //Insert HiRA code here
    }
    if (fIsTDC) {
      fTDCAdditionalChannels->FillOutputBranches();
      //Insert TDC spare channels code here. EX: To retrieve TDCTriggers.MASTER_TRG do fTDCAdditionalChannels->GetBranchValue("TDCTriggers.MASTER_TRG");
    }

    jentry++;
  }

  // closing output file
  FileOut->Close();
}

//____________________________________________________
void E15190Reader::LoopOnCalibratedData(const char * file_name, Long64_t evt_amount)
{
  // this method loops on the first "evt_amount" data entries
  // and creates a ROOT otput file named "file_name"
  // where the user can write some ROOT output
  TFile * FileOut = new TFile(file_name, "RECREATE");

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

    if (fIsNWA) {
      NeutronWallCalibratedData * NWA = fNWACal->Get();
      //Insert NWA code here
    }
    if (fIsNWB) {
      NeutronWallCalibratedData * NWB = fNWBCal->Get();
      //Insert NWB code here
    }
    if (fIsFA) {
      ForwardArrayCalibratedData * ForwardArray = fForwardArrayCal->Get();
      //Insert ForwardArray code here
    }
    if (fIsVW) {
      VetoWallCalibratedData * VetoWall = fVetoWallCal->Get();
      //Insert VetoWall code here
    }
    if (fIsMB) {
      MicroballCalibratedData * Microball = fMicroballCal->Get();
      //Insert Microball code here
    }
    if (fIsHiRA) {
      HiRACalibratedData * HiRA = fHiRACal->Get();
      //Insert HiRA code here
    }
    if (fIsTDC) {
      fTDCAdditionalChannels->FillOutputBranches();
      //Insert TDC spare channels code here. EX: To retrieve TDCTriggers.MASTER_TRG do fTDCAdditionalChannels->GetBranchValue("TDCTriggers.MASTER_TRG");
    }

    jentry++;
  }

  // closing output file
  FileOut->Close();
}
