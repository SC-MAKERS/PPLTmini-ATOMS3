///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppLauncher.h"

///-----------
/// Constructor
///-----------
PPLTAppLauncher::PPLTAppLauncher(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param), selectedCode(0), isReadyToNextApp(false)
{
  // NOP
}

///-----------
/// begin
///-----------
void PPLTAppLauncher::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only
  
  // アプリケーションごとの表示内容を指定
  this->setViewTypeTo( 1, PPLTViewType::Launcher_1 );
  this->setViewTypeTo( 2, PPLTViewType::Launcher_2 );
  this->setViewTypeTo( 3, PPLTViewType::Launcher_3 );
  this->setViewTypeTo( 4, PPLTViewType::Launcher_4 );
  this->setViewTypeTo( 5, PPLTViewType::Launcher_5 );
  this->setViewTypeTo( 6, PPLTViewType::Launcher_6 );
  this->setViewTypeTo( 7, PPLTViewType::Launcher_7 );
  this->setViewTypeTo( 8, PPLTViewType::Launcher_8 );
  this->setViewTypeTo( 9, PPLTViewType::Launcher_9 );
}

///-----------
/// update
///-----------
void PPLTAppLauncher::update() {

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

  // 押下されたボタンを認識
  for(int i=0; i<MAX_MODULENUM; i++) {
    PPLTStateCode targetCode = 0x1 << i;
    if( !nowState.compareTo(targetCode) && this->isReadyToNextApp ){
      this->selectedCode = targetCode;
      break;
    }
  }

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppLauncher::hasNextApp() {
  switch(this->selectedCode) {
    case CODE_TOUCH_1:
    case CODE_TOUCH_2:
    case CODE_TOUCH_4:
    case CODE_TOUCH_5:
    case CODE_TOUCH_6:
    case CODE_TOUCH_7:
    case CODE_TOUCH_8:
    case CODE_TOUCH_9:
      return true;

    default:
      return false;
  }
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppLauncher::getNextApp() {
  switch(this->selectedCode) {
    case CODE_TOUCH_1:
      return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::GameStat));
    case CODE_TOUCH_2:
      return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::KeyPadGame));
    case CODE_TOUCH_4:
      return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::LightsOut));
    case CODE_TOUCH_5:
      return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::Demo));
    case CODE_TOUCH_6:
      return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::FlashTouch));
    case CODE_TOUCH_7:
      return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::GameReady));
    case CODE_TOUCH_8:
      return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::GameReady, 1)); // hard-mode
    case CODE_TOUCH_9:
      return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::GameReady, 2)); // super-hard-mode
    default:
      return PPLTApp::getNextApp();
  }
  
}

///-----------
/// setViewTypeTo
///-----------
void PPLTAppLauncher::setViewTypeTo(const PPLTAddress address, const PPLTViewType view) {
  PPLTApp::postPacket( PPLTPacketToSub(address, PPLTAppType::Launcher, view).getPacketData() );
}

