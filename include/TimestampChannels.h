#ifndef TIMESTAMPCHANNELS_H
#define TIMESTAMPCHANNELS_H

/*****************
 * TimestampChannels class
 * created by Daniele Dell'Aquila (Jan 17th 2019)
 * This class handles the Timestamp of the type SisTimestampe15190 as built for the E15190 experiment,
 * it is derived from TDCSpareChannels
 * This consitutes one of the major limitations of the code since it can handle only this particular
 * type of timestamp.
 * Future implementation of this code might include several types of timestamps that can be
 * chosen and even combined together according to the information contained in the mapping file.
 *
 * For future additional information please contact Daniele Dell'Aquila (dellaquila.daniele@gmail.com)
 *
 **/

#include <fstream>
#include <sstream>
#include <TTree.h>
#include <TChain.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <vector>
#include <string>
#include <map>

#include <HTTSe15190RootEvent.h>

class TimestampChannels
{
public :
  TimestampChannels();
  ~TimestampChannels();

  int InitFromMapping(TTreeReader *, const char *);      // Inits all branches for reading as defined in the mapping file of the corresponding run for detector SisTimestampe15190
  int SetNewBranch(TTreeReader *, const char * name);    // Sets a new branch for reading
  int SetOutputTree(TTree *);                            // Sets all the known branches in the output tree
  void FillOutputBranches();                             // Fills the fData array for the current event

private :
  int fNumChannels;
  std::string fDetName;                                  //Name of this TimestampChannels as in the .map file
  std::map <std::string, HTTSe15190Data *> fData;        // This is set only when FillOutputBranches() is called.
  std::map <std::string, TTreeReaderValue<HTTSe15190Data>*> fReaderData;

  int ParseMapLine(TTreeReader *, const char *);
};

#endif
