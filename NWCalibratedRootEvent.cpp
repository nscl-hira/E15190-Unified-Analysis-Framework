#include <NWCalibratedRootEvent.h>

//________________________________________________
NeutronWallCalibratedData::NeutronWallCalibratedData(int num_bars) :
fmulti(0)
{
  fnumbar      =new Int_t   [num_bars];
  fLeft        =new Short_t [num_bars];
  fRight       =new Short_t [num_bars];
  ffastLeft    =new Short_t [num_bars];
  ffastRight   =new Short_t [num_bars];
  fTimeLeft    =new Double_t[num_bars];
  fTimeRight   =new Double_t[num_bars];
  fGeoMean     =new Double_t[num_bars];
  fGeoMeanSaturationCorrected     =new Double_t[num_bars];
  ffastGeoMean =new Double_t[num_bars];

  fTimeMean    =new Double_t[num_bars];
  fCalGeoMean  =new Double_t[num_bars];
  fMatchedLeft =new Double_t[num_bars];
  fMatchedRight=new Double_t[num_bars];
  fMatchedGeoMean=new Double_t[num_bars];
  fFlattenedGeoMean=new Double_t[num_bars];
  fLeftSaturationCorrected=new Double_t[num_bars];
  fRightSaturationCorrected=new Double_t[num_bars];
  ffastLeftSaturationCorrected=new Double_t[num_bars];
  ffastRightSaturationCorrected=new Double_t[num_bars];
  fPSDLeft     =new Double_t[num_bars];
  fPSDRight    =new Double_t[num_bars];
  fTheta       =new Double_t[num_bars];
  fPhi         =new Double_t[num_bars];
  fThetaRan    =new Double_t[num_bars];
  fPhiRan      =new Double_t[num_bars];

  fDistcm      =new Double_t[num_bars];
  fDistRancm   =new Double_t[num_bars];
  fXcm         =new Double_t[num_bars];
  fIsGamma     =new Bool_t[num_bars];
}

//________________________________________________
NeutronWallCalibratedData::NeutronWallCalibratedData() :
fmulti(0)
{
  fnumbar      =new Int_t   [25];
  fLeft        =new Short_t [25];
  fRight       =new Short_t [25];
  ffastLeft    =new Short_t [25];
  ffastRight   =new Short_t [25];
  fTimeLeft    =new Double_t[25];
  fTimeRight   =new Double_t[25];
  fGeoMean     =new Double_t[25];
  fGeoMeanSaturationCorrected     =new Double_t[25];
  ffastGeoMean =new Double_t[25];

  fTimeMean    =new Double_t[25];
  fCalGeoMean  =new Double_t[25];
  fMatchedLeft =new Double_t[25];
  fMatchedRight=new Double_t[25];
  fMatchedGeoMean=new Double_t[25];
  fFlattenedGeoMean=new Double_t[25];
  fLeftSaturationCorrected=new Double_t[25];
  fRightSaturationCorrected=new Double_t[25];
  ffastLeftSaturationCorrected=new Double_t[25];
  ffastRightSaturationCorrected=new Double_t[25];
  fPSDLeft     =new Double_t[25];
  fPSDRight     =new Double_t[25];
  fTheta       =new Double_t[25];
  fPhi         =new Double_t[25];
  fThetaRan    =new Double_t[25];
  fPhiRan      =new Double_t[25];

  fDistcm      =new Double_t[25];
  fDistRancm   =new Double_t[25];
  fXcm         =new Double_t[25];
  fIsGamma     =new Bool_t[25];
}

//________________________________________________
NeutronWallCalibratedData::~NeutronWallCalibratedData()
{
  delete [] fnumbar   ;
  delete [] fLeft     ;
  delete [] fRight    ;
  delete [] ffastLeft ;
  delete [] ffastRight;
  delete [] fTimeLeft ;
  delete [] fTimeRight;
  delete [] fGeoMean  ;
  delete [] ffastGeoMean;

  delete [] fGeoMeanSaturationCorrected;
  delete [] fTimeMean    ;
  delete [] fCalGeoMean  ;
  delete [] fMatchedLeft ;
  delete [] fMatchedRight;
  delete [] fMatchedGeoMean;
  delete [] fFlattenedGeoMean;
  delete [] fLeftSaturationCorrected;
  delete [] fRightSaturationCorrected;
  delete [] ffastLeftSaturationCorrected;
  delete [] ffastRightSaturationCorrected;
  delete [] fPSDLeft;
  delete [] fPSDRight;
  delete [] fTheta       ;
  delete [] fPhi         ;
  delete [] fThetaRan    ;
  delete [] fPhiRan      ;

  delete [] fDistcm      ;
  delete [] fDistRancm   ;
  delete [] fXcm         ;
  delete [] fIsGamma     ;
}

//________________________________________________
VetoWallCalibratedData::VetoWallCalibratedData(int num_bars) :
fmulti(0)
{
  fnumbar     =new Int_t   [num_bars];
  fTop        =new Short_t [num_bars];
  fBottom     =new Short_t [num_bars];
  fTimeTop    =new Double_t[num_bars];
  fTimeBottom =new Double_t[num_bars];
  fGeoMean    =new Double_t[num_bars];

  fGeoMeanMatched = new Double_t[num_bars];
  fYcm = new Double_t[num_bars];
  fTheta = new Double_t[num_bars];
  fPhi = new Double_t[num_bars];
  fThetaRan = new Double_t[num_bars];
  fPhiRan = new Double_t[num_bars];
  fDistcm = new Double_t[num_bars];
  fDistRancm = new Double_t[num_bars];
}

//________________________________________________
VetoWallCalibratedData::VetoWallCalibratedData() :
fmulti(0)
{
  fnumbar     =new Int_t   [25];
  fTop        =new Short_t [25];
  fBottom     =new Short_t [25];
  fTimeTop    =new Double_t[25];
  fTimeBottom =new Double_t[25];
  fGeoMean    =new Double_t[25];

  fGeoMeanMatched = new Double_t[25];
  fYcm = new Double_t[25];
  fTheta = new Double_t[25];
  fPhi = new Double_t[25];
  fThetaRan = new Double_t[25];
  fPhiRan = new Double_t[25];
  fDistcm = new Double_t[25];
  fDistRancm = new Double_t[25];
}

//________________________________________________
VetoWallCalibratedData::~VetoWallCalibratedData()
{
  delete [] fnumbar  ;
  delete [] fTop     ;
  delete [] fBottom  ;
  delete [] fTimeTop ;
  delete [] fTimeBottom;
  delete [] fGeoMean ;

  delete [] fGeoMeanMatched;
  delete [] fYcm;
  delete [] fTheta;
  delete [] fPhi;
  delete [] fThetaRan;
  delete [] fPhiRan;
  delete [] fDistcm;
  delete [] fDistRancm;
}

//________________________________________________
ForwardArrayCalibratedData::ForwardArrayCalibratedData(int num_dets) :
fmulti(0)
{
  fnumdet      =new Int_t   [num_dets];
  fE           =new Short_t [num_dets];
  fTime        =new Double_t[num_dets];
}

//________________________________________________
ForwardArrayCalibratedData::ForwardArrayCalibratedData() :
fmulti(0)
{
  fnumdet      =new Int_t   [18];
  fE           =new Short_t [18];
  fTime        =new Double_t[18];
}

//________________________________________________
ForwardArrayCalibratedData::~ForwardArrayCalibratedData()
{
  delete [] fnumdet;
  delete [] fE;
  delete [] fTime;
}
