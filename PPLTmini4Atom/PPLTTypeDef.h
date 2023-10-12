///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_TYPEDEF__
#define __PPLT_TYPEDEF__

///----------------------
/// このファイルは当初各所に散らばっていた定義を
/// 取り急ぎ１か所へまとめたものである。
///----------------------

// Main+Subモジュールの最大数。
// ATOMS3のことをモジュールと呼んでいる。
// Main=I2C Master、Sub=I2C Slaveに相当。
#define MAX_MODULENUM  (9)

/// モジュールアドレス（＝I2C通信のスレーブID。7bit）
using PPLTAddress = uint8_t;

/// モジュール（ボタン）の位置を示す9bitのコード
// bit0 : モジュール１
// bit1 : モジュール２
// bit2 : モジュール３
// bit3 : モジュール４
// bit4 : モジュール５
// bit5 : モジュール６
// bit6 : モジュール７
// bit7 : モジュール８
// bit8 : モジュール９
// bit9以降は未使用
//
// ex:四隅タッチは 0b101000101 のように内部で表現される
// *7*  8  *9*  = 0b101000000
//  4   5   6   = 0b000000000
// *1*  2  *3*  = 0b000000101
using PPLTStateCode = uint16_t;

//  7   8   9   = 0b000000000
//  4   5   6   = 0b000000000
//  1   2   3   = 0b000000000
#define CODE_NONE         0b000000000
//  7   8   9   = 0b000000000
//  4   5   6   = 0b000000000
//  1   2   3   = 0b000000000
#define CODE_TOUCH_9      0b100000000
#define CODE_TOUCH_8      0b010000000
#define CODE_TOUCH_7      0b001000000
#define CODE_TOUCH_6      0b000100000
#define CODE_TOUCH_5      0b000010000
#define CODE_TOUCH_4      0b000001000
#define CODE_TOUCH_3      0b000000100
#define CODE_TOUCH_2      0b000000010
#define CODE_TOUCH_1      0b000000001
//  7   8   9   = 0b000000000
//  4  *5*  6   = 0b000010000
//  1   2   3   = 0b000000000
#define CODE_CENTERTOUCH  0b000010000
//  7   8   9   = 0b000000000
//  4   5   6   = 0b000000000
// *1* *2* *3*  = 0b000000111
#define CODE_UNDERTOUCH   0b000000111
//  7   8   9   = 0b000000000
//  4   5   6   = 0b000000000
// *1*  2  *3*  = 0b000000101
#define CODE_SIDETOUCH    0b000000101
// *7*  8  *9*  = 0b101000000
//  4   5   6   = 0b000000000
// *1*  2  *3*  = 0b000000101
#define CODE_LOVETOUCH    0b101000101
// *7* *8* *9*  = 0b111000000
// *4* *5* *6*  = 0b000111000
// *1* *2* *3*  = 0b000000111
#define CODE_FULLTOUCH    0b111111111


/// アプリケーション遷移時に指定するパラメータ
using PPLTIntentParam = uint8_t;

/// 描画タスクへ指定するパラメータ
using PPLTViewParam = uint8_t;

/// モジュールタイプ
enum class PPLTConnectType {
  Main, // I2Cマスター（1個に使用）
  Sub,  // I2Cスレーブ（8個に使用）
};

/// モジュールのボタン押下状態
enum class PPLTButtonState {
  Off,
  Pressed,
};

/// 描画タイプ。モジュールのディスプレイへ指定する表示内容。
/// PPLTApp系クラスで指定し、PPLTView系クラスで参照する。
enum class PPLTViewType : uint8_t {
  Scanning,
  Demo,
  Clear,
  Launcher_1,
  Launcher_2,
  Launcher_3,
  Launcher_4,
  Launcher_5,
  Launcher_6,
  Launcher_7,
  Launcher_8,
  Launcher_9,
  PPLT_Blank,
  PPLT_Ready,
  PPLT_Target,
  PPLT_ResultExcellent,
  PPLT_ResultGreat,
  PPLT_ResultGood,
  PPLT_ResultBad,
  PPLT_Countdown,
  PPLT_Stat,
  LightsOut_On,
  LightsOut_Off,
  FlashTouch_Question,
  FlashTouch_AnswerSuccess,
  FlashTouch_AnswerFailed,
  KeyPad,
  Error
};

/// アプリケーションタイプ。
/// PPLTApp系クラスを増減する場合はこの定義も増減する必要がある。
enum class PPLTAppType {
  Demo,
  Launcher,
  GameReady,
  GameCountdown,
  GamePlaying,
  GameResult,
  GameStat,
  LightsOut,
  FlashTouch,
  KeyPadGame,
};

///----------------------
/// I2C経由で通信するパケット
///----------------------
#pragma pack( push, 1 )
/// I2C通信　Main -> Sub 方向の送信パケット
using PacketToSub = struct PPLTConnectPacketMain2Sub {
  PPLTAddress target;
  PPLTAppType app;
  PPLTViewType view;
  PPLTViewParam param;
};
/// I2C通信　Sub -> Main 方向の返信パケット
using PacketFromSub = struct PPLTConnectPacketSub2Main {
  PPLTButtonState nowButtonState;
  PPLTViewType view;
  PPLTViewParam param;
};
#pragma pack( pop )

#endif //__PPLT_TYPEDEF__
