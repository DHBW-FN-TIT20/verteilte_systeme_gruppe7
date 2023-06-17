/**************************************************************************************************
 * @file    subscriber_type.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    08-June-2023
 * @brief   Datatype for subscriber
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <memory>
#include <string>
#include "endpoint_type.h"
#include "tcp/tcp_server.hpp"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
struct T_Subscriber {
  T_Endpoint endpoint;
  std::shared_ptr<TcpConnection> connection;

  bool operator==(const T_Subscriber &other) const {
    return endpoint == other.endpoint && connection == other.connection;
  }

  bool operator!=(const T_Subscriber &other) const {
    return endpoint != other.endpoint || connection != other.connection;
  }

  std::string toString(void) const {
    return endpoint.toString();
  }
};

inline T_Subscriber StringToSubsciber(const std::string &subscriberString) {
  return {StringToEndpoint(subscriberString), nullptr};
}
