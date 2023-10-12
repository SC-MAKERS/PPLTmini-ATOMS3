///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_DEVICE__
#define __PPLT_DEVICE__

#include <M5Unified.h>
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTModule
///--------------------------
class PPLTModule {
// fields
private:
  PPLTButtonState buttonState;
  PPLTViewType view;
  PPLTViewParam param;

// methods
public:
  PPLTModule();
  void updateButtonState();
  PPLTButtonState getButtonState();
  PPLTViewType getViewType();
  PPLTViewParam getViewParam();

  void setButtonState(const PPLTButtonState);
  void setViewType(const PPLTViewType);
  void setViewParam(const PPLTViewParam);

};

#endif //__PPLT_DEVICE__