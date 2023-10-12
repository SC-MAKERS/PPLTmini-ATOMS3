///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include <math.h>
#include "PPLTViewSample.h"

///-----------
/// reset
///-----------
PPLTViewSample::PPLTViewSample(PPLTAddress addr) : PPLTView(addr) {
}

///-----------
/// draw
///-----------
void PPLTViewSample::draw() {

  // PPTView::updateメソッドで別途更新された
  // 描画タイプ（PPLTView::type）、パラメータ（PPLTView::param）に応じた内容を
  // 内部バッファ（PPLTView::canvas）に描画する
  switch(PPLTView::type) {
    case PPLTViewType::Demo:
      this->drawDemo(PPLTView::param);
      break;
    case PPLTViewType::Scanning:
      this->drawScanning(PPLTView::param);
      break;
    case PPLTViewType::Launcher_1:
      this->drawLauncherIconPPLTStat(PPLTView::param);
      break;
    case PPLTViewType::Launcher_2:
      this->drawLauncherIconKeyPad(PPLTView::param);
      break;
    case PPLTViewType::Launcher_4:
      this->drawLauncherIconLightsOut(PPLTView::param);
      break;
    case PPLTViewType::Launcher_5:
      this->drawLauncherIconDemoMini(PPLTView::param);
      break;
    case PPLTViewType::Launcher_6:
      this->drawLauncherIconFlashTouch(PPLTView::param);
      break;
    case PPLTViewType::Launcher_7:
      this->drawLauncherIconPPLTOriginal(PPLTView::param);
      break;
    case PPLTViewType::Launcher_8:
      this->drawLauncherIconPPLTHard(PPLTView::param);
      break;
    case PPLTViewType::Launcher_9:
      this->drawLauncherIconPPLTSuperHard(PPLTView::param);
      break;
    case PPLTViewType::PPLT_Blank:
      this->drawPPLTBlank(PPLTView::param);
      break;
    case PPLTViewType::PPLT_Ready:
      this->drawPPLTReady(PPLTView::param);
      break;
    case PPLTViewType::PPLT_Target:
      this->drawPPLTTarget(PPLTView::param);
      break;
    case PPLTViewType::PPLT_ResultExcellent:
      this->drawPPLTResultExcellent(PPLTView::param);
      break;
    case PPLTViewType::PPLT_ResultGreat:
      this->drawPPLTResultGreat(PPLTView::param);
      break;
    case PPLTViewType::PPLT_ResultGood:
      this->drawPPLTResultGood(PPLTView::param);
      break;
    case PPLTViewType::PPLT_ResultBad:
      this->drawPPLTResultBad(PPLTView::param);
      break;
    case PPLTViewType::PPLT_Countdown:
      this->drawPPLTCountdown(PPLTView::param);
      break;
    case PPLTViewType::PPLT_Stat:
      this->drawPPLTStat(PPLTView::param);
      break;
    case PPLTViewType::LightsOut_On:
      this->drawLightsOutOn(PPLTView::param);
      break;
    case PPLTViewType::LightsOut_Off:
      this->drawLightsOutOff(PPLTView::param);
      break;
    case PPLTViewType::FlashTouch_Question:
      this->drawFlashTouchQuestion(PPLTView::param);
      break;
    case PPLTViewType::FlashTouch_AnswerSuccess:
      this->drawFlashTouchAnswerSuccess(PPLTView::param);
      break;
    case PPLTViewType::FlashTouch_AnswerFailed:
      this->drawFlashTouchAnswerFailed(PPLTView::param);
      break;
    case PPLTViewType::KeyPad:
      this->drawKeyPad(PPLTView::param);
      break;
    case PPLTViewType::Clear: // fallthrough
    default:
      this->drawDefault(PPLTView::param);
      break;
  }

  // 内部バッファ（PPLTView::canvas）の内容を
  // ディスプレイ（M5.Display）に反映する
  M5.Display.startWrite();
  if (!M5.Display.displayBusy()) {
    PPLTView::canvas->pushSprite(&M5.Display, 0, 0);
  }
  M5.Display.endWrite();
  M5.Display.display();
}

/// 個別描画メソッド ---------------------

///-----------
/// drawDefault
///-----------
void PPLTViewSample::drawDefault(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);
}

///-----------
/// drawScanning
///-----------
void PPLTViewSample::drawScanning(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_WHITE);
  this->printMyAddress(TFT_BLACK, TFT_WHITE);
}

