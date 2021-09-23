#include <VWGeometry.h>

using namespace std;

VWGeometry::VWGeometry(int NumberOfBars):
fVW_center_cor(new TVector3 *[NumberOfBars]),
fNumBars(NumberOfBars),
bar_length(227.237),
bar_width(9.4),
bar_thickness(1),
bar_length_direction(new TVector3(0,1,0)),
bar_width_direction(new TVector3(0.78196,0,-0.62333)),
bar_thickness_direction(new TVector3(-0.62333,0,-0.78196)),
fFiducialPointsLoaded(false)
{
	for(int i=0; i<fNumBars; i++) {
		fVW_center_cor[i]=new TVector3(-9999,-9999,-9999);
	}
}

VWGeometry::~VWGeometry()
{
	for(int i=0; i<fNumBars;i++) {
		delete [] fVW_center_cor[i];
	}
	delete [] fVW_center_cor;
}

int VWGeometry::LoadFiducialPoints(const char *txtfilename)
{
	ifstream FileIn(txtfilename);
	if(!FileIn.is_open()) {
		return -1;
	}

	int NLines=0;

	while(!FileIn.eof()) {
		std::string LineRead;
		std::getline(FileIn, LineRead);

		if(LineRead.empty()) continue;
		LineRead.assign(LineRead.substr(0,LineRead.find('*')));
		if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

		std::istringstream LineStream(LineRead);
		string DetName;
		double DetX;
		double DetY;
		double DetZ;
		LineStream >> DetName;
		int NumBar=std::stoi(DetName.substr(DetName.find("bar")+3));

		LineStream >> DetX >> DetY >> DetZ;

		fVW_center_cor[NumBar]->SetXYZ(DetX,DetY,DetZ);
		NLines++;
	}

	NLines>0 ? fFiducialPointsLoaded=true : fFiducialPointsLoaded=false;
	return NLines;
}

double VWGeometry::GetX(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? fVW_center_cor[VW_fnumbar]->X()+VW_fXcm*bar_length_direction->X() : -9999;
}

double VWGeometry::GetXRan(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? fVW_center_cor[VW_fnumbar]->X() + VW_fXcm*bar_length_direction->X() + gRandom->Uniform(-bar_width/2,bar_width/2)*bar_width_direction->X() : -9999;
}

double VWGeometry::GetZ(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? fVW_center_cor[VW_fnumbar]->Z()+VW_fXcm*bar_length_direction->Z() : -9999;
}

double VWGeometry::GetZRan(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? fVW_center_cor[VW_fnumbar]->Z() + VW_fXcm*bar_length_direction->Z() + gRandom->Uniform(-bar_width/2,bar_width/2)*bar_width_direction->Z() : -9999;
}

double VWGeometry::GetY(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? fVW_center_cor[VW_fnumbar]->Y()+VW_fXcm*bar_length_direction->Y() : -9999;
}

double VWGeometry::GetR(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? sqrt(GetX(VW_fnumbar,VW_fXcm)*GetX(VW_fnumbar,VW_fXcm)+GetY(VW_fnumbar,VW_fXcm)*GetY(VW_fnumbar,VW_fXcm)+GetZ(VW_fnumbar,VW_fXcm)*GetZ(VW_fnumbar,VW_fXcm)) : -9999;
}

double VWGeometry::GetRRan(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? sqrt(GetXRan(VW_fnumbar,VW_fXcm)*GetXRan(VW_fnumbar,VW_fXcm)+GetY(VW_fnumbar,VW_fXcm)*GetY(VW_fnumbar,VW_fXcm)+GetZRan(VW_fnumbar,VW_fXcm)*GetZRan(VW_fnumbar,VW_fXcm)) : -9999;
}

double VWGeometry::GetTheta(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? acos(GetZ(VW_fnumbar,VW_fXcm)/GetR(VW_fnumbar,VW_fXcm))/3.141592654*180 : -9999;
}

double VWGeometry::GetThetaRan(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? acos(GetZRan(VW_fnumbar,VW_fXcm)/GetRRan(VW_fnumbar,VW_fXcm))/3.141592654*180 : -9999;
}

double VWGeometry::GetPhi(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? atan(GetY(VW_fnumbar,VW_fXcm)/GetX(VW_fnumbar,VW_fXcm))/3.141592654*180 : -9999;
}

double VWGeometry::GetPhiRan(int VW_fnumbar,double VW_fXcm) const
{
	return fFiducialPointsLoaded ? atan(GetY(VW_fnumbar,VW_fXcm)/GetXRan(VW_fnumbar,VW_fXcm))/3.141592654*180 : -9999;
}
