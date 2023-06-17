/**************************************************************************************************
 * @file    request_type.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    08-June-2023
 * @brief   Type definition for request for communication between publisher/subscriber and broker 
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <map>
#include <string>
#include <chrono>
#include <ctime>
#include "action_type.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
struct RequestType {
  private:
    std::time_t getTimestamp(void) {
      return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }
    
  public:
    ActionType                              mAction;
    std::map<std::string, std::string>      mParameterList;
    std::time_t                             mTimestamp;
    
    RequestType() = default;
    RequestType(ActionType action, std::map<std::string, std::string> parameterList, std::time_t timestamp) : mAction(action), mParameterList(parameterList), mTimestamp(timestamp) {}
    RequestType(ActionType action, std::map<std::string, std::string> parameterList) : mAction(action), mParameterList(parameterList), mTimestamp(getTimestamp()) {}
    RequestType(const RequestType &other) : mAction(other.mAction), mParameterList(other.mParameterList), mTimestamp(other.mTimestamp) {}

    RequestType &operator=(const RequestType &other) {
      if(this != &other) {
        mAction = other.mAction;
        mParameterList = other.mParameterList;
        mTimestamp = other.mTimestamp;
      }
      return *this;
    }

    bool operator==(const RequestType &other) const {
      return mAction == other.mAction && mParameterList == other.mParameterList && mTimestamp == other.mTimestamp;
    }
};
