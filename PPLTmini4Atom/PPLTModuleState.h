///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_MODLUE_STATE__
#define __PPLT_MODLUE_STATE__

#include <M5Unified.h>
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTModuleState
///--------------------------
class PPLTModuleState {
// fields
private:
  PPLTStateCode stateCode;

// methods
public:
  PPLTModuleState(const PPLTButtonState*);
  PPLTModuleState(const PPLTStateCode);
  PPLTStateCode getCode();
  int compareTo(const PPLTStateCode);

  static PPLTStateCode getRandomCode();
  static PPLTStateCode getRandomCode(const int, const int);

private:
  int compareTo(const PPLTModuleState);

};

#endif //__PPLT_MODLUE_STATE__