///-----------
/// drawDemo
///-----------
void PPLTViewSample::drawDemo(const PPLTViewParam param) {
  
  // 枠をキラキラ光らせたいだけの処理
  auto nowTime = millis() / 50;
  float hue = fmodf((float)(nowTime % 60) * 6.0, 360.0); // 色相環6度ずつ変化
  auto color = this->getRGBfromHSV(hue, 1.0, 1.0);
  PPLTView::canvas->fillScreen(color);

  // 背景塗りつぶし
  auto frameWidth = 12;
  PPLTView::canvas->fillRoundRect(
    frameWidth,
    frameWidth,
    PPLTView::width - (frameWidth<<1),
    PPLTView::height - (frameWidth<<1),
    5,
    TFT_BLACK);

  switch (PPLTView::address) {
    case 7:
      this->printOneCharJpn("ぴ", TFT_WHITE, TFT_BLACK);
      break;
    case 8:
      this->printOneCharJpn("こ", TFT_WHITE, TFT_BLACK);
      break;
    case 9:
      this->printOneCharJpn("ピ", TFT_WHITE, TFT_BLACK);
      break;
    case 4:
      this->printOneCharJpn("コ", TFT_WHITE, TFT_BLACK);
      break;
    case 5:
      this->printOneCharJpn("ら", TFT_WHITE, TFT_BLACK);
      break;
    case 6:
      this->printOneCharJpn("ぶ", TFT_WHITE, TFT_BLACK);
      break;
    case 1:
      this->printOneCharJpn("タ", TFT_WHITE, TFT_BLACK);
      break;
    case 2:
      this->printOneCharJpn("ッ", TFT_WHITE, TFT_BLACK);
      break;
    case 3:
      this->printOneCharJpn("チ", TFT_WHITE, TFT_BLACK);
      break;
    default:
      break;
  }
}

///-----------
/// drawLauncherIconPPLTStat
///-----------
void PPLTViewSample::drawLauncherIconPPLTStat(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);

  // icon
  this->printStringAscii("DATA", TFT_MAGENTA, TFT_BLACK);

  // text
  this->printFooterJpn("統計データ", TFT_WHITE, TFT_BLACK);
}

///-----------
/// drawLauncherIconKeyPad
///-----------
void PPLTViewSample::drawLauncherIconKeyPad(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);

  // icon
  this->printStringAscii("USB", TFT_GREEN, TFT_BLACK);

  // text
  this->printFooterJpn("キーボード", TFT_WHITE, TFT_BLACK);
}

///-----------
/// drawLauncherIconLightsOut
///-----------
void PPLTViewSample::drawLauncherIconLightsOut(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);

  // icon
  const auto square_width = PPLTView::width/5;
  const auto square_height = square_width;
  const auto x_pos = square_width;
  const auto y_pos = square_height;

  // 中央寄せにするための調整値
  const auto x_adj = square_width;
  const auto y_adj = 20;
  
  if (millis() % 1000 < 500) {
    // - * -
    // * - * 
    // - * -
    PPLTView::canvas->fillRect(           x_adj,      y_pos+y_adj, square_width, square_height, TFT_WHITE);
    PPLTView::canvas->fillRect(     x_pos+x_adj,            y_adj, square_width, square_height, TFT_WHITE);
    PPLTView::canvas->fillRect(     x_pos+x_adj, (y_pos<<1)+y_adj, square_width, square_height, TFT_WHITE);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj,      y_pos+y_adj, square_width, square_height, TFT_WHITE);

  }else{
    // - - -
    // - * - 
    // - - -
    PPLTView::canvas->fillRect(     x_pos+x_adj,    y_pos+y_adj, square_width, square_height, TFT_WHITE);
  }

  // text
  this->printFooterJpn("消灯ゲーム", TFT_WHITE, TFT_BLACK);
}

///-----------
/// drawLauncherIconDemoMini
///-----------
void PPLTViewSample::drawLauncherIconDemoMini(const PPLTViewParam param) {

  // 枠をキラキラ光らせたいだけの処理
  auto nowTime = millis() / 50;
  float hue = fmodf((float)(nowTime % 60) * 6.0, 360.0); // 色相環6度ずつ変化
  auto color = this->getRGBfromHSV(hue, 1.0, 1.0);
  PPLTView::canvas->fillScreen(color);

  // 背景塗りつぶし
  auto frameWidth = 12;
  PPLTView::canvas->fillRoundRect(
    frameWidth,
    frameWidth,
    PPLTView::width - (frameWidth<<1),
    PPLTView::height - (frameWidth<<1),
    5,
    TFT_BLACK);

  // icon
  const auto font = &fonts::lgfxJapanGothic_20;
  PPLTView::canvas->setFont(font);
  PPLTView::canvas->setTextSize(2);
  PPLTView::canvas->setTextColor(TFT_WHITE, TFT_BLACK);

  const int x = PPLTView::width >> 1;
  int y = (PPLTView::height >> 1) - PPLTView::canvas->fontHeight();
  PPLTView::canvas->drawCenterString("ぴこ", x, y, font);
  y += PPLTView::canvas->fontHeight();
  PPLTView::canvas->drawCenterString("ピコ", x, y, font);
}

