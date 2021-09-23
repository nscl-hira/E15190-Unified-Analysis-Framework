#include <NWPulseShapeDiscrimination.h>

NWPulseShapeDiscrimination::NWPulseShapeDiscrimination(int TotNumBars) :
	fNumBars(TotNumBars),
	fPSDFlatteningFactor(new double[fNumBars]),
	fFileCuts(NULL),
	fFiducialCuts(new TCutG *[fNumBars]),
	fPSDFlatteningLoaded(false),
	fPSDResidualCalculated(false),
	fCutsLoaded(false)
	//fPSDResidualFactor(vector<vector<vector<vector<double>>>> (25, vector<vector<vector<double>>>(2,vector<vector<double>>(2,vector<double>(5))))),
  //f1_gn(vector<vector<vector<TF1 *>>>(25,vector<vector<TF1 *>>(2,vector<TF1 *>(2)))),
  //gr(vector<vector<TGraph *>>(25,vector<TGraph *>(5))),
{
	for(int i=0; i<fNumBars; i++) {
		fFiducialCuts[i] = NULL;
	}
}

NWPulseShapeDiscrimination::~NWPulseShapeDiscrimination()
{
	delete [] fPSDFlatteningFactor;
	delete [] fFiducialCuts;
	if(fFileCuts) {
		fFileCuts->Close();
		delete fFileCuts;
	}
}

int NWPulseShapeDiscrimination::LoadPSDFlattening(const char * file_name)
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

		if(LineRead.empty()) continue;
		LineRead.assign(LineRead.substr(0,LineRead.find('*')));
		if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

		std::istringstream LineStream(LineRead);

		std::string DetName;
		double factor;

		LineStream>>DetName>>factor;
		int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));
		fPSDFlatteningFactor[NumBar]=factor;

		NRead++;
	}

	NRead>0 ? fPSDFlatteningLoaded=true : fPSDFlatteningLoaded=false;
	return NRead;
}

int NWPulseShapeDiscrimination::LoadPSDResidual(const char * file_name)
{
	std::ifstream FileIn(file_name);
	if(!FileIn.is_open()) {
		return -1;
	}
	int NRead=0;

	double angleList[10];
	double angleParA[10];
	double angleParB[10];
	double angleParC[10];
	double angleParD[10];
	double angleParE[10];

	while (!FileIn.eof()) {
		std::string LineRead;
		std::getline(FileIn, LineRead);

		std::istringstream LineStream(LineRead);

		int NumBar;
		int isRight;
		double gamma0;
		double gamma1;
		double gamma2;
		double gamma3;
		double gamma4;
		double neutron0;
		double neutron1;
		double neutron2;
		double neutron3;
		double neutron4;

		double angle;
		double a;
		double b;
		double c;
		double d;
		double e;

		if (NRead<48) {
			LineStream>>NumBar>>isRight>>gamma0>>gamma1>>gamma2>>gamma3>>gamma4>>neutron0>>neutron1>>neutron2>>neutron3>>neutron4;
			fPSDResidualFactor[NumBar][isRight][0][0]=gamma0;
			fPSDResidualFactor[NumBar][isRight][0][1]=gamma1;
			fPSDResidualFactor[NumBar][isRight][0][2]=gamma2;
			fPSDResidualFactor[NumBar][isRight][0][3]=gamma3;
			fPSDResidualFactor[NumBar][isRight][0][4]=gamma4;
			fPSDResidualFactor[NumBar][isRight][1][0]=neutron0;
			fPSDResidualFactor[NumBar][isRight][1][1]=neutron1;
			fPSDResidualFactor[NumBar][isRight][1][2]=neutron2;
			fPSDResidualFactor[NumBar][isRight][1][3]=neutron3;
			fPSDResidualFactor[NumBar][isRight][1][4]=neutron4;
		}
		else {
			NumBar = ((NRead-48)/10) + 1;
			int index = (NRead-48)%10;
			LineStream>>angle>>a>>b>>c>>d>>e;
			angleList[index]=angle;
			angleParA[index]=a;
			angleParB[index]=b;
			angleParC[index]=c;
			angleParD[index]=d;
			angleParE[index]=e;
			if (index==9) {
				gr[NumBar][0]= new TGraph(10,angleList,angleParA);
				gr[NumBar][1]= new TGraph(10,angleList,angleParB);
				gr[NumBar][2]= new TGraph(10,angleList,angleParC);
				gr[NumBar][3]= new TGraph(10,angleList,angleParD);
				gr[NumBar][4]= new TGraph(10,angleList,angleParE);
			}
		}

		NRead++;
	}

	for (int bar=1; bar<=24; ++bar) {
		for (int lr=0; lr<2; ++lr) {
			for (int gn=0; gn<2; ++gn) {
				f1_gn[bar][lr][gn] = new TF1("f1","pol4", 0, 5000);
				f1_gn[bar][lr][gn] -> SetParameters(&fPSDResidualFactor[bar][lr][gn][0]);
			}
		}
	}

	NRead>0 ? fPSDResidualCalculated=true : fPSDResidualCalculated=false;
	return NRead;
}

