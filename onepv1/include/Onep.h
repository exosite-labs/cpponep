/*=============================================================================
* Onep.h
* Wrapper class for One Platofrm API procedures.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#ifndef ONEPV1_H_
#define ONEPV1_H_

#include "json/json.h"

using std::string;
namespace onepv1{

class Result;
class TransportInterface;
class Onep{
    public:
      explicit Onep(string url);
      Result activate(string clientkey,string codetype, string code);
      // The comment function is deprecated in the One Platform
      //Result comment(string clientkey,string rid, string visibility,string comment);
      Result create(string clientkey,string type,Json::Value desc);
      Result deactivate(string clientkey,string codetype, string code);
      Result drop(string clientkey,string rid);
      Result flush(string clientkey,string rid);
      Result info(string clientkey,string rid,Json::Value options);
      Result listing(string clientkey,Json::Value types);       
      Result lookup(string clientkey,string type, string alias);
      Result map(string clientkey,string rid, string alias);
      Result read(string clientkey,string rid,Json::Value options);
      Result record(string clientkey,string rid,Json::Value entries,Json::Value = Json::Value(Json::objectValue));
      Result recordbatch(string clientkey,string rid,Json::Value entries,Json::Value = Json::Value(Json::objectValue));
      Result revoke(string clientkey,string codetype, string code);
      Result share(string clientkey,string rid, Json::Value options);
      Result unmap(string clientkey,string alias);
      Result update(string clientkey,string rid, Json::Value desc);
      Result usage(string clientkey,string rid, string metric, int starttime, int endtime);         
      Result write(string clientkey,string rid,int value,Json::Value = Json::Value(Json::objectValue));     
      Result write(string clientkey,string rid,double value,Json::Value = Json::Value(Json::objectValue));
      Result write(string clientkey,string rid,const char* value,Json::Value = Json::Value(Json::objectValue));
      Result write(string clientkey,string rid,const string value,Json::Value = Json::Value(Json::objectValue));
      Result write(string clientkey,Json::Value entries,Json::Value = Json::Value(Json::objectValue));
      Result writegroup(string clientkey,Json::Value entries);
      Result writegroup(string clientkey,Json::Value entries, Json::Value options);
      
    private:
      Onep(){}
      TransportInterface* transport;
      Result callRPC(string clientkey,string proc,Json::Value arguments);    
};

}

#endif
