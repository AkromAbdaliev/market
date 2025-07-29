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
            Json::Value jsonUsers = Json::arrayValue;
            for (const auto &row : users)
            {
                jsonUsers.append(row.toJson());
            }
            auto res = HttpResponse::newHttpJsonResponse(jsonUsers);;
            callback(res);
        },
        [callback](const DrogonDbException &e)
        {
            Json::Value error;
            error["error"] = std::string("Database error: ") + e.base().what();
            auto res = HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k500InternalServerError);
            callback(res);
        });
}

void UsersController::getOne(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int userId) const 
{
    auto dbClient = app().getDbClient();
    Mapper<Users> mp (dbClient);

    mp.findOne
    (
        Criteria(Users::Cols::_id, CompareOperator::EQ, userId),
        [callback](const Users &user)
        {
            Json::Value userJson = user.toJson();
            auto res = HttpResponse::newHttpJsonResponse(userJson);
            callback(res);

        },
        [callback](const DrogonDbException &e)
        {
            Json::Value error;
            error["error"] = std::string("User not found.");
            auto res = HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k404NotFound);
            callback(res);
        }
    );
}