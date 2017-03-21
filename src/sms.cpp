#include "kandy/sms.hpp"

#include <iostream>
#include <ostream>
#include <stdexcept>

#include "curl_easy.h"
#include "curl_header.h"
#include "curl_ios.h"
#include "curl_exception.h"
#include "json.hpp"

using namespace std;
using namespace curl;
using namespace nlohmann;

string operator ""_s(const char * str, size_t len) {
    return string(str, str + len);
}

namespace kandy {
	/*** Private ***/

	void sms::check_init_error(string domain_api_key, string domain_secret, string user_id) {
		if (domain_api_key.empty()) throw invalid_argument("Invalid Domain API key"_s);
        if (domain_secret.empty()) throw invalid_argument("Invalid Domain Secret"_s);
        if (user_id.empty()) throw invalid_argument("Invalid User ID"_s);
	}
	    	
	string sms::http_get(string url) {
		ostringstream stream;
	    curl_ios<ostringstream> writer(stream);	// Create a curl_ios object, passing the stream object.

	    curl_easy easy(writer);		// Pass the writer to the easy constructor
	    easy.add<CURLOPT_URL>(url.c_str());
	    easy.add<CURLOPT_SSL_VERIFYPEER>(false);
	    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

	    try {
	        easy.perform();		// Execute the request.
	        return stream.str();	// Return response
	    } catch (curl_easy_exception error) {
	        //curlcpp_traceback errors = error.get_traceback();	// get the entire error stack
	        error.print_traceback();	// Otherwise, print the stack like
	    }
	    return "";
	}
	
	string sms::http_post_json(string url, string payload) {
		ostringstream stream;
	    curl_ios<ostringstream> writer(stream);	// Create a curl_ios object, passing the stream object.

	    curl_header header;
	    header.add("Content-Type: application/json");

	    curl_easy easy(writer);		// Pass the writer to the easy constructor
	    easy.add<CURLOPT_HTTPHEADER>(header.get());
	    easy.add<CURLOPT_URL>(url.c_str());
	    easy.add<CURLOPT_SSL_VERIFYPEER>(false);
	    easy.add<CURLOPT_POSTFIELDS>(payload.c_str());


	    try {
	       	easy.perform();		// Execute the request.
	        return stream.str();	// Return response
	    } catch (curl_easy_exception error) {
	        //curlcpp_traceback errors = error.get_traceback();	// get the entire error stack
	        error.print_traceback();	// Otherwise, print the stack like
	    }
	    return "";
	}
	    	
	json sms::get_json(string body) {
	    if (body.empty()) return 0;
	    return json::parse(body);
	}
	
	void sms::get_user_access_token() {
		string url = "https://api.kandy.io/v1.2/domains/users/accesstokens?key=" + sms::g_domain_api_key 
			+ "&domain_api_secret=" + sms::g_domain_secret + "&user_id=" + sms::g_user_id;
	    string resp = http_get(url);

	    json j = get_json(resp);
	    if (j.empty()) throw runtime_error("User Access Token is null");


        if (j["status"] == 0 and !j["result"].empty() and !j["result"]["user_access_token"].empty()) {
            sms::g_user_access_token = j["result"]["user_access_token"];
        }
	}
	    	
	void sms::get_device_id() {
		string url = "https://api.kandy.io/v1.2/users/devices?key=" + sms::g_user_access_token;
	    string resp = http_get(url);

	    json j = get_json(resp);
	    if (j.empty()) throw runtime_error("Device ID is null");

	    if (!j["result"].empty() and !j["result"]["devices"][0]["id"].empty()) {
            sms::g_device_id = j["result"]["devices"][0]["id"];
        }
	}


	/*** Public ***/

	sms::sms(string domain_api_key, string domain_secret, string user_id, string &user_access_token, string &device_id) {
		sms::check_init_error(domain_api_key, domain_secret, user_id);
		sms::g_domain_api_key = domain_api_key;
		sms::g_domain_secret = domain_secret;
		sms::g_user_id = user_id;

	    sms::get_user_access_token();	    
	    sms::get_device_id();
	    user_access_token = sms::g_user_access_token;
	    device_id = sms::g_device_id;
	}

	sms::sms(string domain_api_key, string domain_secret, string user_id, bool &success) {
		string user_access_token, device_id;
		sms(domain_api_key, domain_secret, user_id, user_access_token, device_id);
		success = (!user_access_token.empty() and !device_id.empty());
	}
			
	bool sms::send(string source, string destination, string text) {
		if (sms::g_user_access_token.empty()) throw runtime_error("User Access Token is null"_s);
		if (sms::g_device_id.empty()) throw runtime_error("Device ID is null"_s);

		if (source.empty()) throw invalid_argument("Invalid source phone number"_s);
        if (destination.empty()) throw invalid_argument("Invalid destination phone number"_s);
        if (text.empty()) throw invalid_argument("Invalid text"_s);

		json payload;
	    payload["message"]["source"] = source;
	    payload["message"]["destination"] = destination;
	    payload["message"]["message"]["text"] = text;

	    string url = "https://api.kandy.io/v1.2/devices/smss?key=" + sms::g_user_access_token + "&device_id=" + sms::g_device_id;
	    string resp = http_post_json(url, payload.dump());


	    json j = get_json(resp);
	    if (j.empty()) throw runtime_error("SMS status is null"_s);

	    return (j["status"] == 0);
	}
}