///-----------
/// drawLauncherIconFlashTouch
///-----------
void PPLTViewSample::drawLauncherIconFlashTouch(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);

  // icon
  const auto square_width = PPLTView::width/5;
  const auto square_height = square_width;
  const auto x_pos = square_width;
  const auto y_pos = square_height;

  // 中央寄せにするための調整値
  const auto x_adj = square_width;
  const auto y_adj = 20;
  
  const auto nowMiliSec = millis() % 1000;
  if (nowMiliSec < 100) {
    // - * -
    // - - - 
    // - - -
    PPLTView::canvas->fillRect(           x_adj,      y_pos+y_adj, square_width, square_height, TFT_WHITE);

  }else if(nowMiliSec < 200){
    // - - -
    // * - - 
    // - - -
    PPLTView::canvas->fillRect(     x_pos+x_adj,            y_adj, square_width, square_height, TFT_WHITE);

  }else if(nowMiliSec < 300){
    // - - -
    // - - * 
    // - - -
    PPLTView::canvas->fillRect(     x_pos+x_adj, (y_pos<<1)+y_adj, square_width, square_height, TFT_WHITE);

  }else if(nowMiliSec < 400){
    // - - -
    // - - - 
    // - * -
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj,       y_pos+y_adj, square_width, square_height, TFT_WHITE);

  }else{
    // - - -
    // - - - 
    // - - -
    // NONE
  }

  // text
  this->printFooterJpn("記憶ゲーム", TFT_WHITE, TFT_BLACK);
}

///-----------
/// drawLauncherIconPPLTOriginal
///-----------
void PPLTViewSample::drawLauncherIconPPLTOriginal(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);

  // icon
  auto color = TFT_BLUE;
  if (millis() % 500 < 250) {
    color = TFT_MAGENTA;
  }
  
  const auto square_width = PPLTView::width/5;
  const auto square_height = square_width;
  const auto x_pos = square_width;
  const auto y_pos = square_height;

  // 中央寄せにするための調整値
  const auto x_adj = square_width;
  const auto y_adj = 20;
  
  // * - *
  // - - - 
  // * - *
  PPLTView::canvas->fillRect(           x_adj,            y_adj, square_width, square_height, color);
  PPLTView::canvas->fillRect((x_pos<<1)+x_adj,            y_adj, square_width, square_height, color);
  PPLTView::canvas->fillRect(           x_adj, (y_pos<<1)+y_adj, square_width, square_height, color);
  PPLTView::canvas->fillRect((x_pos<<1)+x_adj, (y_pos<<1)+y_adj, square_width, square_height, color);

  // text
  this->printFooterJpn("オリジナル", TFT_WHITE, TFT_BLACK);
}

