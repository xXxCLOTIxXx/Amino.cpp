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

namespace http = boost::beast::http;

namespace Helpers {

    // Определения переменных
    const std::vector<unsigned char> PREFIX = {0x19};
    const std::vector<unsigned char> SIG_KEY = {0xdf, 0xa5, 0xed, 0x19, 0x2d, 0xda, 0x6e, 0x88, 0xa1, 0x2f, 0xe1, 0x21, 0x30, 0xdc, 0x62, 0x06, 0xb1, 0x25, 0x1e, 0x44};
    const std::vector<unsigned char> DEVICE_KEY = {0xe7, 0x30, 0x9e, 0xcc, 0x09, 0x53, 0xc6, 0xfa, 0x60, 0x00, 0x5b, 0x27, 0x65, 0xf9, 0x9d, 0xbb, 0xc9, 0x65, 0xc8, 0xe9};

    // Определения функций

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

    void get_headers(http::request<http::string_body>& req, const std::string& deviceId, const std::string& sid, const std::string& data, const std::string& user_agent, const std::string& language, const std::string& content_type) {
        req.set("NDCLANG", lower(language));
        req.set("Accept-Language", lower(language)+"-"+upper(language));
        req.set("User-Agent", user_agent);
        req.set("Accept-Encoding", "identity");
        req.set("Connection", "Upgrade");
        req.set("NDCDEVICEID", deviceId);
        req.set("Content-Type", content_type);
        
        if (!sid.empty()){
            req.set("NDCAUTH", "sid="+sid);
        }
        if (!data.empty()){
            req.set("Content-Length", std::to_string(data.length()));
            req.set("NDC-MSG-SIG", genSignature(data));
        }
    }

    std::vector<unsigned char> genRandomBytes(size_t length) {
        std::vector<unsigned char> randomBytes(length);
        RAND_bytes(randomBytes.data(), static_cast<int>(length));
        return randomBytes;
    }

    std::string genDeviceId(const std::vector<unsigned char>& data) {
        std::vector<unsigned char> identifier = PREFIX;
        identifier.insert(identifier.end(), data.begin(), data.end());

        unsigned int macLen = SHA_DIGEST_LENGTH;
        std::vector<unsigned char> mac(macLen);

        HMAC(EVP_sha1(), DEVICE_KEY.data(), DEVICE_KEY.size(), identifier.data(), identifier.size(), mac.data(), &macLen);

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
        std::vector<unsigned char> hash(SHA_DIGEST_LENGTH);
        HMAC(EVP_sha1(), SIG_KEY.data(), SIG_KEY.size(), reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash.data(), nullptr);

        BIO *bio = BIO_new(BIO_s_mem());
        BIO_write(bio, PREFIX.data(), PREFIX.size());
        BIO_write(bio, hash.data(), hash.size());

        BUF_MEM *bptr;
        BIO_get_mem_ptr(bio, &bptr);

        std::string result(bptr->data, bptr->data + bptr->length);

        BIO_free_all(bio);

        return result;
    }
}
