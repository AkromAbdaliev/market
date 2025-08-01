#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CustomerController : public drogon::HttpController<CustomerController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CustomerController::create, "/api/customer", Post);
    METHOD_LIST_END

    Task<HttpResponsePtr> create(HttpRequestPtr req);
};
