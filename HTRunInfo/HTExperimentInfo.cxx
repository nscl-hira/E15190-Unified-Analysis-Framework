#include <HTExperimentInfo.h>

//________________________________________________
HTExperimentInfo::HTExperimentInfo() :
fDataMerged(false),
fFirstRun(0),
fLastRun(0)
{}

//________________________________________________
HTExperimentInfo::~HTExperimentInfo()
{
  if(fDAQConfigurationFileName) {
    delete [] fDAQConfigurationFileName;
  }
  if(fPedestalFileName) {
    delete [] fPedestalFileName;
  }
  if(fMappingFileName) {
    delete [] fMappingFileName;
  }
  if(fRunEvtFilePath) {
    delete [] fRunEvtFilePath;
  }
  if(fRunTitle) {
    delete [] fRunTitle;
  }
}

//________________________________________________
void HTExperimentInfo::Clear()
{
  fExperimentName.clear();
  fExperimentTitle.clear();
  fEvtFilePath.clear();
  fUnpackedRootFilePath.clear();
  fMappedRootFilePath.clear();
}

//________________________________________________
int HTExperimentInfo::InitClass(const char *file_name)
{
  Clear();
  int NLinesRead=0;

  //Set general setup configuration
  NLinesRead += LoadSetupConfiguration(file_name);

  fDAQConfigurationFileName=(std::string*)new std::string[fLastRun-fFirstRun+1];
  fPedestalFileName=(std::string*)new std::string[fLastRun-fFirstRun+1];
  fMappingFileName=(std::string*)new std::string[fLastRun-fFirstRun+1];
  fRunEvtFilePath=(std::string*)new std::string[fLastRun-fFirstRun+1];
  fRunTitle=(std::string*)new std::string[fLastRun-fFirstRun+1];

  // Retrieving all previously stored run titles from database file
  RetrieveRunTitlesFromDatabaseFile();

  //Set run-by-run setup configuration
  for(int run_num=fFirstRun; run_num<=fLastRun; run_num++)
  {
    NLinesRead += LoadRunConfiguration(file_name,run_num);
    // Only if the run title was not previously found retrieve it from evt file and store into the database file
    if(fRunTitle[run_num-fFirstRun].empty()) {
      const char * TempRunTitle=RetrieveRunTitleFromEvtFile(Form("%srun%d/run-%04d-00.evt",fRunEvtFilePath[run_num-fFirstRun].c_str(),run_num,run_num));
      if(TempRunTitle!=0) {
        fRunTitle[run_num-fFirstRun].assign(TempRunTitle);
        StoreRunTitleInDatabaseFile(TempRunTitle, run_num);
      }
    }
  }

  return NLinesRead;
}

//________________________________________________
int HTExperimentInfo::LoadSetupConfiguration(const char *file_name)
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
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("set ")!=std::string::npos) {
      ParseSetConfigLine(LineReadCommentLess.c_str());
    }

    if(LineReadCommentLess.find("FIRST_RUN")!=std::string::npos) {
      fFirstRun=atoi(LineReadCommentLess.substr(LineReadCommentLess.find("=")+1).c_str());
    }
    if(LineReadCommentLess.find("LAST_RUN")!=std::string::npos) {
      fLastRun=atoi(LineReadCommentLess.substr(LineReadCommentLess.find("=")+1).c_str());
    }

    NRead++;
  }
  FileIn.close();

  return NRead;
}

//________________________________________________
int HTExperimentInfo::LoadRunConfiguration(const char *file_name, int run_num)
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
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("set ")!=std::string::npos) {
      ParseSetConfigLineRunInfo(LineReadCommentLess.c_str(), run_num);
    }

    NRead++;
  }
  FileIn.close();

  return NRead;
}

