<<<<<<< HEAD
/**************************************************************************************************
=======
/**
  *************************************************************************************************
>>>>>>> 2381ea8 (:label: update file names to match naming convention)
  * @file    topic_status_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
  * @brief   
  ************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
<<<<<<< HEAD
#include <string>
#include <ctime>
=======
>>>>>>> 2381ea8 (:label: update file names to match naming convention)
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
