#pragma once

#include <drogon/HttpResponse.h>

using namespace drogon;

namespace ResponseHelper {

    inline HttpResponsePtr makeJsonError(HttpStatusCode statusCode, const std::string &message) {
        Json::Value error;
        error["error"] = message;
        auto res = HttpResponse::newHttpJsonResponse(error);
        res->setStatusCode(statusCode);
        return res;
    }

    inline HttpResponsePtr makeJsonSuccess(HttpStatusCode statusCode, const Json::Value &body) {
        auto res = HttpResponse::newHttpJsonResponse(body);
        res->setStatusCode(statusCode);
        return res;
    }
}
