///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_FLASH_TOUCH__
#define __PPLT_APP_FLASH_TOUCH__

#include <M5Unified.h>
#include "PPLTApp.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTAppFlashTouch
///--------------------------
class PPLTAppFlashTouch : public PPLTApp {
// fields
private:
  PPLTStateCode questionCode;
  PPLTStateCode selectedCode;
  bool isFinished;

// methods
public:
  PPLTAppFlashTouch(PPLTConnectType, PPLTAddress, uint8_t);
  void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  void update();
  bool hasNextApp();
  PPLTAppIntentPointer getNextApp();

private:
  void setViewTypeTo(const PPLTAddress, const PPLTViewType, const PPLTViewParam);
  void changeViewTo(const PPLTStateCode);
  void soundFailed();
  void soundClear();

};

#endif //__PPLT_APP_FLASH_TOUCH__
