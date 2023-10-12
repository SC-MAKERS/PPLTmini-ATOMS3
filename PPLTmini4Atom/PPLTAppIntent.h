///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#ifndef __PPLT_APP_INTENT__
#define __PPLT_APP_INTENT__

#include <memory>
#include <M5Unified.h>
#include "PPLTTypeDef.h"

// PPLTAppIntentクラスは、PPLTApp系クラスがgetNextAppメソッドを通じて
// 次に遷移するアプリケーションを指定するときに任意のパラメータも併せて
// 指定できるようにするためのクラス。
// Androidにおける画面遷移時のIntentを参考にした設計。

///--------------------------
/// PPLTAppIntent
///--------------------------
class PPLTAppIntent {
// fields
private:
  PPLTAppType type;
  PPLTIntentParam param;

// methods
public:
  PPLTAppIntent(PPLTAppType);
  PPLTAppIntent(PPLTAppType, PPLTIntentParam);
  PPLTAppType getType();
  PPLTIntentParam getParam();

};

using PPLTAppIntentPointer = std::shared_ptr<PPLTAppIntent>;

#endif //__PPLT_APP_INTENT__
