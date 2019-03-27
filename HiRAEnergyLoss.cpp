#include "include/HiRAEnergyLoss.h"

//____________________________________________________
HiRAEnergyLoss::HiRAEnergyLoss(int num_tel) :
fConfigurationLoaded(false),
fEnergyLoss(new EnergyLossModule()),
fNumTel(num_tel),
fTheAbsorbers(new std::vector <Absorber>[fNumTel])
{}

//____________________________________________________
HiRAEnergyLoss::~HiRAEnergyLoss()
{
  delete fEnergyLoss;
  for(int i=0; i<fNumTel; i++) {
    fTheAbsorbers[i].clear();
  }
  delete [] fTheAbsorbers;
}

//____________________________________________________
int HiRAEnergyLoss::LoadConfiguration(const char * file_name)
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

    LineRead.assign(LineRead.substr(0, LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;

    std::istringstream LineStream(LineRead);

    std::string command;

    LineStream>>command;

    if(command.compare("set")==0) {
      std::string what_to_set;

      LineStream>>what_to_set;

      if(what_to_set.compare("absorber")==0) {
        int tel_num;
        std::string material;
        double thickness;
        LineStream>>tel_num>>material>>thickness;
        material.assign(material.substr(material.find('\"')+1,material.find_last_of('\"')-material.find('\"')-1));
        SetAbsorber (tel_num, material.c_str(), thickness);
        NRead++;
      } else if(what_to_set.compare("target")==0) {
        std::string material;
        double thickness;
        LineStream>>material>>thickness;
        material.assign(material.substr(material.find('\"')+1,material.find_last_of('\"')-material.find('\"')-1));
        SetTarget (material.c_str(), thickness);
        NRead++;
      }
    }
  }

  fConfigurationLoaded=true;

  return NRead;
}

//____________________________________________________
void HiRAEnergyLoss::SetTarget(const char * material, double thickness_um)
{
  Absorber NewAbsorber;
  NewAbsorber.material.assign(material);
  NewAbsorber.thickness=thickness_um;
  fTheTarget.push_back(NewAbsorber);
}

//____________________________________________________
void HiRAEnergyLoss::SetAbsorber(int telescope_number, const char * material, double thickness_um)
{
  Absorber NewAbsorber;
  NewAbsorber.material.assign(material);
  NewAbsorber.thickness=thickness_um;
  fTheAbsorbers[telescope_number].push_back(NewAbsorber);
}

//____________________________________________________
double HiRAEnergyLoss::GetEinc(int telescope, int Z, int A, double Eres, double theta) const
{
  if(!fConfigurationLoaded) return -9999;

  double ELossAbsorbers = 0;

  for(int i=fTheAbsorbers[telescope].size()-1; i>=0; i--) {
    ELossAbsorbers+=fEnergyLoss->GetEnergyLoss(Z, A, Eres+ELossAbsorbers, (fTheAbsorbers[telescope])[i].material.c_str(), (fTheAbsorbers[telescope])[i].thickness);
  }
  for(int i=fTheTarget.size()-1; i>=0; i--) {
    ELossAbsorbers+=fEnergyLoss->GetEnergyLoss(Z, A, Eres+ELossAbsorbers, fTheTarget[i].material.c_str(), fTheTarget[i].thickness/2./cos(theta));
  }

  return Eres+ELossAbsorbers;

}
