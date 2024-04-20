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
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
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


    bool checkType(const std::string& type, const std::vector<std::string>& validTypes) {
        if (std::find(validTypes.begin(), validTypes.end(), type) == validTypes.end()) {
            return true;
        }
        return false;
    }

    std::string replaceChars(const std::string& str, char from, const std::string& to) {
        std::string result = str;
        size_t pos = result.find(from);
        while (pos != std::string::npos) {
            result.replace(pos, 1, to);
            pos = result.find(from, pos + to.size());
        }
        return result;
    }


    std::string base64_url_decode(const std::string & data) {
        std::string out;
        std::vector<int> T(256, -1);
        unsigned int i;
        for (i =0; i < 64; i++) T[base64_url_alphabet[i]] = i;

        int val = 0, valb = -8;
        for (i = 0; i < data.length(); i++) {
            unsigned char c = data[i];
            if (T[c] == -1) break;
            val = (val<<6) + T[c];
            valb += 6;
            if (valb >= 0) {
            out.push_back(char((val>>valb)&0xFF));
            valb -= 8;
            }
        }
        return out;
    }


    std::string clean_for_json(const std::string &input) {
        std::string result;
        for (char c : input) {
            if (std::isprint(c)) {
                result += c;
            }
        }
        return result;
    }



    json decode_sid(const std::string &SID) {
        int paddingCount = 4 - (SID.length() % 4);
        std::string padding = std::string(paddingCount, '=');
        std::string decoded = base64_url_decode(SID+padding);
        if (decoded.length() > 20) {
            decoded.erase( decoded.length() - 20);
        }
        return json::parse(clean_for_json(decoded));
    }

    std::string sid_to_uid(const std::string &SID) {
        return decode_sid(SID)["2"].get<std::string>();
    }

    std::string sid_to_ip_address(const std::string &SID) {
        return decode_sid(SID)["4"].get<std::string>();
    }

    int sid_created_time(const std::string &SID) {
        return decode_sid(SID)["5"].get<int>();
    }

    int sid_to_client_type(const std::string &SID) {
        return decode_sid(SID)["6"].get<int>();
    }

}
