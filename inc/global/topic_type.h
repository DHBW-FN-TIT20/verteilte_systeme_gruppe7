/**************************************************************************************************
 * @file    topic_type.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    12-June-2023
 * @brief   Datatype for topic
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "request_type.h"
#include "subscriber_list_type.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
struct T_Topic {
  std::string                   TopicName;
  RequestType                   Request;
  T_SubscriberList              SubscriberList;
  std::thread                   HeartbeatThread;
  std::condition_variable       HeartbeatCondition;
  std::mutex                    HeartbeatMutex;
  bool                          StopHeartbeat = false;
};  /*!< type definition for topic */
