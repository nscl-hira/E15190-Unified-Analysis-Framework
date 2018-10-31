#ifndef E15190READER_H
#define E15190READER_H

#include <string.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <TChain.h>
#include <TMath.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include <TCutG.h>
#include <TMultiGraph.h>
#include <TLatex.h>
#include <TCanvas.h>

#include <TDCSpareChannels.h>

#include <HTNeutronWallRootEvent.h>
#include <HTForwardArrayRootEvent.h>
#include <HTVetoWallRootEvent.h>
#include <HTMicroballRootEvent.h>
#include <HTHiRARootEvent.h>
#include <HiRACalibratedRootEvent.h>
#include <HTRunInfo.h>

#include <NWPositionCalibration.h>
#include <NWCosmicRayManager.h>
#include <NWCalibratedRootEvent.h>
#include <NWTimeCalibration.h>
#include <NWGeometry.h>
#include <FATimeCalibration.h>
#include <NWPulseHeightCalibration.h>
#include <NWPulseShapeDiscrimination.h>
#include <VWPulseHeightCalibration.h>
#include <VWIdentification.h>
#include <VWGeometry.h>

#include <MBCalibratedRootEvent.h>
#include <MBDetectorStatus.h>
#include <MBGeometry.h>
#include <MBHitCondition.h>
#include <MBImpactParameter.h>

#include <HiRAGeometry.h>
#include <HiRASiCalibration.h>
#include <HiRACsICalibration.h>
#include <HiRADetectorStatus.h>
#include <HiRAIdentification.h>
#include <HiRAPixelization.h>

#include <shared.h>

/**************************************
E15190Reader class
created by Daniele Dell'Aquila - v1.0 06/22/2018
(dellaqui@nscl.msu.edu)
This class is the core of a unified framework to analyze data of E15190 NSCL Experiment
This framework provides basic tools to loop on raw HiRAEVT data and Calibrated data
by selectively enabling the detector(s) of interest
This class provides methods to get calibrated quantities from raw data structures
A general method to calibrate the whole experiment producing a new tree is provided within the framework (BuildCalibratedTree)
To get calibrated data structure for the current event use the method BuildCalibratedEvent()

*/

class E15190Reader
{
public :
  E15190Reader(TChain *, HTRunInfo *, const char * opt="HiRA-NWA-NWB-VW-FA-uBall-TDC", bool IsDataCalibrated=0);
  ~E15190Reader();

  void InitAllCalibrations();

  int LoadNWPositionCalibration(const char * file_name, const char * WallToCalibrate);
  int LoadNWTimeCalibration(const char * file_name, const char * WallToCalibrate);
  int LoadNWCosmicRayPosition(const char *, const char * WallToCalibrate);
  int LoadNWGeometryFiducialPoints(const char *, const char * WallToCalibrate);
  int LoadNWPulseHeightMatching(const char *, const char * WallToCalibrate);
  int LoadNWPulseHeightCalibration(const char *, const char * WallToCalibrate);
  int LoadNWPSDFlattening(const char *, const char * WallToCalibrate);
  int LoadNWPSDCuts(const char *, const char * WallToCalibrate);
  int LoadFATimeCalibration(const char * file_name);
  int LoadFATimePulseHeightCorrection(const char * file_name);
  int LoadVWGainMatchig(const char * file_name);
  int LoadVWIdentificationCuts(const char * file_name);
  int LoadVWGeometryFiducialPoints(const char * file_name);
  int LoadMBGeometry(const char * file_name);
  int LoadMBDetectorStatus(const char * file_name);
  int LoadMBFastSlowHitCondition(const char * file_name);
  int LoadMBCentrality(const char * file_name);
  int LoadHiRAGeometry(const char *);
  int LoadHiRACsICalibration(const char *);
  int LoadHiRASiCalibration(const char *);
  int LoadHiRAStripBad(const char *);
  int LoadHiRASiHiLowMatching(const char *);
  int LoadHiRACsIPulserInfo(const char *);
  int LoadHiRAIdentification(const char *);

