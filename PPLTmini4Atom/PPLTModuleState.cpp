///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include "PPLTModuleState.h"

///-----------
/// Constructor
///-----------
PPLTModuleState::PPLTModuleState(const PPLTButtonState* buttons) 
{
  this->stateCode = 0;
  // ９つのボタンが押されているかどうかを16bit数値で表現する。
  // bit0 : ボタン１
  // bit1 : ボタン２
  // bit2 : ボタン３
  // bit3 : ボタン４
  // bit4 : ボタン５
  // bit5 : ボタン６
  // bit6 : ボタン７
  // bit7 : ボタン８
  // bit8 : ボタン９
  // bit9以降は未使用
  for(int i=0; i<MAX_MODULENUM; i++) {
    if( buttons[i] == PPLTButtonState::Pressed ) {
      this->stateCode |= (0x1 << i);
    }
  }
}

PPLTModuleState::PPLTModuleState(const PPLTStateCode code) 
{
  this->stateCode = code;
}

///-----------
/// compareTo
///-----------
int PPLTModuleState::compareTo(PPLTModuleState other) {
  auto otherButtonCode = other.getCode();
  return (this->stateCode != otherButtonCode) ? 1 : 0;
}

int PPLTModuleState::compareTo(const PPLTStateCode code) {
  return (this->stateCode != code) ? 1 : 0;
}

///-----------
/// getStateCode
///-----------
PPLTStateCode PPLTModuleState::getCode() {
  return this->stateCode;
}

///-----------
/// getRandomCode
///-----------
PPLTStateCode PPLTModuleState::getRandomCode(){
  return PPLTModuleState::getRandomCode(4, 4);
}

///-----------
/// getRandomCode
///-----------
PPLTStateCode PPLTModuleState::getRandomCode(const int min, const int max){
  PPLTStateCode bits = 0;
  uint8_t __selected[MAX_MODULENUM] = {0}; // 選択されたボタンを示す配列

  randomSeed(millis());

  // ボタン選択数を min ～ max+1 の範囲で決める
  int maxSelection = max;
  if( min < max ) {
    maxSelection = random(min, max+1);
  }

  // ボタンをランダムに選択する
  for(int i=0; i<maxSelection; ) {
    int randomNumber = random(0, MAX_MODULENUM);

    if (__selected[randomNumber] == 0) {
      // まだ選ばれていないボタンなら選択
      bits |= 0x1 << randomNumber;
      __selected[randomNumber] = 1;
      i++; // 選択したボタンの数を増やす
    }
  }
  
  return bits;
}