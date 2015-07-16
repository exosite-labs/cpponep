#include <string>
#include <sstream>
#include <iostream>
#include <list>
/*=============================================================================
* HttpTransport.cpp
* HTTP-based JSON-RPC request call. 
*============================================================================== 
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "HttpTransport.h"
#include "OneException.h"
using namespace std;

namespace onepv1{

HttpTransport::HttpTransport(string url){
  _url=url;
}

string HttpTransport::send(string jsonreq){
  
  try {

    curlpp::Cleanup cleaner;
    curlpp::Easy request;
 
    request.setOpt(new curlpp::options::Url(_url)); 
    request.setOpt(new curlpp::options::Verbose(false)); 
    request.setOpt(new curlpp::options::ConnectTimeout(3000));

    std::list<std::string> header;      
    header.push_back("Content-Type: application/json; charset=utf-8"); 
    request.setOpt(new curlpp::options::HttpHeader(header)); 
    request.setOpt(new curlpp::options::PostFields(jsonreq));
    request.setOpt(new curlpp::options::PostFieldSize( jsonreq.length() )); 

    std::stringstream response;
    request.setOpt(new curlpp::options::WriteStream( &response ) );

    request.perform(); 
    return response.str();    
  }
  catch ( curlpp::LogicError & e ) {
    std::cout << e.what() << std::endl;
  }
  catch ( curlpp::RuntimeError & e ) {   
    std::cout << e.what() << std::endl;
    throw HttpRPCRequestException(e.what());
  }
  return "fail";
}

string HttpTransport::provisionSend(string message, string method, string url, list<string> headers) {
  url = _url + url;
  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    request.setOpt(new curlpp::options::Url(url));
    request.setOpt(new curlpp::options::Verbose(false));
    request.setOpt(new curlpp::options::ConnectTimeout(3000));
    request.setOpt(new curlpp::options::HttpHeader(headers));
    if (method == "POST") {
      request.setOpt(new curlpp::options::PostFields(message));
      request.setOpt(new curlpp::options::PostFieldSize(message.length()));
    }

    std::stringstream response;
    request.setOpt(new curlpp::options::WriteStream(&response));

    request.perform();
    return response.str();
  }
  catch(curlpp::LogicError & e ) {
    std::cout << e.what() << std::endl;
  }
  catch ( curlpp::RuntimeError & e ) {
    std::cout << e.what() << std::endl;
    throw HttpRPCRequestException(e.what());
  }
  return "fail";
}

}