  // NW/VW/FA methods
  double GetNWAXcm(int num_bar, double tleft, double tright) const;
  double GetNWBXcm(int num_bar, double tleft, double tright) const;
  double GetNWACosmicCenter(int num_bar) const;
  double GetNWACosmicStartingPoint(int num_bar) const;
  double GetNWBCosmicCenter(int num_bar) const;
  double GetNWBCosmicStartingPoint(int num_bar) const;
  double GetNWATimeMean(int num_bar, double tleft, double tright) const;
  double GetNWBTimeMean(int num_bar, double tleft, double tright) const;
  double GetNWATheta(int num_bar, double Xcm) const;
  double GetNWAPhi(int num_bar, double Xcm) const;
  double GetNWAThetaRan(int num_bar, double Xcm) const;
  double GetNWAPhiRan(int num_bar, double Xcm) const;
  double GetNWADistance(int num_bar, double Xcm) const;
  double GetNWADistanceRan(int num_bar, double Xcm) const;
  double GetNWBTheta(int num_bar, double Xcm) const;
  double GetNWBPhi(int num_bar, double Xcm) const;
  double GetNWBThetaRan(int num_bar, double Xcm) const;
  double GetNWBPhiRan(int num_bar, double Xcm) const;
  double GetNWBDistance(int num_bar, double Xcm) const;
  double GetNWBDistanceRan(int num_bar, double Xcm) const;
  double GetNWALeftMatched(double ch, int num_bar) const;
  double GetNWARightMatched(double ch, int num_bar) const;
  double GetNWBLeftMatched(double ch, int num_bar) const;
  double GetNWBRightMatched(double ch, int num_bar) const;
  double GetNWAPulseHeightCalibrated(double ch, double Xcm, int num_bar) const;
  double GetNWBPulseHeightCalibrated(double ch, double Xcm, int num_bar) const;
  double GetNWAPSDFlattened(double ch, double ch_fast, int num_bar) const;
  double GetNWBPSDFlattened(double ch, double ch_fast, int num_bar) const;
  bool   IsNWAGamma(double ch, double ch_fast, int numbar) const;
  bool   IsNWBGamma(double ch, double ch_fast, int numbar) const;
  double GetFATimeOffset(int num_det) const;
  double GetFATimePulseHeightCorrection(int num_det, double pulse_height) const;
  double GetVWGeoMeanMatched(double ch, int num_bar) const;
  double GetVWTheta(int num_bar, double Ycm) const;
  double GetVWPhi(int num_bar, double Ycm) const;
  double GetVWThetaRan(int num_bar, double Ycm) const;
  double GetVWPhiRan(int num_bar, double Ycm) const;
  double GetVWDistance(int num_bar, double Ycm) const;
  double GetVWDistanceRan(int num_bar, double Ycm) const;
  bool IsVWChargedParticle(double DE, double TOF) const;
  int GetVWZ(double DE, double TOF) const;
  int GetVWA(double DE, double TOF) const;
  // Microball methods
  double GetMBTheta(int num_ring, int num_det) const;
  double GetMBPhi(int num_ring, int num_det) const;
  double GetMBThetaRandom(int num_ring, int num_det) const;
  double GetMBPhiRandom(int num_ring, int num_det) const;
  double GetMBImpactParameter(int multiplicity) const;
  double GetMBbhat(int multiplicity) const;
  bool IsMBDetectorBad(int num_ring, int num_det) const;
  bool IsMBHit (int num_ring, int num_det, double fast, double tail, double time) const;
  //HiRA methods
  bool IsStripfBad(int telescope, int strip_front) const;
  bool IsStripbBad(int telescope, int strip_back) const;
  double GetThetaPixel(int telescope, int strip_front, int strip_back) const;
  double GetPhiPixel(int telescope, int strip_front, int strip_back) const;
  double GetThetaPixelDeg(int telescope, int strip_front, int strip_back) const;
  double GetPhiPixelDeg(int telescope, int strip_front, int strip_back) const;
  double GetSifIntercept(int telescope, int numstrip) const;
  double GetSibIntercept(int telescope, int numstrip) const;
  double GetSifSlope(int telescope, int numstrip) const;
  double GetSibSlope(int telescope, int numstrip) const;
  double GetSifHiLowMatched(int chHi, int chLow, int telescope, int numstrip) const;
  double GetSibHiLowMatched(int chHi, int chLow, int telescope, int numstrip) const;
  double GetCsIEMeV(double ch, int telescope, int numcsi, int Z=1, int A=1) const;
  double GetCsIVoltage(double ch, int telescope, int numcsi) const;
  double GetSifEMeV(int ch, int telescope, int numstripf) const;
  double GetSibEMeV(int ch, int telescope, int numstripb) const;
  double GetSifHiLowMatchedEMeV(int chHi, int chLow, int telescope, int numstrip) const;
  double GetSibHiLowMatchedEMeV(int chHi, int chLow, int telescope, int numstrip) const;

  // Examples
  void   Loop(const char *, Long64_t evt_amount=0);
  void   LoopOnCalibratedData(const char *, Long64_t evt_amount=0);

  // Output data methods
  void   BuildCalibratedTree(const char *, Long64_t evt_amount=0);
  void   BuildCalibratedEvent();

