// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HTNeutronWallDict
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
#include "HTNeutronWallRootEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_HTNeutronWallData(void *p = 0);
   static void *newArray_HTNeutronWallData(Long_t size, void *p);
   static void delete_HTNeutronWallData(void *p);
   static void deleteArray_HTNeutronWallData(void *p);
   static void destruct_HTNeutronWallData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTNeutronWallData*)
   {
      ::HTNeutronWallData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTNeutronWallData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTNeutronWallData", ::HTNeutronWallData::Class_Version(), "HTNeutronWallRootEvent.h", 6,
                  typeid(::HTNeutronWallData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HTNeutronWallData::Dictionary, isa_proxy, 4,
                  sizeof(::HTNeutronWallData) );
      instance.SetNew(&new_HTNeutronWallData);
      instance.SetNewArray(&newArray_HTNeutronWallData);
      instance.SetDelete(&delete_HTNeutronWallData);
      instance.SetDeleteArray(&deleteArray_HTNeutronWallData);
      instance.SetDestructor(&destruct_HTNeutronWallData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTNeutronWallData*)
   {
      return GenerateInitInstanceLocal((::HTNeutronWallData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::HTNeutronWallData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_HTNeutronWallRootEvent(void *p);
   static void deleteArray_HTNeutronWallRootEvent(void *p);
   static void destruct_HTNeutronWallRootEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HTNeutronWallRootEvent*)
   {
      ::HTNeutronWallRootEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HTNeutronWallRootEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HTNeutronWallRootEvent", ::HTNeutronWallRootEvent::Class_Version(), "HTNeutronWallRootEvent.h", 28,
                  typeid(::HTNeutronWallRootEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HTNeutronWallRootEvent::Dictionary, isa_proxy, 4,
                  sizeof(::HTNeutronWallRootEvent) );
      instance.SetDelete(&delete_HTNeutronWallRootEvent);
      instance.SetDeleteArray(&deleteArray_HTNeutronWallRootEvent);
      instance.SetDestructor(&destruct_HTNeutronWallRootEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HTNeutronWallRootEvent*)
   {
      return GenerateInitInstanceLocal((::HTNeutronWallRootEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::HTNeutronWallRootEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr HTNeutronWallData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTNeutronWallData::Class_Name()
{
   return "HTNeutronWallData";
}

//______________________________________________________________________________
const char *HTNeutronWallData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTNeutronWallData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTNeutronWallData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTNeutronWallData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTNeutronWallData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTNeutronWallData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTNeutronWallData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTNeutronWallData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HTNeutronWallRootEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HTNeutronWallRootEvent::Class_Name()
{
   return "HTNeutronWallRootEvent";
}

//______________________________________________________________________________
const char *HTNeutronWallRootEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTNeutronWallRootEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HTNeutronWallRootEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HTNeutronWallRootEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HTNeutronWallRootEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTNeutronWallRootEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HTNeutronWallRootEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HTNeutronWallRootEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void HTNeutronWallData::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTNeutronWallData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTNeutronWallData::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTNeutronWallData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HTNeutronWallData(void *p) {
      return  p ? new(p) ::HTNeutronWallData : new ::HTNeutronWallData;
   }
   static void *newArray_HTNeutronWallData(Long_t nElements, void *p) {
      return p ? new(p) ::HTNeutronWallData[nElements] : new ::HTNeutronWallData[nElements];
   }
   // Wrapper around operator delete
   static void delete_HTNeutronWallData(void *p) {
      delete ((::HTNeutronWallData*)p);
   }
   static void deleteArray_HTNeutronWallData(void *p) {
      delete [] ((::HTNeutronWallData*)p);
   }
   static void destruct_HTNeutronWallData(void *p) {
      typedef ::HTNeutronWallData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTNeutronWallData

//______________________________________________________________________________
void HTNeutronWallRootEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class HTNeutronWallRootEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HTNeutronWallRootEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(HTNeutronWallRootEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HTNeutronWallRootEvent(void *p) {
      delete ((::HTNeutronWallRootEvent*)p);
   }
   static void deleteArray_HTNeutronWallRootEvent(void *p) {
      delete [] ((::HTNeutronWallRootEvent*)p);
   }
   static void destruct_HTNeutronWallRootEvent(void *p) {
      typedef ::HTNeutronWallRootEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HTNeutronWallRootEvent

namespace {
  void TriggerDictionaryInitialization_HTNeutronWallDict_Impl() {
    static const char* headers[] = {
"HTNeutronWallRootEvent.h",
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
#line 1 "HTNeutronWallDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$HTNeutronWallRootEvent.h")))  HTNeutronWallData;
class __attribute__((annotate("$clingAutoload$HTNeutronWallRootEvent.h")))  HTNeutronWallRootEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "HTNeutronWallDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "HTNeutronWallRootEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"HTNeutronWallData", payloadCode, "@",
"HTNeutronWallRootEvent", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HTNeutronWallDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HTNeutronWallDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HTNeutronWallDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HTNeutronWallDict() {
  TriggerDictionaryInitialization_HTNeutronWallDict_Impl();
}
