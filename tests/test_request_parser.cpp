/**
  *************************************************************************************************
  * @file    test_request_parser.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    28-May-2023
  * @brief   Unit tests for class MESSAGE_PARSER
  *************************************************************************************************
  */

 /**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "../inc/request_parser.h"
#include "T_Request.h"
#include <iostream>
#include <cassert>

 /*************************************************************************************************
 * Unit tests
 *************************************************************************************************/
void TEST_encode() {
  RequestParser tempParser;
  T_Request tempRequest = {
    ACTION_ENUM::SUBSCRIBE_TOPIC,
    {{"topicName", "Topic1"}},
    12345678
  };

  assert(tempParser.encode(tempRequest) == R"({"Action":"SUBSCRIBE_TOPIC","Timestamp":12345678,"ParameterList":{"topicName":"Topic1"}})");
}


int main() {
  TEST_encode();

  std::cout << "All tests for class RequestParser passed" << std::endl;
  return 0;
}
