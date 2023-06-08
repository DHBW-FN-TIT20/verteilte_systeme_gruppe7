/**************************************************************************************************
 * @file    message_parser.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    06-June-2023
 * @brief   Prototype for class MessageParser.
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <string>

/* Own Libs / datatypes */
#include "request_type.h"
#include "action_status_type.h"
#include "topic_status_type.h"
#include "subscriber_type.h"
#include "subscriber_list_type.h"

#include "nlohmann/json.hpp"

/**************************************************************************************************
 * Public - classes
 *************************************************************************************************/
class MessageParser {
  public:
    /**
     * @brief function template for decoding json to different datatypes
     * 
     * @tparam T type to decode json string into
     * @param objectString json string
     * @return T object of type T that holds the respective data from the json string
     */
    template <typename T>
    T decodeObject(const std::string& objectString) {
      nlohmann::json j = nlohmann::json::parse(objectString);
      return j.get<T>();
    }

    /**
     * @brief function template to encode different datatypes to json
     * 
     * @tparam T datatype to convert into json
     * @param object object of type T to encode
     * @return std::string json string with the data of the respective object
     */
    template <typename T>
    std::string encodeObject(const T& object) {
      nlohmann::json jsonObject = object;
      return jsonObject.dump();
    }
};

/**************************************************************************************************
 * Function overloads for message parser
 *************************************************************************************************/

// RequestType
inline void to_json(nlohmann::json& j, const RequestType& obj) {
    j = nlohmann::json{
      {"mAction", static_cast<int>(obj.mAction)},
      {"mParameterList", obj.mParameterList},
      {"mTimestamp", obj.mTimestamp}
    };
}

inline void from_json(const nlohmann::json& j, RequestType& obj) {
    obj.mAction = static_cast<ActionType::Action>(j["mAction"]);
    j.at("mParameterList").get_to(obj.mParameterList);
    j.at("mTimestamp").get_to(obj.mTimestamp);
}

// ActionStatusType
inline void to_json(nlohmann::json& j, const ActionStatusType& obj) {
  j = nlohmann::json{
    {"ActionStatus", static_cast<int>(obj)}
  };
}

inline void from_json(const nlohmann::json& j, ActionStatusType& obj) {
  obj = static_cast<ActionStatusType::ActionStatus>(j["ActionStatus"]);
}

// SubscriberList
inline void to_json(nlohmann::json& j, const T_SubscriberList& obj) {
  j = nlohmann::json::array();
  for(const auto& subscriber : obj) {
    j.push_back(subscriber.toString());
  }
}

inline void from_json(const nlohmann::json& j, T_SubscriberList& obj) {
  obj.clear();
  for(const auto& item : j) {
    obj.push_back(StringToSubsciber(item.get<std::string>()));
  }
}

// TopicStatus
inline void to_json(nlohmann::json& j, const T_TopicStatus& obj) {
  j = {
    {"Timestamp", obj.Timestamp},
    {"SubscriberList_t", obj.SubscriberList}
  };
}

inline void from_json(const nlohmann::json& j, T_TopicStatus& obj) {
  j.at("Timestamp").get_to(obj.Timestamp);
  j.at("SubscriberList_t").get_to(obj.SubscriberList);
}

