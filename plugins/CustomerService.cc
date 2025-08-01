/**
 *
 *  CustomerService.cc
 *
 */

#include "CustomerService.h"
#include <drogon/drogon.h>

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

Task<std::optional<Customer>> CustomerService::getCustomer(int customerId)
{
    try {
        auto dbClient = app().getFastDbClient();
        CoroMapper<Customer> mp(dbClient);

        auto customer = co_await mp.findByPrimaryKey(customerId);
        co_return customer;
    }
    catch (const DrogonDbException &e) {
        LOG_ERROR << "Database error fetching customer: " << e.base().what();
        co_return std::nullopt;
    }
}

Task<std::vector<Customer>> CustomerService::getAll()
{
    try {
        auto dbClient = app().getFastDbClient();
        CoroMapper<Customer> mp(dbClient);

        auto customers = co_await mp.findAll();
        co_return customers;
    }
    catch (const DrogonDbException &e) {
        LOG_ERROR << "Database error fetching customers: " << e.base().what();
        throw; // Re-throw for controller to handle
    }
}













