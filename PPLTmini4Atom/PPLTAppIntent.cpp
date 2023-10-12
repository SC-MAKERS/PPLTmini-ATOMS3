///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppIntent.h"

///-----------
/// Constructor
///-----------
PPLTAppIntent::PPLTAppIntent(PPLTAppType type) 
: type(type), param(0)
{
  // NOP
}

///-----------
/// Constructor
///-----------
PPLTAppIntent::PPLTAppIntent(PPLTAppType type, PPLTIntentParam param) 
: type(type), param(param)
{
  // NOP
}

///-----------
/// getType
///-----------
PPLTAppType PPLTAppIntent::getType() {
  return this->type;
}

///-----------
/// getParam
///-----------
uint8_t PPLTAppIntent::getParam() {
  return this->param;
}