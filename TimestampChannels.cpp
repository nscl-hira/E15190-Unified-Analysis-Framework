#include <TimestampChannels.h>

//____________________________________________________
TimestampChannels::TimestampChannels() :
fNumChannels(0)
{}

//____________________________________________________
TimestampChannels::~TimestampChannels()
{
  for(std::map<std::string, HTTSe15190Data *>::iterator TheChannel = fData.begin(); TheChannel != fData.end(); TheChannel++) {
    delete (*TheChannel).second;
  }
  for(std::map<std::string, TTreeReaderValue<HTTSe15190Data>*>::iterator TheChannel = fReaderData.begin(); TheChannel != fReaderData.end(); TheChannel++) {
    delete (*TheChannel).second;
  }
}

//____________________________________________________
int TimestampChannels::InitFromMapping(TTreeReader * theReader, const char * file_name)
{
  std::ifstream FileIn(file_name);

  if(!FileIn.is_open()) {
    return -1;
  }

  int NChannelsMapped=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    //NOTE: here it is possible to define only a SisTimestampe15190
    //future improvements might include other kind of timestamps.
    if(LineReadCommentLess.find("define ")!=std::string::npos) {
      if(LineReadCommentLess.find("SisTimestampe15190")!=std::string::npos) {
        fDetName.assign(LineReadCommentLess.substr(LineReadCommentLess.find("\"")+1,LineReadCommentLess.find_last_of("\"")-(LineReadCommentLess.find("\"")+1)));
        SetNewBranch(theReader, Form("%s.", fDetName.c_str()));
        NChannelsMapped++;
      }
    }
  }
  FileIn.close();

  return NChannelsMapped;
}

//____________________________________________________
int TimestampChannels::SetNewBranch(TTreeReader * theReader, const char * name)
{
  if(fReaderData.find(name)==fReaderData.end()) {
    //this entry was not added before
    TTreeReaderValue<HTTSe15190Data> * newChannel = new TTreeReaderValue<HTTSe15190Data>(*theReader, name);
    fReaderData[name]=newChannel;
    HTTSe15190Data * newChannelData = new HTTSe15190Data;
    fData[name]=newChannelData;
    fNumChannels++;
    return 1;
  }
  return 0;
}

//____________________________________________________
int TimestampChannels::SetOutputTree(TTree * theTree)
{
  int NumBranches=0;
  for(std::map<std::string, HTTSe15190Data *>::iterator TheChannel = fData.begin(); TheChannel != fData.end(); TheChannel++) {
    //NOTE: also here we have HTTSe15190Data explicitly. For future improvements make it genereal.
    theTree->Branch((*TheChannel).first.c_str(), "HTTSe15190Data", (*TheChannel).second, 32768,1);
    NumBranches++;
  }
  return NumBranches;
}

//____________________________________________________
void TimestampChannels::FillOutputBranches()
{
  for(std::map<std::string, HTTSe15190Data *>::iterator TheChannel = fData.begin(); TheChannel != fData.end(); TheChannel++) {
    *(*TheChannel).second=*(fReaderData[(*TheChannel).first]->Get());
  }
}
