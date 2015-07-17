#ifndef PROVISION_H_
#define PROVISION_H_

#include <string>
#include <list>

using std::string;
using namespace std;
namespace onepv1{

class Result;
class TransportInterface;
class Provision{
	public:
		explicit Provision(string url, bool managebycik, bool managebysharecode);
		Result content_create(string key, string model, string contentid, string meta, bool protect);
		Result content_download(string cik, string vendor, string model, string contentid);
		Result content_info(string key, string model, string contentid, string vendor);
		Result content_list(string key, string model);
		Result content_remove(string key, string model, string contentid);
		Result content_upload(string key, string model, string contentid, string data, string mimetype);
		Result model_create(string key, string model, string sharecode, bool aliases, bool comments, bool historical);
		Result model_info(string key, string model);
		Result model_list(string key);
		Result model_remove(string key, string model);
		Result model_update(string key, string model, string clonerid, bool aliases, bool comments, bool historical);
		Result serialnumber_activate(string model, string serialnumber, string vendor);
		Result serialnumber_add(string key, string model, string sn);
		Result serialnumber_add_batch(string key, string model, string sns[], int snsSize);
		Result serialnumber_disable(string key, string model, string serialnumber);
		Result serialnumber_enable(string key, string  model, string serialnumber, string owner);
		Result serialnumber_info(string key, string model, string serialnumber);
		Result serialnumber_list(string key, string model, int offset, int limit);
		Result serialnumber_reenable(string key, string model, string serialnumber);
		Result serialnumber_remap(string key, string model, string serialnumber, string oldsn);
		Result serialnumber_remove(string key, string model, string serialnumber);
		Result serialnumber_remove_batch(string key, string model, string sns[], int snsSize);
		Result vendor_register(string key, string vendor);
		Result vendor_show(string key);
		Result vendor_unregister(string key, string vendor);
		static const string PROVISION_BASE;
		static const string PROVISION_ACTIVATE;
		static const string PROVISION_DOWNLOAD;
		static const string PROVISION_MANAGE;
		static const string PROVISION_MANAGE_MODEL;
		static const string PROVISION_MANAGE_CONTENT;
		static const string PROVISION_REGISTER;
	private:
		Provision(){}
		TransportInterface* transport;
		bool _manage_by_cik;
		bool _manage_by_sharecode;
		Result request(string path, string key, string data, string method, bool managebycik, list<string> extra_headers);
	};
}

#endif
