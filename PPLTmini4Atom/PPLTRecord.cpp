///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include <FS.h>
#include <SPIFFS.h>
#include "PPLTRecord.h"

/// SPIFFSに書きこむファイル名。
/// 総プレイ数
const auto FILENAME_TOTALCOUNT = "/count";
/// ハイスコア（オリジナルモード）
const auto FILENAME_HIGHSCORE_ORIGINAL = "/score0";
/// ハイスコア（ハードモード）
const auto FILENAME_HIGHSCORE_HARD = "/score1";
/// ハイスコア（スーパーハードモード）
const auto FILENAME_HIGHSCORE_SUPERHARD = "/score2";

///-----------
/// Constructor
///-----------
PPLTRecord::PPLTRecord() {
  // 記録領域の初期化
  SPIFFS.begin(true);
}

///-----------
/// reset
///-----------
void PPLTRecord::reset() {
  fs::FS fs = SPIFFS;
  fs.remove(FILENAME_TOTALCOUNT);
  fs.remove(FILENAME_HIGHSCORE_ORIGINAL);
  fs.remove(FILENAME_HIGHSCORE_HARD);
  fs.remove(FILENAME_HIGHSCORE_SUPERHARD);
}

///------------
/// getPlayCount
///------------
uint16_t PPLTRecord::getPlayCount() {
  return this->getUint16(FILENAME_TOTALCOUNT);
}

///------------
/// writePlayCount
///------------
void PPLTRecord::writePlayCount(const uint16_t data) {
  this->writeUint16(FILENAME_TOTALCOUNT, data);
}

///------------
/// getHighScoreOriginal
///------------
uint16_t PPLTRecord::getHighScoreOriginal(){
  return this->getUint16(FILENAME_HIGHSCORE_ORIGINAL);
}

///------------
/// writeHighScoreOriginal
///------------
void PPLTRecord::writeHighScoreOriginal(const uint16_t data){
  this->writeUint16(FILENAME_HIGHSCORE_ORIGINAL, data);
}

///------------
/// getHighScoreHard
///------------
uint16_t PPLTRecord::getHighScoreHard(){
  return this->getUint16(FILENAME_HIGHSCORE_HARD);
}

///------------
/// writeHighScoreHard
///------------
void PPLTRecord::writeHighScoreHard(const uint16_t data){
  this->writeUint16(FILENAME_HIGHSCORE_HARD, data);
}

///------------
/// getHighScoreSuperHard
///------------
uint16_t PPLTRecord::getHighScoreSuperHard(){
  return this->getUint16(FILENAME_HIGHSCORE_SUPERHARD);
}

///------------
/// writeHighScoreSuperHard
///------------
void PPLTRecord::writeHighScoreSuperHard(const uint16_t data){
  this->writeUint16(FILENAME_HIGHSCORE_SUPERHARD, data);
}

///------------
/// getUint16
///------------
uint16_t PPLTRecord::getUint16(const char* filename) {
  fs::FS fs = SPIFFS;
  File file;

  if (fs.exists(filename)) {
    file = fs.open(filename, "r");

  } else {
    Serial.printf("Not found: %s\n", filename);
    return 0;
  }

  uint8_t buffer[2];
  buffer[0] = file.read();
  buffer[1] = file.read();
  file.close();

  return *(uint16_t*)buffer;
}

///------------
/// writeUint16
///------------
void PPLTRecord::writeUint16(const char* filename, const uint16_t data) {
  fs::FS fs = SPIFFS;
  File file = fs.open(filename, "w");
  
  if( file ){
    file.write( (data >> 0) & 0xFF );
    file.write( (data >> 8) & 0xFF );
    file.close();
  }else{
    Serial.printf("Can't open: %s\n", filename);
  }
}