///-----------
/// drawLauncherIconPPLTHard
///-----------
void PPLTViewSample::drawLauncherIconPPLTHard(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);

  // icon
  auto color = TFT_BLUE;
  if (millis() % 500 < 250) {
    color = TFT_MAGENTA;
  }

  const auto square_width = PPLTView::width/5;
  const auto square_height = square_width;
  const auto x_pos = square_width;
  const auto y_pos = square_height;

  // 中央寄せにするための調整値
  const auto x_adj = square_width;
  const auto y_adj = 20;

  if (millis() % 2000 < 1000) {
    // * - *
    // - - - 
    // * - *
    PPLTView::canvas->fillRect(           x_adj,            y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect(           x_adj, (y_pos<<1)+y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj,            y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj, (y_pos<<1)+y_adj, square_width, square_height, color);

  }else{
    // - * *
    // - - * 
    // * - -
    PPLTView::canvas->fillRect(           x_adj, (y_pos<<1)+y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect(     x_pos+x_adj,            y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj,            y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj,      y_pos+y_adj, square_width, square_height, color);
  }

  // text
  this->printFooterJpn("ハードモード", TFT_WHITE, TFT_BLACK);
}

///-----------
/// drawLauncherIconPPLTSuperHard
///-----------
void PPLTViewSample::drawLauncherIconPPLTSuperHard(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);

  // icon
  auto color = TFT_BLUE;
  if (millis() % 500 < 250) {
    color = TFT_MAGENTA;
  }

  const auto square_width = PPLTView::width/5;
  const auto square_height = square_width;
  const auto x_pos = square_width;
  const auto y_pos = square_height;

  // 中央寄せにするための調整値
  const auto x_adj = square_width;
  const auto y_adj = 20;

  if (millis() % 2000 < 1000) {
    // * * *
    // - - * 
    // * - *
    PPLTView::canvas->fillRect(           x_adj,            y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect(           x_adj, (y_pos<<1)+y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect(     x_pos+x_adj,            y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj,            y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj,      y_pos+y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj, (y_pos<<1)+y_adj, square_width, square_height, color);

  }else{
    // - - *
    // - * * 
    // * * -
    PPLTView::canvas->fillRect(           x_adj, (y_pos<<1)+y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect(     x_pos+x_adj,      y_pos+y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect(     x_pos+x_adj, (y_pos<<1)+y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj,            y_adj, square_width, square_height, color);
    PPLTView::canvas->fillRect((x_pos<<1)+x_adj,      y_pos+y_adj, square_width, square_height, color);
  }

  // text
  this->printFooterJpn("SUPERハード", TFT_WHITE, TFT_BLACK);
}

///-----------
/// drawPPLTBlank
///-----------
void PPLTViewSample::drawPPLTBlank(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);

  // ゲーム進行状況を示すプログレスバーの表示
  this->showProgressBar(param);
}

///-----------
/// drawPPLTReady
///-----------
void PPLTViewSample::drawPPLTReady(const PPLTViewParam param) {

  auto color = TFT_BLACK;
  PPLTView::canvas->fillScreen(color);
  
  switch(PPLTView::address) {
    case 4:
      this->printStringAscii("PRESS", TFT_WHITE, TFT_BLACK);
      this->printFooterJpn("青いPRESSを", TFT_BLACK, TFT_WHITE);
      break;
    case 5:
      this->printStringAscii("TO", TFT_WHITE, TFT_BLACK);
      this->printFooterJpn("すべて押すと", TFT_BLACK, TFT_WHITE);
      break;
    case 6:
      this->printStringAscii("START", TFT_WHITE, TFT_BLACK);
      this->printFooterJpn("始まります", TFT_BLACK, TFT_WHITE);
      break;
    default:
      // NOP
      break;
  }
}

///-----------
/// drawPPLTTarget
///-----------
void PPLTViewSample::drawPPLTTarget(const PPLTViewParam param) {
  if (PPLTView::buttonState == PPLTButtonState::Off) {
    // ボタンを押さえる前の表示

    auto bgColor = TFT_BLACK;
    if (millis() % 500 < 250) {
      bgColor = TFT_BLUE;
    }
    PPLTView::canvas->fillScreen(bgColor);
    this->printStringAscii("PRESS", TFT_WHITE, bgColor);

  } else {
    // ボタンを押さえている時の表示
    PPLTView::canvas->fillScreen(TFT_MAGENTA);
  }

  // ゲーム進行状況を示すプログレスバーの表示
  this->showProgressBar(param);
}

///-----------
/// drawPPLTResultExcellent
///-----------
void PPLTViewSample::drawPPLTResultExcellent(const PPLTViewParam param) {
  
  // 枠をキラキラ光らせたいだけの処理
  auto nowTime = millis() / 50;
  float hue = fmodf((float)(nowTime % 60) * 6.0, 360.0); // 色相環6度ずつ変化
  auto color = this->getRGBfromHSV(hue, 1.0, 1.0);
  PPLTView::canvas->fillScreen(color);

  switch (PPLTView::address) {
    case 7:
      this->printStringAscii("Exce", TFT_WHITE, color);
      break;
    case 8:
      this->printStringAscii("llen", TFT_WHITE, color);
      break;
    case 9:
      this->printStringAscii("t!!!", TFT_WHITE, color);
      break;
    case 5:
      PPLTView::canvas->fillScreen(color);
      
      // タッチ成功数を目立たせるための塗りつぶし
      {
        auto frameWidth = 20;
        PPLTView::canvas->fillRoundRect(
          frameWidth,
          frameWidth,
          PPLTView::width - (frameWidth<<1),
          PPLTView::height - (frameWidth<<1),
          16,
          TFT_BLACK);
      }

      this->printStringAscii(String(param), TFT_WHITE, TFT_BLACK);
      this->printFooterJpn("タッチ成功数", TFT_WHITE, color);
      break;
    case 1:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("RESET", TFT_WHITE, color);
        this->printFooterJpn("RESETを", TFT_WHITE, TFT_BLACK);
      } else {
        PPLTView::canvas->fillScreen(TFT_WHITE);
      }
      break;
    case 2:
      PPLTView::canvas->fillScreen(color);
      this->printFooterJpn("すべて押すと", TFT_WHITE, TFT_BLACK);
      break;
    case 3:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("RESET", TFT_WHITE, color);
        this->printFooterJpn("戻ります", TFT_WHITE, TFT_BLACK);
      } else {
        PPLTView::canvas->fillScreen(TFT_WHITE);
      }
      break;
    default:
      break;
  }
}

///-----------
/// drawPPLTResultGreat
///-----------
void PPLTViewSample::drawPPLTResultGreat(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_MAGENTA);
  switch (PPLTView::address) {
    case 7:
      this->printStringAscii("Gr", TFT_WHITE, TFT_MAGENTA);
      break;
    case 8:
      this->printStringAscii("eat", TFT_WHITE, TFT_MAGENTA);
      break;
    case 9:
      this->printStringAscii("!!!", TFT_WHITE, TFT_MAGENTA);
      break;
    case 5:
      // タッチ成功数を目立たせるための塗りつぶし
      {
        auto frameWidth = 20;
        PPLTView::canvas->fillRoundRect(
          frameWidth,
          frameWidth,
          PPLTView::width - (frameWidth<<1),
          PPLTView::height - (frameWidth<<1),
          16,
          TFT_BLACK);
      }
      this->printStringAscii(String(param), TFT_WHITE, TFT_BLACK);
      this->printFooterJpn("タッチ成功数", TFT_WHITE, TFT_MAGENTA);
      break;
    case 1:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("RESET", TFT_WHITE, TFT_MAGENTA);
        this->printFooterJpn("RESETを", TFT_WHITE, TFT_BLACK);
      } else {
        PPLTView::canvas->fillScreen(TFT_WHITE);
      }
      break;
    case 2:
      this->printFooterJpn("すべて押すと", TFT_WHITE, TFT_BLACK);
      break;
    case 3:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("RESET", TFT_WHITE, TFT_MAGENTA);
        this->printFooterJpn("戻ります", TFT_WHITE, TFT_BLACK);
      } else {
        PPLTView::canvas->fillScreen(TFT_WHITE);
      }
      break;
    default:
      break;
  }
}

