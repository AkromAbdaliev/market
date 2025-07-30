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
            error["error"] = "User not found.";
            auto res = HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k404NotFound);
            callback(res);
        }
    );
}

void UsersController::update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int userId) const 
{
    auto dbClient = app().getDbClient();
    Mapper<Users> mp (dbClient);

    try
    {
        auto json = req->getJsonObject();
        if (!json) {
            Json::Value jsonError;
            jsonError["error"] = "Invalid JSON";
            auto res = HttpResponse::newHttpJsonResponse(jsonError);
            res->setStatusCode(k400BadRequest);
            callback(res);
            return;
        }
        mp.findOne
        (
            Criteria(Users::Cols::_id, CompareOperator::EQ, userId),
            [callback, json, mp](Users user) mutable
            {
                if (json->isMember("name")) {user.setName((*json)["name"].asString());}
                if (json->isMember("email")) {user.setEmail((*json)["email"].asString());}
                
                mp.update(user,
                    [callback](const size_t)
                    {
                        Json::Value successJson;
                        successJson["success"] = "User has been updated.";
                        auto res = HttpResponse::newHttpJsonResponse(successJson);
                        callback(res);
                    },
                    [callback](const DrogonDbException &e)
                    {
                        Json::Value failJson;
                        failJson["error"] = e.base().what();
                        auto res = HttpResponse::newHttpJsonResponse(failJson);
                        res->setStatusCode(k500InternalServerError);
                        callback(res);
                    }
                );
            },
            [callback](const DrogonDbException &e)
            {
                Json::Value error;
                error["error"] = "User does not exist.";
                auto res = HttpResponse::newHttpJsonResponse(error);
                res->setStatusCode(k404NotFound);
                callback(res);
            }
        );
    }

    catch(const std::exception &ex)
    {
        Json::Value error;
        error["error"] = ex.what();

        auto resp = HttpResponse::newHttpJsonResponse(error);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
    }
    
}

void UsersController::deleteOne(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int userId) const
{
    auto dbClient = app().getDbClient();
    Mapper<Users> mp(dbClient);

    mp.deleteBy(
        Criteria(Users::Cols::_id, CompareOperator::EQ, userId),
        [callback](const size_t count)
        {
            if (count > 0) {
                Json::Value successJson;
                successJson["success"] = "User has been deleted.";
                auto res = HttpResponse::newHttpJsonResponse(successJson);
                callback(res);
            } else {
                Json::Value error;
                error["error"] = "User not found";
                auto res = HttpResponse::newHttpJsonResponse(error);
                res->setStatusCode(k404NotFound);
                callback(res);
            }
        },
        [callback](const DrogonDbException &e) {
            Json::Value error;
            error["error"] = "Database error";
            auto res = HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k500InternalServerError);
            callback(res);
        });
}

void UsersController::create(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    auto dbClient = app().getDbClient();
    Mapper<Users> mp(dbClient);

    try
    {
        auto json = req->getJsonObject();
        if (!json) {
            Json::Value jsonError;
            jsonError["error"] = "Invalid JSON";
            auto res = HttpResponse::newHttpJsonResponse(jsonError);
            res->setStatusCode(k400BadRequest);
            callback(res);
            return;
        }
        
        if (!json->isMember("name") || !json->isMember("email"))
        {
            Json::Value jsonError;
            jsonError["error"] = "'name' and 'email' are required.";
            auto res = HttpResponse::newHttpJsonResponse(jsonError);
            res->setStatusCode(k400BadRequest);
            callback(res);
            return;
        }
        
        Users user;
        user.setName((*json)["name"].asString());
        user.setEmail((*json)["email"].asString());

        mp.insert(user,
            [callback](Users user)
            {
                Json::Value userJson;
                userJson["id"] = user.getValueOfId();
                userJson["name"] = user.getValueOfName();
                userJson["email"] = user.getValueOfEmail();

                auto res = HttpResponse::newHttpJsonResponse(userJson);
                res->setStatusCode(k201Created);
                callback(res);
            },
            [callback](const DrogonDbException &e)
            {
                Json::Value error;
                error["error"] = e.base().what();
                auto res = HttpResponse::newHttpJsonResponse(error);
                res->setStatusCode(k400BadRequest);
                callback(res);
            }
        );
    }
    catch(const std::exception& ex)
    {
        Json::Value error;
        error["error"] = ex.what();

        auto resp = HttpResponse::newHttpJsonResponse(error);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
    }
    
}









