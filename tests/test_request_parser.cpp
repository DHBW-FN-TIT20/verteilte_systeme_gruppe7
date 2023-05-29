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
#include "request_parser.cpp"
#include "T_Request.h"
#include <iostream>
#include <cassert>

 /*************************************************************************************************
 * Unit tests
 *************************************************************************************************/
void TestEncode() {
  RequestParser tempParser;
  T_Request tempRequest = {
    ACTION_ENUM::SUBSCRIBE_TOPIC,
    {{"topicName", "Topic1"}},
    12345678
  };
  assert(tempParser.encode(tempRequest) == R"({"Action_t":"SUBSCRIBE_TOPIC","ParameterList":{"topicName":"Topic1"},"Timestamp":12345678})");
}

int main() {
  TestEncode();

  std::cout << "All tests for class RequestParser passed" << std::endl;
  return 0;
}