///-----------
/// drawPPLTResultGood
///-----------
void PPLTViewSample::drawPPLTResultGood(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_YELLOW);
  switch (PPLTView::address) {
    case 7:
      this->printStringAscii("Go", TFT_BLACK, TFT_YELLOW);
      break;
    case 8:
      this->printStringAscii("od", TFT_BLACK, TFT_YELLOW);
      break;
    case 9:
      this->printStringAscii("!!", TFT_BLACK, TFT_YELLOW);
      break;
    case 5:
      // タッチ成功数を目立たせるための塗りつぶし
      {
        auto frameWidth = 20;
        PPLTView::canvas->fillRoundRect(
          frameWidth,
          frameWidth,
          PPLTView::width - (frameWidth<<1),
          PPLTView::height - (frameWidth<<1),
          16,
          TFT_BLACK);
      }
      this->printStringAscii(String(param), TFT_WHITE, TFT_BLACK);
      this->printFooterJpn("タッチ成功数", TFT_BLACK, TFT_YELLOW);
      break;
    case 1:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("RESET", TFT_BLACK, TFT_YELLOW);
        this->printFooterJpn("RESETを", TFT_WHITE, TFT_BLACK);
      } else {
        PPLTView::canvas->fillScreen(TFT_WHITE);
      }
      break;
    case 2:
      this->printFooterJpn("すべて押すと", TFT_WHITE, TFT_BLACK);
      break;
    case 3:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("RESET", TFT_BLACK, TFT_YELLOW);
        this->printFooterJpn("戻ります", TFT_WHITE, TFT_BLACK);
      } else {
        PPLTView::canvas->fillScreen(TFT_WHITE);
      }
      break;
    default:
      break;
  }
}

///-----------
/// drawPPLTResultBad
///-----------
void PPLTViewSample::drawPPLTResultBad(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLUE);
  switch (PPLTView::address) {
    case 7:
      this->printStringAscii("Oh!", TFT_WHITE, TFT_BLUE);
      break;
    case 8:
      this->printStringAscii("Bad", TFT_WHITE, TFT_BLUE);
      break;
    case 9:
      this->printStringAscii("...", TFT_WHITE, TFT_BLUE);
      break;
    case 5:
      // タッチ成功数を目立たせるための塗りつぶし
      {
        auto frameWidth = 20;
        PPLTView::canvas->fillRoundRect(
          frameWidth,
          frameWidth,
          PPLTView::width - (frameWidth<<1),
          PPLTView::height - (frameWidth<<1),
          16,
          TFT_BLACK);
      }
      this->printStringAscii(String(param), TFT_WHITE, TFT_BLACK);
      this->printFooterJpn("タッチ成功数", TFT_WHITE, TFT_BLUE);
      break;
    case 1:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("RESET", TFT_WHITE, TFT_BLUE);
        this->printFooterJpn("RESETを", TFT_WHITE, TFT_BLACK);
      } else {
        PPLTView::canvas->fillScreen(TFT_WHITE);
      }
      break;
    case 2:
      this->printFooterJpn("すべて押すと", TFT_WHITE, TFT_BLACK);
      break;
    case 3:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("RESET", TFT_WHITE, TFT_BLUE);
        this->printFooterJpn("戻ります", TFT_WHITE, TFT_BLACK);
      } else {
        PPLTView::canvas->fillScreen(TFT_WHITE);
      }
      break;
    default:
      break;
  }
}

///-----------
/// drawPPLTCountdown
///-----------
void PPLTViewSample::drawPPLTCountdown(const PPLTViewParam param) {
  auto count = param;
  switch(count) {
    case 3:
      PPLTView::canvas->fillScreen(TFT_BLACK);
      this->printOneCharAscii("3", TFT_WHITE, TFT_BLACK);
      break;
    case 2:
      PPLTView::canvas->fillScreen(TFT_BLUE);
      this->printOneCharAscii("2", TFT_WHITE, TFT_BLUE);
      break;
    case 1:
      PPLTView::canvas->fillScreen(TFT_YELLOW);
      this->printOneCharAscii("1", TFT_BLACK, TFT_YELLOW);
      break;
    case 0:
      PPLTView::canvas->fillScreen(TFT_MAGENTA);
      this->printStringAscii("Go!", TFT_WHITE, TFT_MAGENTA);
      break;
    default:
      PPLTView::canvas->fillScreen(TFT_BLACK);
      break;
  }
}

