///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTConnectMain.h"

///-----------
/// Constructor
///-----------
PPLTConnectMain::PPLTConnectMain(PPLTAddress addr) : address(addr){
}

///-----------
/// begin
///-----------
bool PPLTConnectMain::begin(PPLTModuleInfoPointer moduleInfo) {

  this->moduleInfo = moduleInfo;

  // I2C begin
  bool isWireOK = Wire.begin(SDA_PIN, SCL_PIN, (uint32_t)0);
  Wire.setClock(400000); // fastmode: 400kHz
  Serial.printf("Wire Master OK?: %s\n", (isWireOK) ? "true" : "false");

  // Scan Sub Modules
  this->scanAll();

  return isWireOK;
}

///-----------
/// update
///-----------
void PPLTConnectMain::update() {

  // 自モジュール情報を更新
  this->moduleInfo->updateMyButtonState();

  // Subモジュール群の状態を収集
  this->scanOnlyEnabled();
}

///-----------
/// scanAll
///-----------
void PPLTConnectMain::scanAll() {
  // Subモジュールと通信できるかどうかを試すことで
  // Subモジュールの有無を確認するメソッド

  // reset
  memset(this->enabledSub, 0, sizeof(this->enabledSub));

  // scan
  Serial.println("Scaning...");
  delay(2000); // Subモジュール群が起動するのを少し待つ

  // 想定しているモジュールの数だけループ
  for(int i=0; i<MAX_MODULENUM; i++) {
    int targetAddress = i+1; // 1 origin
    if( targetAddress == (int)this->address ) {
      // 自分は対象外
      continue;
    }

    // Subモジュールに対してデータ返送依頼
    const int TARGET_SIZE = sizeof(PacketFromSub);
    uint8_t responseByte = Wire.requestFrom(targetAddress, TARGET_SIZE);

    // 既定のデータ受け取り
    if( responseByte > 0 ) {
      uint8_t receivedData[TARGET_SIZE];
      memset(receivedData, 0, TARGET_SIZE);

      // バッファに溜まるまで待つ
      while( Wire.available() < TARGET_SIZE ) {
        delay(1);
      }
      for(int j=0; j<TARGET_SIZE; j++) {
        receivedData[j] = Wire.read();
      }

      // 受け取ったデータを解釈
      Serial.printf("recv:[id:%d] btn:%d\n",
        targetAddress, ((PacketFromSub*)&receivedData)->nowButtonState);

      // Subモジュールが存在するものとして認識
      this->enabledSub[i] = 1;
    }
    delay(100); // 安定性を高めるために少し待つ
  }

  Serial.println("Scan end.");
}

///-----------
/// scanOnlyEnabled
///-----------
void PPLTConnectMain::scanOnlyEnabled() {

  // 存在するSubモジュールへ個別に問い合わせることで
  // Subモジュールの最新情報（ボタン押下状態など）把握するためのメソッド

  // 想定しているモジュールの数だけループ
  for(int i=0; i<MAX_MODULENUM; i++) {
    if (this->enabledSub[i] == 0) {
      // 存在しないSubモジュールは飛ばす
      continue;
    }

    int targetAddress = i+1; // 1 origin

    // Subモジュールに対してデータ返送依頼
    const int TARGET_SIZE = sizeof(PacketFromSub);
    uint8_t responseByte = Wire.requestFrom(targetAddress, TARGET_SIZE);

    // 既定のデータ受け取り
    if( responseByte > 0 ) {
      uint8_t receivedData[TARGET_SIZE];
      memset(receivedData, 0, TARGET_SIZE);

      // バッファに溜まるまで待つ
      while( Wire.available() < TARGET_SIZE ) {
        delay(1);
      }
      for(int j=0; j<TARGET_SIZE; j++) {
        receivedData[j] = Wire.read();
      }
      
      // 受信データを保存
      this->moduleInfo->setFromSub(targetAddress, (PacketFromSub*)&receivedData);
    }
  }
}

///-----------
/// postData
///-----------
void PPLTConnectMain::postData(PPLTPacketToSubPointer packet) {

  assert( 0 < packet->target );
  assert( packet->target <= MAX_MODULENUM );

  // 自分自身を対象とするパケットは自己処理する
  if( packet->target == this->address ) {
    this->moduleInfo->updateMyView(packet->view, packet->param);
    return;
  }

  int indexToCheck = packet->target - 1;
  if (this->enabledSub[indexToCheck] == 0) {
    // 存在しないSubモジュールを対象にしたものは無視
    return;
  }

  // Subモジュールに対してデータ送信
  const int TARGET_SIZE = sizeof(PacketToSub);
  Wire.beginTransmission(packet->target);
  PacketToSub* raw_pointer = packet.get();
  Wire.write((uint8_t*)raw_pointer, TARGET_SIZE);
  Wire.endTransmission();
}
