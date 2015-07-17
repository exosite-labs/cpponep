#include <string>
#include <iostream>
#include <list>
#include "JsonHandler.h"
#include "Provision.h"
#include "HttpTransport.h"
#include "Result.h"

using namespace std;

namespace onepv1{
	const string Provision::PROVISION_BASE = "/provision";
	const string Provision::PROVISION_ACTIVATE = PROVISION_BASE + "/activate";
	const string Provision::PROVISION_DOWNLOAD = PROVISION_BASE + "/download";
	const string Provision::PROVISION_MANAGE = PROVISION_BASE + "/manage";
	const string Provision::PROVISION_MANAGE_MODEL = PROVISION_MANAGE +"/model/";
	const string Provision::PROVISION_MANAGE_CONTENT = PROVISION_MANAGE +"/content/";
	const string Provision::PROVISION_REGISTER = PROVISION_BASE + "/register";

	Provision::Provision(string url, bool managebycik, bool manangebysharecode) : _manage_by_cik(managebycik), _manage_by_sharecode(manangebysharecode) {
		HttpTransport *obj = new HttpTransport(url);
		transport = (TransportInterface*) obj;
	}

	Result Provision::request(string path, string key, string data, string method, bool managebycik, list<string> extra_headers) {
		string url, body;
		if (method == "GET")
		{
			if (data.length() > 0)
				url = path + "?" + data;
			else
				url = path;
			body = "";    
		}
		else
		{
			url = path;
			body = data;
		}
		list<string> headers;
		if (_manage_by_cik)
			headers.push_back("X-Exosite-CIK: " + key);
		else
			headers.push_back("X-Exosite-Token: " + key);
		if (method == "POST")
			headers.push_back("Content-Type: application/x-www-form-urlencoded; charset=utf-8");
		headers.push_back("Accept: text/plain, text/csv, application/x-www-form-urlencoded");
		if (!extra_headers.empty()) { 
			headers.splice(headers.end(), extra_headers);
		}
		string response = transport->provisionSend(body, method, url, headers);
		if (response == "fail") return Result(Result::FAIL, "Provision Request failed");
		else return Result(Result::OK, response);
	}

	Result Provision::content_create(string key, string model, string contentid, string meta, bool protect) {
		string data = "id=" + contentid + "&meta=" + meta;
		if (protect != false) data = data + "&protected=true";
		string path = PROVISION_MANAGE_CONTENT + model + "/";
		return request(path, key, data, "POST", _manage_by_cik, list<string>());
	}

	Result Provision::content_download(string cik, string vendor, string model, string contentid) {
		string data = "vendor=" + vendor + "&model=" + model + "&id=" + contentid;
		list<string> headers;
		headers.push_back("Accept: *");
		return request(PROVISION_DOWNLOAD, cik, data, "GET", true, headers);
	}

