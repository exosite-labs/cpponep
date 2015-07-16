/*=============================================================================
* TransportInterface.h
* Transport tool interface - e.g. HTTP, XMPP.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#ifndef TRANSPORT_INTERFACE_H_
#define TRANSPORT_INTERFACE_H_

#include <list>

namespace onepv1{

class TransportInterface{
  public:
    virtual std::string send(std::string) = 0;
    virtual std::string provisionSend(std::string message, std::string method, std::string url, std::list<std::string> headers) = 0;
};

}

#endif


