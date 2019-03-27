#include "include/KinematicsModule.h"

//____________________________________________________
KinematicsModule::KinematicsModule() :
fTheMassDatabase(new nuclear_masses("./input/masses.conf"))
{}

//____________________________________________________
KinematicsModule::~KinematicsModule()
{
  delete fTheMassDatabase;
}

//____________________________________________________
void KinematicsModule::SetBeam(const char * the_nucleus, double Ene_per_amu)
{
  fBeamMass = fTheMassDatabase->get_mass_Z_A(the_nucleus);
  double TotEnergy = fBeamMass + Ene_per_amu*fTheMassDatabase->get_mass_Z_A_uma(the_nucleus);
  double MomentumZ = sqrt(pow(TotEnergy,2)-pow(fBeamMass,2));
  fQBeam.SetPxPyPzE(0,0,MomentumZ,TotEnergy);
}

//____________________________________________________
void KinematicsModule::SetTarget(const char * the_nucleus)
{
  fTargetMass = fTheMassDatabase->get_mass_Z_A(the_nucleus);
  fQTarget.SetPxPyPzE(0,0,0,fTargetMass);
}

//____________________________________________________
void KinematicsModule::SetParticle(int Z, int A, double Ekin, double Theta, double Phi)
{
  fParticleMass = fTheMassDatabase->get_mass_Z_A(Z,A);
  double TotEnergy = fParticleMass + Ekin;
  fParticleMomentum = sqrt(pow(TotEnergy,2)-pow(fParticleMass,2));
  fQParticle.SetPxPyPzE(fParticleMomentum*sin(Theta)*cos(Phi),fParticleMomentum*sin(Theta)*sin(Phi),fParticleMomentum*cos(Theta),TotEnergy);
  fQParticleCMS.SetPxPyPzE(fQParticle.Px(), fQParticle.Py(), fQParticle.Pz(), fQParticle.E());
  fQParticleCMS.Boost(-(fQBeam+fQTarget).BoostVector());
}

//____________________________________________________
double KinematicsModule::GetMomentum() const
{
  return fParticleMomentum;
}

//____________________________________________________
double KinematicsModule::GetMomentumCMS() const
{
  return fQParticleCMS.P();
}

//____________________________________________________
double KinematicsModule::GetEkinCMS() const
{
  return fQParticleCMS.E()-fParticleMass;
}

//____________________________________________________
double KinematicsModule::GetThetaCMS() const
{
  return fQParticleCMS.Theta();
}
