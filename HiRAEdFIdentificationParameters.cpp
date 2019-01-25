#include <HiRAEdFIdentificationParameters.h>

//________________________________________________
HiRAEdFIdentificationParameters::HiRAEdFIdentificationParameters() :
fNumParameters(0),
fParameters(0)
{}

//________________________________________________
HiRAEdFIdentificationParameters::~HiRAEdFIdentificationParameters()
{
  if(fParameters) delete [] fParameters;
}

//________________________________________________
void HiRAEdFIdentificationParameters::SetNumParameters(int tot_num_par)
{
  fNumParameters=tot_num_par;
  fParameters = new double [fNumParameters];
}

//________________________________________________
void HiRAEdFIdentificationParameters::SetParameter(int num_par, double value)
{
  fParameters[num_par]=value;
}

//________________________________________________
void HiRAEdFIdentificationParameters::SetParameters(double * value)
{
  for(int i=0; i<fNumParameters; i++) {
    fParameters[i]=value[i];
  }
}

// Function for DE-E identification based
// on formulas from N. Le Neindre et al. NIM A490 (2002) 251
// modified following the formula of W. Gawlikowicz
// for Light-Energy relation in CsI(Tl)
// NIM A491 (2002) 181. Adapted by Amalia Pop following
// ref.: J. Blicharska et al. LNS report 2005
// This formula needs 14 fit parameters
//________________________________________________
double HiRAEdFIdentificationParameters::func14(MPart &p) const
{
   double X = p.x;
   double Z = p.Z;
   double A = p.A;
   double xx,exp1,exp2,res=1.0;
   double reslog,ene;

   if(Z==0 && A==0) {
    return fParameters[12];
   }
   xx = X-fParameters[13];
   //if xx<0 never reached from data analysis
   if(xx<=0) {
     return res;
   }

   exp1 = fParameters[2] + fParameters[3] + 1;
   exp2 = 1./exp1;
   reslog = log(1.+ fParameters[9]* Z)*(1.- exp(-fParameters[10]*pow(Z,fParameters[11])))/Z;
   ene = fParameters[6] * reslog * xx ;
   ene = ene + fParameters[7] * Z * sqrt(A) * log(1. + fParameters[8] * reslog  * xx);
   res = pow(ene,exp1) +
         pow((fParameters[4]* pow(Z,fParameters[0]) * pow(A,fParameters[1])),exp1) +
         fParameters[5]*pow(Z,2) * pow(A,fParameters[2]) * pow(ene,fParameters[3]);
   res = pow(res,exp2) - ene + fParameters[12];
   return res;
}

//________________________________________________
int HiRAEdFIdentificationParameters::Get_Charge(double de, double fast, int *iter, double *zeta)
{
 const int maxiter=50, zlim=MAX_Z_IDENTIFIED_HIRA;
 int cres = 1,izeta;
 double zmin=1, zmax=zlim, ztest, atest=0, yy, dist;
 double amass=0,amassp=0,amassm=0;
 bool found = false;
 MPart p;

 *iter = 0;
 *zeta = 0.0;
 while(*iter < maxiter) {
  (*iter)++;
  ztest = (zmin + zmax) / 2.0;
  atest = GetMassCharity(int(ztest+0.5));

  if(atest==1)atest=2.;

  p.x = fast;
  p.Z = ztest;
  p.A = atest;

  yy = func14(p);
  if(yy == 1.0) {
   cres = 0;
   return cres;
  }
  if((int)(zmin+0.5) == (int)(zmax+0.5)) {
   found = true;
   break;
  }
  if((de - yy)>=0) {
   zmin = ztest;
   continue;
  }
  else {
   zmax = ztest;
   continue;
  }
 }
 if(!found) {
  //std::cout<<"Get_Charge>> Convergence not reached"<<std::endl;
  return 0;
 }
 cres = (int)(zmin+0.5);
 izeta = cres;
 if(cres>zlim) {
  *zeta = izeta;
  return cres;
 }

// dispersion around mean charge value
  p.Z = izeta;

  amass = GetMassCharity(izeta);
  amassp = GetMassCharity(izeta+1);
  amassm = GetMassCharity(izeta>1 ? izeta-1 : izeta);

  p.A = amass;
  yy = func14(p);
  dist = de - yy;

  if(dist >= 0.0) {
   p.Z = izeta+1;
   p.A = amassp;  //z+1
   *zeta = (double)izeta + dist/(func14(p)-yy);
  }
  else {
   p.Z = izeta-1;
   p.A = amassm;  //zeta-1
   *zeta = (double)izeta + dist/(yy- (izeta>1 ? func14(p) : 0.));
  }
  if(*zeta>0 && *zeta<0.5) {
    return 0.;
  }
  return cres;
}

double HiRAEdFIdentificationParameters::Get_Mass(int charge, double de, double fast, int *iter)
{
 const int maxiter=100;
 bool found = false;
 double amin,amax;
 double Amin[] = {0, 2, 4, 6, 7, 9, 11, 13, 14, 17, 19, 21, 22, 23};
 double Amax[] = {6, 10, 11, 12, 13, 15, 18, 26, 29, 32, 35, 36, 38, 41};
 double mass = 0.0, fmass, yy, atest, dist, dmin=0.10;
 MPart p;

 *iter = 0;
 amin = Amin[charge-1];
 amax = Amax[charge-1];

 p.x = fast;
 p.Z = charge;
 while(*iter < maxiter) {
  (*iter)++;
  atest = (amax + amin) / 2.0;
  p.A = atest;
  yy = func14(p);
  if(yy == 1.0) {
   return 0.0;
  }
  dist = de - yy;

  if(fabs(dist) <= dmin) {
   found = true;
   break;
  }
  if((de - yy)>=0) {
   amin = atest;
   continue;
  }
  else {
   amax = atest;
   continue;
  }
}  //end convergence loop

 if(!found) {
  if(amin==amax) {
   return 0.0;
  }
  else {
   if(charge>1) {
    //std::cout<<"Get_Mass>> Warning: charge convergenze failed:  Z="<<charge<<std::endl;
   }
  }
 }

 mass = int(atest+0.5);
 p.A = mass;
 yy = func14(p);
 if(yy == 1.0) {
  return 0.0;
 }
 if(mass==0) {
   return 0;
 }

// calculate dispersion around mean mass value
 dist = de - yy;
 if(dist >= 0.0) {
   p.A = mass + 1.;
   fmass = mass + dist/(func14(p)-yy);
  }
  else {
   p.A = mass - 1.;
   fmass = mass + dist/(yy-func14(p));
  }
 if(int(fmass+0.5) != mass) {
  if(dist>0)
   fmass = int(fmass+0.5) + 0.501;
  else
   fmass = int(fmass+0.5) + 0.499;
 }
 if(fmass>0 && fmass<0.5)fmass = 0.51;
 return fmass;
}

//Return the mass by the Charity formula
//PRC 58(1998)1073
double HiRAEdFIdentificationParameters::GetMassCharity(double Z) const
{
 double A;

 if(Z<=6) {
  int CharityLight[] = {1,4,7,9,10,12};
  A = CharityLight[(int)Z-1];
  return A;
 }
 else
  return (unsigned int)(2.072*Z + 2.32E-03 * Z*Z) + 1;
}
