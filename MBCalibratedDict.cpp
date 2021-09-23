// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME MBCalibratedDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "MBCalibratedRootEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_MicroballCalibratedData(void *p = 0);
   static void *newArray_MicroballCalibratedData(Long_t size, void *p);
   static void delete_MicroballCalibratedData(void *p);
   static void deleteArray_MicroballCalibratedData(void *p);
   static void destruct_MicroballCalibratedData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MicroballCalibratedData*)
   {
      ::MicroballCalibratedData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MicroballCalibratedData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MicroballCalibratedData", ::MicroballCalibratedData::Class_Version(), "MBCalibratedRootEvent.h", 8,
                  typeid(::MicroballCalibratedData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MicroballCalibratedData::Dictionary, isa_proxy, 4,
                  sizeof(::MicroballCalibratedData) );
      instance.SetNew(&new_MicroballCalibratedData);
      instance.SetNewArray(&newArray_MicroballCalibratedData);
      instance.SetDelete(&delete_MicroballCalibratedData);
      instance.SetDeleteArray(&deleteArray_MicroballCalibratedData);
      instance.SetDestructor(&destruct_MicroballCalibratedData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MicroballCalibratedData*)
   {
      return GenerateInitInstanceLocal((::MicroballCalibratedData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::MicroballCalibratedData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr MicroballCalibratedData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MicroballCalibratedData::Class_Name()
{
   return "MicroballCalibratedData";
}

//______________________________________________________________________________
const char *MicroballCalibratedData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MicroballCalibratedData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MicroballCalibratedData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MicroballCalibratedData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MicroballCalibratedData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MicroballCalibratedData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MicroballCalibratedData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MicroballCalibratedData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void MicroballCalibratedData::Streamer(TBuffer &R__b)
{
   // Stream an object of class MicroballCalibratedData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MicroballCalibratedData::Class(),this);
   } else {
      R__b.WriteClassBuffer(MicroballCalibratedData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MicroballCalibratedData(void *p) {
      return  p ? new(p) ::MicroballCalibratedData : new ::MicroballCalibratedData;
   }
   static void *newArray_MicroballCalibratedData(Long_t nElements, void *p) {
      return p ? new(p) ::MicroballCalibratedData[nElements] : new ::MicroballCalibratedData[nElements];
   }
   // Wrapper around operator delete
   static void delete_MicroballCalibratedData(void *p) {
      delete ((::MicroballCalibratedData*)p);
   }
   static void deleteArray_MicroballCalibratedData(void *p) {
      delete [] ((::MicroballCalibratedData*)p);
   }
   static void destruct_MicroballCalibratedData(void *p) {
      typedef ::MicroballCalibratedData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MicroballCalibratedData

namespace {
  void TriggerDictionaryInitialization_MBCalibratedDict_Impl() {
    static const char* headers[] = {
"MBCalibratedRootEvent.h",
0
    };
    static const char* includePaths[] = {
"./include",
"./Nuclear_Masses",
"./HTRunInfo",
"/mnt/spirit/analysis/user/fanurs/software/python/spirit/include/",
"/mnt/spirit/analysis/user/fanurs/e15190-e14030/E15190-Unified-Analysis-Framework/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "MBCalibratedDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$MBCalibratedRootEvent.h")))  MicroballCalibratedData;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "MBCalibratedDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "MBCalibratedRootEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"MicroballCalibratedData", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MBCalibratedDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MBCalibratedDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MBCalibratedDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MBCalibratedDict() {
  TriggerDictionaryInitialization_MBCalibratedDict_Impl();
}
