#ifndef HIRAIDENTIFICATION_H
#define HIRAIDENTIFICATION_H

#include <fstream>
#include <sstream>
#include <string>

#include <HiRACalibratedRootEvent.h>
#include <HiRAEdFIdentificationParameters.h>

#include <shared.h>

/* HiRAIdentification class
 * 2018 October 10 - Created by Daniele Dell'Aquila (dellaquila.daniele@gmail.com)
 * This class handles HiRA Identifications with the DE-E techniques
 * Identification are made crystal-by-crystal
 *
 * Calculations are made according to Enrico De Filippo's model from the CHIMERA collaboration.
 *
 */

class HiRAIdentification
{
public :
  HiRAIdentification(int tot_num_tel, int num_csi_tel);
  ~HiRAIdentification();

  int LoadIdentification(const char *);

  int PerformIdentification(HiRACalibratedData *);

private :
  int fNumTel;
  int fNumCsITel;
  int fNumCsITot;
  HiRAEdFIdentificationParameters * fEdFTool;

  bool fIdentificationLoaded;
};

#endif
