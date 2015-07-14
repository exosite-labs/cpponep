/*=============================================================================
* JsonHandler.h
* Parse and process JSON-RPC request/response string.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#ifndef JSON_HANDLER_H_
#define JSON_HANDLER_H_

#include "cpponep.h"

namespace onepv1{

class Result;

class JsonHandler{
  public:
    friend class Onep;  
    static std::string getRequest(std::string,std::string,Json::Value);
    static Result parseResponse(std::string);
    
  private:
    JsonHandler(){}
    static Json::Value getArguments(std::string first);
    static Json::Value getArguments(Json::Value desc);    
    static Json::Value getArguments(std::string first,Json::Value desc);
    static Json::Value getArguments(Json::Value entries,Json::Value options);    
    static Json::Value getArguments(std::string first,std::string second);
    static Json::Value getArguments(std::string first,std::string second,std::string third); 
    static Json::Value getArguments(std::string rid,Json::Value entries,Json::Value options);
    static Json::Value getArguments(std::string rid,int value,Json::Value options);   
    static Json::Value getArguments(std::string rid,double value,Json::Value options);
    static Json::Value getArguments(std::string rid,std::string value,Json::Value options);
    static Json::Value getArguments(std::string rid,const char* value,Json::Value options);
    static Json::Value getArguments(std::string rid,std::string metric, int starttime, int endtime);
};

}

#endif 
