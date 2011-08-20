/*=============================================================================
* EmptyOption.cpp
* For empty option in procedure call.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#include "EmptyOption.h"

namespace onepv1{

Json::Value EmptyOption::getInstance(){
  static Json::Value instance = Json::Value(Json::objectValue);
  return instance;
}

}
