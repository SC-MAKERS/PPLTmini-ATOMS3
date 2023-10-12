///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_DEMO__
#define __PPLT_APP_DEMO__

#include <M5Unified.h>
#include "PPLTApp.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTAppDemo
///--------------------------
class PPLTAppDemo : public PPLTApp {
// fields
private:
  bool isReadyToNextApp;
  bool isFinished;

// methods
public:
  PPLTAppDemo(PPLTConnectType, PPLTAddress, PPLTIntentParam);
  void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  void update();
  bool hasNextApp();
  PPLTAppIntentPointer getNextApp();

private:
  void setViewTypeTo(PPLTAddress, PPLTViewType);
  void soundOpening();
  void soundPush();

};

#endif //__PPLT_APP_DEMO__
