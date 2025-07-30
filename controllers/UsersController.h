#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class UsersController : public drogon::HttpController<UsersController>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(UsersController::get, "/{2}/{1}", Get); // path is /UsersController/{arg2}/{arg1}
    // METHOD_ADD(UsersController::your_method_name, "/{1}/{2}/list", Get); // path is /UsersController/{arg1}/{arg2}/list
    // ADD_METHOD_TO(UsersController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    ADD_METHOD_TO(UsersController::get, "/api/users", Get);
    ADD_METHOD_TO(UsersController::getOne, "/api/users/{id}", Get);
    ADD_METHOD_TO(UsersController::update, "/api/users/{id}", Put);
    ADD_METHOD_TO(UsersController::deleteOne, "/api/users/{id}", Delete);
    ADD_METHOD_TO(UsersController::create, "/api/users", Post);
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void create(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void getOne(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int userId) const;
    void update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int userId) const;
    void deleteOne(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int userId) const;
};
