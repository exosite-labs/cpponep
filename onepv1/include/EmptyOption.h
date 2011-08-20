/*=============================================================================
* EmptyOption.h
* For empty option in procedure call.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#include "json/json.h"
namespace onepv1{

class EmptyOption
{
   public:
       static Json::Value getInstance();
       ~EmptyOption(){}
   private:
       EmptyOption(){}     
};

}
