///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_CONNECT_SUB__
#define __PPLT_CONNECT_SUB__

#include <M5Unified.h>
#include <Wire.h>
#include "PPLTConnect.h"

///--------------------------
/// PPLTConnectSub
///--------------------------
class PPLTConnectSub : public PPLTConnect {
// fields
private:
  PPLTAddress address;
  PPLTModuleInfoPointer moduleInfo;

// methods
public:
  PPLTConnectSub(PPLTAddress);
  bool begin(PPLTModuleInfoPointer);
  void update();
  void postData(PPLTPacketToSubPointer);

private:
  static void onReceive(int);
  static void onRequest();

};

#endif //__PPLT_CONNECT_SUB__