/**************************************************************************************************
 * @file    message_parser.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    03-June-2023
 * @brief   
 **************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "message_parser.h"
#include "request_type.h"
#include "action_status_enum.h"
#include "T_TopicStatus.h"

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
    obj.mAction = static_cast<ACTION_ENUM::Action>(j["mAction"]);
    j.at("mParameterList").get_to(obj.mParameterList);
    j.at("mTimestamp").get_to(obj.mTimestamp);
}

// ACTION_STATUS_ENUM
void to_json(nlohmann::json& j, const ACTION_STATUS_ENUM& obj) {
  j = nlohmann::json{
    {"ActionStatus", static_cast<int>(obj)}
  };
}

void from_json(const nlohmann::json& j, ACTION_STATUS_ENUM& obj) {
  obj = static_cast<ACTION_STATUS_ENUM::ActionStatus>(j["ActionStatus"]);
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
