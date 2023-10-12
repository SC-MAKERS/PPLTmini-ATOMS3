///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppLightsOut.h"

///-----------
/// Constructor
///-----------
PPLTAppLightsOut::PPLTAppLightsOut(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param),
 isFinished(false),
 lastCode(0),
 finishTime(0),
 progressTime(0),
 progressCount(0),
 countDownTime(0),
 countDownTickNum(3) // カウントダウン秒数はデフォルト3
{
  // 初期状態はランダム生成
  this->nowState = PPLTModuleState::getRandomCode(1, MAX_MODULENUM);
}

///-----------
/// begin
///-----------
void PPLTAppLightsOut::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only

  auto nowTime = millis();
  this->finishTime = nowTime + 30000; // 30秒（30000ms）後に終了する
  this->countDownTime = this->finishTime - (1000 * this->countDownTickNum); // ラスト3秒でカウントダウン開始

  // 進行時間を描画クラスへ毎秒伝えるためのタイマーを開始
  this->progressTime = nowTime + 1000;

  this->changeViewTo( this->nowState );
}

///-----------
/// update
///-----------
void PPLTAppLightsOut::update() {

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }

  // Main only
  auto nowTime = millis();

  // 進行状況を更新
  if (this->progressTime <= nowTime ) {
    this->progressCount++;
    this->progressTime += 1000;  // 1秒後に再設定

    // 表示内容を更新
    this->changeViewTo( this->nowState );
  }
  
  if( this->finishTime != 0 && this->finishTime <= nowTime) {
    // タイムアップでゲーム終了
    this->soundFailed();
    isFinished = true;
    return;
  }

  // ラスト3秒で毎秒カウントダウン効果音を再生。
  // タイムアップの瞬間には効果音を再生させたくないので
  // countDownTickNum が > 0 のときだけ再生する。
  if (this->countDownTickNum > 0 && this->countDownTime <= nowTime ) {
    this->countDownTickNum--;     // Tick数を減らす
    this->soundCountDownTick();
    this->countDownTime += 1000;  // 1秒後に再設定
  }

  auto moduleState = PPLTApp::moduleInfo->getModuleState();
  auto nowCode = moduleState.getCode();
  if( this->lastCode == nowCode ) {
    // ボタン押下状態に変更がない場合は何もしない
    return;
  }
  this->lastCode = nowCode;

  // 状態に合わせてパネルの色を変更する
  this->updateStateWith( this->lastCode );
  this->changeViewTo( this->nowState );

  if( this->nowState == CODE_NONE ){
    // すべて消灯したらゲーム終了
    this->soundClear();
    isFinished = true;
  }

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppLightsOut::hasNextApp() {
  return this->isFinished;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppLightsOut::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::Launcher));
}

