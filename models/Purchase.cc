/**
 *
 *  Purchase.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Purchase.h"
#include "Customer.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::market;

const std::string Purchase::Cols::_id = "\"id\"";
const std::string Purchase::Cols::_customer_id = "\"customer_id\"";
const std::string Purchase::Cols::_purchase_date = "\"purchase_date\"";
const std::string Purchase::primaryKeyName = "id";
const bool Purchase::hasPrimaryKey = true;
const std::string Purchase::tableName = "\"purchase\"";

const std::vector<typename Purchase::MetaData> Purchase::metaData_={
{"id","int32_t","integer",4,1,1,1},
{"customer_id","int32_t","integer",4,0,0,0},
{"purchase_date","::trantor::Date","timestamp without time zone",0,0,0,0}
};
const std::string &Purchase::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Purchase::Purchase(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["customer_id"].isNull())
        {
            customerId_=std::make_shared<int32_t>(r["customer_id"].as<int32_t>());
        }
        if(!r["purchase_date"].isNull())
        {
            auto timeStr = r["purchase_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                purchaseDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 3 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            customerId_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                purchaseDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}

Purchase::Purchase(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            customerId_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[2]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                purchaseDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

Purchase::Purchase(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("customer_id"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["customer_id"].isNull())
        {
            customerId_=std::make_shared<int32_t>((int32_t)pJson["customer_id"].asInt64());
        }
    }
    if(pJson.isMember("purchase_date"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["purchase_date"].isNull())
        {
            auto timeStr = pJson["purchase_date"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                purchaseDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

void Purchase::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            customerId_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[2]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                purchaseDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

void Purchase::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("customer_id"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["customer_id"].isNull())
        {
            customerId_=std::make_shared<int32_t>((int32_t)pJson["customer_id"].asInt64());
        }
    }
    if(pJson.isMember("purchase_date"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["purchase_date"].isNull())
        {
            auto timeStr = pJson["purchase_date"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                purchaseDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

const int32_t &Purchase::getValueOfId() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Purchase::getId() const noexcept
{
    return id_;
}
void Purchase::setId(const int32_t &pId) noexcept
{
    id_ = std::make_shared<int32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename Purchase::PrimaryKeyType & Purchase::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const int32_t &Purchase::getValueOfCustomerId() const noexcept
{
    static const int32_t defaultValue = int32_t();
    if(customerId_)
        return *customerId_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Purchase::getCustomerId() const noexcept
{
    return customerId_;
}
void Purchase::setCustomerId(const int32_t &pCustomerId) noexcept
{
    customerId_ = std::make_shared<int32_t>(pCustomerId);
    dirtyFlag_[1] = true;
}
void Purchase::setCustomerIdToNull() noexcept
{
    customerId_.reset();
    dirtyFlag_[1] = true;
}

const ::trantor::Date &Purchase::getValueOfPurchaseDate() const noexcept
{
    static const ::trantor::Date defaultValue = ::trantor::Date();
    if(purchaseDate_)
        return *purchaseDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Purchase::getPurchaseDate() const noexcept
{
    return purchaseDate_;
}
void Purchase::setPurchaseDate(const ::trantor::Date &pPurchaseDate) noexcept
{
    purchaseDate_ = std::make_shared<::trantor::Date>(pPurchaseDate);
    dirtyFlag_[2] = true;
}
void Purchase::setPurchaseDateToNull() noexcept
{
    purchaseDate_.reset();
    dirtyFlag_[2] = true;
}

void Purchase::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Purchase::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "customer_id",
        "purchase_date"
    };
    return inCols;
}

void Purchase::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getCustomerId())
        {
            binder << getValueOfCustomerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getPurchaseDate())
        {
            binder << getValueOfPurchaseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Purchase::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    return ret;
}

void Purchase::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getCustomerId())
        {
            binder << getValueOfCustomerId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getPurchaseDate())
        {
            binder << getValueOfPurchaseDate();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Purchase::toJson() const
{
    Json::Value ret;
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getCustomerId())
    {
        ret["customer_id"]=getValueOfCustomerId();
    }
    else
    {
        ret["customer_id"]=Json::Value();
    }
    if(getPurchaseDate())
    {
        ret["purchase_date"]=getPurchaseDate()->toDbStringLocal();
    }
    else
    {
        ret["purchase_date"]=Json::Value();
    }
    return ret;
}

std::string Purchase::toString() const
{
    return toJson().toStyledString();
}

Json::Value Purchase::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 3)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[0]]=getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getCustomerId())
            {
                ret[pMasqueradingVector[1]]=getValueOfCustomerId();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getPurchaseDate())
            {
                ret[pMasqueradingVector[2]]=getPurchaseDate()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getCustomerId())
    {
        ret["customer_id"]=getValueOfCustomerId();
    }
    else
    {
        ret["customer_id"]=Json::Value();
    }
    if(getPurchaseDate())
    {
        ret["purchase_date"]=getPurchaseDate()->toDbStringLocal();
    }
    else
    {
        ret["purchase_date"]=Json::Value();
    }
    return ret;
}

bool Purchase::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("customer_id"))
    {
        if(!validJsonOfField(1, "customer_id", pJson["customer_id"], err, true))
            return false;
    }
    if(pJson.isMember("purchase_date"))
    {
        if(!validJsonOfField(2, "purchase_date", pJson["purchase_date"], err, true))
            return false;
    }
    return true;
}
bool Purchase::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                  const std::vector<std::string> &pMasqueradingVector,
                                                  std::string &err)
{
    if(pMasqueradingVector.size() != 3)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Purchase::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(pJson.isMember("customer_id"))
    {
        if(!validJsonOfField(1, "customer_id", pJson["customer_id"], err, false))
            return false;
    }
    if(pJson.isMember("purchase_date"))
    {
        if(!validJsonOfField(2, "purchase_date", pJson["purchase_date"], err, false))
            return false;
    }
    return true;
}
bool Purchase::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                std::string &err)
{
    if(pMasqueradingVector.size() != 3)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Purchase::validJsonOfField(size_t index,
                                const std::string &fieldName,
                                const Json::Value &pJson,
                                std::string &err,
                                bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 2:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
Customer Purchase::getCustomer(const DbClientPtr &clientPtr) const {
    static const std::string sql = "select * from customer where id = $1";
    Result r(nullptr);
    {
        auto binder = *clientPtr << sql;
        binder << *customerId_ << Mode::Blocking >>
            [&r](const Result &result) { r = result; };
        binder.exec();
    }
    if (r.size() == 0)
    {
        throw UnexpectedRows("0 rows found");
    }
    else if (r.size() > 1)
    {
        throw UnexpectedRows("Found more than one row");
    }
    return Customer(r[0]);
}

void Purchase::getCustomer(const DbClientPtr &clientPtr,
                           const std::function<void(Customer)> &rcb,
                           const ExceptionCallback &ecb) const
{
    static const std::string sql = "select * from customer where id = $1";
    *clientPtr << sql
               << *customerId_
               >> [rcb = std::move(rcb), ecb](const Result &r){
                    if (r.size() == 0)
                    {
                        ecb(UnexpectedRows("0 rows found"));
                    }
                    else if (r.size() > 1)
                    {
                        ecb(UnexpectedRows("Found more than one row"));
                    }
                    else
                    {
                        rcb(Customer(r[0]));
                    }
               }
               >> ecb;
}
