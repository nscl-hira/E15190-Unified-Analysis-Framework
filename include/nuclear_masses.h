#ifndef NUCL_MASSES_H
#define NUCL_MASSES_H

#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <string.h>
#include <vector>
#include <map>
#include <TROOT.h>

/* nuclear_masses class
 * created by Daniele Dell'Aquila
 * This class has been improved on March 26th 2019, it now can return the mass in MeV or uma of a nucleus
 * starting from a string containing its name.
 *
 */

class nuclear_masses
{
public:
  nuclear_masses(const char * file_conf_name="masses.conf");
  ~nuclear_masses();

  double get_mass_Z_A(int Z, int A) const;
  double get_mass_Z_A_uma(int Z, int A) const;
  double get_mass_Z_A(const char *) const;
  double get_mass_Z_A_uma(const char *) const;

private:
  double ** atomic_masses; // atomic_masses[Z][A]
  char *** element_names; // element_names[Z][A]
  std::map <std::string, double> nuclear_masses_string; //map string -> nuclear_mass (MeV)
  double electron_mass; // MeV
  double UMA_MeV; // MeV/uma

};

#endif
