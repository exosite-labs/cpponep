/*=============================================================================
* example.cpp
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
#include <thread>
#include <chrono>

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
       string alias2 = "X2";
       Onep conn = Onep("https://m2.exosite.com/onep:v1/rpc/process");             
        
       try{
         string rid;
         string rid2;
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
           Result res_newdp2 = conn.create(cik, "dataport", getDescription());
           if (res_newdp2.status() == Result::OK){
             rid2 = res_newdp2.message();
             cout << "Dataport: "<< rid2 << " is created." << endl;
             // Map alias to new created dataport.
             if (Result::OK ==conn.map(cik,rid2,alias2).status()){
               cout << "Dataport: "<< rid2 << " is mapped to " << alias << endl;
             }
           }
         }
         // write data to dataport
         srand((unsigned)time(0)); 
         int data = int(rand()%100);
         Result res1 = conn.write(cik,rid,data);         
         if (res1.status() == Result::OK){
            cout<< "Data " << data << " is written to single dataport X1."<<endl;
         }

         // read data from dataport       
         Result res2 = conn.read(cik,rid,EmptyOption::getInstance());        
         if (res2.status() == Result::OK){
           cout << "Data read from X1:" << endl << res2.message(); 
         }

         // write group data to dataports
         this_thread::sleep_for(chrono::seconds(2));
         srand((unsigned)time(0));
         data = int(rand()%100);
         Json::Value entries;
         Json::Value array;
         array.append(rid);
         array.append(data);
         Json::Value array2;
         array2.append(rid2);
         array2.append(data);
         entries.append(array);
         entries.append(array2);
         Result res8 = conn.writegroup(cik,entries); 
         if (res8.status() == Result::OK) {
            cout << "Data " << data << " is written to both dataports X1 and X2" << endl;
         }

         // read data from dataports
         Result res9 = conn.read(cik, rid, EmptyOption::getInstance());
         if (res9.status() == Result::OK) {
            cout << "Data read from X1:" << endl << res9.message();
         }
         Result res10 = conn.read(cik, rid2, EmptyOption::getInstance());
         if (res10.status() == Result::OK) {
            cout << "Data read from X2:" << endl << res10.message();
         }

         // drop dataports
         Result res3 = conn.drop(cik,rid);
         if (res3.status() == Result::OK){
           cout << "Dataport: "<< rid << " is dropped." << endl; 
         }
         Result res11 = conn.drop(cik,rid2);
         if (res11.status() == Result::OK) {
            cout << "Dataport: " << rid2 << " is dropped." << endl;
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

