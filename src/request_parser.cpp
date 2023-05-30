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

std::string RequestParser::encode(RequestType request) const {
  nlohmann::json jsonRequest = {
    {"mAction", static_cast<int>(request.mAction)},
    {"mParameterList", request.mParameterList},
    {"mTimestamp", request.mTimestamp}
  };

  return jsonRequest.dump();
}

RequestType RequestParser::decode(std::string requestString) const {
  nlohmann::json jsonRequest = nlohmann::json::parse(requestString);
  
  RequestType request;
  request.mAction = static_cast<ACTION_ENUM::Action>(jsonRequest["mAction"]);
  request.mParameterList = jsonRequest["mParameterList"];
  request.mTimestamp = jsonRequest["mTimestamp"];

  return request;
}
