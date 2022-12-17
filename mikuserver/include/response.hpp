#pragma once

#include <httpserver.hpp>
#include <iostream>

using namespace httpserver;

class Response
{
public:
    static inline std::shared_ptr<http_response> badAuth() { return std::shared_ptr<http_response>(new string_response("bad token", 401)); }
    static inline std::shared_ptr<http_response> badReq(const std::string& msg) 
    { 
        return std::shared_ptr<http_response>(new string_response(msg, 400)); 
    }
};
