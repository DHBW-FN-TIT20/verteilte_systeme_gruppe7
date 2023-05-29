/**
  *************************************************************************************************
  * @file    request_parser.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    29-May-2023
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
    {"Action_t", static_cast<int>(request.Action_t)},
    {"ParameterList", request.ParameterList},
    {"Timestamp", request.Timestamp}
  };

  return jsonRequest.dump();
}

T_Request RequestParser::decode(std::string requestString) const {
  nlohmann::json jsonRequest = nlohmann::json::parse(requestString);
  
  T_Request request;
  request.Action_t = static_cast<ACTION_ENUM::Action>(jsonRequest["Action_t"]);
  request.ParameterList = jsonRequest["ParameterList"];
  request.Timestamp = jsonRequest["Timestamp"];

  return request;
}
