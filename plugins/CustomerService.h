#pragma once

#include <drogon/plugins/Plugin.h>
#include "Customer.h"
#include <optional>

using namespace drogon;
using namespace drogon::orm;
using drogon_model::market::Customer;

class CustomerService : public drogon::Plugin<CustomerService>
{
public:
    CustomerService() {}

    /// Initialize and start the plugin.
    void initAndStart(const Json::Value &config) override;

    /// Shutdown the plugin.
    void shutdown() override;

    /// Create a new customer
    virtual Task<Customer> createCustomer(const std::string &name, const std::string &email);

    /// Get customer by ID (returns std::nullopt if not found)
    virtual Task<std::optional<Customer>> getCustomer(int customerId);

    virtual Task<std::vector<Customer>> getAll();
};
