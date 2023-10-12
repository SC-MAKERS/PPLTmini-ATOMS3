///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTConnectSub.h"

// I2C通信で使用するデータを一時的に保存する変数。
// I2C通信のイベントハンドラ（静的メソッド） onReceive, onRequestが
// アクセスできる位置に定義する必要があった。
static PacketToSub __receivdData;
static PacketFromSub __storedDataToMain;

///-----------
/// Constructor
///-----------
PPLTConnectSub::PPLTConnectSub(PPLTAddress addr) : address(addr) {
}

///-----------
/// begin
///-----------
bool PPLTConnectSub::begin(PPLTModuleInfoPointer moduleInfo) {

  this->moduleInfo = moduleInfo;

  // I2Cスレーブではこれを入れておかないと下記エラーが出て初期化失敗する
  //   [E][Wire.cpp:251] begin(): Bus already started in Master Mode.
  M5.In_I2C.release();

  // I2C通信を安定して初期化するためのDelay
  // （全Subモジュールの電源を同時に入れると仮定し
  // 　スレーブIDがそれぞれ異なることを利用してWire.beginを実行するタイミングを
  // 　Subモジュールごとにずらすことが目的）
  int waitTime = 200 * this->address;
  delay(waitTime);

  // I2C begin
  bool isWireOK = Wire.begin(this->address, SDA_PIN, SCL_PIN, (uint32_t)0);
  Serial.printf("Wire Slave(%d) OK?: %s\n", address, (isWireOK) ? "true" : "false");

  if (isWireOK) {
    Wire.setClock(400000); // fastmode: 400kHz
    // Set handlers
    Wire.onReceive(PPLTConnectSub::onReceive);
    Wire.onRequest(PPLTConnectSub::onRequest);
  }

  return isWireOK;
}

///-----------
/// update
///-----------
void PPLTConnectSub::update() {

  // 自モジュール情報を更新
  this->moduleInfo->updateMyButtonState();
  this->moduleInfo->updateMyView(__receivdData.view, __receivdData.param);

  // 自身のモジュール情報を参照してMainへ返送するデータを更新
  auto myData = this->moduleInfo->getMyData();
  __storedDataToMain.nowButtonState = myData.getButtonState();
  __storedDataToMain.view = myData.getViewType();
  __storedDataToMain.param = myData.getViewParam();
}

///-----------
/// postData
///-----------
void PPLTConnectSub::postData(PPLTPacketToSubPointer __unused) {
  // NOP (main only)
}

///-----------
/// I2C通信　Mainからデータ受信時のイベントハンドラ
///-----------
void PPLTConnectSub::onReceive(int numBytes) {

  const int TARGET_SIZE = sizeof(PacketToSub);
  if (Wire.available() < TARGET_SIZE) {
    // 受信データが規定パケットサイズ未満なら無視する
    return;
  }

  // clear temporary buffer
  uint8_t receivedData[TARGET_SIZE];
  memset(receivedData, 0, TARGET_SIZE);

  // receive to temporary buffer
  for (int i=0; i<TARGET_SIZE; i++){
    receivedData[i] = (uint8_t)Wire.read();
  }
  memcpy(&__receivdData, &receivedData[0], TARGET_SIZE);
}

///-----------
/// I2C通信　Mainからデータ送信要求受信時のイベントハンドラ
///-----------
void PPLTConnectSub::onRequest() {
  Wire.write( (uint8_t*)&__storedDataToMain, sizeof(__storedDataToMain) );
}
