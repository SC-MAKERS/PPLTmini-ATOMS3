///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_CONNECT_MAIN__
#define __PPLT_CONNECT_MAIN__

#include <M5Unified.h>
#include <Wire.h>
#include "PPLTConnect.h"

///--------------------------
/// PPLTConnectMain
///--------------------------
class PPLTConnectMain : public PPLTConnect {
// fields
private:
  PPLTAddress address;
  PPLTModuleInfoPointer moduleInfo;
  uint8_t enabledSub[MAX_MODULENUM];

// methods
public:
  PPLTConnectMain(PPLTAddress);
  bool begin(PPLTModuleInfoPointer);
  void update();
  void postData(PPLTPacketToSubPointer);

private:
  void scanAll();
  void scanOnlyEnabled();

};

#endif //__PPLT_CONNECT_MAIN__