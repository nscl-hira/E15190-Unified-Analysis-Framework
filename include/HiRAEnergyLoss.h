#ifndef HIRAENERGYLOSS_H
#define HIRAENERGYLOSS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <EnergyLossModule.h>

/* HiRAEnergyLoss class
 * created by Daniele Dell'Aquila
 * 27 March 2019
 *
 * This class handles the reconstruction of the kinetic energy of particles detected by HiRA
 * taking into account the energy loss in the absorbers placed in front of the telescopes
 * See the corrisponding calibration files to know how to set-up the class for each run.
 *
 * One can include an arbitrary number of targets and an arbitrary numbers of absorbers.
 *
 */

typedef struct Absorber_ {
  std::string material;
  double thickness;  //um
} Absorber;

class HiRAEnergyLoss
{
public :
  HiRAEnergyLoss(int);
  ~HiRAEnergyLoss();

  void SetTarget(const char *, double);
  void SetAbsorber(int, const char *, double);
  int LoadConfiguration(const char *);

  double GetEinc(int telescope, int Z, int A, double Eres, double theta=0) const;

private :
  bool fConfigurationLoaded;
  EnergyLossModule * fEnergyLoss;
  int fNumTel;
  std::vector <Absorber> * fTheAbsorbers;
  std::vector <Absorber> fTheTarget;

} ;

#endif
