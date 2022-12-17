#pragma once

#include <string>
#include <list>

#include <json.hpp>

class Client
{
public:
    using Headers = std::list<std::string>;
    using Data = nlohmann::json;

    struct Response
    {
        enum Code : uint16_t
        {
            OK = 200,
            BAD_REQUEST = 400,
            UNAUTHORIZED = 401
        } code;

        Data data;
    };

    struct StringResponse : Response
    {
        std::string data;
    };
    
    static const Response sendGet(const std::string& endpoint, Headers headers = Headers());
    static const StringResponse sendGetStr(const std::string& endpoint, Headers headers = Headers());
    static const Response sendPost(const std::string& endpoint, const Data& data, Headers headers = Headers());
    static const Response sendPost(const std::string& endpoint, const std::string& data, Headers headers = Headers());
    static const StringResponse sendPostStr(const std::string& endpoint, const std::string& data, Headers headers = Headers());

    // requests to resources other than mikuserver endpoints
    static const StringResponse sendExternalGet(const std::string& url, const Headers& headers = Headers());
    static const StringResponse sendExternalPost(const std::string& url, const std::string& data, const Headers& headers = Headers());

private:
    static constexpr const char* ROOT_ENDPOINT = "/miku";

    static const StringResponse sendRequest(const std::string& url, const Headers& headers, const std::string& postData = "");
};
