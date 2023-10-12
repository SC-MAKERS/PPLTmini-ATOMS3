///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppGameReady.h"

///-----------
/// Constructor
///-----------
PPLTAppGameReady::PPLTAppGameReady(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param),
   isFinished(false), 
   finishTime(0),
   nextAppType(PPLTAppType::Launcher),
   nextAppParam(0),
   progressTime(0),
   progressCount(0)
{
  this->gameMode = param; // original:0, hard:1, superhard:2
}

///-----------
/// begin
///-----------
void PPLTAppGameReady::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only

  auto nowTime = millis();
  this->finishTime = nowTime + 30000; // 30秒（30000ms）後に終了する

  // 進行時間を描画クラスへ毎秒伝えるためのタイマーを開始
  this->progressTime = nowTime + 1000;

  // 表示内容を更新
  this->updateView();
}

///-----------
/// update
///-----------
void PPLTAppGameReady::update() {

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }

  // Main only
  auto nowState = PPLTApp::moduleInfo->getModuleState();
  auto nowTime = millis();

  // 進行状況を更新
  if (this->progressTime <= nowTime ) {
      this->progressCount++;
      this->progressTime += 1000;  // 1秒後に再設定

      // 表示内容を更新
      this->updateView();
  }
  
  if( !nowState.compareTo(CODE_LOVETOUCH) ){
    // 指定されたボタンをすべて押したときはゲームへ
    this->nextAppType = PPLTAppType::GameCountdown;
    this->nextAppParam = this->gameMode;
    this->isFinished = true;

  }else if( this->finishTime != 0 && this->finishTime <= nowTime) {
    // タイムアップしたときはメニューに戻る
    this->nextAppType = PPLTAppType::Launcher;
    this->nextAppParam = 0;
    this->isFinished = true;
  }

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppGameReady::hasNextApp() {
  return this->isFinished;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppGameReady::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(this->nextAppType, this->nextAppParam));
}

///-----------
/// setViewTypeTo
///-----------
void PPLTAppGameReady::setViewTypeTo(const PPLTAddress address, const PPLTViewType view) {
  PPLTApp::postPacket( PPLTPacketToSub(address, PPLTAppType::GameReady, view, 0).getPacketData() );
}

void PPLTAppGameReady::setViewTypeTo(const PPLTAddress address, const PPLTViewType view, const PPLTViewParam param) {
  PPLTApp::postPacket( PPLTPacketToSub(address, PPLTAppType::GameReady, view, param).getPacketData() );
}

///-----------
/// updateView
///-----------
void PPLTAppGameReady::updateView() {
  this->setViewTypeTo( 1, PPLTViewType::PPLT_Target, this->progressCount );
  this->setViewTypeTo( 2, PPLTViewType::PPLT_Blank, this->progressCount );
  this->setViewTypeTo( 3, PPLTViewType::PPLT_Target, this->progressCount );
  this->setViewTypeTo( 4, PPLTViewType::PPLT_Ready );
  this->setViewTypeTo( 5, PPLTViewType::PPLT_Ready );
  this->setViewTypeTo( 6, PPLTViewType::PPLT_Ready );
  this->setViewTypeTo( 7, PPLTViewType::PPLT_Target, this->progressCount );
  this->setViewTypeTo( 8, PPLTViewType::PPLT_Blank, this->progressCount );
  this->setViewTypeTo( 9, PPLTViewType::PPLT_Target, this->progressCount );
}