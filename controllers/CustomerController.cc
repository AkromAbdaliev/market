#include "CustomerController.h"
#include "Customer.h"
#include "ResponseHelper.h"
#include <optional>
#include "CustomerList.h"

using namespace ResponseHelper;
using namespace drogon;
using namespace drogon::orm;
using drogon_model::market::Customer;

Task<HttpResponsePtr> CustomerController::create(HttpRequestPtr req)
{
    try {
        auto json = req->getJsonObject();
        if (!json) {
            co_return makeJsonError(k400BadRequest, "Invalid JSON body.");
        }

        if (!json->isMember("name") || !json->isMember("email")) {
            co_return makeJsonError(k400BadRequest, "'Name' and 'email' are required.");
        }

        std::string name = (*json)["name"].asString();
        std::string email = (*json)["email"].asString();

        // plugin test
        auto plugin = app().getPlugin<CustomerList>();
        if(!plugin->isNameAllowed(name))
        {
            co_return  makeJsonError(k400BadRequest, name + " is in black list!");
        }

        auto dbClient = app().getFastDbClient();
        CoroMapper<Customer> mp(dbClient);

        Customer customer;
        customer.setName(name);
        customer.setEmail(email);
        auto createdCustomer = co_await mp.insert(customer);

        Json::Value userJson = createdCustomer.toJson();

        co_return makeJsonSuccess(k201Created, userJson);
    }
    catch (const std::exception& e) {
        LOG_ERROR << "Error creating customer: " << e.what();

        co_return makeJsonError(k500InternalServerError, "Error occured while creating customer.");
    }
}

Task<HttpResponsePtr> CustomerController::getCustomer(HttpRequestPtr req, int customerId)
{
    try {
        auto dbClient = app().getFastDbClient();
        CoroMapper<Customer> mp(dbClient);

        auto customer = co_await mp.findByPrimaryKey(customerId);

        Json::Value userJson = customer.toJson();

        co_return makeJsonSuccess(k200OK, userJson);
    }
    catch (const RangeError &re){
            co_return makeJsonError(k404NotFound, "Customer not found.");
    }
    catch (const DrogonDbException &e) {
        LOG_ERROR << "Database error while fetching customer: " << e.base().what();
        co_return makeJsonError(k500InternalServerError, "Error occured while fetching customer by id.");
    }
}

void CustomerController::getCustomerSync(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int customerId) const
{
    try{
        auto dbClient = app().getDbClient();
        Mapper<Customer> mp(dbClient);

        auto customer = mp.findByPrimaryKey(customerId);
        Json::Value customerJson = customer.toJson();

        auto res = HttpResponse::newHttpJsonResponse(customerJson);
        callback(res);

    }catch(const DrogonDbException &e)
    {
        Json::Value err;
        err["error"] = "User not found.";
        auto res = HttpResponse::newHttpJsonResponse(err);
        res->setStatusCode(k404NotFound);
        callback(res);
    }
}

Task<HttpResponsePtr> CustomerController::getAll(HttpRequestPtr req)
{
    try {
        auto dbClient = app().getFastDbClient();
        CoroMapper<Customer> mp(dbClient);

        auto customers = co_await mp.findAll();

        Json::Value customersJson(Json::arrayValue);
        for (const auto& customer : customers) {
            Json::Value userJson = customer.toJson();
            customersJson.append(userJson);
        }
        co_return makeJsonSuccess(k200OK, customersJson);

    }
    catch (const DrogonDbException &e) {
        LOG_ERROR << "Database error while fetching customers: " << e.base().what();
        co_return makeJsonError(k500InternalServerError, "Error occured while fetching customer list.");
    }
}

Task<HttpResponsePtr> CustomerController::updateCustomer(HttpRequestPtr req, int customerId)
{

    try{
        auto json = req->getJsonObject();
        if (!json) {
            co_return makeJsonError(k400BadRequest, "Invalid JSON body.");
        }

        if (!json->isMember("name") || !json->isMember("email")) {
            co_return makeJsonError(k400BadRequest, "'Name' and 'email' are required.");
        }

        std::string name = (*json)["name"].asString();
        std::string email = (*json)["email"].asString();

        auto dbClient = app().getFastDbClient();
        CoroMapper<Customer> mp(dbClient);

        auto customer = co_await mp.findByPrimaryKey(customerId);

        customer.setName(name);
        customer.setEmail(email);

        co_await mp.update(customer);

        Json::Value updatedJson = customer.toJson();

        co_return makeJsonSuccess(k200OK, updatedJson);

    }
    catch (const RangeError &re){
        co_return makeJsonError(k404NotFound, "Customer not found.");
    }
    catch(const DrogonDbException &e){
        LOG_ERROR <<  "Customer update error: " << e.base().what();
        co_return makeJsonError(k500InternalServerError, "Error occured while updating customer.");
    }
}

Task<HttpResponsePtr> CustomerController::deleteCustomer(HttpRequestPtr req, int customerId)
{
    try{
        auto dbClient = app().getFastDbClient();
        CoroMapper<Customer> mp(dbClient);

        auto affectedRows  = co_await mp.deleteByPrimaryKey(customerId);

        if(affectedRows == 0){

            co_return makeJsonError(k404NotFound, "Customer not found.");
        }

        HttpResponsePtr resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k204NoContent);
        co_return resp;

    }
    catch(const DrogonDbException &e){
        LOG_ERROR << "Customer delete error: " << e.base().what();
        co_return makeJsonError(k500InternalServerError, "Error occured while deleting customer.");
    }
}




















