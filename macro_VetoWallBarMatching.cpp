#include <shared.h>

void macro_VetoWallBarMatching()
{
  TFile * FileIn = new TFile("outputNW/UsefulHistograms_VetoWall_Merged_4427_4661_NotCorrected.root");

  ofstream FileOut("calibrations/VW_GainMatchig_4427.dat");
  FileOut<<"*Veto Wall Gain matching parameters\n";
  FileOut<<"*"<<setw(10)<<"bar_num"<<setw(20)<<"matching_slope\n";

  TH2D * VWDETOF[NUM_BARS_VW];
  for(int i=0; i<NUM_BARS_VW; i++) {
    VWDETOF[i]=(TH2D*)FileIn->Get(Form("VWDETOF%02d",i));
  }

  double StartTime=40;
  double EndTime=41;
  double MatchingValue=1000;

  TCanvas * c1 = new TCanvas("c1","",800,600);

  for(int i=0; i<NUM_BARS_VW; i++) {
    VWDETOF[i]->Draw("colz");
    VWDETOF[i]->GetYaxis()->SetRange(VWDETOF[i]->GetYaxis()->FindBin(300),4096);
    gPad->Modified();
    gPad->Update();

    c1->Print(Form("pictures/VW_DE_TOF_%02d.png",i));

    getchar();

    TH1D * proj = VWDETOF[i]->ProjectionY(Form("ProjY_%02d", i), VWDETOF[i]->GetXaxis()->FindBin(StartTime), VWDETOF[i]->GetXaxis()->FindBin(EndTime));
    proj->Draw();
    int maxProj = proj->GetMaximumBin();
    double tentativePos = proj->GetBinCenter(maxProj);
    proj->Fit("gaus","","",tentativePos-50, tentativePos+50);
    proj->SetTitle(Form("VWbar%02d 40ns<TOF<41ns",i));
    gPad->Modified();
    gPad->Update();

    c1->Print(Form("pictures/VW_DE_MATCHING_%02d.png",i));

    getchar();

    TF1 * fitFunc = proj->GetFunction("gaus");

    FileOut<<setw(10)<<i<<setw(20)<<MatchingValue/fitFunc->GetParameter(1)<<endl;

  }

  FileOut.close();
  FileIn->Close();

  return;
}
