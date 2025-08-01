#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CustomerController : public drogon::HttpController<CustomerController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CustomerController::create, "/api/customer", Post);
        ADD_METHOD_TO(CustomerController::getCustomer, "/api/customer/{id}", Get);
        ADD_METHOD_TO(CustomerController::getAll, "/api/customer", Get);
    METHOD_LIST_END

    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getCustomer(HttpRequestPtr req, int customerId);
    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
};
