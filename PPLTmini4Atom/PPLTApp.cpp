///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTApp.h"
#include "PPLTAppDemo.h"
#include "PPLTAppLauncher.h"
#include "PPLTAppGameReady.h"
#include "PPLTAppGameCountdown.h"
#include "PPLTAppGamePlaying.h"
#include "PPLTAppGameResult.h"
#include "PPLTAppGameStat.h"
#include "PPLTAppLightsOut.h"
#include "PPLTAppFlashTouch.h"
#include "PPLTAppKeyPadGame.h"

///-----------
/// Constructor
///-----------
PPLTApp::PPLTApp(PPLTConnectType conType, PPLTAddress addr, PPLTIntentParam param)
: type(conType), address(addr)
{
  // NOP
}

///-----------
/// factory
///-----------
std::unique_ptr<PPLTApp> PPLTApp::factory(PPLTConnectType conType, PPLTAddress addr, PPLTAppType type) {
  auto intent = PPLTAppIntentPointer(new PPLTAppIntent(type, 0));
  return PPLTApp::factory(conType, addr, intent);
}

///-----------
/// factory
///-----------
std::unique_ptr<PPLTApp> PPLTApp::factory(PPLTConnectType conType, PPLTAddress addr, PPLTAppIntentPointer intent) {
  // PPLTAppIntentで指定されたアプリケーションタイプ、パラメータに応じた
  // PPLTApp系クラスのインスタンスを生成して返却する。
  // newしたクラスのインスタンスが不要になった時自動的に開放されるようにunique_ptrを使用。
  switch(intent->getType()){
    case PPLTAppType::Demo:
      return std::unique_ptr<PPLTApp>(new PPLTAppDemo(conType, addr, intent->getParam()));
    case PPLTAppType::GameReady:
      return std::unique_ptr<PPLTApp>(new PPLTAppGameReady(conType, addr, intent->getParam()));
    case PPLTAppType::GameCountdown:
      return std::unique_ptr<PPLTApp>(new PPLTAppGameCountdown(conType, addr, intent->getParam()));
    case PPLTAppType::GameResult:
      return std::unique_ptr<PPLTApp>(new PPLTAppGameResult(conType, addr, intent->getParam()));
    case PPLTAppType::GamePlaying:
      return std::unique_ptr<PPLTApp>(new PPLTAppGamePlaying(conType, addr, intent->getParam()));
    case PPLTAppType::GameStat:
      return std::unique_ptr<PPLTApp>(new PPLTAppGameStat(conType, addr, intent->getParam()));
    case PPLTAppType::LightsOut:
      return std::unique_ptr<PPLTApp>(new PPLTAppLightsOut(conType, addr, intent->getParam()));
    case PPLTAppType::FlashTouch:
      return std::unique_ptr<PPLTApp>(new PPLTAppFlashTouch(conType, addr, intent->getParam()));
    case PPLTAppType::KeyPadGame:
      return std::unique_ptr<PPLTApp>(new PPLTAppKeyPadGame(conType, addr, intent->getParam()));
    default:
      return std::unique_ptr<PPLTApp>(new PPLTAppLauncher(conType, addr, intent->getParam()));
  }
}

///-----------
/// begin
///-----------
void PPLTApp::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  this->queue = queue;
  this->moduleInfo = moduleInfo;
}

///-----------
/// hasNextApp
///-----------
bool PPLTApp::hasNextApp() {
  return false;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTApp::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::Demo));
}

///-----------
/// postPacket
///-----------
void PPLTApp::postPacket(PPLTPacketToSubPointer packet) {
  if( this->type == PPLTConnectType::Sub ) {
    // Subモジュールは送信機能を持たない
    return;
  }
  // Queueにパケットを追加しておけば
  // PPLTConnectクラスが自動的にそれを配信する
  this->queue->push( packet );
}
