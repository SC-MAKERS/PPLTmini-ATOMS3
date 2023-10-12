///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppGamePlaying.h"

///-----------
/// Constructor
///-----------
PPLTAppGamePlaying::PPLTAppGamePlaying(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param),
   targetCode(CODE_LOVETOUCH),
   finishTime(0),
   isFinished(false),
   touchCount(0),
   progressTime(0),
   progressCount(0),
   forceShuffleTime(0),
   countDownTime(0),
   countDownTickNum(3) // カウントダウン秒数はデフォルト3
{
  this->gameMode = param; // original:0, hard:1, superhard:2
}

///-----------
/// begin
///-----------
void PPLTAppGamePlaying::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only

  auto nowTime = millis();
  this->finishTime = nowTime + 30000; // 30秒（30000ms）後に終了する
  this->countDownTime = this->finishTime - (1000 * this->countDownTickNum); // ラスト3秒でカウントダウン開始
  this->changeViewTo( this->getNextRandomCode() );

  // 進行時間を描画クラスへ毎秒伝えるためのタイマーを開始
  this->progressTime = nowTime + 1000;
  
  if( this->gameMode != 0 ) {
    // オリジナルモード以外の場合は毎秒変化させるためのタイマーを開始
    this->forceShuffleTime = nowTime + 1000;
  }
}

///-----------
/// update
///-----------
void PPLTAppGamePlaying::update() {

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }

  // Main only
  auto nowState = PPLTApp::moduleInfo->getModuleState();
  auto nowTime = millis();

  if( !nowState.compareTo(this->targetCode) ){
    this->touchCount++; // タッチ数を数える
    this->soundTouchOK();

    if( this->gameMode != 0 ) {
      // オリジナルモード以外の場合は毎秒変化させるためのタイマーを更新
      this->forceShuffleTime = nowTime + 1000;
    }

    this->changeViewTo( this->getNextRandomCode() );
  }

  // 進行状況を更新
  if (this->progressTime <= nowTime ) {
      this->progressCount++;
      this->progressTime += 1000;  // 1秒後に再設定

      // 描画クラスに現在の表示内容を再送信
      this->changeViewTo( this->targetCode );
  }

  // ラスト3秒で毎秒カウントダウン効果音を再生。
  // タイムアップの瞬間には効果音を再生させたくないので
  // countDownTickNum が > 0 のときだけ再生する。
  if (this->countDownTickNum > 0 && this->countDownTime <= nowTime ) {
      this->countDownTickNum--;     // Tick数を減らす
      this->soundCountDownTick();
      this->countDownTime += 1000;  // 1秒後に再設定
  }
  
  // オリジナルモード以外のときはターゲットとなるボタン位置を毎秒変化させる
  if( this->gameMode != 0 && this->forceShuffleTime <= nowTime) {
    
    if( this->forceShuffleTime <= nowTime) {
      this->changeViewTo( this->getNextRandomCode() );
      this->soundForceShuffle();

      // タイマーを更新。1秒後に再設定
      this->forceShuffleTime = nowTime + 1000;
    }
  }

  // ゲームがタイムアップしたとき
  if( this->finishTime != 0 && this->finishTime <= nowTime) {

    // 画面表示をまずクリア
    this->clearView();

    // 総プレイ数をインクリメント（SPIFFSの状態によって少し時間のかかる場合がある）
    auto rec = PPLTRecord();
    auto count = rec.getPlayCount();
    rec.writePlayCount(count+1);

    // ハイスコアを更新
    switch(this->gameMode) {
      case 0:  // オリジナルモード
        {
          auto score = rec.getHighScoreOriginal();
          if( score < this->touchCount ) {
            rec.writeHighScoreOriginal(this->touchCount);
          }
        }
        break;
      case 1:  // ハードモード
        {
          auto score = rec.getHighScoreHard();
          if( score < this->touchCount ) {
            rec.writeHighScoreHard(this->touchCount);
          }
        }
        break;
      case 2:  // スーパーハードモード
        {
          auto score = rec.getHighScoreSuperHard();
          if( score < this->touchCount ) {
            rec.writeHighScoreSuperHard(this->touchCount);
          }
        }
        break;
    }

    // アプリ終了
    this->isFinished = true;
  }

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppGamePlaying::hasNextApp() {
  return this->isFinished;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppGamePlaying::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::GameResult, this->touchCount));
}

///-----------
/// getNextApp
///-----------
PPLTStateCode PPLTAppGamePlaying::getNextRandomCode() {
  switch(this->gameMode) {
    case 2:  // スーパーハードモード
      return PPLTModuleState::getRandomCode(4, 6);
    default: // その他
      return PPLTModuleState::getRandomCode();
  }
}

///-----------
/// changeViewTo
///-----------
void PPLTAppGamePlaying::changeViewTo(const PPLTStateCode nextCode) {
  this->targetCode = nextCode;
  for(int i=0; i<MAX_MODULENUM; i++) {
    PPLTViewType targetView = PPLTViewType::PPLT_Blank;
    if( (nextCode >> i) & 0x1 == 0x1 ){
      targetView = PPLTViewType::PPLT_Target;
    }

    PPLTApp::postPacket( PPLTPacketToSub(i+1, PPLTAppType::GamePlaying, targetView, this->progressCount).getPacketData() );
  }
}

///-----------
/// clearView
///-----------
void PPLTAppGamePlaying::clearView() {
  for(int i=0; i<MAX_MODULENUM; i++) {
    PPLTApp::postPacket( PPLTPacketToSub(i+1, PPLTAppType::GamePlaying, PPLTViewType::PPLT_Blank, this->progressCount).getPacketData() );
  }
}

///-----------
/// soundTouchOK
///-----------
void PPLTAppGamePlaying::soundTouchOK() {
  M5.Speaker.tone(1760.000, 50);
  M5.delay(50);
  M5.Speaker.tone(2217.461, 50);
  M5.delay(50);
  M5.Speaker.tone(2637.020, 50);
  M5.delay(50);
}

///-----------
/// soundForceShuffle
///-----------
void PPLTAppGamePlaying::soundForceShuffle() {
  M5.Speaker.tone(1760.000, 50);
  M5.delay(50);
}

///-----------
/// soundCountDownTick
///-----------
void PPLTAppGamePlaying::soundCountDownTick() {
  M5.Speaker.tone(880.000, 100);
  M5.delay(100);
}