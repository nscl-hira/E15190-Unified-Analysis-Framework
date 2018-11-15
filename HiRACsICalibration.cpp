#include <HiRACsICalibration.h>

//______________________________________________
HiRACsICalibrationManager::HiRACsICalibrationManager() :
fPulserLoaded(false)
{
  for(int i=0; i<NUM_TEL; i++) {
    for(int j=0; j<NUM_CSI_TEL; j++) {
      fCsIChToVInterpolated [i*NUM_CSI_TEL+j]=0;
      fCsIChToVExtrapolated [i*NUM_CSI_TEL+j]=0;
    }
  }
  for(int i=0; i<Z_MAX; i++) {
    for(int j=0; j<A_MAX; j++) {
      for(int k=0; k<NUM_TEL*NUM_CSI_TEL; k++) {
        fCalib[i][j][k]=0;
      }
    }
  }
}

//______________________________________________
HiRACsICalibrationManager::~HiRACsICalibrationManager()
{
  for(int i=0; i<NUM_TEL; i++) {
    for(int j=0; j<NUM_CSI_TEL; j++) {
      if(fCsIChToVInterpolated [i*NUM_CSI_TEL+j]) {
        delete fCsIChToVInterpolated [i*NUM_CSI_TEL+j];
        delete fCsIChToVExtrapolated [i*NUM_CSI_TEL+j];
      }
    }
  }
  for(int i=0; i<Z_MAX; i++) {
    for(int j=0; j<A_MAX; j++) {
      for(int k=0; k<NUM_TEL*NUM_CSI_TEL; k++) {
        if (fCalib[i][j][k]) delete fCalib[i][j][k];
      }
    }
  }
}

//______________________________________________
void HiRACsICalibrationManager::Clear()
{
  for(int i=0; i<NUM_TEL; i++) {
    for(int j=0; j<NUM_CSI_TEL; j++) {
      if(fChValues[i*NUM_CSI_TEL+j].size()) {
        fChValues [i*NUM_CSI_TEL+j].clear();
        fVoltageValues [i*NUM_CSI_TEL+j].clear();
      }
      if(fCsIChToVInterpolated [i*NUM_CSI_TEL+j]) {
        delete fCsIChToVInterpolated [i*NUM_CSI_TEL+j];
        delete fCsIChToVExtrapolated [i*NUM_CSI_TEL+j];
      }
    }
  }
  fPulserLoaded=false;
}

//______________________________________________
int HiRACsICalibrationManager::LoadPulserInfo(const char * file_name)
{
  Clear();

  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    printf("Error: error while reading pulser file\n");
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    std::string LineReadCommentLess (LineRead.substr(0, LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;
    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineReadCommentLess);

    int numtel;
    int numcsi;
    int peaknum;
    double voltage;
    double channel;

    LineStream >> numtel >> numcsi >> peaknum >> voltage >> channel;

    fChValues [numtel*NUM_CSI_TEL+numcsi].push_back(channel);
    fVoltageValues [numtel*NUM_CSI_TEL+numcsi].push_back(voltage);

    NRead++;
  }


  for(int i=0; i<NUM_TEL; i++) {
    for(int j=0; j<NUM_CSI_TEL; j++) {
      if(fChValues[i*NUM_CSI_TEL+j].size()>1) {
        fCsIChToVExtrapolated [i*NUM_CSI_TEL+j] = new TGraph(fChValues[i*NUM_CSI_TEL+j].size(), fChValues[i*NUM_CSI_TEL+j].data(), fVoltageValues[i*NUM_CSI_TEL+j].data());
        fCsIChToVInterpolated [i*NUM_CSI_TEL+j] = new TSpline3(Form("CsIChToVInterpolated%02d_%02d", i, j), fCsIChToVExtrapolated [i*NUM_CSI_TEL+j]);
        //fCsIChToVInterpolated [i*NUM_CSI_TEL+j]->SetBit(TGraph::kIsSortedX);
      }
    }
  }

  fPulserLoaded=true;
  return NRead;
}

