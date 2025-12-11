/* Copyright 2010-2012 The MathWorks, Inc. */

#ifndef slsv_diagnostic_codegen_c_api_h
#define slsv_diagnostic_codegen_c_api_h

#include "tmwtypes.h"

#ifdef BUILDING_SL_SERVICES
 /* being included from inside sl_services module */
  #include "package.h"
  #define SL_SERVICES_PUBLISHED_C extern "C" DLL_EXPORT_SYM
#else
 /* being included from outside, such as raccel code */
  #if defined(__cplusplus)
 /* Needed for non-inlined C++ S-functions */
    #define SL_SERVICES_PUBLISHED_C extern "C"
  #else 
    #define SL_SERVICES_PUBLISHED_C extern
  #endif
#endif

#define CODEGEN_SUPPORT_ARG_NUMERIC_TYPE (int)1
#define CODEGEN_SUPPORT_ARG_STRING_TYPE (int)2
#define CODEGEN_SUPPORT_ARG_ENCODED_STRING_TYPE (int)3
#define CODEGEN_SUPPORT_ARG_ESCAPED_STRING_TYPE (int)4

SL_SERVICES_PUBLISHED_C char* CreateDiagnosticXMLSnippet(const char* id,
                                                         int nargs, ...);

SL_SERVICES_PUBLISHED_C void* CreateDiagnosticAsVoidPtr(const char* id,
                                                        int nargs, ...);

#endif /* slsv_diagnostic_codegen_c_api_h */
