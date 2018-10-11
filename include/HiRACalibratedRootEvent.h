#ifndef HIRACALIBRATEDROOTEVENT_H
#define HIRACALIBRATEDROOTEVENT_H

#include <TROOT.h>

#include "shared.h"

class HiRACalibratedData
{
public:
  Int_t    fmulti;
  Int_t    *fnumtel;       //[fmulti]
  Int_t    *fnumstripf;    //[fmulti]
  UShort_t *fEnergySifHi;  //[fmulti]
  UShort_t *fEnergySifLo;  //[fmulti]
  UShort_t *fTimeSif;      //[fmulti]
  Int_t    *fnumstripb;    //[fmulti]
  UShort_t *fEnergySibHi;  //[fmulti]
  UShort_t *fEnergySibLo;  //[fmulti]
  UShort_t *fTimeSib;      //[fmulti]
  Int_t    *fnumcsi;       //[fmulti]
  UShort_t *fEnergycsi;    //[fmulti]
  Double_t *fTimecsi;      //[fmulti]

  Double_t *fEnergySifMatched; //[fmulti]
  Double_t *fEnergySibMatched; //[fmulti]
  Double_t *fEnergySifCal;     //[fmulti]
  Double_t *fEnergySibCal;     //[fmulti]
  Double_t *fEnergycsiCal;     //[fmulti]
  Double_t *fEnergycsiCalProtons;     //[fmulti]

  Double_t *fKinEnergy;        //[fmulti]
  Double_t *fBeta;             //[fmulti]
  Double_t *fMomentum;         //[fmulti]
  Double_t *fTheta;            //[fmulti]
  Double_t *fPhi;              //[fmulti]
  Double_t *fZ;                //[fmulti]
  Double_t *fA;                //[fmulti]
  Int_t    *fZId;              //[fmulti]
  Int_t    *fAId;              //[fmulti]
  Int_t    *fIdCode;           //[fmulti]

  HiRACalibratedData(int);
  HiRACalibratedData();
  virtual ~HiRACalibratedData();

  ClassDef(HiRACalibratedData,1);
};

class HiRACalibratedBuffer
{
public:
  Int_t    fmultistripf;
  Int_t    *fnumstripf;    //[fmultistripf]
  UShort_t *fEnergySifHi;  //[fmultistripf]
  UShort_t *fEnergySifLo;  //[fmultistripf]
  UShort_t *fTimeSif;      //[fmultistripf]
  Double_t *fEnergySifMatched; //[fmultistripf]
  Double_t *fEnergySifCal;     //[fmultistripf]

  Int_t    fmultistripb;
  Int_t    *fnumstripb;    //[fmultistripf]
  UShort_t *fEnergySibHi;  //[fmultistripf]
  UShort_t *fEnergySibLo;  //[fmultistripf]
  UShort_t *fTimeSib;      //[fmultistripf]
  Double_t *fEnergySibMatched; //[fmultistripf]
  Double_t *fEnergySibCal;     //[fmultistripf]

  Int_t    fmulticsi;
  Int_t    *fnumcsi;       //[fmultistripf]
  UShort_t *fEnergycsi;    //[fmultistripf]
  Double_t *fTimecsi;      //[fmultistripf]
  Double_t *fEnergycsiCal;     //[fmultistripf]

  HiRACalibratedBuffer();
  virtual ~HiRACalibratedBuffer();

  ClassDef(HiRACalibratedBuffer,1);
};

#endif
