#ifndef HTRUNINFO_H
#define HTRUNINFO_H

#include <fstream>
#include <sstream>


#include <HTDAQStackInfo.h>
/*
#include <RBHINPUnpacker.h>
#include <RBPh7xxUnpacker.h>
#include <RBCAEN7xxUnpacker.h>
#include <RBCAEN1x90Unpacker.h>
#include <RBSisTimestampUnpacker.h>
#include <RBTimestamp.h>
*/

class HTRunInfo
{
public:
  HTRunInfo(int run_number, const char * run_title="");                             //! Constructor
  ~HTRunInfo();                                          //! Destructor

  int LoadDAQSettings(const char *);                     //! Read DAQ settings from file
  int SetPedestalsFile(const char *);                    //! Set Pathname of pedestal file
  int SetMappingFile(const char *);                      //! Set Pathname of mapping file

  const char * GetTitle() const;                         //! Returns run title
  int GetRunNumber() const;                              //! Returns run number
  const char * GetEvtFilePath() const;                   //! Returns path containing evt files for the run
  const char * GetPedestalFile() const;                  //! Returns the path to pedestal file for the run
  const char * GetMappingFile() const;                   //! Returns the path to the mapping file for the run
  int GetNStacks() const;                                //! Returns number of stacks
  HTDAQStackInfo * GetStackInfo(int) const;              //! Returns a HTDAQStackInfo object

  //E15190-Analysis-Framework methods
  void SetNWAPositionCalibrationFile(const char * file_name) {fNWAPositionCalibrationFileName.assign(file_name);}
  void SetNWBPositionCalibrationFile(const char * file_name) {fNWBPositionCalibrationFileName.assign(file_name);}
  void SetNWATimeOffsetCalibrationFile(const char * file_name) {fNWATimeOffsetCalibrationFileName.assign(file_name);}
  void SetNWBTimeOffsetCalibrationFile(const char * file_name) {fNWBTimeOffsetCalibrationFileName.assign(file_name);}
  void SetNWAGainMatchingCalibrationFile(const char * file_name) {fNWAGainMatchingCalibrationFileName.assign(file_name);}
  void SetNWBGainMatchingCalibrationFile(const char * file_name) {fNWBGainMatchingCalibrationFileName.assign(file_name);}
  void SetNWAGeometryCalibrationFile(const char * file_name) {fNWAGeometryFileName.assign(file_name);}
  void SetNWBGeometryCalibrationFile(const char * file_name) {fNWBGeometryFileName.assign(file_name);}
  void SetFATimeCalibrationFile(const char * file_name) {fFATimeCalibrationFileName.assign(file_name);}
  void SetFAPulseHeightCorrectionFile(const char * file_name) {fFAPulseHeightCorrectionFileName.assign(file_name);}
  void SetVWGainMatchingCalibrationFile(const char * file_name) {fVWGainMatchingCalibrationFileName.assign(file_name);}
  void SetMBDetectorStatusFile(const char * file_name) {fMBDetectorStatusFileName.assign(file_name);}
  void SetMBGeometryFile(const char * file_name) {fMBGeometryFileName.assign(file_name);}
  void SetMBImpactParameterFile(const char * file_name) {fMBImpactParameterFileName.assign(file_name);}
  void SetMBHitConditionFile(const char * file_name) {fMBHitConditionFileName.assign(file_name);}
  void SetHiRASiEnergyCalibrationFile(const char * file_name) {fHiRASiEnergyCalibrationFileName.assign(file_name);}
  void SetHiRACsIEnergyCalibrationFile(const char * file_name) {fHiRACsIEnergyCalibrationFileName.assign(file_name);}
  void SetHiRACsIPulserFile(const char * file_name) {fHiRACsIPulserFileName.assign(file_name);}
  void SetHiRADetectorStatusFile(const char * file_name) {fHiRADetectorStatusFileName.assign(file_name);}
  void SetHiRASiHiLowMatchingFile(const char * file_name) {fHiRASiHiLowMatchingFileName.assign(file_name);}
  void SetHiRAGeometryFile(const char * file_name) {fHiRAGeometryFileName.assign(file_name);}
  const char * GetNWAPositionCalibrationFileName() const {return fNWAPositionCalibrationFileName.c_str();}
  const char * GetNWBPositionCalibrationFileName() const {return fNWBPositionCalibrationFileName.c_str();}
  const char * GetNWATimeOffsetCalibrationFileName() const {return fNWATimeOffsetCalibrationFileName.c_str();}
  const char * GetNWBTimeOffsetCalibrationFileName() const {return fNWBTimeOffsetCalibrationFileName.c_str();}
  const char * GetNWAGainMatchingCalibrationFileName() const {return fNWAGainMatchingCalibrationFileName.c_str();}
  const char * GetNWBGainMatchingCalibrationFileName() const {return fNWBGainMatchingCalibrationFileName.c_str();}
  const char * GetNWAGeometryCalibrationFileName() const {return fNWAGeometryFileName.c_str();}
  const char * GetNWBGeometryCalibrationFileName() const {return fNWBGeometryFileName.c_str();}
  const char * GetFATimeCalibrationFileName() const {return fFATimeCalibrationFileName.c_str();}
  const char * GetFAPulseHeightCorrectionFileName() const {return fFAPulseHeightCorrectionFileName.c_str();}
  const char * GetVWGainMatchingCalibrationFileName() const {return fVWGainMatchingCalibrationFileName.c_str();}
  const char * GerMBDetectorStatusFileName() const {return fMBDetectorStatusFileName.c_str();}
  const char * GetMBGeometryFileName() const {return fMBGeometryFileName.c_str();}
  const char * GetMBImpactParameterFileName() const {return fMBImpactParameterFileName.c_str();}
  const char * GetMBHitConditionFileName() const {return fMBHitConditionFileName.c_str();}
  const char * GetHiRASiEnergyCalibrationFileName() const {return fHiRASiEnergyCalibrationFileName.c_str();}
  const char * GetHiRACsIEnergyCalibrationFileName() const {return fHiRACsIEnergyCalibrationFileName.c_str();}
  const char * GetHiRACsIPulserFileName() const {return fHiRACsIPulserFileName.c_str();}
  const char * GetHiRADetectorStatusFileName() const {return fHiRADetectorStatusFileName.c_str();}
  const char * GetHiRASiHiLowMatchingFileName() const {return fHiRASiHiLowMatchingFileName.c_str();}
  const char * GetHiRAGeometryFileName() const {return fHiRAGeometryFileName.c_str();}

