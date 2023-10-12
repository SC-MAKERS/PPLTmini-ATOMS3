///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_GAME_RESULT__
#define __PPLT_APP_GAME_RESULT__

#include <M5Unified.h>
#include "PPLTApp.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTAppGameResult
///--------------------------
class PPLTAppGameResult : public PPLTApp {
// fields
private:
  bool isFinished;
  PPLTViewType resultViewType;
  PPLTViewParam successCount;

// methods
public:
  PPLTAppGameResult(PPLTConnectType, PPLTAddress, PPLTIntentParam);
  void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  void update();
  bool hasNextApp();
  PPLTAppIntentPointer getNextApp();

private:
  void changePanelsTo(const PPLTStateCode);
  void soundResult();

};

#endif //__PPLT_APP_GAME_RESULT__
