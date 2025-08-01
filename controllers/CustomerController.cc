#include "CustomerController.h"
#include "CustomerService.h"

Task<HttpResponsePtr> CustomerController::create(HttpRequestPtr req)
{
    try {
        auto json = req->getJsonObject();
        if (!json) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            resp->setBody("Invalid request body");
            co_return resp;
        }

        if (!json->isMember("name") || !json->isMember("email")) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            resp->setBody("Name and email are required");
            co_return resp;
        }

        std::string name = (*json)["name"].asString();
        std::string email = (*json)["email"].asString();

        auto customerServicePtr = app().getPlugin<CustomerService>();
        auto customer = co_await customerServicePtr->createCustomer(name, email);

        Json::Value ret;
        ret["id"] = customer.getValueOfId();
        ret["name"] = customer.getValueOfName();
        ret["email"] = customer.getValueOfEmail();

        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    catch (const std::exception& e) {
        LOG_ERROR << "Error creating customer: " << e.what();
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        resp->setBody("Error creating customer");
        co_return resp;
    }
}


Task<HttpResponsePtr> CustomerController::getCustomer(HttpRequestPtr req, int customerId)
{
    auto customerService = app().getPlugin<CustomerService>();
    auto customer = co_await customerService->getCustomer(customerId);

    if (!customer) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k404NotFound);
        resp->setBody("Customer not found");
        co_return resp;
    }

    Json::Value ret;
    ret["id"] = customer->getValueOfId();
    ret["name"] = customer->getValueOfName();
    ret["email"] = customer->getValueOfEmail();

    auto resp = HttpResponse::newHttpJsonResponse(ret);
    co_return resp;
}

Task<HttpResponsePtr> CustomerController::getAll(HttpRequestPtr req)
{
    try {
        auto customerService = app().getPlugin<CustomerService>();
        auto customers = co_await customerService->getAll();

        Json::Value ret(Json::arrayValue);
        for (auto& customer : customers) {
            Json::Value item;
            item["id"] = customer.getValueOfId();
            item["name"] = customer.getValueOfName();
            item["email"] = customer.getValueOfEmail();
            ret.append(item);
        }

        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    }
    catch (const std::exception& e) {
        LOG_ERROR << "Error fetching customers: " << e.what();
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        resp->setBody("Error fetching customer list");
        co_return resp;
    }
}























