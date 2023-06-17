/**************************************************************************************************
 * @file    topic_status_type.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    08-June-2023
 * @brief   Datatype for topic status
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string>
#include <ctime>
#include "subscriber_list_type.h"
#include "action_status_type.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
struct T_TopicStatus {
  std::time_t         Timestamp;
  T_SubscriberList    SubscriberList;

  std::string toString() {
    std::string result = "Timestamp: " + std::to_string(Timestamp) + "; Subscriber: ";

    for(size_t i = 0; i < SubscriberList.size(); i++) {
      result += SubscriberList.at(i).endpoint.toString();

      result += (i != SubscriberList.size() - 1)? ", " : ";";
    }

    return result;
  }

  bool operator==(const T_TopicStatus &other) const {
    return Timestamp == other.Timestamp && SubscriberList == other.SubscriberList;
  }
};
