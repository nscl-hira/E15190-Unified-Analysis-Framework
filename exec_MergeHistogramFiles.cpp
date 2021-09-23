#include <TFile.h>
#include <TH1.h>
#include <stdio.h>
#include <stdlib.h>
#include <TKey.h>
#include <TROOT.h>
#include <TClass.h>

int main (int argc, char ** argv)
{
  if(argc <3) {
    printf("Please specify 2 or more files to merge\n");
    return -1;
  }

  TFile * FileOut = new TFile("output/E15190_Merged.root","RECREATE");

  TFile * FileIn[argc-1];
  TIter * NextObj[argc-1];
  TKey  * key[argc-1];
  for (int i=0; i<argc-1; i++)
  {
    printf("Opened %s file\n", argv[i+1]);
    FileIn[i] = new TFile(argv[i+1]);
    NextObj[i]= new TIter(FileIn[i]->GetListOfKeys());
  }

  while ((key[0] = (TKey*)(*NextObj[0])()))
  {
    TClass *cl = gROOT->GetClass(key[0]->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;
    TH1 *h = (TH1*)key[0]->ReadObj();

    //printf("found %s histogram\n", h->GetName());

    for(int i=1; i<argc-1; i++)
    {
      while(key[i] = (TKey*)(*NextObj[i])()) {
        TClass *cl2 = gROOT->GetClass(key[i]->GetClassName());
        if (!cl2->InheritsFrom("TH1")) continue;
        TH1 *h2 = (TH1*)key[i]->ReadObj();
	if(h2==0) continue;

        if(strcmp(h->GetName(),h2->GetName())==0) {
          printf("Adding %s to %s from file %s\n",h->GetName(), h2->GetName(), argv[i+1]);
          h->Add(h2);
	  delete h2;
          break;
        }
      }
    }

    FileOut->WriteTObject(h, h->GetName());
  }

  FileOut->Close();

  return 0;
}
