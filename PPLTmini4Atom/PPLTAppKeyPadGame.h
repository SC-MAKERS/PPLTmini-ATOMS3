///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_KEYPAD_GAME__
#define __PPLT_APP_KEYPAD_GAME__

#include <M5Unified.h>
#include "PPLTApp.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTAppKeyPadGame
///--------------------------
class PPLTAppKeyPadGame : public PPLTApp {
// fields
private:
  bool isFinished;
  PPLTStateCode lastCode;

// methods
public:
  PPLTAppKeyPadGame(PPLTConnectType, PPLTAddress, PPLTIntentParam);
  void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  void update();
  bool hasNextApp();
  PPLTAppIntentPointer getNextApp();

private:
  void changePanelsTo(const PPLTStateCode);

};

#endif //__PPLT_APP_KEYPAD_GAME__
