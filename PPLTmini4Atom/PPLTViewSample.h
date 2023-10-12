///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_VIEW_SAMPLE__
#define __PPLT_VIEW_SAMPLE__

#include <M5Unified.h>
#include "PPLTView.h"

///--------------------------
/// PPLTViewSample
///--------------------------
class PPLTViewSample : public PPLTView {
// fields

// methods
public:
  PPLTViewSample(PPLTAddress);
  void draw();
private:
  void drawDefault(const PPLTViewParam);
  void drawScanning(const PPLTViewParam);
  void drawDemo(const PPLTViewParam);
  void drawLauncherIconPPLTStat(const PPLTViewParam);
  void drawLauncherIconKeyPad(const PPLTViewParam);
  void drawLauncherIconLightsOut(const PPLTViewParam);
  void drawLauncherIconFlashTouch(const PPLTViewParam);
  void drawLauncherIconDemoMini(const PPLTViewParam);
  void drawLauncherIconPPLTOriginal(const PPLTViewParam);
  void drawLauncherIconPPLTHard(const PPLTViewParam);
  void drawLauncherIconPPLTSuperHard(const PPLTViewParam);
  void drawPPLTBlank(const PPLTViewParam);
  void drawPPLTReady(const PPLTViewParam);
  void drawPPLTTarget(const PPLTViewParam);
  void drawPPLTResultExcellent(const PPLTViewParam);
  void drawPPLTResultGreat(const PPLTViewParam);
  void drawPPLTResultGood(const PPLTViewParam);
  void drawPPLTResultBad(const PPLTViewParam);
  void drawPPLTCountdown(const PPLTViewParam);
  void drawPPLTStat(const PPLTViewParam);
  void drawLightsOutOn(const PPLTViewParam);
  void drawLightsOutOff(const PPLTViewParam);
  void drawFlashTouchQuestion(const PPLTViewParam);
  void drawFlashTouchAnswerSuccess(const PPLTViewParam);
  void drawFlashTouchAnswerFailed(const PPLTViewParam);
  void drawKeyPad(const PPLTViewParam);

  void printMyAddress(const uint16_t, const uint16_t);
  void printOneCharAscii(const String, const uint16_t, const uint16_t);
  void printOneCharJpn(const String, const uint16_t, const uint16_t);
  void printStringAscii(const String, const uint16_t);
  void printStringAscii(const String, const uint16_t, const uint16_t);
  void printStringJpn(const String, const uint16_t, const uint16_t);
  void printHeaderJpn(const char*, const uint16_t, const uint16_t);
  void printFooterJpn(const char*, const uint16_t, const uint16_t);

  void showProgressBar(const PPLTViewParam);
  uint16_t getRGBfromHSV(float, float, float);

};

#endif //__PPLT_VIEW_SAMPLE__
