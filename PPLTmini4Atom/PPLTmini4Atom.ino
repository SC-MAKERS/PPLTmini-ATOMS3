///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include <memory>
#include <queue>
#include "PPLTConnect.h"
#include "PPLTView.h"
#include "PPLTApp.h"

#include "PPLTModuleInfo.h"
#include "PPLTPacketToSub.h"

//==================================================
// 各モジュールのパラメータ
// （モジュールへソフトウェアを書き込む前に書き換える）
//==================================================
const PPLTAddress MY_ADDRESS = 8;                      // 自アドレス(1-9)。I2Cアドレスとしても使用する。
const PPLTConnectType MY_TYPE = PPLTConnectType::Main; // 通信モード(Main or Sub)

//==================================================
// Variables
//==================================================

// タスクハンドラ
static TaskHandle_t taskComHandle;
static TaskHandle_t taskViewHandle;
static TaskHandle_t taskAppHandle;

// アプリケーションクラス
// アプリケーションタスクで使用。詳細は PPLTApp***クラスを参照。
// （電源ON時はDemoアプリ＝タイトル画面を生成する）
static auto ppltApp = PPLTApp::factory(MY_TYPE, MY_ADDRESS, PPLTAppType::Demo);

// 通信クラス（MY_TYPEに応じて異なるクラスが生成される）
// 通信タスクで使用。詳細は PPLTConnect***クラスを参照。
static auto ppltConnect = PPLTConnect::factory(MY_TYPE, MY_ADDRESS);

// 描画クラス
// 描画タスクで使用。詳細は PPLTView***クラスを参照。
static auto ppltView = PPLTView::factory(MY_ADDRESS);

// モジュール情報（ボタン押下状態など）を記憶するクラス。
// Mainモジュールは全てのSubモジュールの状態も記憶しており
// ９つのボタンがどのように操作されているか判断材料とする。
static auto ppltModuleInfo = PPLTModuleInfoPointer(new PPLTModuleInfo(MY_ADDRESS));
// MainモジュールからSubモジュールへ送信するパケットを記憶するキュー
static auto ppltQueue = std::queue<PPLTPacketToSubPointer>();

//==================================================
// Tasks
//==================================================

// アプリケーションタスク
void taskApp(void *__unused) {

  // 通信タスクの準備(begin)が終わるまで待機する
  vTaskSuspend(NULL); // NULL＝自分自身をサスペンド

  // Initialize App
  ppltApp->begin(&ppltQueue, ppltModuleInfo);

  // 無限ループ
  while (true) {
    ppltApp->update();

    // 次のアプリケーションに切り替える処理
    if (ppltApp->hasNextApp()) {
      auto intent = ppltApp->getNextApp();
      ppltApp = PPLTApp::factory(MY_TYPE, MY_ADDRESS, intent);
      ppltApp->begin(&ppltQueue, ppltModuleInfo);
    }
    delay(1);
  }
}

// 通信タスク
void taskCom(void *__unused) {

  // Initialize I2C Connection
  ppltConnect->begin(ppltModuleInfo);

  // 通信準備が整ったらアプリケーションタスクの実行を許可
  // （サスペンド状態になっているAppタスクを再開する）
  vTaskResume(taskAppHandle);

  // 無限ループ
  while (true) {
    ppltConnect->update();

    // 送信するデータがキューにあれば送る
    while (!ppltQueue.empty()) {
      auto popedData = ppltQueue.front();
      ppltConnect->postData(popedData);
      ppltQueue.pop();  // delete front data
      delay(1);
    }
    delay(1);
  }
}

// 描画タスク
void taskView(void *__unused) {

  // Initialize View
  ppltView->begin(ppltModuleInfo);

  // 無限ループ
  while (true) {
    ppltView->update();
    ppltView->draw();
    delay(1);
  }
}

//==================================================
// Methods
//==================================================

/// --------------
/// setup（エントリポイント）
/// --------------
void setup() {
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  cfg.output_power = true;   // 5V出力を利用する
  cfg.internal_imu = false;  // 内蔵IMUは使用しない
  M5.begin(cfg);
  
  // スピーカー設定（パッシブブザーを用いる）
  if( MY_TYPE == PPLTConnectType::Main ) {
    auto spk_cfg = M5.Speaker.config();
    spk_cfg.pin_data_out = 2; // ATOM S3のGrove互換インターフェースのピン番号
    spk_cfg.buzzer = true;
    M5.Speaker.config(spk_cfg);

    // 音量は最大に設定
    M5.Speaker.setVolume(255);
    M5.Speaker.setAllChannelVolume(255);
    M5.Speaker.setChannelVolume(0, 255);
  }

  // CPU周波数指定（240, 160, 80, 40, 20, 10）
  // Default: 240
  // ATOM S3を9個使用したときに消費電流が500mAを超える恐れがあり
  // USBポートへの負荷を抑えるために機能に影響ない範囲で下げておく
  setCpuFrequencyMhz(80);

  // タスクを起動
  xTaskCreatePinnedToCore(
    taskApp,         // タスクとして実行される関数へのポインタ
    "TaskApp",       // タスクの名前
    4096,            // タスクのスタックサイズ(byte)
    NULL,            // タスクに渡すパラメータ
    1,               // タスクの優先度(小さいほど高い)
    &taskAppHandle,  // タスクハンドルへのポインタ
    1);              // タスクを実行するコア（その他）

  xTaskCreatePinnedToCore(
    taskCom,         // タスクとして実行される関数へのポインタ
    "TaskCom",       // タスクの名前
    4096,            // タスクのスタックサイズ(byte)
    NULL,            // タスクに渡すパラメータ
    1,               // タスクの優先度(小さいほど高い)
    &taskComHandle,  // タスクハンドルへのポインタ
    0);              // タスクを実行するコア（通信タスク専用）

  xTaskCreatePinnedToCore(
    taskView,        // タスクとして実行される関数へのポインタ
    "TaskView",      // タスクの名前
    4096,            // タスクのスタックサイズ(byte)
    NULL,            // タスクに渡すパラメータ
    1,               // タスクの優先度(小さいほど高い)
    &taskViewHandle, // タスクハンドルへのポインタ
    1);              // タスクを実行するコア（その他）
}

/// --------------
/// loop
/// --------------
void loop() {
  // デフォルトのタスクは M5.update を実行し続ける役割
  delay(1);
  M5.update();
}
