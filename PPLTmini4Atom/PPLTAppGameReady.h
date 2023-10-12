///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_GAME_READY__
#define __PPLT_APP_GAME_READY__

#include <M5Unified.h>
#include "PPLTApp.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTAppGameReady
///--------------------------
class PPLTAppGameReady : public PPLTApp {
// fields
private:
  bool isFinished;
  uint8_t gameMode;
  PPLTAppType nextAppType;
  PPLTIntentParam nextAppParam;
  unsigned long finishTime;
  unsigned long progressTime;
  uint8_t progressCount;

// methods
public:
  PPLTAppGameReady(PPLTConnectType, PPLTAddress, PPLTIntentParam);
  void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  void update();
  bool hasNextApp();
  PPLTAppIntentPointer getNextApp();

private:
  void setViewTypeTo(const PPLTAddress, const PPLTViewType);
  void setViewTypeTo(const PPLTAddress, const PPLTViewType, const PPLTViewParam);
  void updateView();

};

#endif //__PPLT_APP_GAME_READY__
