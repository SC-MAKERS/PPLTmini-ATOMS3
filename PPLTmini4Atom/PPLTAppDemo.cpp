///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppDemo.h"

///-----------
/// Constructor
///-----------
PPLTAppDemo::PPLTAppDemo(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param), isFinished(false), isReadyToNextApp(false)
{
  // NOP
}

///-----------
/// begin
///-----------
void PPLTAppDemo::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only

  // ボタンごとの表示内容を指定
  for(int i=1; i<=MAX_MODULENUM; i++) {
    this->setViewTypeTo( i, PPLTViewType::Demo );
  }
  
  // 起動音を再生
  this->soundOpening();
}

///-----------
/// update
///-----------
void PPLTAppDemo::update() {

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }

  // Main only
  auto nowState = PPLTApp::moduleInfo->getModuleState();

  // 誤操作防止のための機能
  // 何かのボタンを押しっぱなしの状態でこのAppに遷移すると
  // いきなり別のAppへ不意に遷移してしまうことを避けたい
  if( !nowState.compareTo(CODE_NONE) ){
    // いったんすべてのボタンから指が離れたことを検知してから
    // 次のAppへ遷移させるようにする
    this->isReadyToNextApp = true;
  }

  if( nowState.compareTo(CODE_NONE) && this->isReadyToNextApp ) {
    this->soundPush();
    this->isFinished = true;
  }

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppDemo::hasNextApp() {
  return this->isFinished;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppDemo::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::Launcher));
}

///-----------
/// setViewTypeTo
///-----------
void PPLTAppDemo::setViewTypeTo(const PPLTAddress address, const PPLTViewType view) {
  PPLTApp::postPacket( PPLTPacketToSub(address, PPLTAppType::Launcher, view).getPacketData() );
}

///-----------
/// soundOpening
///-----------
void PPLTAppDemo::soundOpening() {
  M5.Speaker.tone(880.000, 50);
  M5.delay(100);
  M5.Speaker.tone(1108.731, 50);
  M5.delay(100);
  M5.Speaker.tone(1318.510, 50);
  M5.delay(100);
  M5.Speaker.tone(1760.000, 50);
  M5.delay(100);
}

///-----------
/// soundPush
///-----------
void PPLTAppDemo::soundPush() {
  M5.Speaker.tone(880.000, 50);
  M5.delay(100);
  M5.Speaker.tone(1174.659, 50);
  M5.delay(100);
  M5.Speaker.tone(1479.978, 50);
  M5.delay(100);
  M5.Speaker.tone(1760.000, 50);
  M5.delay(100);
}