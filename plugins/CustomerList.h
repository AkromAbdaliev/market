#pragma once

#include <drogon/plugins/Plugin.h>
#include <unordered_set>
#include <string>

class CustomerList : public drogon::Plugin<CustomerList>
{
  public:
    CustomerList() {}
    /// This method must be called by drogon to initialize and start the plugin.
    /// It must be implemented by the user.
    void initAndStart(const Json::Value &config) override;

    /// This method must be called by drogon to shutdown the plugin.
    /// It must be implemented by the user.
    void shutdown() override;

    bool isNameAllowed(const std::string &name) const;

private:
    std::unordered_set<std::string> blacklist_;
};

