///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppGameCountdown.h"

///-----------
/// Constructor
///-----------
PPLTAppGameCountdown::PPLTAppGameCountdown(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param), finishTime(0), nextCountTime(0), count(0)
{
  this->gameMode = param; // original:0, hard:1, superhard:2
}

///-----------
/// begin
///-----------
void PPLTAppGameCountdown::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only

  this->count = 3;  // 3カウント
  this->changeViewTo( CODE_NONE );

  auto nowTime = millis();
  this->finishTime = nowTime + 4000; // 4秒（4000ms）後に終了する
  this->nextCountTime = nowTime + 1000;
}

///-----------
/// update
///-----------
void PPLTAppGameCountdown::update() {

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }

  // Main only
  auto nowState = PPLTApp::moduleInfo->getModuleState();

  auto nowTime = millis();
  if( this->count > 0 && this->nextCountTime <= nowTime) {
    this->changeViewTo( CODE_FULLTOUCH );

    // カウントダウン
    this->count--;
    this->nextCountTime += 1000; // 1秒後に再設定
    this->soundCountDown();

  }else if(this->count == 0 && this->nextCountTime <= nowTime){
    this->changeViewTo( CODE_FULLTOUCH );

    // スタート
    this->soundGo();
  }

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppGameCountdown::hasNextApp() {
  auto nowTime = millis();
  if( this->finishTime != 0 && this->finishTime <= nowTime) {
    // 終了予定時間を超えたら次のアプリケーションへ
    return true;
  }
  return false;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppGameCountdown::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::GamePlaying, this->gameMode));
}

///-----------
/// changeViewTo
///-----------
void PPLTAppGameCountdown::changeViewTo(const PPLTStateCode nextCode) {
  for(int i=0; i<MAX_MODULENUM; i++) {
    PPLTViewType targetView = PPLTViewType::Clear;
    if( (nextCode >> i) & 0x1 == 0x1 ){
      targetView = PPLTViewType::PPLT_Countdown;
    }
    PPLTApp::postPacket( PPLTPacketToSub(i+1, PPLTAppType::GameCountdown, targetView, this->count).getPacketData() );
  }
}

///-----------
/// soundCountDown
///-----------
void PPLTAppGameCountdown::soundCountDown() {
  M5.Speaker.tone(880.000, 50);
  M5.delay(50);
}

///-----------
/// soundGo
///-----------
void PPLTAppGameCountdown::soundGo() {
  M5.Speaker.tone(1760.000, 250);
  M5.delay(250);
}