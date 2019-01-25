#ifndef NWPULSESHAPEDISCRIMINATION_H
#define NWPULSESHAPEDISCRIMINATION_H

#include <TCutG.h>
#include <TFile.h>
#include <string>
#include <fstream>
#include <sstream>
#include <TRandom3.h>

class NWPulseShapeDiscrimination
{
public :
	NWPulseShapeDiscrimination(int TotNumBars);
	~NWPulseShapeDiscrimination();

	int LoadPSDFlattening(const char *);
	int LoadIsGammaCuts(const char *);

	double GetPSDFlattened(double ch, double ch_fast, int numbar) const;
	bool IsGamma(double ch, double ch_fast, int numbar) const;

private :
	int fNumBars;
	double * fPSDFlatteningFactor;
	TFile * fFileCuts;
	TCutG ** fFiducialCuts;

	bool fPSDFlatteningLoaded;
	bool fCutsLoaded;
};

#endif
