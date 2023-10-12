///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_VIEW__
#define __PPLT_VIEW__

#include <M5Unified.h>
#include <memory>
#include "PPLTModuleInfo.h"
#include "PPLTTypeDef.h"

///--------------------------
/// PPLTView（抽象クラス）
///--------------------------
class PPLTView {
// fields
protected:
  PPLTAddress address;
  PPLTViewType type;
  PPLTViewParam param;
  PPLTModuleInfoPointer moduleInfo;
  PPLTButtonState buttonState;
  int height;
  int width;
  std::unique_ptr<M5Canvas> canvas;

// methods
public:
  PPLTView(PPLTAddress);
  static std::unique_ptr<PPLTView> factory(PPLTAddress);
  virtual void begin(PPLTModuleInfoPointer);
  virtual void update();
  virtual void draw() = 0;

};

#endif //__PPLT_VIEW__
