///=====================================
/// Piko Piko Love Touch Mini for ATOM S3
/// (c)2023 Software Control Corporation
/// This software is licensed under the MIT license. See LICENSE file in the project root directory.
///=====================================

#include <memory>
#include "PPLTConnect.h"
#include "PPLTConnectMain.h"
#include "PPLTConnectSub.h"

///-----------
/// factory
///-----------
std::unique_ptr<PPLTConnect> PPLTConnect::factory(PPLTConnectType type, PPLTAddress addr) {
  switch(type){
    case PPLTConnectType::Sub:
      return std::unique_ptr<PPLTConnect>(new PPLTConnectSub(addr));
    default:
      return std::unique_ptr<PPLTConnect>(new PPLTConnectMain(addr));
  }
  
}

