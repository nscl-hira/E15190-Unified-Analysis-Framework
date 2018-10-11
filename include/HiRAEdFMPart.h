#ifndef HIRAEDFMPART_H
#define HIRAEDFMPART_H

/* HiRAEdFMPart is the data structure MPart used by
 * Enrico De Filippo (E.d.F.) to implement DE-E fits in CHIMERA
 * 2018 October 10 - Created by Daniele Dell'Aquila
 *
 */

//The fit data structure (by Enrico De Filippo)
typedef struct MPart_ {
 double x,y;   //x,y points
 double Z,A;   //Charge and mass
 double e;     //Error
} MPart;

#endif
