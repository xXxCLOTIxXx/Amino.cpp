#ifndef HELPERS_H
#define HELPERS_H

#include <boost/beast/http.hpp>
namespace http = boost::beast::http;
#include <string>
#include "../objects/args/constants.h"
#include "json.hpp"
using json = nlohmann::json;

namespace Helpers {

    std::string upper(const std::string& str);
    std::string lower(const std::string& str);
    void set_headers(http::request<http::string_body>& req, const std::string& deviceId, const std::string& sid = "", const std::string& uid = "", const std::string& data = "", const std::string& user_agent = "Apple iPhone12,1 iOS v15.5 Main/3.12.2", const std::string& language = "en",  const std::string& content_type = "application/json");
    std::string genSignature(const std::string& data);
    std::vector<unsigned char> genRandomBytes(size_t length);
    std::string genDeviceId(const std::vector<unsigned char>& data = genRandomBytes(20));
    std::string base64_encode(const std::vector<unsigned char>& input);
    long int timestamp();
    bool checkType(const std::string& type, const std::vector<std::string>& validTypes);
    std::string replaceChars(const std::string& str, char from, const std::string& to);
    std::string base64_url_decode(const std::string & data);
    json decode_sid(const std::string &SID);
    std::string sid_to_ip_address(const std::string &SID);
    std::string sid_to_uid(const std::string &SID);
    int sid_created_time(const std::string &SID);
    int sid_to_client_type(const std::string &SID);
    std::string clean_for_json(const std::string &input);


    const char base64_url_alphabet[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'
};

}
#endif
