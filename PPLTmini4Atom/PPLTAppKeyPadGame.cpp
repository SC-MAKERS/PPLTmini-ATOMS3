///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppKeyPadGame.h"
#include <USB.h>
#include <USBHIDKeyboard.h>
static USBHIDKeyboard Keyboard;

// ボタンごとに送信する文字
static const char __targetKeys[] = {
  'z', 'x', 'c',
  'a', 's', 'd',
  'q', 'w', 'e'
};

///-----------
/// Constructor
///-----------
PPLTAppKeyPadGame::PPLTAppKeyPadGame(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param), isFinished(false), lastCode(0)
{
}

///-----------
/// begin
///-----------
void PPLTAppKeyPadGame::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only
  this->changePanelsTo( CODE_NONE );

  Keyboard.begin();
  USB.begin();
}

///-----------
/// update
///-----------
void PPLTAppKeyPadGame::update() {

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }

  // Main only
  auto nowButtons = PPLTApp::moduleInfo->getModuleState();
  auto code = nowButtons.getCode();

  if( this->lastCode == code ){
    // 前回と今回のキー状態が同じ場合は無視
    return;
  }

  // 前回のキー状態と今回のキー状態を比較して
  // 差分のあるところだけpressまたはreleaseを行う
  for(int i=0; i<MAX_MODULENUM; i++) {

    // 前回OFFだったが今回ONだったキー
    if( ((this->lastCode >> i) & 0x1) == 0x0
    &&  ((code >> i)           & 0x1) == 0x1) {
      Keyboard.press(__targetKeys[i]);   // Key Down

    // 前回ONだったが今回OFFだったキー
    }else if( ((this->lastCode >> i) & 0x1) == 0x1
    &&        ((code >> i)           & 0x1) == 0x0 ) {
      Keyboard.release(__targetKeys[i]); // Key Up
    }
  }

  // キー状態を更新
  this->lastCode = code;

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppKeyPadGame::hasNextApp() {
  return this->isFinished;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppKeyPadGame::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::Launcher));
}

///-----------
/// changePanelsTo
///-----------
void PPLTAppKeyPadGame::changePanelsTo(const PPLTStateCode nextCode) {
  for(int i=0; i<MAX_MODULENUM; i++) {
    PPLTApp::postPacket( PPLTPacketToSub(i+1, PPLTAppType::KeyPadGame, PPLTViewType::KeyPad).getPacketData() );
  }
}