///-----------
/// updateStateWith
///-----------
bool PPLTAppLightsOut::updateStateWith(const PPLTStateCode nowCode) {

  // address 1 が押されたとき
  if( (nowCode >> 0) & 0x1 == 0x1 ) {
    //  7   8   9
    // *4*  5   6
    // *1* *2*  3
    this->nowState ^= (1 << 0); // ビット反転
    this->nowState ^= (1 << 1); // ビット反転
    this->nowState ^= (1 << 3); // ビット反転
    return true;
  }
  // address 2 が押されたとき
  else if( (nowCode >> 1) & 0x1 == 0x1 ) {
    //  7   8   9
    //  4  *5*  6
    // *1* *2* *3*
    this->nowState ^= (1 << 0); // ビット反転
    this->nowState ^= (1 << 1); // ビット反転
    this->nowState ^= (1 << 2); // ビット反転
    this->nowState ^= (1 << 4); // ビット反転
    return true;
  }
  // address 3 が押されたとき
  else if( (nowCode >> 2) & 0x1 == 0x1  ) {
    //  7   8   9
    //  4   5  *6*
    //  1  *2* *3*
    this->nowState ^= (1 << 1); // ビット反転
    this->nowState ^= (1 << 2); // ビット反転
    this->nowState ^= (1 << 5); // ビット反転
    return true;
  }
  // address 4 が押されたとき
  else if( (nowCode >> 3) & 0x1 == 0x1  ) {
    // *7*  8   9
    // *4* *5*  6 
    // *1*  2   3 
    this->nowState ^= (1 << 0); // ビット反転
    this->nowState ^= (1 << 3); // ビット反転
    this->nowState ^= (1 << 4); // ビット反転
    this->nowState ^= (1 << 6); // ビット反転
    return true;
  }
  // address 5 が押されたとき
  else if( (nowCode >> 4) & 0x1 == 0x1  ) {
    //  7  *8*  9
    // *4* *5* *6*
    //  1  *2*  3 
    this->nowState ^= (1 << 1); // ビット反転
    this->nowState ^= (1 << 3); // ビット反転
    this->nowState ^= (1 << 4); // ビット反転
    this->nowState ^= (1 << 5); // ビット反転
    this->nowState ^= (1 << 7); // ビット反転
    return true;
  }
  // address 6 が押されたとき
  else if( (nowCode >> 5) & 0x1 == 0x1  ) {
    //  7   8  *9*
    //  4  *5* *6*
    //  1   2  *3*
    this->nowState ^= (1 << 2); // ビット反転
    this->nowState ^= (1 << 4); // ビット反転
    this->nowState ^= (1 << 5); // ビット反転
    this->nowState ^= (1 << 8); // ビット反転
    return true;
  }
  // address 7 が押されたとき
  else if( (nowCode >> 6) & 0x1 == 0x1  ) {
    // *7* *8*  9
    // *4*  5   6
    //  1   2   3
    this->nowState ^= (1 << 3); // ビット反転
    this->nowState ^= (1 << 6); // ビット反転
    this->nowState ^= (1 << 7); // ビット反転
    return true;
  }
  // address 8 が押されたとき
  else if( (nowCode >> 7) & 0x1 == 0x1  ) {
    // *7* *8* *9*
    //  4  *5*  6
    //  1   2   3
    this->nowState ^= (1 << 4); // ビット反転
    this->nowState ^= (1 << 6); // ビット反転
    this->nowState ^= (1 << 7); // ビット反転
    this->nowState ^= (1 << 8); // ビット反転
    return true;
  }
  // address 9 が押されたとき
  else if( (nowCode >> 8) & 0x1 == 0x1  ) {
    //  7  *8* *9*
    //  4   5  *6*
    //  1   2   3
    this->nowState ^= (1 << 5); // ビット反転
    this->nowState ^= (1 << 7); // ビット反転
    this->nowState ^= (1 << 8); // ビット反転
    return true;
  }

  return false;
}

///-----------
/// changeViewTo
///-----------
void PPLTAppLightsOut::changeViewTo(const PPLTStateCode nextCode) {
  for(int i=0; i<MAX_MODULENUM; i++) {
    PPLTViewType targetView = PPLTViewType::LightsOut_Off;
    if( (nextCode >> i) & 0x1 == 0x1 ){
      targetView = PPLTViewType::LightsOut_On;
    }

    PPLTApp::postPacket( PPLTPacketToSub(i+1, PPLTAppType::LightsOut, targetView, this->progressCount).getPacketData() );
  }
}

///-----------
/// soundClear
///-----------
void PPLTAppLightsOut::soundClear() {
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

///-----------
/// soundFailed
///-----------
void PPLTAppLightsOut::soundFailed() {
  M5.Speaker.tone(1760.000, 500);
  M5.delay(500);
  M5.Speaker.tone(880.000, 500);
  M5.delay(500);
}

///-----------
/// soundCountDownTick
///-----------
void PPLTAppLightsOut::soundCountDownTick() {
  M5.Speaker.tone(880.000, 100);
  M5.delay(100);
}