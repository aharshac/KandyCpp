# **Kandy C++ SMS Library**
C++ wrapper for [Kandy.io](https://www.kandy.io/) REST API endpoints that deal with SMS.  

Read the complete docs for the REST API at [Kandy Developers](https://developer.kandy.io/docs/rest-api)

    

## Dependencies
* [libcurl](https://curl.haxx.se/libcurl/)
* [curlcpp](https://github.com/JosephP91/curlcpp)
* [json - JSON for Modern C++](https://github.com/nlohmann/json)

## Installation
Assumes a **git** based dependent project on **linux**, with **cmake** as the build system.

1. Install **libcurl**  
  `sudo apt-get install libcurl4-openssl-dev`

2. Install **cmake**  
  `sudo apt install cmake`

3. Install **kandy** library as a submodule.  
  This will initialize the submodule at `lib/kandy`.   
  `git submodule add git@bitbucket.org:kandyhack/kandycpp.git lib/kandy`

4. Download **kandy** library files.  
  `git submodule update --init --recursive`

5. Add **cmake** dependencies to your project.
  ```
  add_subdirectory(lib/kandy)   
  include("${KANDY_SOURCE_DIR}/kandyConfig.cmake")    
  ```

6. Build cmake *generator*.   
  `cmake -G "Unix Makefiles"`

7. Build project output.  
  `make`

8. Update **kandy** and other submodules.   
  `git submodule update --recursive --remote`

    

# Library Reference

## Class **kandy::sms**

### Constructor  
```
sms (string domain_api_key, string domain_secret, string user_id,   
    string &user_access_token, string &device_id)

ARGS:
  domain_api_key = API key of Domain
  domain_api_secret = API secret of Domain
  user_id = ID of User sending the SMS
  user_access_token = string variable to store User Access Token, on success.
  device_id = string variable to store Device ID Token, on success.

THROWS:
  std::invalid_argument - arguments are invalid or empty strings.
  std::runtime_error - invalid reply from Kandy REST API.
```

### Constructor   
```
sms (string domain_api_key, string domain_secret, string user_id,   
    bool &success)

ARGS:
  domain_api_key = API key of Domain
  domain_api_secret = API secret of Domain
  user_id = ID of User sending the SMS
  success = boolean variable to store initialization success.

THROWS:
  std::invalid_argument - arguments are invalid or empty strings.
  std::runtime_error - invalid reply from Kandy REST API.
```

### Send SMS   
```
send (string source, string destination, string text)

ARGS:
  source = Sender's phone number
  destination = Recipient's phone number
  text = Message to be sent

THROWS:
  std::invalid_argument - arguments are invalid or empty strings.
  std::runtime_error - invalid reply from Kandy REST API.
```
