#ifndef HELPERS_H
#define HELPERS_H



#include <boost/beast/http.hpp>
namespace http = boost::beast::http;

#include <vector>
#include <string>



namespace Helpers {

    // Объявления переменных
    extern const std::vector<unsigned char> PREFIX;
    extern const std::vector<unsigned char> SIG_KEY;
    extern const std::vector<unsigned char> DEVICE_KEY;

    // Объявления функций
    std::string upper(const std::string& str);
    std::string lower(const std::string& str);
    void set_headers(http::request<http::string_body>& req, const std::string& deviceId, const std::string& sid = "", const std::string& uid = "", const std::string& data = "", const std::string& user_agent = "Apple iPhone12,1 iOS v15.5 Main/3.12.2", const std::string& language = "en",  const std::string& content_type = "application/json");
    std::string genSignature(const std::string& data);
    std::vector<unsigned char> genRandomBytes(size_t length);
    std::string genDeviceId(const std::vector<unsigned char>& data = genRandomBytes(20));
    std::string base64_encode(const std::vector<unsigned char>& input);
    long int timestamp();

}
#endif // HELPERS_H
