/**
  *************************************************************************************************
  * @file    request_parser.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    28-May-2023
  * @brief   Implementation for class RequestParser
  *************************************************************************************************
  */

 /**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "request_parser.h"
#include "nlohmann/json.hpp"

std::string RequestParser::encode(T_Request request) const {
  nlohmann::json jsonRequest = {
    {"Action_t", request.Action_t.toString()},
    {"ParameterList", request.ParameterList},
    {"Timestamp", request.Timestamp}
  };

  return jsonRequest.dump();
}