	Result Provision::content_info(string key, string model, string contentid, string vendor) {
		if (vendor == "") {
			string path = PROVISION_MANAGE_CONTENT + model + "/" + contentid;
			return request(path, key, "", "GET", _manage_by_cik, list<string>());
		}
		else {
			string data = "vendor=" + vendor + "&model=" + model + "&info=true";
			return request(PROVISION_DOWNLOAD, key, data, "GET", _manage_by_cik, list<string>());
		}
	}
	Result Provision::content_list(string key, string model) {
		string path = PROVISION_MANAGE_CONTENT + model + "/";
        return request(path, key, "", "GET", _manage_by_cik, list<string>()); 
	}
	Result Provision::content_remove(string key, string model, string contentid) {
		string path = PROVISION_MANAGE_CONTENT + model + "/" + contentid;
        return request(path, key, "", "DELETE", _manage_by_cik, list<string>());
	}
	Result Provision::content_upload(string key, string model, string contentid, string data, string mimetype) {
		list<string> headers; 
		headers.push_back("Content-Type: " + mimetype);
		string path = PROVISION_MANAGE_CONTENT + model + "/" + contentid;
        return request(path, key, data, "POST", _manage_by_cik, headers);
	}
	Result Provision::model_create(string key, string model, string sharecode, bool aliases, bool comments, bool historical) {
		string data = "model=" + model;
		if (_manage_by_sharecode) data = data + "&code=" + sharecode;
		else data = data + "&rid=" + sharecode;
		if (aliases == false) data = data + "&options[]=noaliases";
		if (comments == false) data = data + "&options[]=nocomments";
		if (historical == false) data = data + "&options[]=nohistorical";
		return request(PROVISION_MANAGE_MODEL, key, data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::model_info(string key, string model) {
		return request(PROVISION_MANAGE_MODEL + model, key, "", "GET", _manage_by_cik, list<string>());
	}
	Result Provision::model_list(string key) {
		return request(PROVISION_MANAGE_MODEL, key, "", "GET", _manage_by_cik, list<string>());
	}
	Result Provision::model_remove(string key, string model) {
		string data = "delete=true&model=" + model + "&confirm=true";
		string path = PROVISION_MANAGE_MODEL + model;
		return request(path, key, data, "DELETE", _manage_by_cik, list<string>());
	}
	Result Provision::model_update(string key, string model, string clonerid, bool aliases, bool comments, bool historical) {
		string data = "rid=" + clonerid;
		if (aliases == false) data = data + "&options[]=noaliases";
		if (comments == false) data = data + "&options[]=nocomments";
		if (historical == false) data = data + "&options[]=nohistorical";
		string path = PROVISION_MANAGE_MODEL + model;
		return request(path, key, data, "PUT", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_activate(string model, string serialnumber, string vendor) {
		string data = "vendor=" + vendor + "&model=" + model + "&sn=" + serialnumber;
		return request(PROVISION_ACTIVATE, "", data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_add(string key, string model, string sn) {
		string data = "add=true&sn=" + sn;
		string path = PROVISION_MANAGE_MODEL + model + "/";
		return request(path, key, data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_add_batch(string key, string model, string sns[], int snsSize) {
		string data = "add=true";
		for (int i = 0; i < snsSize; i++) {
			data = data + "&sn[]=" + sns[i];
		}
		string path = PROVISION_MANAGE_MODEL + model + "/";
		return request(path, key, data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_disable(string key, string model, string serialnumber) {
		string data = "disable=true";
		string path = PROVISION_MANAGE_MODEL + model + "/" + serialnumber;
		return request(path, key, data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_enable(string key, string model, string serialnumber, string owner) {
		string data = "enable=true&owner=" + owner;
		string path = PROVISION_MANAGE_MODEL + model + "/" + serialnumber;
		return request(path, key, data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_info(string key, string model, string serialnumber) {
		string path = PROVISION_MANAGE_MODEL + model + "/" + serialnumber;
		return request(path, key, "", "GET", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_list(string key, string model, int offset, int limit) {
		string data = "offset=" + to_string(offset) + "&limit=" + to_string(limit);
		string path = PROVISION_MANAGE_MODEL + model + "/";
		return request(path, key, data, "GET", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_reenable(string key, string model, string serialnumber) {
		string data = "enable=true";
		string path = PROVISION_MANAGE_MODEL + model + "/" + serialnumber;
		return request(path, key, data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_remap(string key, string model, string serialnumber, string oldsn) {
		string data = "enable=true&oldsn=" + oldsn;
		string path = PROVISION_MANAGE_MODEL + model + "/" + serialnumber;
		return request(path, key, data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_remove(string key, string model, string serialnumber) {
		string path = PROVISION_MANAGE_MODEL + model + "/" + serialnumber;
		return request(path, key, "", "DELETE", _manage_by_cik, list<string>());
	}
	Result Provision::serialnumber_remove_batch(string key, string model, string sns[], int snsSize) {
		string data = "remove=true";
		for (int i = 0; i < snsSize; i++) {
			data = data + "&sn[]=" + sns[i];
		}
		string path = PROVISION_MANAGE_MODEL + model + "/";
        return request(path, key, data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::vendor_register(string key, string vendor) {
		string data = "vendor=" + vendor;
		return request(PROVISION_REGISTER, key, data, "POST", _manage_by_cik, list<string>());
	}
	Result Provision::vendor_show(string key) {
		return request(PROVISION_REGISTER, key, "", "GET", false, list<string>());
	}
	Result Provision::vendor_unregister(string key, string vendor) {
		string data = "delete=true&vendor=" + vendor;
		return request(PROVISION_REGISTER, key, data, "POST", false, list<string>());
	}
}