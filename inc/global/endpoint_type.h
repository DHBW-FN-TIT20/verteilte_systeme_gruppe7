/**************************************************************************************************
 * @file    endpoint_type.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   Endpoint datatype.
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string>
#include <cstdlib>
#include <algorithm>
#include <regex>

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
struct T_Endpoint {
  std::string address;
  std::string port;

  /* operator overloads */
  bool operator==(const T_Endpoint &other) const {
    return address == other.address && port == other.port;
  }

  bool operator!=(const T_Endpoint &other) const {
    return address != other.address || port != other.port;
  }

  std::string toString(void) const {
    return address + ":" + port;
  }


  bool isValid() const {
    std::regex ip4_regex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

    return std::stoi(port) > 49151 && std::stoi(port) < 65536 && std::regex_match(address, ip4_regex);
  }
};

T_Endpoint StringToEndpoint(std::string endpointString) {
  T_Endpoint endpoint;

  std::size_t pos = endpointString.find(':');
  if(pos != std::string::npos) {
    endpoint.address = endpointString.substr(0, pos);
    endpoint.port = endpointString.substr(pos + 1);
  } else {
    endpoint.address = "0.0.0.0";
    endpoint.port = "0";
  }
  return endpoint;
}
