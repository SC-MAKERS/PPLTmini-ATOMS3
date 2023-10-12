///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_GAME_PLAYING__
#define __PPLT_APP_GAME_PLAYING__

#include <M5Unified.h>
#include "PPLTApp.h"
#include "PPLTTypeDef.h"
#include "PPLTRecord.h"

///--------------------------
/// PPLTAppGamePlaying
///--------------------------
class PPLTAppGamePlaying : public PPLTApp {
// fields
private:
  uint8_t gameMode;
  PPLTStateCode targetCode;
  unsigned long finishTime;
  bool isFinished;
  uint8_t touchCount;
  unsigned long progressTime;
  uint8_t progressCount;
  unsigned long forceShuffleTime;
  unsigned long countDownTime;
  int countDownTickNum;

// methods
public:
  PPLTAppGamePlaying(PPLTConnectType, PPLTAddress, PPLTIntentParam);
  void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  void update();
  bool hasNextApp();
  PPLTAppIntentPointer getNextApp();

private:
  PPLTStateCode getNextRandomCode();
  void changeViewTo(const PPLTStateCode);
  void clearView();
  void soundTouchOK();
  void soundForceShuffle();
  void soundCountDownTick();

};

#endif //__PPLT_APP_GAME_PLAYING__