///-----------
/// drawPPLTStat
///-----------
void PPLTViewSample::drawPPLTStat(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);

  switch (PPLTView::address) {
    case 7:
      // オリジナルモード　ハイスコア
      {
        auto count = param;
        this->printStringAscii(String(count), TFT_MAGENTA, TFT_BLACK);
      }
      this->printHeaderJpn("HIGH SCORE", TFT_BLACK, TFT_WHITE);
      this->printFooterJpn("オリジナル", TFT_WHITE, TFT_BLACK);
      break;
    case 8:
      // ハードモード　ハイスコア
      {
        auto count = param;
        this->printStringAscii(String(count), TFT_MAGENTA, TFT_BLACK);
      }
      this->printHeaderJpn("HIGH SCORE", TFT_BLACK, TFT_WHITE);
      this->printFooterJpn("ハードモード", TFT_WHITE, TFT_BLACK);
      break;
    case 9:
      // スーパーハードモード　ハイスコア
      {
        auto count = param;
        this->printStringAscii(String(count), TFT_MAGENTA, TFT_BLACK);
      }
      this->printHeaderJpn("HIGH SCORE", TFT_BLACK, TFT_WHITE);
      this->printFooterJpn("SUPERハード", TFT_WHITE, TFT_BLACK);
      break;
    case 4:
      // 総プレイ数
      {
        auto count = param;
        this->printStringAscii(String(count), TFT_YELLOW, TFT_BLACK);
      }
      this->printHeaderJpn("TOTAL PLAY", TFT_BLACK, TFT_WHITE);
      this->printFooterJpn("総プレイ数", TFT_WHITE, TFT_BLACK);
      break;
    case 5:
      // 戻るボタン
      this->drawLauncherIconDemoMini(param);
      break;
    case 1:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("DEL", TFT_WHITE, TFT_RED);
        this->printFooterJpn("注意! DELを", TFT_YELLOW, TFT_BLACK);
      } else {
        // 注意の必要な操作なので点滅
        auto bgColor = TFT_RED;
        if (millis() % 200 < 100) {
          bgColor = TFT_YELLOW;
        }
        PPLTView::canvas->fillScreen(bgColor);
      }
      break;
    case 2:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("DEL", TFT_WHITE, TFT_RED);
        this->printFooterJpn("すべて押すと", TFT_YELLOW, TFT_BLACK);
      } else {
        // 注意の必要な操作なので点滅
        auto bgColor = TFT_RED;
        if (millis() % 200 < 100) {
          bgColor = TFT_YELLOW;
        }
        PPLTView::canvas->fillScreen(bgColor);
      }
      break;
    case 3:
      if (PPLTView::buttonState == PPLTButtonState::Off) {
        this->printStringAscii("DEL", TFT_WHITE, TFT_RED);
        this->printFooterJpn("記録消えます", TFT_YELLOW, TFT_BLACK);
      } else {
        // 注意の必要な操作なので点滅
        auto bgColor = TFT_RED;
        if (millis() % 200 < 100) {
          bgColor = TFT_YELLOW;
        }
        PPLTView::canvas->fillScreen(bgColor);
      }
      break;
    default:
      break;
  }
}

///-----------
/// drawLightsOutOn
///-----------
void PPLTViewSample::drawLightsOutOn(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_WHITE);

  // ゲーム進行状況を示すプログレスバーの表示
  this->showProgressBar(param);
}

///-----------
/// drawLightsOutOff
///-----------
void PPLTViewSample::drawLightsOutOff(const PPLTViewParam param) {
  PPLTView::canvas->fillScreen(TFT_BLACK);
  
  // ゲーム進行状況を示すプログレスバーの表示
  this->showProgressBar(param);
}

///-----------
/// drawFlashTouchQuestion
///-----------
void PPLTViewSample::drawFlashTouchQuestion(const PPLTViewParam param) {
  const auto target = param;

  auto textColor = TFT_WHITE;
  auto bgColor = TFT_BLACK;
  if( target != 0 ){
    textColor = TFT_BLACK;
    bgColor = TFT_WHITE;
  }
  PPLTView::canvas->fillScreen(bgColor);
  
  switch (PPLTView::address) {
    case 4:
      this->printStringAscii("Press", textColor, bgColor);
      this->printFooterJpn("光ったボタン", textColor, bgColor);
      break;
    case 5:
      this->printStringAscii("Flash", textColor, bgColor);
      this->printFooterJpn("すべて押して", textColor, bgColor);
      break;
    case 6:
      this->printStringAscii("Btns", textColor, bgColor);
      this->printFooterJpn("ください", textColor, bgColor);
      break;
  }
}

///-----------
/// drawFlashTouchAnswerSuccess
///-----------
void PPLTViewSample::drawFlashTouchAnswerSuccess(const PPLTViewParam param) {
  if (PPLTView::buttonState == PPLTButtonState::Off) {
    PPLTView::canvas->fillScreen(TFT_BLACK);
    
  }else{
    // 正解タッチ時は点灯
    PPLTView::canvas->fillScreen(TFT_WHITE);
  }
}

