///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppGameResult.h"

///-----------
/// Constructor
///-----------
PPLTAppGameResult::PPLTAppGameResult(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param), isFinished(false), successCount(param)
{
  // ゲーム結果（タッチ成功回数）に応じてモードを変える
  // 判断基準は初代Miniのアルゴリズムに準拠
  if( this->successCount < 8 ) {
    this->resultViewType = PPLTViewType::PPLT_ResultBad;
  }else if( this->successCount < 16 ) {
    this->resultViewType = PPLTViewType::PPLT_ResultGood;
  }else if( this->successCount < 24 ){
    this->resultViewType = PPLTViewType::PPLT_ResultGreat;
  }else{
    this->resultViewType = PPLTViewType::PPLT_ResultExcellent;
  }

}

///-----------
/// begin
///-----------
void PPLTAppGameResult::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only

  this->changePanelsTo( CODE_SIDETOUCH );
  this->soundResult();
}

///-----------
/// update
///-----------
void PPLTAppGameResult::update() {

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }

  // Main only
  auto nowState = PPLTApp::moduleInfo->getModuleState();

  if( !nowState.compareTo(CODE_SIDETOUCH) ){
    isFinished = true;
  }

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppGameResult::hasNextApp() {
  return this->isFinished;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppGameResult::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::Launcher));
}

///-----------
/// changePanelsTo
///-----------
void PPLTAppGameResult::changePanelsTo(const PPLTStateCode nextCode) {
  for(int i=0; i<MAX_MODULENUM; i++) {
    PPLTApp::postPacket( PPLTPacketToSub(i+1, PPLTAppType::GameResult, this->resultViewType, this->successCount).getPacketData() );
  }
}

///-----------
/// soundResult
///-----------
void PPLTAppGameResult::soundResult() {
  switch(this->resultViewType) {
    case PPLTViewType::PPLT_ResultExcellent:
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
      break;

    case PPLTViewType::PPLT_ResultGreat:
      M5.Speaker.tone(1479.978, 100);
      M5.delay(100);
      M5.Speaker.tone(1864.655, 100);
      M5.delay(100);
      M5.Speaker.tone(2349.318, 100);
      M5.delay(100);
      M5.Speaker.tone(1567.982, 100);
      M5.delay(100);
      M5.Speaker.tone(1975.533, 100);
      M5.delay(100);
      M5.Speaker.tone(2489.016, 100);
      M5.delay(100);
      break;

    case PPLTViewType::PPLT_ResultGood:
      M5.Speaker.tone(1318.510, 250);
      M5.delay(250);
      M5.Speaker.tone(1567.982, 250);
      M5.delay(250);
      M5.Speaker.tone(2093.005, 500);
      M5.delay(500);
      break;

    case PPLTViewType::PPLT_ResultBad:
      M5.Speaker.tone(1760.000, 500);
      M5.delay(500);
      M5.Speaker.tone(880.000, 500);
      M5.delay(500);
      break;
    default:
      break;
  }
}