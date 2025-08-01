/**
 *
 *  CustomerService.cc
 *
 */

#include "CustomerService.h"
#include <drogon/drogon.h>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::market;

void CustomerService::initAndStart(const Json::Value &config)
{
    /// Initialize and start the plugin
}

void CustomerService::shutdown() 
{
    /// Shutdown the plugin
}

Task<Customer> CustomerService::createCustomer(const std::string &name, const std::string &email)
{
    auto dbClient = app().getFastDbClient();
    CoroMapper<Customer> mp(dbClient);

    Customer customer;
    customer.setName(name);
    customer.setEmail(email);
    co_return co_await mp.insert(customer);
}
