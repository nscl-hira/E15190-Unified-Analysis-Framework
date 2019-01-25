#include <NWPulseShapeDiscrimination.h>

NWPulseShapeDiscrimination::NWPulseShapeDiscrimination(int TotNumBars) :
	fNumBars(TotNumBars),
	fPSDFlatteningFactor(new double[fNumBars]),
	fFileCuts(NULL),
	fFiducialCuts(new TCutG *[fNumBars]),
	fPSDFlatteningLoaded(false),
	fCutsLoaded(false)
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

		LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.empty()) continue;
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

bool NWPulseShapeDiscrimination::IsGamma(double ch, double ch_fast, int numbar) const
{
	if(!fCutsLoaded || !fPSDFlatteningLoaded) return true; //we are interested in not-gamma
	if(fFiducialCuts[numbar]!=0 && !(fFiducialCuts[numbar]->IsInside(ch,GetPSDFlattened(ch,ch_fast,numbar)))) return false;
	else return true;
}