///-----------
/// drawFlashTouchAnswerFailed
///-----------
void PPLTViewSample::drawFlashTouchAnswerFailed(const PPLTViewParam param) {
  if (PPLTView::buttonState == PPLTButtonState::Off) {
    PPLTView::canvas->fillScreen(TFT_BLACK);

  }else{
    // 誤タッチ時は点滅
    auto bgColor = TFT_RED;
    if (millis() % 200 < 100) {
      bgColor = TFT_YELLOW;
    }
    PPLTView::canvas->fillScreen(bgColor);
  }
}

///-----------
/// drawKeyPad
///-----------
void PPLTViewSample::drawKeyPad(const PPLTViewParam param) {
  
  const char* __myChars[] = {
    "z", "x", "c",
    "a", "s", "d",
    "q", "w", "e"
  };
  const int index = (int)this->address - 1;

  if (PPLTView::buttonState == PPLTButtonState::Off) {
    PPLTView::canvas->fillScreen(TFT_BLACK);
    this->printOneCharAscii(__myChars[index], TFT_WHITE, TFT_BLACK);

  } else {
    PPLTView::canvas->fillScreen(TFT_BLUE);
    this->printOneCharAscii(__myChars[index], TFT_WHITE, TFT_BLUE);
  }
}

/// 共通処理 ---------------------

///-----------
/// printMyAddress
///-----------
void PPLTViewSample::printMyAddress(const uint16_t fontColor, const uint16_t bgColor) {

  const auto font = &fonts::Font0;

  PPLTView::canvas->setFont(font);
  PPLTView::canvas->setTextSize(6);
  PPLTView::canvas->setTextColor(fontColor, bgColor);

  const int x = PPLTView::width >> 1;
  const int y = PPLTView::height >> 1;
  PPLTView::canvas->setCursor(x - 20, y - 20);  // adjustment
  PPLTView::canvas->printf("%d", (int)this->address);
}

///-----------
/// printOneCharAscii
///-----------
void PPLTViewSample::printOneCharAscii(const String text, const uint16_t fontColor, const uint16_t bgColor) {

  const auto font = &fonts::Font0;

  PPLTView::canvas->setFont(font);
  PPLTView::canvas->setTextSize(5);
  PPLTView::canvas->setTextColor(fontColor, bgColor);

  const int x = PPLTView::width >> 1;
  const int y = (PPLTView::height >> 1) - (PPLTView::canvas->fontHeight() >> 1);
  PPLTView::canvas->drawCenterString(text, x, y, font);
}

///-----------
/// printOneCharJpn
///-----------
void PPLTViewSample::printOneCharJpn(const String text, const uint16_t fontColor, const uint16_t bgColor) {

  const auto font = &fonts::lgfxJapanGothic_20;

  PPLTView::canvas->setFont(font);
  PPLTView::canvas->setTextSize(5);
  PPLTView::canvas->setTextColor(fontColor, bgColor);

  const int x = PPLTView::width >> 1;
  const int y = (PPLTView::height >> 1) - (PPLTView::canvas->fontHeight() >> 1);
  PPLTView::canvas->drawCenterString(text, x, y, font);
}

///-----------
/// printStringAscii
///-----------
void PPLTViewSample::printStringAscii(const String text, const uint16_t fontColor) {

  const auto font = &fonts::Font0;

  PPLTView::canvas->setFont(font);
  PPLTView::canvas->setTextSize(4);
  PPLTView::canvas->setTextColor(fontColor);
  
  const int x = PPLTView::width >> 1;
  const int y = (PPLTView::height >> 1) - (PPLTView::canvas->fontHeight() >> 1);
  PPLTView::canvas->drawCenterString(text, x, y, font);
}

///-----------
/// printStringAscii
///-----------
void PPLTViewSample::printStringAscii(const String text, const uint16_t fontColor, const uint16_t bgColor) {

  const auto font = &fonts::Font0;

  PPLTView::canvas->setFont(font);
  PPLTView::canvas->setTextSize(4);
  PPLTView::canvas->setTextColor(fontColor, bgColor);
  
  const int x = PPLTView::width >> 1;
  const int y = (PPLTView::height >> 1) - (PPLTView::canvas->fontHeight() >> 1);
  PPLTView::canvas->drawCenterString(text, x, y, font);
}

///-----------
/// printStringJpn
///-----------
void PPLTViewSample::printStringJpn(const String text, const uint16_t fontColor, const uint16_t bgColor) {

  const auto font = &fonts::lgfxJapanGothic_20;

  PPLTView::canvas->setFont(font);
  PPLTView::canvas->setTextSize(2);
  PPLTView::canvas->setTextColor(fontColor, bgColor);

  const int x = PPLTView::width >> 1;
  const int y = (PPLTView::height >> 1) - (PPLTView::canvas->fontHeight() >> 1);
  PPLTView::canvas->drawCenterString(text, x, y, font);
}

