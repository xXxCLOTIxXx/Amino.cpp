#ifndef HELPERS_H
#define HELPERS_H



#include <boost/beast/http.hpp>
namespace http = boost::beast::http;

#include <string>

#include "../objects/constants.h"

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

}
#endif // HELPERS_H
