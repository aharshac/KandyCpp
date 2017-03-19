#ifndef KANDY_SMS_HPP
#define KANDY_SMS_HPP

#include <iostream>
#include <ostream>

#include "curl_easy.h"
#include "curl_header.h"
#include "curl_ios.h"
#include "curl_exception.h"
#include "json.hpp"

using namespace std;
using namespace curl;
using namespace nlohmann;

namespace kandy {
	class sms {
		private:
			string g_domain_api_key;
	    	string g_domain_secret;
	    	string g_user_id;
	    	string g_user_access_token;
	    	string g_device_id;

	    	void check_init_error(string domain_api_key, string domain_secret, string user_id);
	    	string http_get(string url);
	    	string http_post_json(string url, string payload);
	    	json get_json(string body);
	    	void get_user_access_token();
	    	void get_device_id();
	    	
		public:
			sms(string domain_key, string domain_secret, string user_id);
			bool send(string source, string destination, string text);
	};
}
#endif