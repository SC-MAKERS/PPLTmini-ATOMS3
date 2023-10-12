///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTView.h"
#include "PPLTViewSample.h"

///-----------
/// Constructor
///-----------
PPLTView::PPLTView(PPLTAddress addr) : address(addr), type(PPLTViewType::Error), param(0)
{
  // NOP
}

///-----------
/// factory
///-----------
std::unique_ptr<PPLTView> PPLTView::factory(PPLTAddress addr) {
  // 描画処理をアレンジしたい場合はPPLTViewSampleクラス自体をそのまま改造しても良いし
  // PPLTViewクラスを継承した別のクラスを作ってこの部分を置き換えても良い。
  return std::unique_ptr<PPLTView>(new PPLTViewSample(addr));
}

///-----------
/// begin
///-----------
void PPLTView::begin(PPLTModuleInfoPointer moduleInfo) {

  // 自デバイスに関する情報はmoduleInfoを経由して得る。
  // moduleInfoの内部情報を更新するのは別タスクである。
  this->moduleInfo = moduleInfo;

  // Set Display size
  this->height = M5.Display.height();
  this->width = M5.Display.width();

  // Initizalize Text size
  M5.Display.setTextSize(3);
  M5.Display.setRotation(2); // 2: flipped

  // Initizalize Double Buffering
  this->canvas = std::unique_ptr<M5Canvas>( new M5Canvas() );
  this->canvas->setPsram(false);
  this->canvas->createSprite(this->width, this->height);
}

///-----------
/// update
///-----------
void PPLTView::update() {
  // PPLTView::moduleInfoから得た情報を使って
  // 描画に必要な内部情報を更新する
  auto myData = PPLTView::moduleInfo->getMyData();
  this->type = myData.getViewType();
  this->param = myData.getViewParam();
  this->buttonState = myData.getButtonState();
}
