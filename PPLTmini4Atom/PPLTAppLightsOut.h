///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_LIGHTS_OUT__
#define __PPLT_APP_LIGHTS_OUT__

#include <M5Unified.h>
#include "PPLTApp.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTAppLightsOut
///--------------------------
class PPLTAppLightsOut : public PPLTApp {
// fields
private:
  PPLTStateCode lastCode;
  PPLTStateCode nowState;
  bool isFinished;
  unsigned long finishTime;
  unsigned long progressTime;
  uint8_t progressCount;
  unsigned long countDownTime;
  int countDownTickNum;

// methods
public:
  PPLTAppLightsOut(PPLTConnectType, PPLTAddress, uint8_t);
  void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  void update();
  bool hasNextApp();
  PPLTAppIntentPointer getNextApp();

private:
  bool updateStateWith(const PPLTStateCode);
  void changeViewTo(const PPLTStateCode);
  void soundClear();
  void soundFailed();
  void soundCountDownTick();

};

#endif //__PPLT_APP_LIGHTS_OUT__
