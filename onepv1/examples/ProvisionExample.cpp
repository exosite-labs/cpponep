/*=============================================================================
* ProvisionExample.cpp
* Provision use-case examples.
* Note that CIK strings ("PUTA40CHARACTER...") need to be replaced with a valid
* value.
*==============================================================================
*
* Copyright (c) 2015, Exosite LLC
* All rights reserved.
*/

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "json/json.h"
#include "cpponep.h"

using namespace std;
using namespace onepv1;

int main (int argc, char *argv[]) {
      cout << "cpponep ProvisionExample.cpp" << endl << endl;
      string vendorname = "VENDORNAMEHERE";
      string vendortoken = "VENDORTOKENHERE";
      string clonecik = "CLONECIKHERE";
      string cloneportalcik = "CLONEPORTALCIKHERE"; //use only if managing by sharecode
      string portalcik = "PORTALCIKHERE";

      srand((unsigned)time(0));
      int r = int(rand() % 10000001);
      string model = "MyTestModel" + to_string(r);
      string sn1 = "001" + to_string(r);
      string sn2 = "002" + to_string(r);
      string sn3 = "003" + to_string(r);
      Onep conn = Onep("http://m2.exosite.com/onep:v1/rpc/process");
      Result portalridResult = conn.lookup(portalcik, "alias", "");
      string portalrid;
      string clonerid;
      if (portalridResult.status() == Result::OK) {
            portalrid = portalridResult.message();
            cout << "portalrid: " << portalrid << endl;
      }
      else cout << "Failed to look up portal RID";
      Result cloneridResult = conn.lookup(clonecik, "alias", "");
      Provision provision("", NULL, NULL);
      if (cloneridResult.status() == Result::OK) {
            clonerid = cloneridResult.message();
            cout << "clonerid: " << clonerid << endl;
            provision = Provision("http://m2.exosite.com", false, true);
      }
      else cout << "Failed to look up clone RID";
      Json::Value meta;
      string option = "[\"" + vendorname + "\", \"" + model + "\"]";
      meta["meta"] = option;
      string sharecode = conn.share(cloneportalcik, clonerid, meta).message();
      try {
            cout << endl << "model_create()" << endl << provision.model_create(vendortoken, model, sharecode, false, true, true).message() << endl;
            cout << endl << "model_list()" << endl << provision.model_list(vendortoken).message() << endl;
            cout << endl << "model_info()" << endl << provision.model_info(vendortoken, model).message() << endl;
            cout << endl << "serialnumber_add()" << endl << provision.serialnumber_add(vendortoken, model, sn1).message() << endl;
            cout << endl << "serialnumber_add_batch()" << endl;
            static int sn2andsn3Size = 2;
            string sn2andsn3[sn2andsn3Size];
            sn2andsn3[0] = sn2;
            sn2andsn3[1] = sn3;
            cout << endl << provision.serialnumber_add_batch(vendortoken, model, sn2andsn3, sn2andsn3Size).message() << endl;
            cout << endl << "serialnumber_list()" << endl << provision.serialnumber_list(vendortoken, model, 0, 10).message() << endl;
            cout << endl << "serialnumber_remove_batch()" << endl << provision.serialnumber_remove_batch(vendortoken, model, sn2andsn3, sn2andsn3Size).message() << endl;
            cout << endl << "serialnumber_list()" << endl << provision.serialnumber_list(vendortoken, model, 0, 1000).message() << endl;
            cout << endl << "serialnumber_enable()" << endl; 
            provision.serialnumber_enable(vendortoken, model, sn1, portalrid); //return clientid
            cout << endl << "AFTER ENABLE: " << provision.serialnumber_info(vendortoken, model, sn1).message() << endl;
            cout << endl << "serialnumber_disable()" << endl;
            provision.serialnumber_disable(vendortoken, model, sn1);
            cout << endl << "AFTER DISABLE: " << provision.serialnumber_info(vendortoken, model, sn1).message() << endl;
            cout << endl << "serialnumber_reenable()" << endl;
            provision.serialnumber_reenable(vendortoken, model, sn1);
            cout << endl << "AFTER REENABLE: " << provision.serialnumber_info(vendortoken, model, sn1).message() << endl;
            cout << endl << "serialnumber_activate()" << endl;
            //return client key
            string sn_cik = provision.serialnumber_activate(model, sn1, vendorname).message();
            cout << endl << "AFTER ACTIVATE: " << provision.serialnumber_info(vendortoken, model, sn1).message() << endl;
            cout << endl << "content_create()" << endl << provision.content_create(vendortoken, model, "a.txt", "This is text", false).message() << endl;
            cout << endl << "content_upload()" << endl <<provision.content_upload(vendortoken, model, "a.txt", "This is content data", "text/plain").message() << endl;
            cout << endl << "content_list()" << endl << provision.content_list(vendortoken, model).message() << endl;
            cout << endl << vendortoken << endl << model << endl << "a.txt" << endl;
            cout << endl << "content_remove()" << endl;
            provision.content_remove(vendortoken, model, "a.txt");
            cout << endl << "model_remove()" << endl;
            provision.model_remove(vendortoken, model);
      }
      catch (ProvisionException e) {
            cout << endl << "ProvisionExample sequence exception:" << endl << e.message();
      }
      return 0;
}