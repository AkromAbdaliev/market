#include "UsersController.h"
#include "Users.h"

using namespace drogon::orm;
using drogon_model::market::Users;

// Add definition of your processing function here
void UsersController::get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    auto dbClient = app().getDbClient();
    Mapper<Users> mp (dbClient);

    mp.findAll
        (
        [callback](const std::vector<Users> &users)
        {
            
        },

        [callback](){}
        );
}
