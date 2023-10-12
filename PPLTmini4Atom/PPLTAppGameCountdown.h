///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_GAME_COUNTDOWN__
#define __PPLT_APP_GAME_COUNTDOWN__

#include <M5Unified.h>
#include "PPLTApp.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTAppGameCountdown
///--------------------------
class PPLTAppGameCountdown : public PPLTApp {
// fields
private:
  uint8_t gameMode;
  unsigned long finishTime;
  unsigned long nextCountTime;
  uint8_t count;

// methods
public:
  PPLTAppGameCountdown(PPLTConnectType, PPLTAddress, uint8_t);
  void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  void update();
  bool hasNextApp();
  PPLTAppIntentPointer getNextApp();

private:
  void changeViewTo(const PPLTStateCode);
  void soundCountDown();
  void soundGo();

};

#endif //__PPLT_APP_GAME_COUNTDOWN__
