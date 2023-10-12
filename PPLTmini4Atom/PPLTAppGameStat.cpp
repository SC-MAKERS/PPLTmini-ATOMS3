///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTAppGameStat.h"
#include "PPLTRecord.h"

///-----------
/// Constructor
///-----------
PPLTAppGameStat::PPLTAppGameStat(PPLTConnectType type, PPLTAddress addr, PPLTIntentParam param)
 : PPLTApp(type, addr, param), isFinished(false), isReadyToNextApp(false)
{
  // NOP
}

///-----------
/// begin
///-----------
void PPLTAppGameStat::begin(std::queue<PPLTPacketToSubPointer>* queue, PPLTModuleInfoPointer moduleInfo) {
  PPLTApp::begin(queue, moduleInfo);

  if( PPLTApp::type == PPLTConnectType::Sub ) {
    return;
  }
  // Main only
  
  this->soundOpening();

  // 表示する統計データを取得。
  auto rec = PPLTRecord();
  auto total = rec.getPlayCount();
  auto score0 = rec.getHighScoreOriginal();
  auto score1 = rec.getHighScoreHard();
  auto score2 = rec.getHighScoreSuperHard();

  // ボタンごとの表示内容を指定
  this->setViewTypeTo( 7, PPLTViewType::PPLT_Stat, (uint8_t)score0 ); // ハイスコア（オリジナル）
  this->setViewTypeTo( 8, PPLTViewType::PPLT_Stat, (uint8_t)score1 ); // ハイスコア（ハードモード）
  this->setViewTypeTo( 9, PPLTViewType::PPLT_Stat, (uint8_t)score2 ); // ハイスコア（スーパーハード）

  // FIXME: PPLTRecordクラスから得られるデータはuint16_tだがPPLTViewクラスへ渡せる
  // パラメータはuint8_tしかないため、総プレイ数は現在256以上表示できない仕様である。
  this->setViewTypeTo( 4, PPLTViewType::PPLT_Stat, (uint8_t)total );  // 総プレイ数
  this->setViewTypeTo( 5, PPLTViewType::PPLT_Stat );
  this->setViewTypeTo( 6, PPLTViewType::PPLT_Stat );

  this->setViewTypeTo( 1, PPLTViewType::PPLT_Stat );
  this->setViewTypeTo( 2, PPLTViewType::PPLT_Stat );
  this->setViewTypeTo( 3, PPLTViewType::PPLT_Stat );
  
}

///-----------
/// update
///-----------
void PPLTAppGameStat::update() {

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

  // 特定の操作でデータを消去
  if( !nowState.compareTo(CODE_UNDERTOUCH) ){
    this->soundReset();

    auto rec = PPLTRecord();
    rec.reset();
    // 表示する数値もリセット
    this->setViewTypeTo( 7, PPLTViewType::PPLT_Stat ); // ハイスコア（オリジナル）
    this->setViewTypeTo( 8, PPLTViewType::PPLT_Stat ); // ハイスコア（ハードモード）
    this->setViewTypeTo( 9, PPLTViewType::PPLT_Stat ); // ハイスコア（スーパーハード）
    this->setViewTypeTo( 4, PPLTViewType::PPLT_Stat ); // 総プレイ数
  }

  // 特定の操作でアプリを終了
  if( !nowState.compareTo(CODE_CENTERTOUCH) ){
    this->soundBack();
    isFinished = true;
  }

}

///-----------
/// hasNextApp
///-----------
bool PPLTAppGameStat::hasNextApp() {
  return this->isFinished;
}

///-----------
/// getNextApp
///-----------
PPLTAppIntentPointer PPLTAppGameStat::getNextApp() {
  return PPLTAppIntentPointer(new PPLTAppIntent(PPLTAppType::Launcher));
}

///-----------
/// setViewTypeTo
///-----------
void PPLTAppGameStat::setViewTypeTo(const PPLTAddress address, const PPLTViewType view) {
  PPLTApp::postPacket( PPLTPacketToSub(address, PPLTAppType::Launcher, view).getPacketData() );
}

void PPLTAppGameStat::setViewTypeTo(const PPLTAddress address, const PPLTViewType view, const PPLTViewParam param) {
  PPLTApp::postPacket( PPLTPacketToSub(address, PPLTAppType::Launcher, view, param).getPacketData() );
}

///-----------
/// soundReset
///-----------
void PPLTAppGameStat::soundReset() {
  M5.Speaker.tone(880.000, 50);
  M5.delay(100);
  M5.Speaker.tone(880.000, 50);
  M5.delay(100);
  M5.Speaker.tone(880.000, 50);
  M5.delay(100);
}

///-----------
/// soundOpening
///-----------
void PPLTAppGameStat::soundOpening() {
  M5.Speaker.tone(783.991, 50);
  M5.delay(100);
  M5.Speaker.tone(1174.659, 50);
  M5.delay(100);
  M5.Speaker.tone(1567.982, 50);
  M5.delay(100);
  M5.Speaker.tone(1975.533, 50);
  M5.delay(100);
}

///-----------
/// soundBack
///-----------
void PPLTAppGameStat::soundBack() {
  M5.Speaker.tone(880.000, 50);
  M5.delay(100);
  M5.Speaker.tone(1174.659, 50);
  M5.delay(100);
  M5.Speaker.tone(1479.978, 50);
  M5.delay(100);
  M5.Speaker.tone(1760.000, 50);
  M5.delay(100);
}