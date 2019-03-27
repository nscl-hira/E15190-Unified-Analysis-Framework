#ifndef KINEMATICSMODULE_H
#define KINEMATICSMODULE_H

#include <string>
#include <math.h>
#include <TLorentzVector.h>

#include <nuclear_masses.h>

class KinematicsModule
{
public :
  KinematicsModule();
  ~KinematicsModule();

  void SetBeam(const char *, double);
  void SetTarget(const char *);
  void SetParticle (int Z, int A, double Ekin, double Theta, double Phi);

  double GetEkinCMS() const;
  double GetThetaCMS() const;
  double GetMomentum() const;
  double GetMomentumCMS() const;

private :
  nuclear_masses * fTheMassDatabase;
  double fBeamMass;
  TLorentzVector fQBeam;
  double fTargetMass;
  TLorentzVector fQTarget;
  double fParticleMass;
  double fParticleMomentum;
  TLorentzVector fQParticle;
  TLorentzVector fQParticleCMS;

};

#endif
