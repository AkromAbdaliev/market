#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CustomerController : public drogon::HttpController<CustomerController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CustomerController::create, "/api/customer", Post);
        ADD_METHOD_TO(CustomerController::getCustomer, "/api/customer/{id}", Get);

        ADD_METHOD_TO(CustomerController::getCustomerSync, "/api/customerSync/{id}", Get);

        ADD_METHOD_TO(CustomerController::getAll, "/api/customer", Get);
        ADD_METHOD_TO(CustomerController::updateCustomer,  "/api/customer/{id}", Put);
        ADD_METHOD_TO(CustomerController::deleteCustomer, "/api/customer/{id}", Delete);
    METHOD_LIST_END

    Task<HttpResponsePtr> create(HttpRequestPtr);
    Task<HttpResponsePtr> getCustomer(HttpRequestPtr, int);
    void getCustomerSync(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int) const;
    Task<HttpResponsePtr> getAll(HttpRequestPtr);
    Task<HttpResponsePtr> updateCustomer(HttpRequestPtr, int);
    Task<HttpResponsePtr> deleteCustomer(HttpRequestPtr, int);
};
