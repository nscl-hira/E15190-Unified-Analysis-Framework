#ifndef HTTSE15190ROOTEVENT_H
#define HTTSE15190ROOTEVENT_H

#include <TROOT.h>

class HTTSe15190Data
{
public:
  Long64_t fTimestamp;
  Long64_t fTimestampKoreans;

  HTTSe15190Data();
  virtual ~HTTSe15190Data();

  ClassDef(HTTSe15190Data,1);
};

class HTTSe15190RootEvent
{
 private:

 public:
 HTTSe15190Data fSisTimestamp;

 HTTSe15190RootEvent();
 virtual ~HTTSe15190RootEvent();

 ClassDef(HTTSe15190RootEvent,1);
};

#endif
