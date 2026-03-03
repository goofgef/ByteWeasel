#ifdef _WIN32
#ifdef ZAGMATE_EXPORTS
  #define ZAGMATE_API __declspec(dllexport)
#else
  #define ZAGMATE_API __declspec(dllimport)
#endif
#else
#define ZAGMATE_API __attribute__((visibility("default")))
#endif

#ifndef ZAGMATE_ZAGMATE_BUILTIN_H
#define ZAGMATE_ZAGMATE_BUILTIN_H
#include "zagmate.h"

ZAGMATE_API int add(VM* vm, Instruction* instruction);
ZAGMATE_API int sub(VM* vm, Instruction* instruction);

#endif //ZAGMATE_ZAGMATE_BUILTIN_H