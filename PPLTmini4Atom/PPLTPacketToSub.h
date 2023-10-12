///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_QUEUE_DATA__
#define __PPLT_QUEUE_DATA__

#include <memory>
#include "PPLTTypeDef.h"

using PPLTPacketToSubPointer = std::shared_ptr<PacketToSub>;

///--------------------------
/// PPLTPacketToSub
///--------------------------
class PPLTPacketToSub {
private:
  PPLTAddress target;
  PPLTAppType app;
  PPLTViewType view;
  PPLTViewParam param;

// methods
public:
  PPLTPacketToSub(PPLTAddress, PPLTAppType, PPLTViewType);
  PPLTPacketToSub(PPLTAddress, PPLTAppType, PPLTViewType, PPLTViewParam);
  PPLTPacketToSubPointer getPacketData();
};

#endif //__PPLT_QUEUE_DATA__
