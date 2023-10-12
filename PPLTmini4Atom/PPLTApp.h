///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP__
#define __PPLT_APP__

#include <memory>
#include <queue>
#include <M5Unified.h>
#include "PPLTModuleInfo.h"
#include "PPLTPacketToSub.h"
#include "PPLTAppIntent.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTApp（抽象クラス）
///--------------------------
class PPLTApp {
protected:
  PPLTAddress address;
  PPLTConnectType type;
  std::queue<PPLTPacketToSubPointer>* queue;
  PPLTModuleInfoPointer moduleInfo;

// methods
public:
  PPLTApp(PPLTConnectType, PPLTAddress, PPLTIntentParam);
  static std::unique_ptr<PPLTApp> factory(PPLTConnectType, PPLTAddress, PPLTAppType);
  static std::unique_ptr<PPLTApp> factory(PPLTConnectType, PPLTAddress, PPLTAppIntentPointer);
  virtual void begin(std::queue<PPLTPacketToSubPointer>*, PPLTModuleInfoPointer);
  virtual void update() = 0;
  virtual bool hasNextApp();
  virtual PPLTAppIntentPointer getNextApp();
protected:
  virtual void postPacket(PPLTPacketToSubPointer);

};

#endif //__PPLT_APP__