  //Customized methods
  // input here customized methods
  void   CreateUsefulVetoWallHistograms(const char *, Long64_t evt_amount=0);
  void   CreateUsefulForwardArrayHistograms(const char *, Long64_t evt_amount=0);
  void   CreateUsefulHiRAHistograms(const char *, Long64_t evt_amount=0);

private :
  //The Run Info
  HTRunInfo * fCurrRunInfo;
  //The TTreeReader
  TTreeReader * fE15190Reader;
  //TDC Spare channels
  TDCSpareChannels * fTDCAdditionalChannels;
  //TTreeReaderValue for non-calibrated classes
  TTreeReaderValue<HTNeutronWallData> *fNWA;
  TTreeReaderValue<HTNeutronWallData> *fNWB;
  TTreeReaderValue<HTVetoWallData> *fVetoWall;
  TTreeReaderValue<HTForwardArrayData> *fForwardArray;
  TTreeReaderValue<HTMicroballData> *fMicroball;
  TTreeReaderValue<HTHiRAData> **fHiRA;
  //TTreeReaderValue for calibrated classes
  TTreeReaderValue<NeutronWallCalibratedData> *fNWACal;
  TTreeReaderValue<NeutronWallCalibratedData> *fNWBCal;
  TTreeReaderValue<VetoWallCalibratedData> *fVetoWallCal;
  TTreeReaderValue<ForwardArrayCalibratedData> *fForwardArrayCal;
  TTreeReaderValue<MicroballCalibratedData> *fMicroballCal;
  TTreeReaderValue<HiRACalibratedData> *fHiRACal;

  //Calibrated objects for event building
  NeutronWallCalibratedData fNWACalibratedData;
  NeutronWallCalibratedData fNWBCalibratedData;
  VetoWallCalibratedData fVetoWallCalibratedData;
  ForwardArrayCalibratedData fForwardArrayCalibratedData;
  MicroballCalibratedData fMicroballCalibratedData;
  HiRACalibratedData fHiRACalibratedData;
  HiRACalibratedBuffer fHiRACalibratedDataBuffer;

  TChain      * fChain;

  TNamed * fBeam;
  TNamed * fBeamEnergy;
  TNamed * fTarget;

  double fDegToRad;
  double fRadToDeg;
  double fSpeedOfLight;    //cm/ns
  double fNWBarLength;     //cm
  double fNWBarHigh;       //cm
  double fNWBarThickness;  //cm

  bool fIsTDC;
  bool fIsNWA;
  bool fIsNWB;
  bool fIsFA;
  bool fIsVW;
  bool fIsMB;
  bool fIsHiRA;
  bool fIsDataCalibrated;
  bool fNWAPositionCalibrated;
  bool fNWBPositionCalibrated;
  bool fNWTimeCalibrated;
  bool fNWPulseHeightCalibrated;
  bool fNWACosmicRayPositionLoaded;
  bool fNWBCosmicRayPositionLoaded;
  bool fNWATimeCalibrated;
  bool fNWBTimeCalibrated;
  bool fNWAGeometryCalibrated;
  bool fNWBGeometryCalibrated;
  bool fNWAPulseHeightMatched;
  bool fNWBPulseHeightMatched;
  bool fNWAPulseHeightCalibrated;
  bool fNWBPulseHeightCalibrated;
  bool fNWAPSDFlattened;
  bool fNWBPSDFlattened;
  bool fNWAPSDCutsLoaded;
  bool fNWBPSDCutsLoaded;
  bool fFATimeCalibrated;
  bool fVWGainMatched;
  bool fVWIdentificationLoaded;
  bool fVWGeometryLoaded;
  bool fMBGeometryLoaded;
  bool fMBStatusLoaded;
  bool fMBHitConditionLoaded;
  bool fMBCentralityLoaded;
  bool fHiRACsICalibrated;
  bool fHiRACsIPulserCalibrated;
  bool fHiRASiCalibrated;
  bool fHiRAGeometryCalibrated;
  bool fHiRAStripBadLoaded;
  bool fHiRASiHiLowMatched;
  bool fHiRAIdentificationLoaded;

  NWPositionCalibration * fNWBPositionCalibration;
  NWPositionCalibration * fNWAPositionCalibration;
  NWCosmicRayManager    * fNWACosmicRayInfo;
  NWCosmicRayManager    * fNWBCosmicRayInfo;
  NWTimeCalibration     * fNWATimeCalibration;
  NWTimeCalibration     * fNWBTimeCalibration;
  NWGeometry            * fNWAGeometry;
  NWGeometry            * fNWBGeometry;
  NWPulseHeightCalibration * fNWAPulseHeightCalibrationTools;
  NWPulseHeightCalibration * fNWBPulseHeightCalibrationTools;
  NWPulseShapeDiscrimination * fNWAPulseShapeDiscriminationTools;
  NWPulseShapeDiscrimination * fNWBPulseShapeDiscriminationTools;
  FATimeCalibration        * fFATimeCalibration;
  VWPulseHeightCalibration * fVWPulseHeightCalibrationTools;
  VWIdentification         * fVWIdentificationModule;
  VWGeometry               * fVWGeometryModule;

  MBDetectorStatus      * fMicroballStatus;
  MBGeometry            * fMicroballGeometry;
  MBHitCondition        * fMicroballHitCondition;
  MBImpactParameter     * fMicroballCentrality;

  HiRAGeometry *fHiRAGeometryTab;
  HiRASiCalibration *fSiCalibrationTools;
  HiRACsICalibrationManager *fCsICalibrationModule;
  HiRADetectorStatus *fHiRAStatus;
  HiRAIdentification *fHiRAIdentifiationModule;
  HiRAPixelization * fHiRAPixelizationModule;

  void PrintPercentage(Long64_t, Long64_t) const;
};

#endif
