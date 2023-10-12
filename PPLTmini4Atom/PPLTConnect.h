///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_CONNECT__
#define __PPLT_CONNECT__

#include <M5Unified.h>
#include <Wire.h>
#include <memory>
#include "PPLTModuleInfo.h"
#include "PPLTPacketToSub.h"
#include "PPLTTypeDef.h"

// I2C通信で使用するピン番号。ATOM S3以外のデバイスを使う場合は要変更。
#define SDA_PIN (38)
#define SCL_PIN (39)

///--------------------------
/// PPLTConnect（抽象クラス）
///--------------------------
class PPLTConnect {

// methods
public:
  static std::unique_ptr<PPLTConnect> factory(PPLTConnectType, PPLTAddress);
  virtual bool begin(PPLTModuleInfoPointer) = 0;
  virtual void update() = 0;
  virtual void postData(PPLTPacketToSubPointer) = 0;

};

#endif //__PPLT_CONNECT__