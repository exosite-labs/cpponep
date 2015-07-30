/*=============================================================================
* Onep.cpp
* Wrapper class for One Platofrm API procedures.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#include <string>
#include <iostream>
#include "JsonHandler.h"
#include "Onep.h"
#include "HttpTransport.h"
#include "Result.h"

using namespace std;

namespace onepv1{

  Onep::Onep(string url){
     HttpTransport *obj =  new HttpTransport(url);
     transport =  (TransportInterface*) obj; 
  }

  Result Onep::callRPC(string clientkey,string proc,Json::Value arguments){
    string reqstr = JsonHandler::getRequest(clientkey,proc,arguments);
    string resstr = transport->send(reqstr);
    return JsonHandler::parseResponse(resstr);
  }

  Result Onep::activate(string clientkey,string codetype, string code){
    Json::Value argu = JsonHandler::getArguments(codetype,code);
    return callRPC(clientkey,"activate",argu);
  }

  /* The comment function is deprecated in the One Platform
  Result Onep::comment(string clientkey,string rid, string visibility,string comment){
    Json::Value argu = JsonHandler::getArguments(rid,visibility,comment);
    return callRPC(clientkey,"comment",argu);
  }*/

  Result Onep::create(string clientkey,string type,Json::Value desc){
    Json::Value argu = JsonHandler::getArguments(type,desc);
    return callRPC(clientkey,"create",argu);
  }
  Result Onep::deactivate(string clientkey,string codetype, string code){
    Json::Value argu = JsonHandler::getArguments(codetype,code);
    return callRPC(clientkey,"deactivate",argu);
  }
  Result Onep::drop(string clientkey,string rid){
    Json::Value argu= JsonHandler::getArguments(rid);
    return callRPC(clientkey,"drop",argu);   
  }
  Result Onep::flush(string clientkey,string rid){
    Json::Value argu= JsonHandler::getArguments(rid);
    return callRPC(clientkey,"flush",argu);   
  }
  Result Onep::info(string clientkey,string rid,Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid,options);
    return callRPC(clientkey,"info",argu);
  }
  Result Onep::listing(string clientkey,Json::Value types){
    Json::Value argu = JsonHandler::getArguments(types);
    return callRPC(clientkey,"listing",argu);
  }
  Result Onep::listing(string clientkey,Json::Value types,Json::Value options){
    Json::Value argu = JsonHandler::getArguments(types, options);
    return callRPC(clientkey,"listing",argu);
  }
  Result Onep::listing(string clientkey, string rid, Json::Value types){
    Json::Value argu = JsonHandler::getArguments(rid, types);
    return callRPC(clientkey,"listing",argu);
  }
  Result Onep::listing(string clientkey, string rid, Json::Value types, Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid, types, options);
    return callRPC(clientkey,"listing",argu);
  }
  Result Onep::lookup(string clientkey,string type, string alias){
    Json::Value argu = JsonHandler::getArguments(type,alias);
    return callRPC(clientkey,"lookup",argu);   
  }

  Result Onep::map(string clientkey,string rid, string alias){
    Json::Value argu = JsonHandler::getArguments("alias",rid,alias);
    return callRPC(clientkey,"map",argu);
  }
  Result Onep::read(string clientkey,string rid,Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid,options);
    return callRPC(clientkey,"read",argu);   
  }  
  Result Onep::record(string clientkey,string rid,Json::Value entries, Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid,entries,options);
    return callRPC(clientkey,"record",argu); 
  }
  Result Onep::recordbatch(string clientkey,string rid,Json::Value entries, Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid,entries,options);
    return callRPC(clientkey,"recordbatch",argu);
  }
  Result Onep::revoke(string clientkey,string codetype, string code){
    Json::Value argu = JsonHandler::getArguments(codetype,code);
    return callRPC(clientkey,"revoke",argu);
  }
  Result Onep::share(string clientkey,string rid,Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid,options);
    return callRPC(clientkey,"share",argu);   
  }
  Result Onep::unmap(string clientkey,string alias){
    Json::Value argu = JsonHandler::getArguments("alias",alias);
    return callRPC(clientkey,"unmap",argu);    
  }
  Result Onep::update(string clientkey,string rid, Json::Value desc){
    Json::Value argu = JsonHandler::getArguments(rid,desc);
    return callRPC(clientkey,"update",argu);   
  } 
  Result Onep::usage(string clientkey,string rid, string metric, int starttime, int endtime) {
    Json::Value argu = JsonHandler::getArguments(rid,metric,starttime,endtime);
    return callRPC(clientkey,"usage",argu);
  }

  Result Onep::write(string clientkey,string rid,int value,Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid,value,options);
    return callRPC(clientkey,"write",argu);    
  }
 
  Result Onep::write(string clientkey,string rid,double value,Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid,value,options);
    return callRPC(clientkey,"write",argu);    
  } 
 
  Result Onep::write(string clientkey,string rid,const char* value,Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid,value,options);
    return callRPC(clientkey,"write",argu);    
  } 
  
  Result Onep::write(string clientkey,string rid,const string value,Json::Value options){
    Json::Value argu = JsonHandler::getArguments(rid,value,options);
    return callRPC(clientkey,"write",argu);    
  } 
  
  Result Onep::write(string clientkey,Json::Value entries,Json::Value options){
    Json::Value argu = JsonHandler::getArguments(entries,options);
    return callRPC(clientkey,"write",argu);    
  } 

  Result Onep::writegroup(string clientkey,Json::Value entries) {
    Json::Value argu = JsonHandler::getArguments(entries);
    return callRPC(clientkey,"writegroup",argu);
  }

  Result Onep::writegroup(string clientkey,Json::Value entries, Json::Value options) {
    Json::Value argu = JsonHandler::getArguments(entries,options);
    return callRPC(clientkey,"writegroup",argu);
  }
  
}