//______________________________________________
double HiRACsICalibrationManager::GetVoltageValue(double ch, int numtel, int numcsi) const
{
  if(fCsIChToVInterpolated[numtel*NUM_CSI_TEL+numcsi]==0) return -1;
  if(ch>=fCsIChToVInterpolated[numtel*NUM_CSI_TEL+numcsi]->GetXmin() && ch<=fCsIChToVInterpolated[numtel*NUM_CSI_TEL+numcsi]->GetXmax()) {
    return fCsIChToVInterpolated[numtel*NUM_CSI_TEL+numcsi]->Eval(ch);
  } else {
    return fCsIChToVExtrapolated[numtel*NUM_CSI_TEL+numcsi]->Eval(ch,0,"");
  }
}

// CsI Calibrations are obtained with different functional formula for different isotopes as given in the calibration file
// The calibration is now V(or ch) to MeV
//
//______________________________________________
double HiRACsICalibrationManager::GetEnergyValue(double ch, int numtel, int numcsi, int Z, int A) const
{
  if(fCalib[Z][A][numtel*NUM_CSI_TEL+numcsi]==0 || !fPulserLoaded) return -1;

  return fCalib[Z][A][numtel*NUM_CSI_TEL+numcsi]->GetEnergy(GetVoltageValue(ch,numtel,numcsi));
}

//______________________________________________
void HiRACsICalibrationManager::DrawChVoltage(int numtel, int numcsi) const
{
  if(!fPulserLoaded) {
    printf("No pulser loaded\n");
    return;
  }

  const int NPoints = fChValues [numtel*NUM_CSI_TEL+numcsi].size();
  if(NPoints==0) {
    printf("No pulser available for this crystal\n");
    return;
  }
  const double *CsChPoints = fChValues [numtel*NUM_CSI_TEL+numcsi].data();
  const double *CsVoltagePoints = fVoltageValues [numtel*NUM_CSI_TEL+numcsi].data();

  const int NPointsInterpolation = NPoints*1000;
  double CsChPointsInterpolation[NPointsInterpolation];
  double CsVoltagePointsInterpolation[NPointsInterpolation];

  for(int i=0; i<NPointsInterpolation; i++) {
    CsChPointsInterpolation[i]=double(i*4096)/NPointsInterpolation;
    CsVoltagePointsInterpolation[i]=fCsIChToVExtrapolated[numtel*NUM_CSI_TEL+numcsi]->Eval(CsChPointsInterpolation[i],0,"");
  }

  TGraph *PulserGraph = new TGraph(NPoints,CsChPoints,CsVoltagePoints);
  TGraph *PulserGraphInterpolation = new TGraph(NPointsInterpolation,CsChPointsInterpolation,CsVoltagePointsInterpolation);

  //TCanvas c1 ("c1", "", 800, 600);
  PulserGraphInterpolation->Draw("AL");
  PulserGraph->Draw("same *");
  PulserGraphInterpolation->SetLineColor(kRed);
  PulserGraph->SetMarkerColor(kBlue);
  PulserGraphInterpolation->SetTitle(Form("HiRA_CsI_Pulser_VvsCh_%02d_%02d",numtel,numcsi));
  //c1.Print(Form("pictures/HiRA_CsI_Pulser_VvsCh_%02d_%02d.png",numtel,numcsi));

  return;
}

//______________________________________________
int HiRACsICalibrationManager::LoadEnergyCalibration(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    printf("Error: error while opening CsI calibration file\n");
    return -1;
  }
  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    std::string LineReadCommentLess (LineRead.substr(0, LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;
    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineReadCommentLess);

    int numtel;
    int numcsi;
    int Z;
    int A;
    std::string formula;
    double parameter_read;
    std::vector<double> parameters;
    int num_parameters;

    LineStream >> numtel >> numcsi >> Z >> A >> formula >> num_parameters;
    for(int i=0; i<num_parameters; i++) {
      LineStream>>parameter_read;
      parameters.push_back(parameter_read);
    }
    std::replace (formula.begin(), formula.end(), '.', '*');

    if(Z>Z_MAX || A>A_MAX) continue;

    fCalib[Z][A][numtel*NUM_CSI_TEL+numcsi]= new HiRACsICalibration(Z, A);

    fCalib[Z][A][numtel*NUM_CSI_TEL+numcsi]->SetNumParameters(num_parameters);
    for(int i=0; i<num_parameters; i++) {
      fCalib[Z][A][numtel*NUM_CSI_TEL+numcsi]->SetParameter(i,parameters[i]);
    }

    fCalib[Z][A][numtel*NUM_CSI_TEL+numcsi]->InitCalibration(formula.c_str());

    NRead++;
  }

  return NRead;
}