  void SetEvtFilePath(const char *);                     //! Set path for evt files of the run
  void SetRunTitle(const char *);                        //! Set run title

  //void AddModuleToStackInfo(RBElectronics *);            //! Add a module to the HTDAQStackInfo object

private:
  std::string fRunTitle;                                 //!
  int fRunNumber;                                        //!
  std::string fEvtFilePath;                              //!
  std::string fPedestalsFilePath;                        //!
  std::string fMappingFilePath;                          //!
  int fNStacks;                                          //!
  bool fDAQLoaded;                                       //!
  bool fPedestalsFileSet;                                //!
  bool fMappingFileSet;                                  //!

  //E15190-Analysis-Framework data members
  std::string  fNWAPositionCalibrationFileName;
  std::string  fNWBPositionCalibrationFileName;
  std::string  fNWATimeOffsetCalibrationFileName;
  std::string  fNWBTimeOffsetCalibrationFileName;
  std::string  fNWAGainMatchingCalibrationFileName;
  std::string  fNWBGainMatchingCalibrationFileName;
  std::string  fNWAGeometryFileName;
  std::string  fNWBGeometryFileName;
  std::string  fFATimeCalibrationFileName;
  std::string  fFAPulseHeightCorrectionFileName;
  std::string  fVWGainMatchingCalibrationFileName;
  std::string  fMBDetectorStatusFileName;
  std::string  fMBGeometryFileName;
  std::string  fMBImpactParameterFileName;
  std::string  fMBHitConditionFileName;
  std::string  fHiRASiEnergyCalibrationFileName;
  std::string  fHiRACsIEnergyCalibrationFileName;
  std::string  fHiRACsIPulserFileName;
  std::string  fHiRADetectorStatusFileName;
  std::string  fHiRASiHiLowMatchingFileName;
  std::string  fHiRAGeometryFileName;

  std::vector <HTDAQStackInfo *> fStackInfo;             //!

  void ParseDefineDAQLine(const char *);
  void ParseAddDAQLine(const char *);

};

#endif