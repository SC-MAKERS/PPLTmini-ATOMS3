///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTPacketToSub.h"

///-----------
/// Constructor
///-----------
PPLTPacketToSub::PPLTPacketToSub(PPLTAddress addr, PPLTAppType app, PPLTViewType view)
 : PPLTPacketToSub(addr, app, view, 0)
{
  // NOP
}

///-----------
/// Constructor
///-----------
PPLTPacketToSub::PPLTPacketToSub(PPLTAddress addr, PPLTAppType app, PPLTViewType view, PPLTViewParam param)
 : target(addr), app(app), view(view), param(param)
{
  // NOP
}

///-----------
/// begin
///-----------
PPLTPacketToSubPointer PPLTPacketToSub::getPacketData() {
  auto packet = PPLTPacketToSubPointer(new PacketToSub());
  packet->target = this->target;
  packet->app = this->app;
  packet->view = this->view;
  packet->param = this->param;
  return packet;
}
