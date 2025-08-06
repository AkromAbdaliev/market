#include "CustomerList.h"
#include  <drogon/HttpAppFramework.h>

using namespace drogon;

void CustomerList::initAndStart(const Json::Value &config)
{
    for (const auto &name : config["black_list"])
    {
        blacklist_.insert(name.asString());
    }

    drogon::app().getLoop()->runEvery(config.get("check_timeout", 5).asInt(),[]{
        LOG_DEBUG << "testing timer";
    });
}

void CustomerList::shutdown() 
{
    /// Shutdown the plugin
}

bool CustomerList::isNameAllowed(const std::string &name) const {
    return blacklist_.find(name) == blacklist_.end();
}

