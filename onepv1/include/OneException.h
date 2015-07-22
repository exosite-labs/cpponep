/*=============================================================================
* OneException.h
* Exception classes for JSON-RPC. 
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#ifndef ONE_EXCEPTION_H_
#define ONE_EXCEPTION_H_

namespace onepv1{

class OneException{
  public:
    explicit OneException(std::string message) : _message(message) {}
    std::string message();
  private:
    OneException(){}
    std::string _message;      
};
class OnePlatformException: public OneException{
  public:
    OnePlatformException(std::string message) : OneException(message) {}         
};
class HttpRPCRequestException: public OneException{
  public:
    HttpRPCRequestException(std::string message) : OneException(message) {}         
};
class ProvisionException: public OneException{
  public:
    ProvisionException(std::string message) : OneException(message) {}
};

}

#endif
