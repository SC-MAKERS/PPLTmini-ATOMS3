///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTModuleInfo.h"

///-----------
/// Constructor
///-----------
PPLTModuleInfo::PPLTModuleInfo(PPLTAddress addr) : myAddress(addr) {
  // Initialize
  memset(&this->isPressed[0], 0, sizeof(this->isPressed));
}

///-----------
/// getModuleState
///-----------
PPLTModuleState PPLTModuleInfo::getModuleState() {
  return PPLTModuleState(this->isPressed);
}

///-----------
/// updateMyButtonState
///-----------
void PPLTModuleInfo::updateMyButtonState(){
  this->devices[this->myAddress].updateButtonState();
  
  // update array for pressed info
  auto isPressed = this->devices[this->myAddress].getButtonState();
  int index = this->myAddress - 1;
  this->isPressed[index] = isPressed;
}

///-----------
/// updateMyView
///-----------
void PPLTModuleInfo::updateMyView(const PPLTViewType view){
  this->updateMyView(view, 0);
}

void PPLTModuleInfo::updateMyView(const PPLTViewType view, const PPLTViewParam param){
  this->devices[this->myAddress].setViewType(view);
  this->devices[this->myAddress].setViewParam(param);
}

///-----------
/// getMyData
///-----------
PPLTModule PPLTModuleInfo::getMyData(){
  return this->devices[this->myAddress];
}

///-----------
/// setFromSub
///-----------
void PPLTModuleInfo::setFromSub(const PPLTAddress addr, const PacketFromSub* packet){
  this->devices[addr].setButtonState(packet->nowButtonState);
  this->devices[addr].setViewType(packet->view);
  this->devices[addr].setViewParam(packet->param);

  // update array for pressed info
  int index = addr - 1;
  this->isPressed[index] = packet->nowButtonState;
}
