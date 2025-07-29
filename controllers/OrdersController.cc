#include "OrdersController.h"
#include "Orders.h"

using namespace drogon::orm;
using drogon_model::market::Orders;
// Add definition of your processing function here

void OrdersController::get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    auto dbClient = app().getDbClient();
    Mapper<Orders> mp (dbClient);

    mp.findAll
    (
        [callback](const std::vector<Orders> &orders)
        {
            Json::Value ordersJson = Json::arrayValue;
            for (const auto &row : orders)
            {
                ordersJson.append(row.toJson());
            }
            auto res = HttpResponse::newHttpJsonResponse(ordersJson);
            callback(res);
            
        },
        [callback](const DrogonDbException &e)
        {
            Json::Value error; 
            error["error"] = std::string("Database error: ") + e.base().what();
            auto res = HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k500InternalServerError);
            callback(res);
        }
    );
}

void OrdersController::getOne(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int orderId) const 
{
    auto dbClient = app().getDbClient();
    Mapper<Orders> mp(dbClient);

    mp.findOne
    (
        Criteria(Orders::Cols::_id, CompareOperator::EQ, orderId),
        [callback](const Orders &order)
        {
            Json::Value orderJson = order.toJson();
            auto res = HttpResponse::newHttpJsonResponse(orderJson);
            callback(res);
        },
        [callback](const DrogonDbException &e)
        {
            Json::Value error;
            error["error"] = std::string("Order not found.");
            auto res = HttpResponse::newHttpJsonResponse(error);
            res->setStatusCode(k404NotFound);
            callback(res);
        }
    );
}




