//________________________________________________
HTRunInfo * HTExperimentInfo::GetRunInfo(int run_num) const
{
  HTRunInfo * newRunInfo = new HTRunInfo(run_num,fRunTitle[run_num-fFirstRun].c_str());

  if(newRunInfo->LoadDAQSettings(fDAQConfigurationFileName[run_num-fFirstRun].c_str())<=0) {
    delete newRunInfo;
    return 0;
  }
  if(newRunInfo->SetPedestalsFile(fPedestalFileName[run_num-fFirstRun].c_str())!=0) {
    delete newRunInfo;
    return 0;
  }
  if(newRunInfo->SetMappingFile(fMappingFileName[run_num-fFirstRun].c_str())!=0) {
    delete newRunInfo;
    return 0;
  }
  if(!fRunEvtFilePath[run_num-fFirstRun].empty()) {
    newRunInfo->SetEvtFilePath(fRunEvtFilePath[run_num-fFirstRun].c_str());
  } else {
    newRunInfo->SetEvtFilePath(fEvtFilePath.c_str());
  }

  return newRunInfo;
}

//________________________________________________
void HTExperimentInfo::ParseSetConfigLine(const char *line_to_parse)
{
  std::string LineToParse(line_to_parse);

  LineToParse.assign(LineToParse.substr(LineToParse.find("set ")+4)); //remove set command

  std::istringstream LineStream(LineToParse);

  std::string ValueToSet;
  LineStream>>ValueToSet;
  std::string NewValue(LineToParse.substr(LineToParse.find("\"")+1,LineToParse.find_last_of("\"")-(LineToParse.find("\"")+1)));

  if(ValueToSet.compare("EXPERIMENT_NAME")==0) {
    fExperimentName.assign(NewValue);
  } else if (ValueToSet.compare("EXPERIMENT_TITLE")==0) {
    fExperimentTitle.assign(NewValue);
  } else if (ValueToSet.compare("MERGED_DATA")==0) {
    NewValue.compare("true")==0 ? fDataMerged=true : fDataMerged=false;
  } else if (ValueToSet.compare("EVENT_FILE_PATH")==0) {
    if(LineToParse.find("--run")==std::string::npos) { //EvtFileName might be different run-by-run, if --run is specified don't set it now but in ParseSetConfigLineRunInfo
      fEvtFilePath.assign(NewValue);
    }
  } else if (ValueToSet.compare("HiRAEVTUNPACKER_ROOT_FILE_PATH")==0) {
    fUnpackedRootFilePath.assign(NewValue);
  } else if (ValueToSet.compare("HiRAEVTMAPPER_ROOT_FILE_PATH")==0) {
    fMappedRootFilePath.assign(NewValue);
  }

  return;
}

//________________________________________________
void HTExperimentInfo::ParseSetConfigLineRunInfo(const char *line_to_parse, int run_num)
{
  std::string LineToParse(line_to_parse);

  LineToParse.assign(LineToParse.substr(LineToParse.find("set ")+4)); //remove set command

  std::istringstream LineStream(LineToParse);

  std::string ValueToSet;
  LineStream>>ValueToSet;
  std::string NewValue;

  //NOTE: for a future improvement take into account more possible options not only --run and --exclude
  if(LineToParse.find("--run")!=std::string::npos) { //found --run option
    LineToParse.assign(LineToParse.substr(LineToParse.find("--run")+5));
    int StartRunNum=atoi(LineToParse.substr(LineToParse.find("=")+1,LineToParse.find("-")).c_str());
    int StopRunNum=atoi(LineToParse.substr(LineToParse.find("-")+1,LineToParse.find("\"")-LineToParse.find("-")).c_str());

    if(LineToParse.find("--exclude")!=std::string::npos) { //found --exclude option
      LineToParse.assign(LineToParse.substr(LineToParse.find("--exclude")+10));
      std::istringstream LineExcludeStream(LineToParse.substr(0,LineToParse.find("--")!=std::string::npos ? LineToParse.find("--") : LineToParse.find("\"")));
      std::string RunToExclude;

      while(std::getline(LineExcludeStream, RunToExclude, ',')) {
        if(run_num==std::stoi(RunToExclude)) return; //this run is excluded
      }
    }

    if(run_num>=StartRunNum && run_num<=StopRunNum) {
      NewValue.assign(LineToParse.substr(LineToParse.find("\"")+1,LineToParse.find_last_of("\"")-(LineToParse.find("\"")+1)));
    } else return;
  } else return;

  // if I'm here so run_num has been found in the configuration line
  if(ValueToSet.compare("DAQ_CONFIG")==0) {
    fDAQConfigurationFileName[run_num-fFirstRun].assign(NewValue);
  } else if (ValueToSet.compare("PEDESTAL_VALUES")==0) {
    fPedestalFileName[run_num-fFirstRun].assign(NewValue);
  } else if (ValueToSet.compare("CHANNEL_MAPPING")==0) {
    fMappingFileName[run_num-fFirstRun].assign(NewValue);
  } else if (ValueToSet.compare("EVENT_FILE_PATH")==0) {
    fRunEvtFilePath[run_num-fFirstRun].assign(NewValue);
  }

  return;

}

