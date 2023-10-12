///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_DEVICE_INFO__
#define __PPLT_DEVICE_INFO__

#include <memory>
#include <unordered_map>
#include <M5Unified.h>
#include "PPLTModule.h"
#include "PPLTModuleState.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTModuleInfo
///--------------------------
class PPLTModuleInfo {
// fields
private:
  PPLTAddress myAddress;
  std::unordered_map<PPLTAddress, PPLTModule> devices;
  PPLTButtonState isPressed[MAX_MODULENUM];

// methods
public:
  PPLTModuleInfo(PPLTAddress);

  // Appクラスが使う
  PPLTModuleState getModuleState();

  // Viewクラスが使う
  void updateMyButtonState();
  void updateMyView(const PPLTViewType);
  void updateMyView(const PPLTViewType, const PPLTViewParam);
  PPLTModule getMyData();

  // Connectクラスが使う
  void setFromSub(const PPLTAddress, const PacketFromSub*);

};

using PPLTModuleInfoPointer = std::shared_ptr<PPLTModuleInfo>;

#endif //__PPLT_DEVICE_INFO__