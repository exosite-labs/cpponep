/*=============================================================================
* Result.cpp
* Represents the result of JSON-RPC.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#include <string>
#include "Result.h"

using std::string;
namespace onepv1{

Result::Result(string status,string message): _status(status),_message(message){}
string Result::status(){return _status;}
string Result::message(){return _message;}
const string Result::OK   = "ok";
const string Result::FAIL = "fail";

}
