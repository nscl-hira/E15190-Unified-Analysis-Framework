// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME NWCalibratedDict
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
#include "NWCalibratedRootEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_NeutronWallCalibratedData(void *p = 0);
   static void *newArray_NeutronWallCalibratedData(Long_t size, void *p);
   static void delete_NeutronWallCalibratedData(void *p);
   static void deleteArray_NeutronWallCalibratedData(void *p);
   static void destruct_NeutronWallCalibratedData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::NeutronWallCalibratedData*)
   {
      ::NeutronWallCalibratedData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::NeutronWallCalibratedData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("NeutronWallCalibratedData", ::NeutronWallCalibratedData::Class_Version(), "NWCalibratedRootEvent.h", 6,
                  typeid(::NeutronWallCalibratedData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::NeutronWallCalibratedData::Dictionary, isa_proxy, 4,
                  sizeof(::NeutronWallCalibratedData) );
      instance.SetNew(&new_NeutronWallCalibratedData);
      instance.SetNewArray(&newArray_NeutronWallCalibratedData);
      instance.SetDelete(&delete_NeutronWallCalibratedData);
      instance.SetDeleteArray(&deleteArray_NeutronWallCalibratedData);
      instance.SetDestructor(&destruct_NeutronWallCalibratedData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::NeutronWallCalibratedData*)
   {
      return GenerateInitInstanceLocal((::NeutronWallCalibratedData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::NeutronWallCalibratedData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_VetoWallCalibratedData(void *p = 0);
   static void *newArray_VetoWallCalibratedData(Long_t size, void *p);
   static void delete_VetoWallCalibratedData(void *p);
   static void deleteArray_VetoWallCalibratedData(void *p);
   static void destruct_VetoWallCalibratedData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::VetoWallCalibratedData*)
   {
      ::VetoWallCalibratedData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::VetoWallCalibratedData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("VetoWallCalibratedData", ::VetoWallCalibratedData::Class_Version(), "NWCalibratedRootEvent.h", 50,
                  typeid(::VetoWallCalibratedData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::VetoWallCalibratedData::Dictionary, isa_proxy, 4,
                  sizeof(::VetoWallCalibratedData) );
      instance.SetNew(&new_VetoWallCalibratedData);
      instance.SetNewArray(&newArray_VetoWallCalibratedData);
      instance.SetDelete(&delete_VetoWallCalibratedData);
      instance.SetDeleteArray(&deleteArray_VetoWallCalibratedData);
      instance.SetDestructor(&destruct_VetoWallCalibratedData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::VetoWallCalibratedData*)
   {
      return GenerateInitInstanceLocal((::VetoWallCalibratedData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::VetoWallCalibratedData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_ForwardArrayCalibratedData(void *p = 0);
   static void *newArray_ForwardArrayCalibratedData(Long_t size, void *p);
   static void delete_ForwardArrayCalibratedData(void *p);
   static void deleteArray_ForwardArrayCalibratedData(void *p);
   static void destruct_ForwardArrayCalibratedData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ForwardArrayCalibratedData*)
   {
      ::ForwardArrayCalibratedData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ForwardArrayCalibratedData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ForwardArrayCalibratedData", ::ForwardArrayCalibratedData::Class_Version(), "NWCalibratedRootEvent.h", 77,
                  typeid(::ForwardArrayCalibratedData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ForwardArrayCalibratedData::Dictionary, isa_proxy, 4,
                  sizeof(::ForwardArrayCalibratedData) );
      instance.SetNew(&new_ForwardArrayCalibratedData);
      instance.SetNewArray(&newArray_ForwardArrayCalibratedData);
      instance.SetDelete(&delete_ForwardArrayCalibratedData);
      instance.SetDeleteArray(&deleteArray_ForwardArrayCalibratedData);
      instance.SetDestructor(&destruct_ForwardArrayCalibratedData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ForwardArrayCalibratedData*)
   {
      return GenerateInitInstanceLocal((::ForwardArrayCalibratedData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ForwardArrayCalibratedData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr NeutronWallCalibratedData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *NeutronWallCalibratedData::Class_Name()
{
   return "NeutronWallCalibratedData";
}

//______________________________________________________________________________
const char *NeutronWallCalibratedData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NeutronWallCalibratedData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int NeutronWallCalibratedData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::NeutronWallCalibratedData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *NeutronWallCalibratedData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NeutronWallCalibratedData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *NeutronWallCalibratedData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::NeutronWallCalibratedData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr VetoWallCalibratedData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *VetoWallCalibratedData::Class_Name()
{
   return "VetoWallCalibratedData";
}

//______________________________________________________________________________
const char *VetoWallCalibratedData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::VetoWallCalibratedData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int VetoWallCalibratedData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::VetoWallCalibratedData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *VetoWallCalibratedData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::VetoWallCalibratedData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *VetoWallCalibratedData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::VetoWallCalibratedData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ForwardArrayCalibratedData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ForwardArrayCalibratedData::Class_Name()
{
   return "ForwardArrayCalibratedData";
}

//______________________________________________________________________________
const char *ForwardArrayCalibratedData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ForwardArrayCalibratedData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ForwardArrayCalibratedData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ForwardArrayCalibratedData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ForwardArrayCalibratedData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ForwardArrayCalibratedData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ForwardArrayCalibratedData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ForwardArrayCalibratedData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void NeutronWallCalibratedData::Streamer(TBuffer &R__b)
{
   // Stream an object of class NeutronWallCalibratedData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(NeutronWallCalibratedData::Class(),this);
   } else {
      R__b.WriteClassBuffer(NeutronWallCalibratedData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_NeutronWallCalibratedData(void *p) {
      return  p ? new(p) ::NeutronWallCalibratedData : new ::NeutronWallCalibratedData;
   }
   static void *newArray_NeutronWallCalibratedData(Long_t nElements, void *p) {
      return p ? new(p) ::NeutronWallCalibratedData[nElements] : new ::NeutronWallCalibratedData[nElements];
   }
   // Wrapper around operator delete
   static void delete_NeutronWallCalibratedData(void *p) {
      delete ((::NeutronWallCalibratedData*)p);
   }
   static void deleteArray_NeutronWallCalibratedData(void *p) {
      delete [] ((::NeutronWallCalibratedData*)p);
   }
   static void destruct_NeutronWallCalibratedData(void *p) {
      typedef ::NeutronWallCalibratedData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::NeutronWallCalibratedData

//______________________________________________________________________________
void VetoWallCalibratedData::Streamer(TBuffer &R__b)
{
   // Stream an object of class VetoWallCalibratedData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(VetoWallCalibratedData::Class(),this);
   } else {
      R__b.WriteClassBuffer(VetoWallCalibratedData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_VetoWallCalibratedData(void *p) {
      return  p ? new(p) ::VetoWallCalibratedData : new ::VetoWallCalibratedData;
   }
   static void *newArray_VetoWallCalibratedData(Long_t nElements, void *p) {
      return p ? new(p) ::VetoWallCalibratedData[nElements] : new ::VetoWallCalibratedData[nElements];
   }
   // Wrapper around operator delete
   static void delete_VetoWallCalibratedData(void *p) {
      delete ((::VetoWallCalibratedData*)p);
   }
   static void deleteArray_VetoWallCalibratedData(void *p) {
      delete [] ((::VetoWallCalibratedData*)p);
   }
   static void destruct_VetoWallCalibratedData(void *p) {
      typedef ::VetoWallCalibratedData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::VetoWallCalibratedData

//______________________________________________________________________________
void ForwardArrayCalibratedData::Streamer(TBuffer &R__b)
{
   // Stream an object of class ForwardArrayCalibratedData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ForwardArrayCalibratedData::Class(),this);
   } else {
      R__b.WriteClassBuffer(ForwardArrayCalibratedData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ForwardArrayCalibratedData(void *p) {
      return  p ? new(p) ::ForwardArrayCalibratedData : new ::ForwardArrayCalibratedData;
   }
   static void *newArray_ForwardArrayCalibratedData(Long_t nElements, void *p) {
      return p ? new(p) ::ForwardArrayCalibratedData[nElements] : new ::ForwardArrayCalibratedData[nElements];
   }
   // Wrapper around operator delete
   static void delete_ForwardArrayCalibratedData(void *p) {
      delete ((::ForwardArrayCalibratedData*)p);
   }
   static void deleteArray_ForwardArrayCalibratedData(void *p) {
      delete [] ((::ForwardArrayCalibratedData*)p);
   }
   static void destruct_ForwardArrayCalibratedData(void *p) {
      typedef ::ForwardArrayCalibratedData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ForwardArrayCalibratedData

namespace {
  void TriggerDictionaryInitialization_NWCalibratedDict_Impl() {
    static const char* headers[] = {
"NWCalibratedRootEvent.h",
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
#line 1 "NWCalibratedDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$NWCalibratedRootEvent.h")))  NeutronWallCalibratedData;
class __attribute__((annotate("$clingAutoload$NWCalibratedRootEvent.h")))  VetoWallCalibratedData;
class __attribute__((annotate("$clingAutoload$NWCalibratedRootEvent.h")))  ForwardArrayCalibratedData;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "NWCalibratedDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "NWCalibratedRootEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"ForwardArrayCalibratedData", payloadCode, "@",
"NeutronWallCalibratedData", payloadCode, "@",
"VetoWallCalibratedData", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("NWCalibratedDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_NWCalibratedDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_NWCalibratedDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_NWCalibratedDict() {
  TriggerDictionaryInitialization_NWCalibratedDict_Impl();
}
