///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTModule.h"

///-----------
/// Constructor
///-----------
PPLTModule::PPLTModule() : buttonState(PPLTButtonState::Off), view(PPLTViewType::Scanning) {
}

///-----------
/// updateButtonState
///-----------
void PPLTModule::updateButtonState() {
  // ボタン押下状態を更新
  auto state = M5.BtnA.isPressed()  ? PPLTButtonState::Pressed
                                    : PPLTButtonState::Off;
  this->buttonState = state;
}

///-----------
/// getButtonState
///-----------
PPLTButtonState PPLTModule::getButtonState() {
  return this->buttonState;
}

///-----------
/// getViewType
///-----------
PPLTViewType PPLTModule::getViewType() {
  return this->view;
}

///-----------
/// getViewParam
///-----------
PPLTViewParam PPLTModule::getViewParam() {
  return this->param;
}

///-----------
/// setButtonState
///-----------
void PPLTModule::setButtonState(const PPLTButtonState state) {
  // ボタン押下状態を更新
  this->buttonState = state;
}

///-----------
/// setViewType
///-----------
void PPLTModule::setViewType(const PPLTViewType view) {
  // 描画タイプを更新
  this->view = view;
}

///-----------
/// setViewParam
///-----------
void PPLTModule::setViewParam(const PPLTViewParam param) {
  // 描画用パラメータを更新
  this->param = param;
}
