#include "include/NWGeometry.h"

using namespace std;

NWGeometry::NWGeometry(int NumberOfBars) :
fposition_NW_cor(new double *[NumberOfBars]),
fNumBars(NumberOfBars)
{
  for(int i=0; i<fNumBars; i++) {
    fposition_NW_cor[i]= new double [3];
  }
}

NWGeometry::~NWGeometry()
{
  for(int i=0; i<fNumBars; i++) {
    delete [] fposition_NW_cor[i];
  }
  delete [] fposition_NW_cor;
}

int NWGeometry::LoadFiducialPoints(const char *txtfilename)
{
	ifstream FileIn(txtfilename);
  if(!FileIn.is_open()) {
    return -1;
  }

  int NLines=0;

	while(!FileIn.eof()) {
    std::string LineRead;
    std::getline(FileIn, LineRead);

    LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

		string DetName;

    LineStream >> DetName;
    int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));

		LineStream >> fposition_NW_cor[NumBar][0] >> fposition_NW_cor[NumBar][1] >> fposition_NW_cor[NumBar][2];
    NLines++;
  }

  return NLines;
}

double NWGeometry::GetX(int NW_fnumbar,double NW_fXcm) const
{
	return fposition_NW_cor[NW_fnumbar][0] - position_NW_direction[0]/2 + position_NW_direction[0]/bar_length_raw*(NW_fXcm) + position_NW_direction[2]/bar_length_raw*bar_thickness;
}

double NWGeometry::GetYRan(int NW_fnumbar,double NW_fXcm) const
{
	return fposition_NW_cor[NW_fnumbar][1] - position_NW_direction[1]/2 + position_NW_direction[1]/bar_length_raw*(NW_fXcm) + gRandom->Uniform(-bar_height/2,bar_height/2);
}

double NWGeometry::GetY(int NW_fnumbar,double NW_fXcm) const
{
	return fposition_NW_cor[NW_fnumbar][1] - position_NW_direction[1]/2 + position_NW_direction[1]/bar_length_raw*(NW_fXcm);
}

double NWGeometry::GetZ(int NW_fnumbar,double NW_fXcm) const
{
	return fposition_NW_cor[NW_fnumbar][2] - position_NW_direction[2]/2 + position_NW_direction[2]/bar_length_raw*(NW_fXcm) + (-position_NW_direction[0])/bar_length_raw*bar_thickness;
}

double NWGeometry::GetR(int NW_fnumbar,double NW_fXcm) const
{
	return sqrt(GetX(NW_fnumbar,NW_fXcm)*GetX(NW_fnumbar,NW_fXcm)+GetY(NW_fnumbar,NW_fXcm)*GetY(NW_fnumbar,NW_fXcm)+GetZ(NW_fnumbar,NW_fXcm)*GetZ(NW_fnumbar,NW_fXcm));
}

double NWGeometry::GetRRan(int NW_fnumbar,double NW_fXcm) const
{
	return sqrt(GetX(NW_fnumbar,NW_fXcm)*GetX(NW_fnumbar,NW_fXcm)+GetYRan(NW_fnumbar,NW_fXcm)*GetYRan(NW_fnumbar,NW_fXcm)+GetZ(NW_fnumbar,NW_fXcm)*GetZ(NW_fnumbar,NW_fXcm));
}

double NWGeometry::GetTheta(int NW_fnumbar,double NW_fXcm) const
{
	return acos(GetZ(NW_fnumbar,NW_fXcm)/GetR(NW_fnumbar,NW_fXcm))/3.141592654*180;
}

double NWGeometry::GetPhi(int NW_fnumbar,double NW_fXcm) const
{
	return atan(GetY(NW_fnumbar,NW_fXcm)/GetX(NW_fnumbar,NW_fXcm))/3.141592654*180;
}

double NWGeometry::GetThetaRan(int NW_fnumbar,double NW_fXcm) const
{
	return acos(GetZ(NW_fnumbar,NW_fXcm)/GetRRan(NW_fnumbar,NW_fXcm))/3.141592654*180;
}

double NWGeometry::GetPhiRan(int NW_fnumbar,double NW_fXcm) const
{
	return atan(GetYRan(NW_fnumbar,NW_fXcm)/GetX(NW_fnumbar,NW_fXcm))/3.141592654*180;
}
