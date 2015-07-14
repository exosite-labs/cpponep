/*=============================================================================
* JsonHandler.cpp
* Parse and process JSON-RPC request/response string.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#include <string>
#include "json/json.h"
#include <typeinfo>
#include <iostream>
#include <sstream>

#include "JsonHandler.h"

using namespace std;

namespace onepv1{

  string JsonHandler::getRequest(string parentkey,string procedure,Json::Value argument){
    Json::Value root;
    Json::Value cik;
    Json::Value call;
    Json::Value calls;
    call["id"]=1;
    call["procedure"] = procedure;
    call["arguments"] = argument;
    calls.append(call);
    cik["cik"]= parentkey;
    root["auth"] = cik;
    root["calls"] = calls;    
    string out = root.toStyledString();
    return out;
  }
  Result JsonHandler::parseResponse(string response){
    Json::Reader reader;
    Json::Value root;
    bool parseOK = reader.parse(response,root);     
    if (parseOK){
      if (root.isObject()){                       
        throw OnePlatformException(root["error"].toStyledString()); 
      }          
      string status = root[0]["status"].asString();
      Json::Value result = root[0]["result"];   
      if (Result::OK == status) {              
        if (result.isString()){
          return Result(Result::OK, result.asString());                   
        }else if (result.isArray() || result.isObject()){
          return Result(Result::OK, result.toStyledString());
        }else{
          return Result(Result::OK, Result::OK);         
        }
      }else{
        return  Result(Result::FAIL, status);
      }     
    }
    throw OneException("Unknown Error.");    
  }

 Json::Value JsonHandler::getArguments(string first,Json::Value desc){
    Json::Value arguments = getArguments(first);
    arguments.append(desc);
    return arguments;
  }

  Json::Value JsonHandler::getArguments(string first){
    Json::Value arguments;
    Json::Value item = first;    
    arguments.append(item);    
    return arguments;     
  }
  Json::Value JsonHandler::getArguments(Json::Value desc){
    Json::Value arguments;
    arguments.append(desc);
    return arguments;
  }
  Json::Value JsonHandler::getArguments(string rid,Json::Value entries,Json::Value options){
    Json::Value arguments;
    arguments.append(rid);
    arguments.append(entries);
    arguments.append(options);
    return arguments;
  }
  Json::Value JsonHandler::getArguments(Json::Value entries,Json::Value options){
    Json::Value arguments;
    arguments.append(entries);
    arguments.append(options);
    return arguments;
  }
  Json::Value JsonHandler::getArguments(string first,string second){
    Json::Value arguments = getArguments(first);
    Json::Value item = second;
    arguments.append(item);
    return arguments;
  }

  Json::Value JsonHandler::getArguments(string first,string second,string third){
    Json::Value arguments = getArguments(first,second);
    Json::Value item = third;
    arguments.append(item);
    return arguments;
  }
  Json::Value JsonHandler::getArguments(string rid,int value,Json::Value options){
    Json::Value arguments;
    arguments.append(rid);
    arguments.append(value);
    arguments.append(options);
    return arguments;    
  }
  
  Json::Value JsonHandler::getArguments(string rid,double value,Json::Value options){
    Json::Value arguments;
    arguments.append(rid);
    arguments.append(value);
    arguments.append(options);
    return arguments;    
  }
  Json::Value JsonHandler::getArguments(string rid,string value,Json::Value options){
    Json::Value arguments;
    arguments.append(rid);
    arguments.append(value);
    arguments.append(options);
    return arguments;    
  }
  Json::Value JsonHandler::getArguments(string rid,const char* value,Json::Value options){
    Json::Value arguments;
    arguments.append(rid);
    arguments.append(value);
    arguments.append(options);
    return arguments;    
  }  

  Json::Value JsonHandler::getArguments(string rid, string metric, int starttime, int endtime) {
    Json::Value arguments;
    arguments.append(rid);
    arguments.append(metric);
    arguments.append(starttime);
    arguments.append(endtime);
    return arguments;
  }
}
