/*=============================================================================
* HttpTransport.h
* HTTP-based JSON-RPC request call. 
*============================================================================== 
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#ifndef HTTP_TRANSPORT_H_
#define HTTP_TRANSPORT_H_

#include "TransportInterface.h"

namespace onepv1{

class HttpTransport : public TransportInterface{
  public:
    explicit HttpTransport(std::string url);
  private: 
    HttpTransport(){}
    std::string _url;
    std::string send(std::string request);        
};

}

#endif


