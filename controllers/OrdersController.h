#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class OrdersController : public drogon::HttpController<OrdersController>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(OrdersController::get, "/{2}/{1}", Get); // path is /OrdersController/{arg2}/{arg1}
    // METHOD_ADD(OrdersController::your_method_name, "/{1}/{2}/list", Get); // path is /OrdersController/{arg1}/{arg2}/list
    // ADD_METHOD_TO(OrdersController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    ADD_METHOD_TO(OrdersController::get, "/api/orders", Get);
    ADD_METHOD_TO(OrdersController::getOne, "/api/orders/{id}", Get);
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void getOne(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int orderId) const;
  };
