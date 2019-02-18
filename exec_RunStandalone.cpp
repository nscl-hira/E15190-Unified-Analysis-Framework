#include <E15190Reader.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TChain.h>
#include <TH2.h>
#include <iostream>

#include <HTExperimentInfo.h>
#include <HTRunInfo.h>

#include <HiRACalibratedRootEvent.h>
#include <MBCalibratedRootEvent.h>
#include <NWCalibratedRootEvent.h>

#include <E15190ReaderLogo.h>

int main (int argc, char ** argv)
{
  PrintE15190ReaderLogo(); //logo printing

  if(argc<=1) { //no input provided
    printf("Error: Please provide at least one input!\n");
    return -1;
  }

  // Building Epxeriment Info class
  HTExperimentInfo * ExpInfo = new HTExperimentInfo();
  ExpInfo->InitClass("config/HiRAEVT.conf");

  // Initializing input file
  std::string data_path(ExpInfo->GetMappedRootFilePath());
  TChain *dataChain = (TChain*) new TChain(Form("E%s",ExpInfo->GetName()));
  std::string first_run_name(argv[1]);
  int first_run = atoi(first_run_name.c_str());
  int last_run=first_run;
  if(argc>2) {
    std::string last_run_name(argv[2]);
    last_run = atoi(last_run_name.c_str());
  }

  // Event-by-Event loop ////////////////
  for(int cur_run=first_run; cur_run<=last_run; cur_run++)
  {
    dataChain->Reset();
    int n_files = dataChain->Add(Form("%srun-%04d*.root",data_path.c_str(),cur_run));
    printf("%d Root files added to chain for run %d\n", n_files, cur_run);
    if(n_files<=0) continue;

    //Building HTRunInfo class ///////////
    HTRunInfo * CurrRunInfo = ExpInfo->GetRunInfo(cur_run);
    printf("Run Title: %s\nBeam: %s@%sMeV/u\nTarget: %s\n", CurrRunInfo->GetTitle(),CurrRunInfo->GetBeam(),CurrRunInfo->GetBeamEnergy(),CurrRunInfo->GetTarget());

    //Building framework /////////////////
    E15190Reader E15190Analyzer(dataChain, CurrRunInfo, ExpInfo->GetDetectorToAnalyze());

    //Exclude run if it is Junk //////////
    if(CurrRunInfo->IsJunk()) {
      printf("Run %d is junk -> the run will be skipped.\n", cur_run);
      continue;
    }

    //Loading calibration files //////////
    //These are loaded for the current run
    E15190Analyzer.InitAllCalibrations();

    // Here is the standalone code //////////
    while (E15190Analyzer.Next()) {
      HiRACalibratedData * HiRA = (HiRACalibratedData *)E15190Analyzer.GetData("HiRA"); //For example, I can get the calibrated HiRA
      
      //...
    }
    //////////////////////////////////////
    
  }
  // End of the main loop //////////////////
  printf("\nData Analyzed, Bye!\n");

  return 0;
}
