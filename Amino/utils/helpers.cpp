#include "helpers.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/rand.h>
#include <boost/beast/http.hpp>

#include <typeinfo>

namespace http = boost::beast::http;

namespace Helpers {

    std::string upper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::toupper(c); });
        return result;
    }

    std::string lower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::tolower(c); });
        return result;
    }

    void set_headers(http::request<http::string_body>& req, const std::string& deviceId, const std::string& sid, const std::string& uid, const std::string& data, const std::string& user_agent, const std::string& language, const std::string& content_type) {
        req.set("NDCLANG", lower(language));
        req.set("Accept-Language", lower(language)+"-"+upper(language));
        req.set("User-Agent", user_agent);
        req.set("Accept-Encoding", "identity");
        req.set("Accept", "*/*");
        req.set("Connection", "keep-alive");
        req.set("NDCDEVICEID", deviceId);
        req.set("Content-Type", content_type);
        if (sid!=""){
            req.set("NDCAUTH", "sid="+sid);
        }
        if (data!=""){
            req.set("Content-Length", std::to_string(data.length()));
            req.set("NDC-MSG-SIG", genSignature(data));
        }
        if (uid!=""){
            req.set("AUID", uid);
        }
    }

    std::vector<unsigned char> genRandomBytes(size_t length) {
        std::vector<unsigned char> randomBytes(length);
        RAND_bytes(randomBytes.data(), static_cast<int>(length));
        return randomBytes;
    }

    std::string genDeviceId(const std::vector<unsigned char>& data) {
        std::vector<unsigned char> identifier = Constants::PREFIX;
        identifier.insert(identifier.end(), data.begin(), data.end());

        unsigned int macLen = SHA_DIGEST_LENGTH;
        std::vector<unsigned char> mac(macLen);

        HMAC(EVP_sha1(), Constants::DEVICE_KEY.data(), Constants::DEVICE_KEY.size(), identifier.data(), identifier.size(), mac.data(), &macLen);

        std::stringstream deviceId;
        deviceId << std::hex << std::uppercase << std::setfill('0');
        for (const auto& byte : identifier) {
            deviceId << std::setw(2) << static_cast<int>(byte);
        }
        for (const auto& byte : mac) {
            deviceId << std::setw(2) << static_cast<int>(byte);
        }

        return deviceId.str();
    }

    std::string genSignature(const std::string& data) {
        unsigned int hashLen;
        unsigned char hash[EVP_MAX_MD_SIZE];
        HMAC(EVP_sha1(), Constants::SIG_KEY.data(), Constants::SIG_KEY.size(), reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash, &hashLen);

        std::vector<unsigned char> prefixHash(Constants::PREFIX);
        prefixHash.insert(prefixHash.end(), hash, hash + hashLen);

        return base64_encode(prefixHash);
    }

    std::string base64_encode(const std::vector<unsigned char>& input) {
        BIO *bio = BIO_new(BIO_s_mem());
        BIO *b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); // Remove this line to include newline characters
        bio = BIO_push(b64, bio);

        BIO_write(bio, input.data(), input.size());
        BIO_flush(bio);

        BUF_MEM *bptr;
        BIO_get_mem_ptr(bio, &bptr);

        std::string result(bptr->data, bptr->data + bptr->length);

        BIO_free_all(bio);

        return result;
    }


    long int timestamp(){
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto value = now_ms.time_since_epoch().count();
        return value;
    }

    std::string sock_signbody(){
        return "";
    }


}
