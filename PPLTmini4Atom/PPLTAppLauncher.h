///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_LAUNCHER__
#define __PPLT_APP_LAUNCHER__

#include <memory>
#include <M5Unified.h>
#include "PPLTTypeDef.h"

#include "PPLTApp.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTAppLauncher
///--------------------------
class PPLTAppLauncher : public PPLTApp {
// fields
private:
  bool isReadyToNextApp;
  PPLTStateCode selectedCode;

// methods
public:
  PPLTAppLauncher(PPLTConnectType, PPLTAddress, PPLTIntentParam);
  void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  void update();
  bool hasNextApp();
  PPLTAppIntentPointer getNextApp();

private:
  void setViewTypeTo(const PPLTAddress, const PPLTViewType);

};

#endif //__PPLT_APP_LAUNCHER__
