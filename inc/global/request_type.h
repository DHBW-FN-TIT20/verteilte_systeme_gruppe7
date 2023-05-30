/**
  *************************************************************************************************
  * @file    T_Request.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    27-May-2023
  * @brief   Type definition for request for communication between publisher/subscriber and broker 
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <map>
#include <string>
#include <ctime>
#include "action_enum.h"


/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
class RequestType {
  public:
    ACTION_ENUM                             mAction;
    std::map<std::string, std::string>      mParameterList;
    std::time_t                             mTimestamp;
    
    RequestType() = default;
    RequestType(ACTION_ENUM action, std::map<std::string, std::string> parameterList, std::time_t timestamp) : mAction(action), mParameterList(parameterList), mTimestamp(timestamp) {}
    RequestType(ACTION_ENUM action, std::map<std::string, std::string> parameterList) : mAction(action), mParameterList(parameterList), mTimestamp(getTimestamp()) {}

    std::time_t getTimestamp(void) {
      return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }
};
