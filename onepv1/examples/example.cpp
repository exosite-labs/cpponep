/*=============================================================================
* examples.cpp
* Use-case examples.
* Note that CIK strings ("PUTA40CHARACTER...") need to be replaced with a valid
* value.
*==============================================================================
*
* Copyright (c) 2011, Exosite LLC
* All rights reserved.
*/

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "json/json.h"
#include "cpponep.h"

using namespace std;
using namespace onepv1;

Json::Value getDescription(){
  Json::Value desc;
  desc["format"] = "integer";//data format
  desc["name"] = "who is me";//dataport name
  Json::Value preprocess1;
  preprocess1.append("add");//proprocess 'add 0'
  preprocess1.append(0);
  Json::Value preprocess;
  preprocess.append(preprocess1);
  desc["preprocess"]=preprocess;
  Json::Value retention;
  retention["count"] = "infinity";   // retention count
  retention["duration"]= "infinity";
  desc["retention"] = retention;  
  return desc; 
}

int main (int argc, char *argv[])
{     
       string cik  = "PUTA40CHARACTERCIKHERE";
       string alias = "X1"; 
       Onep conn = Onep("http://m2.exosite.com/api:v1/rpc/process");             
        
       try{
         string rid;
         // Get resource id (RID) of dataport given its alias name.
         Result res0 = conn.lookup(cik,"alias",alias);
         if (Result::OK == res0.status()){
            rid = res0.message();            
         }
         else{
           // If dataport with alias didn't exist, we will create it
           Result res_newdp = conn.create(cik, "dataport", getDescription());
           if (res_newdp.status() == Result::OK){
             rid = res_newdp.message();
             cout << "Dataport: "<< rid << " is created." << endl;
             // Map alias to new created dataport.
             if (Result::OK ==conn.map(cik,rid,alias).status()){
               cout << "Dataport: "<< rid << " is mapped to " << alias << endl;
             }
           }
         }
         // write data to dataport
         srand((unsigned)time(0)); 
         int data = int(rand()%100);
         Result res1 = conn.write(cik,rid,data);         
         if (res1.status() == Result::OK){
            cout<< "Data " << data << " is written."<<endl;
         }

         // read data from dataport       
         Result res2 = conn.read(cik,rid,EmptyOption::getInstance());        
         if (res2.status() == Result::OK){
           cout << "Data read:" << endl << res2.message(); 
         }

         // drop dataport
         Result res3 = conn.drop(cik,rid);
         if (res3.status() == Result::OK){
           cout << "Dataport: "<< rid << " is dropped." << endl; 
         }

         // List a client's dataports
          Json::Value options;
          options.append("dataport");
          Result res4 = conn.listing(cik,options);
          if (res4.status() == Result::OK){
               cout << "Dataport RIDs for client CIK " << cik << ":" << endl;
               cout << res4.message();
          }

          /* Get all mapping aliases information of dataports */
          // Get resource id of device given device key
          Result res5 = conn.lookup(cik,"alias","");
          string deviceRID = res5.message();
          // Get the alias information of given device
          Json::Value option;
          option["aliases"] = true;
          Result res6 = conn.info(cik,deviceRID,option);
          if (res6.status() == Result::OK){
            cout << "Dataport Alias' for client CIK " << cik << ":" << endl;
            cout << res6.message();
          }          
  
       }catch(HttpRPCRequestException e){
         cout<<e.message();
       }catch(OnePlatformException e){
         cout<<e.message();
       }     
     
  return 0;
}

