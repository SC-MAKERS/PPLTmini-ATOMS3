///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_RECORD__
#define __PPLT_RECORD__

#include "PPLTTypeDef.h"

///--------------------------
/// PPLTRecord
///--------------------------
class PPLTRecord {
private:

// methods
public:
  PPLTRecord();
  void reset();
  uint16_t getPlayCount();
  void writePlayCount(const uint16_t);

  uint16_t getHighScoreOriginal();
  void writeHighScoreOriginal(const uint16_t);
  uint16_t getHighScoreHard();
  void writeHighScoreHard(const uint16_t);
  uint16_t getHighScoreSuperHard();
  void writeHighScoreSuperHard(const uint16_t);

private:
  uint16_t getUint16(const char*);
  void writeUint16(const char*, const uint16_t);
};

#endif //__PPLT_RECORD__