///-----------
/// printHeaderJpn
///-----------
void PPLTViewSample::printHeaderJpn(const char* text, const uint16_t fontColor, const uint16_t bgColor) {

  const auto font = &fonts::lgfxJapanGothic_20;
  PPLTView::canvas->setFont(font);
  PPLTView::canvas->setTextSize(1);

  const int x = 0;
  const int y = 0;

  // 背景塗りつぶし
  PPLTView::canvas->fillRect(x, y, PPLTView::width, PPLTView::canvas->fontHeight(), bgColor);

  // テキスト
  PPLTView::canvas->setCursor(x, y);
  PPLTView::canvas->setTextColor(fontColor, bgColor);
  PPLTView::canvas->printf(text);
}

///-----------
/// printFooterJpn
///-----------
void PPLTViewSample::printFooterJpn(const char* text, const uint16_t fontColor, const uint16_t bgColor) {

  const auto font = &fonts::lgfxJapanGothic_20;
  PPLTView::canvas->setFont(font);
  PPLTView::canvas->setTextSize(1);

  const int x = 0;
  const int y = PPLTView::height - PPLTView::canvas->fontHeight();

  // 背景塗りつぶし
  PPLTView::canvas->fillRect(x, y, PPLTView::width, PPLTView::canvas->fontHeight(), bgColor);

  // テキスト
  PPLTView::canvas->setCursor(x, y);
  PPLTView::canvas->setTextColor(fontColor, bgColor);
  PPLTView::canvas->printf(text);
}

///-----------
/// showProgressBar
///-----------
void PPLTViewSample::showProgressBar(const PPLTViewParam param) {
  
  const auto progressCount = param; // MIX:0 MAX:30

  // ラスト3秒で色を変える
  auto color = TFT_GREEN;
  if( progressCount >= 27 ) {
    color = TFT_RED;
  }

  // 画面と同じ幅のバーをゲーム経過時間（MAX 30秒）に合わせて画面外から横に移動
  const int16_t w = PPLTView::width * 3;  // バーの長さ
  const int16_t h = 3;                    // バーの太さ

  const int16_t move = PPLTView::width * (param / 10.0);  // 時間あたりの移動量

  const int16_t x_7 = -w;
  const int16_t x_8 = x_7 - PPLTView::width;
  const int16_t x_9 = x_8 - PPLTView::width;
  const int16_t x_3 = PPLTView::width;
  const int16_t x_2 = PPLTView::width + x_3;
  const int16_t x_1 = PPLTView::width + x_2;

  switch(PPLTView::address) {
    case 7:
      PPLTView::canvas->fillRect(x_7 + move, 0, w, h, color);
      break;
    case 8:
      PPLTView::canvas->fillRect(x_8 + move, 0, w, h, color);
      break;
    case 9:
      PPLTView::canvas->fillRect(x_9 + move, 0, w, h, color);
      break;
    case 1:
      PPLTView::canvas->fillRect(x_1 - move, PPLTView::height - h, w, h, color);
      break;
    case 2:
      PPLTView::canvas->fillRect(x_2 - move, PPLTView::height - h, w, h, color);
      break;
    case 3:
      PPLTView::canvas->fillRect(x_3 - move, PPLTView::height - h, w, h, color);
      break;
  }
}

///-----------
/// getRGBfromHSV
///-----------
uint16_t PPLTViewSample::getRGBfromHSV(float hue, float saturation, float value){

  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  if (saturation == 0.0) {
      // グレースケールの場合
      r = g = b = (uint8_t)(value * 255);
      return PPLTView::canvas->color565(r, g, b);
  }

  float sectionedHue = hue / 60.0;        // 0-6の範囲に変換
  int section = (int)sectionedHue;        // hue（色相）の整数部分
  float decimal = sectionedHue - section; // hue（色相）の小数部分

  // 一時変数。彩度（saturation）と明度（value）に基づいて計算
  float p = value * (1 - saturation);
  float q = value * (1 - saturation * decimal);
  float t = value * (1 - saturation * (1 - decimal));

  switch (section) {
    case 0:
        r = (uint8_t)(value * 255);
        g = (uint8_t)(t * 255);
        b = (uint8_t)(p * 255);
        break;
    case 1:
        r = (uint8_t)(q * 255);
        g = (uint8_t)(value * 255);
        b = (uint8_t)(p * 255);
        break;
    case 2:
        r = (uint8_t)(p * 255);
        g = (uint8_t)(value * 255);
        b = (uint8_t)(t * 255);
        break;
    case 3:
        r = (uint8_t)(p * 255);
        g = (uint8_t)(q * 255);
        b = (uint8_t)(value * 255);
        break;
    case 4:
        r = (uint8_t)(t * 255);
        g = (uint8_t)(p * 255);
        b = (uint8_t)(value * 255);
        break;
    default:
        r = (uint8_t)(value * 255);
        g = (uint8_t)(p * 255);
        b = (uint8_t)(q * 255);
        break;
  }
  return PPLTView::canvas->color565(r, g, b);
}