int NWPulseShapeDiscrimination::LoadIsGammaCuts(const char * file_name)
{
	int NCuts=0;

	fFileCuts = new TFile(file_name);
	if(fFileCuts->IsZombie()) {
		return -1;
	}

	for(int i=0; i<fNumBars; i++) {
		fFiducialCuts[i]=(TCutG*)fFileCuts->Get(Form("NWCUT_%02d",i));
		if(fFiducialCuts[i]) NCuts++;
	}

	if(NCuts>0) fCutsLoaded=true;
	return NCuts;

}

double NWPulseShapeDiscrimination::GetPSDFlattened(double ch, double ch_fast, int numbar) const
{
	return fPSDFlatteningLoaded ? ch_fast-ch*fPSDFlatteningFactor[numbar] : -9999;
}

double NWPulseShapeDiscrimination::GetLeftPSDResidual(double left_ch, double left_ch_fast, double right_ch, double right_ch_fast, double Xcm, int numbar) const
{
	double xleft = f1_gn[numbar][0][0]->Eval(left_ch) - left_ch_fast;
	double yleft = f1_gn[numbar][0][0]->Eval(left_ch) - f1_gn[numbar][0][1]->Eval(left_ch);
	double xright = f1_gn[numbar][1][0]->Eval(right_ch) - right_ch_fast;
	double yright = f1_gn[numbar][1][0]->Eval(right_ch) - f1_gn[numbar][1][1]->Eval(right_ch);

	double fResLeft = xleft / yleft;
	double fResRight = xright / yright;

	// fix gamma peak as (0,0)
	fResLeft -= gr[numbar][1]->Eval(Xcm, 0, "S");
	fResRight -= gr[numbar][0]->Eval(Xcm, 0, "S");

	// fix gamma neutron distance as 1;
	fResLeft /= gr[numbar][2]->Eval(Xcm, 0, "S");
	fResRight /= gr[numbar][2]->Eval(Xcm, 0, "S");

	//rotate neutron peak to (1,0)
	double theta = gr[numbar][4]->Eval(Xcm, 0, "S");
	double fPsdLeft = fResLeft * cos(theta) - fResRight * sin(theta);
	double fPsdRight = fResLeft * sin(theta) + fResRight * cos(theta);

	return fPSDResidualCalculated ? fPsdLeft : -9999;
}

double NWPulseShapeDiscrimination::GetRightPSDResidual(double left_ch, double left_ch_fast, double right_ch, double right_ch_fast, double Xcm, int numbar) const
{
	double xleft = f1_gn[numbar][0][0]->Eval(left_ch) - left_ch_fast;
	double yleft = f1_gn[numbar][0][0]->Eval(left_ch) - f1_gn[numbar][0][1]->Eval(left_ch);
	double xright = f1_gn[numbar][1][0]->Eval(right_ch) - right_ch_fast;
	double yright = f1_gn[numbar][1][0]->Eval(right_ch) - f1_gn[numbar][1][1]->Eval(right_ch);

	double fResLeft = xleft / yleft;
	double fResRight = xright / yright;

	// fix gamma peak as (0,0)
	fResLeft -= gr[numbar][1]->Eval(Xcm, 0, "S");
	fResRight -= gr[numbar][0]->Eval(Xcm, 0, "S");

	// fix gamma neutron distance as 1;
	fResLeft /= gr[numbar][2]->Eval(Xcm, 0, "S");
	fResRight /= gr[numbar][2]->Eval(Xcm, 0, "S");

	//rotate neutron peak to (1,0)
	double theta = gr[numbar][4]->Eval(Xcm, 0, "S");
	double fPsdLeft = fResLeft * cos(theta) - fResRight * sin(theta);
	double fPsdRight = fResLeft * sin(theta) + fResRight * cos(theta);

	return fPSDResidualCalculated ? fPsdRight : -9999;
}

bool NWPulseShapeDiscrimination::IsGamma(double ch, double ch_fast, int numbar , double ch_left , double ch_right) const
{
	if(!fCutsLoaded || !fPSDFlatteningLoaded) return true; //we are interested in not-gamma
	if((fFiducialCuts[numbar]!=0 && !(fFiducialCuts[numbar]->IsInside(ch,GetPSDFlattened(ch,ch_fast,numbar)))) || (ch_left>4090) || (ch_right>4090)) return false; // assume gamma won't have such high energy to make channel saturated
	else return true;
}