//________________________________________________
bool HTExperimentInfo::IsDataMerged() const
{
  return fDataMerged;
}

//________________________________________________
const char * HTExperimentInfo::GetName() const
{
  return fExperimentName.c_str();
}

//________________________________________________
const char * HTExperimentInfo::GetTitle() const
{
  return fExperimentTitle.c_str();
}

//________________________________________________
const char * HTExperimentInfo::GetEvtFilePath() const
{
  return fEvtFilePath.c_str();
}

//________________________________________________
const char * HTExperimentInfo::GetRootFilePath() const
{
  return fUnpackedRootFilePath.c_str();
}

//________________________________________________
const char * HTExperimentInfo::GetMappedRootFilePath() const
{
  return fMappedRootFilePath.c_str();
}

//________________________________________________
int HTExperimentInfo::RetrieveRunTitlesFromDatabaseFile()
{
  std::ifstream FileIn(Form("config/%s.run",fExperimentName.c_str()));
  if(!FileIn.is_open()) {
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    if(LineRead.empty()) continue;
    if(LineRead.find('*')==0) continue;
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    int run_num;

    LineStream>>run_num;
    if(run_num>=fFirstRun && run_num<=fLastRun) {
      NRead++;
      fRunTitle[run_num-fFirstRun].assign(LineRead.substr(LineRead.find_first_not_of(' ',LineRead.find_first_of(' '))));
    }
  }

  FileIn.close();
  return NRead;
}

//________________________________________________
void HTExperimentInfo::StoreRunTitleInDatabaseFile(const char * run_title, int run_num)
{
  std::ofstream FileOut(Form("config/%s.run",fExperimentName.c_str()),std::ios::app);

  FileOut << run_num << " " << run_title << std::endl;

  FileOut.close();
}

//________________________________________________
const char * HTExperimentInfo::RetrieveRunTitleFromEvtFile(const char * evtfile_name) const
{
  std::ifstream evtfile;
  evtfile.open(evtfile_name,std::ios::binary);

  if(!evtfile.is_open()) {
    return 0;
  }

  unsigned short *point;
  std::string RunTitle;

  for(int j=0; !evtfile.eof(); j++)  // loop over items in a evtfile
  {
    // Reading Header ================================
    int const hBufferWords = 4;
    int const hBufferBytes = hBufferWords*2;
    unsigned short hBuffer[hBufferWords];
    evtfile.read((char*)hBuffer,hBufferBytes);

    point = hBuffer;
    int nbytes = *point++;
    point++;
    int type = *point++;
    // ===============================================

    // Reading the rest of the buffer until I find start of run ================
    const int dBufferBytes = nbytes - 8; //Skipping the inclusive size and data type
    const int dBufferWords = dBufferBytes/2; //Calculating 16 bit words from bytes

    unsigned short dBuffer[dBufferWords];
    evtfile.read((char*)dBuffer,dBufferBytes);
    point = dBuffer;
    // =====================================================================

    // Checking if the body header exists ============
    //This is to read the Body Header
    // Body header has
    int BHsize = *point++;
    point++;

    if(BHsize==20) {
      point +=4; //Skipping the timestamp for now;
      point++;
      point++;
      point++;
      point++;
    }
    else {
      //Buffers with no body header
    }
    // ===============================================

    if (type == 1) { // start of run
      RunTitle.assign((char*)(point+8));
      break;
    }
  }

  evtfile.close();

  return RunTitle.c_str();
}
