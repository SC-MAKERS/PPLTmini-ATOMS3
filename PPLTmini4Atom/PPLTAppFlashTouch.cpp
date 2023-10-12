///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppFlashTouch.h"

///-----------
/// Constructor
///-----------
PPLTAppFlashTouch::PPLTAppFlashTouch(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param), isFinished(false), selectedCode(0)
{
  // 初期状態はランダム生成
  this->questionCode = PPLTModuleState::getRandomCode();
}

///-----------
/// begin
///-----------
void PPLTAppFlashTouch::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only

  // 出題開始
  for(int i=0; i<MAX_MODULENUM; i++) {
    auto targetAddress = i + 1;
    this->setViewTypeTo( targetAddress, PPLTViewType::FlashTouch_Question, 0 );
  }
  M5.delay(1000);

  // 押してほしいボタンをフラッシュ
  for(int i=0; i<MAX_MODULENUM; i++) {
    if( (this->questionCode >> i) & 0x1 == 0x1 ){
      auto targetAddress = i + 1;
      this->setViewTypeTo( targetAddress, PPLTViewType::FlashTouch_Question, 1 );
      M5.delay(100);
      this->setViewTypeTo( targetAddress, PPLTViewType::FlashTouch_Question, 0 );
    }
  }
  M5.delay(1000);

  // 解答モードへ
  this->changeViewTo( this->questionCode );
}

///-----------
/// update
///-----------
void PPLTAppFlashTouch::update() {

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }

  // Main only
  auto moduleState = PPLTApp::moduleInfo->getModuleState();
  auto nowCode = moduleState.getCode();
  if( this->selectedCode == nowCode ) {
    // ボタン押下状態に変更がない場合は何もしない
    return;
  }
  this->selectedCode = nowCode;

  if( (this->questionCode|this->selectedCode) != this->questionCode ){
    // 設問と異なるボタンがタッチされている場合はエラー音を再生
    this->soundFailed();
  }

  if( (this->questionCode&this->selectedCode) == this->questionCode ){
    // 設問と全く同じボタンがタッチされたらゲーム終了
    this->soundClear();
    isFinished = true;
  }

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppFlashTouch::hasNextApp() {
  return this->isFinished;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppFlashTouch::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::Launcher));
}

///-----------
/// setViewTypeTo
///-----------
void PPLTAppFlashTouch::setViewTypeTo(const PPLTAddress address, const PPLTViewType view, const PPLTViewParam param) {
  PPLTApp::postPacket( PPLTPacketToSub(address, PPLTAppType::Launcher, view, param).getPacketData() );
}

///-----------
/// changeViewTo
///-----------
void PPLTAppFlashTouch::changeViewTo(const PPLTStateCode nextCode) {
  for(int i=0; i<MAX_MODULENUM; i++) {
    PPLTViewType targetView = PPLTViewType::FlashTouch_AnswerFailed;
    if( (nextCode >> i) & 0x1 == 0x1 ){
      targetView = PPLTViewType::FlashTouch_AnswerSuccess;
    }

    PPLTApp::postPacket( PPLTPacketToSub(i+1, PPLTAppType::FlashTouch, targetView).getPacketData() );
  }
}

///-----------
/// soundFailed
///-----------
void PPLTAppFlashTouch::soundFailed() {
  M5.Speaker.tone(880.000, 100);
  M5.delay(100);
}

///-----------
/// soundClear
///-----------
void PPLTAppFlashTouch::soundClear() {
  M5.Speaker.tone(1864.655, 100);
  M5.delay(100);
  M5.Speaker.tone(2349.318, 100);
  M5.delay(100);
  M5.Speaker.tone(2793.826, 100);
  M5.delay(100);
  M5.Speaker.tone(3729.310, 100);
  M5.delay(100);
  M5.Speaker.tone(2793.826, 100);
  M5.delay(100);
  M5.Speaker.tone(2349.318, 100);
  M5.delay(100);
  M5.Speaker.tone(1864.655, 100);
  M5.delay(100);
  M5.Speaker.tone(2349.318, 100);
  M5.delay(100);
  M5.Speaker.tone(2793.826, 100);
  M5.delay(100);
  M5.Speaker.tone(3729.310, 500);
  M5.delay(500);
}