//______________________________________________
HiRACsICalibration * HiRACsICalibrationManager::GetCalibration(int numtel, int numcsi, int Z, int A) const
{
  return fCalib[Z][A][numtel*NUM_CSI_TEL+numcsi];
}

//______________________________________________
HiRACsICalibration::HiRACsICalibration(int Z, int A) :
fNumParameters(0),
fParameters(0),
fCalibrationFunc(0),
fCalibrationInitialized(false),
fZ(Z),
fA(A)
{}

//______________________________________________
HiRACsICalibration::~HiRACsICalibration()
{}

//______________________________________________
void HiRACsICalibration::SetNumParameters(int num_parameters)
{
  fNumParameters=num_parameters;
  fParameters = new double[fNumParameters];
  return;
}

//______________________________________________
void HiRACsICalibration::SetParameter(int par_to_set, double value)
{
  fParameters[par_to_set]=value;
}

//______________________________________________
void HiRACsICalibration::InitCalibration(const char * formula)
{
  fCalibrationFunc = new TF1Fast ("fCalibrationFunc", formula, 0, 5000);

  fCalibrationFunc->SetParameters(fParameters);
  fCalibrationFunc->InitInverseFunction();

  //the calibration is correctly initialized
  fCalibrationInitialized=true;
}

//______________________________________________
double HiRACsICalibration::GetEnergy(double V) const
{
  if(!fCalibrationInitialized || V<0) {
    return -1;
  }
  return fCalibrationFunc->EvalInverse(V);
}

//______________________________________________
TF1Fast::TF1Fast(double precision) :
fFunctionSet(false),
fTheRootFunction(0),
fInversePrecision(precision),
fTheRootInverseFunction(0)
{}

//______________________________________________
TF1Fast::TF1Fast(const char * name, const char * formula, double xmin, double xmax, double precision) :
fFunctionSet(true),
fName(name),
fTheRootFunction(new TF1(name, formula, xmin, xmax)),
fInversePrecision(precision),
fTheRootInverseFunction(0)
{}

//______________________________________________
TF1Fast::~TF1Fast()
{
  if(fFunctionSet) {
    delete fTheRootFunction;
  }
}

//______________________________________________
TF1 * TF1Fast::GetFunction()
{
  return fTheRootFunction;
}

//______________________________________________
void TF1Fast::SetFunction(TF1 * TheFunction)
{
  fTheRootFunction=TheFunction;
  fName.assign(TheFunction->GetName());
  fTheRootInverseFunction=0;
  fFunctionSet=true;
}

//______________________________________________
void TF1Fast::InitInverseFunction()
{
  double xmin;
  double xmax;
  fTheRootFunction->GetRange(xmin,xmax);

  for(double TheEnergy=xmin; TheEnergy<xmax; TheEnergy+=fInversePrecision) {
    fInterpolatedEnergy.push_back(TheEnergy);
    fInterpolatedLight.push_back(fTheRootFunction->Eval(TheEnergy));
  }
  fInterpolatedEnergy.push_back(xmax);
  fInterpolatedLight.push_back(fTheRootFunction->Eval(xmax));

  fymin=fTheRootFunction->Eval(xmin);
  fymax=fTheRootFunction->Eval(xmax);

  fTheRootInverseFunction = new TSpline3("TheRootInverseFunction", fInterpolatedLight.data() ,fInterpolatedEnergy.data(), fInterpolatedLight.size());
}

//______________________________________________
void TF1Fast::SetParameters(double * TheParameters)
{
  if(fFunctionSet) fTheRootFunction->SetParameters(TheParameters);
}

//______________________________________________
void TF1Fast::SetParameter(int n_par, double TheParameter)
{
  if(fFunctionSet) fTheRootFunction->SetParameter(n_par, TheParameter);
}

//______________________________________________
double TF1Fast::Eval(double X)
{
  return fTheRootFunction->Eval(X);
}

//______________________________________________
double TF1Fast::EvalInverse(double Y)
{
  return Y>=fymin && Y<=fymax ? fTheRootInverseFunction->Eval(Y) : -9999;
}
