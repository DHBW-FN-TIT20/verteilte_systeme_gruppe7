/**************************************************************************************************
 * @file    message_parser.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   This file contains the implementation for class MessageParser and function overloads
 *          for converting own datatypes.
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "message_parser.h"
#include "nlohmann/json.hpp"

/**************************************************************************************************
 * Class implementation
 *************************************************************************************************/
template <typename T>
T MessageParser::decodeObject(const std::string& objectString) {
  nlohmann::json j = nlohmann::json::parse(objectString);
  return j.get<T>();
}

template <typename T>
std::string MessageParser::encodeObject(const T& object) {
  nlohmann::json jsonObject = object;
  return jsonObject.dump();
}


// RequestType
void to_json(nlohmann::json& j, const RequestType& obj) {
    j = nlohmann::json{
      {"mAction", static_cast<int>(obj.mAction)},
      {"mParameterList", obj.mParameterList},
      {"mTimestamp", obj.mTimestamp}
    };
}

void from_json(const nlohmann::json& j, RequestType& obj) {
    obj.mAction = static_cast<ActionType::Action>(j["mAction"]);
    j.at("mParameterList").get_to(obj.mParameterList);
    j.at("mTimestamp").get_to(obj.mTimestamp);
}

// ActionStatusType
void to_json(nlohmann::json& j, const ActionStatusType& obj) {
  j = nlohmann::json{
    {"ActionStatus", static_cast<int>(obj)}
  };
}

void from_json(const nlohmann::json& j, ActionStatusType& obj) {
  obj = static_cast<ActionStatusType::ActionStatus>(j["ActionStatus"]);
}

// SubscriberList
void to_json(nlohmann::json& j, const T_SubscriberList& obj) {
  j = nlohmann::json::array();
  for(const auto& endpoint : obj) {
    j.push_back(endpoint.toString());
  }
}

void from_json(const nlohmann::json& j, T_SubscriberList& obj) {
  obj.clear();
  for(const auto& item : j) {
    obj.push_back(StringToEndpoint(item.get<std::string>()));
  }
}

// TopicStatus
void to_json(nlohmann::json& j, const T_TopicStatus& obj) {
  j = {
    {"Timestamp", obj.Timestamp},
    {"SubscriberList_t", obj.SubscriberList_t}
  };
}

void from_json(const nlohmann::json& j, T_TopicStatus& obj) {
  j.at("Timestamp").get_to(obj.Timestamp);
  j.at("SubscriberList_t").get_to(obj.SubscriberList_t);
}
