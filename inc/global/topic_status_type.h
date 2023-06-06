/**
  *************************************************************************************************
  * @file    topic_status_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
  * @brief   
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "subscriber_list_type.h"
#include "action_status_type.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
typedef struct T_TopicStatusType {
  int32_t             Timestamp;
  T_SubscriberList    SubscriberList_t;
  ActionStatusType    ActionStatus;

  std::string toString() {
    std::string result = "Timestamp: " + std::to_string(Timestamp) + "; Subscriber: ";

    for(size_t i = 0; i < SubscriberList_t.size(); i++) {
      result += SubscriberList_t.at(i);

      result += (i != SubscriberList_t.size() - 1)? ", " : "; ";
    }

    result += "Action Status: " + ActionStatus.toString();

    return result;
  }
} T_TopicStatus;