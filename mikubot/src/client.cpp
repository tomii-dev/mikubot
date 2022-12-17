#include "client.hpp"

#include "mikubot.hpp"
#include "secrets.hpp"

#include <sstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

/* static */ const Client::Response Client::sendGet(const std::string& endpoint, Headers headers)
{
    headers.push_back("authorization: " + BOT_TOKEN);

    StringResponse res = sendRequest(SERVER_IP + ROOT_ENDPOINT + endpoint, headers);    
    Response response;
    response.code = res.code;
    response.data = Data::parse(res.data);
   
    return response;
}

/* static */ const Client::StringResponse Client::sendGetStr(const std::string& endpoint, Headers headers)
{
    headers.push_back("authorization: " + BOT_TOKEN);

    return sendRequest(SERVER_IP + ROOT_ENDPOINT + endpoint, headers);
}

/* static */ const Client::Response Client::sendPost(const std::string& endpoint, const Data& data, Headers headers)
{
    return sendPost(endpoint, data.dump(), headers);
}

/* static */ const Client::Response Client::sendPost(const std::string& endpoint, const std::string& data, Headers headers)
{
    StringResponse res = sendPostStr(endpoint, data, headers);

    Response response;
    response.code = res.code;
    response.data = Data::parse(res.data);

    return response;
}

/* static */ const Client::StringResponse Client::sendPostStr(const std::string& endpoint, const std::string& data, Headers headers)
{
    headers.push_back("authorization: " + BOT_TOKEN);

    return sendRequest(SERVER_IP + ROOT_ENDPOINT + endpoint, headers, data);
}

/* static */ const Client::StringResponse Client::sendExternalGet(const std::string& url, const Headers& headers)
{
    return sendRequest(url, headers);
}

/* static */ const Client::StringResponse Client::sendExternalPost(const std::string& url, const std::string& data, const Headers& headers)
{
    return sendRequest(url, headers, data);
}

/* static */ const Client::StringResponse Client::sendRequest(const std::string& url, const Headers& headers, const std::string& postData)
{
    curlpp::Easy req;
    
    std::stringstream res;
    
    using namespace curlpp::options;
    req.setOpt(new Url(url));
    req.setOpt(new HttpHeader(headers));
    req.setOpt(WriteStream(&res));
    if(!postData.empty())
    {
        req.setOpt(new PostFields(postData));
        req.setOpt(new PostFieldSize(postData.size()));
    }
    req.perform();

    StringResponse response;
    response.code = Response::Code(curlpp::infos::ResponseCode::get(req));
    response.data = res.str();
   
    return response;
}
