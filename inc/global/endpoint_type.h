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
    static const std::regex ip4_regex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

    try {
      int portInt = std::stoi(port);
      if(portInt <= 49151 || portInt >= 65536)
        return false;
    } catch (const std::invalid_argument& e) {
      //conversion failed
      return false;
    } catch (const std::out_of_range& e) {
      //out of valid range
      return false;
    }
    
    if(!std::regex_match(address, ip4_regex))
      return false;
    
    return true;
  }
};

inline T_Endpoint StringToEndpoint(std::string endpointString) {
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
