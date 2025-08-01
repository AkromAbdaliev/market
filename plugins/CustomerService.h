/**
 *
 *  CustomerService.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include "models/Customer.h"
#include <drogon/utils/coroutine.h>


class CustomerService : public drogon::Plugin<CustomerService>
{
  public:
    CustomerService() {}
    /// This method must be called by drogon to initialize and start the plugin.
    /// It must be implemented by the user.
    void initAndStart(const Json::Value &config) override;

    /// This method must be called by drogon to shutdown the plugin.
    /// It must be implemented by the user.
    void shutdown() override;


    drogon::Task<drogon_model::market::Customer> createCustomer(const std::string &name, const std::string &email);
};

