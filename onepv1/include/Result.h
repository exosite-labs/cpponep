/*=============================================================================
* Result.h
* Represents the result of JSON-RPC.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#ifndef RESULT_H_
#define RESULT_H_

namespace onepv1{

class Result{
  public:
    Result(std::string,std::string);
    static const std::string OK;
    static const std::string FAIL;
    std::string status();
    std::string message();
  private:
    Result(){}
    std::string _status;
    std::string _message;
      
};

}

#endif

