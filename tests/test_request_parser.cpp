/**
  *************************************************************************************************
  * @file    test_request_parser.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    29-May-2023
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

void TestDecode() {
  RequestParser tempParser;
  T_Request tempExpectedRequest = {
    ACTION_ENUM::SUBSCRIBE_TOPIC,
    {{"topicName", "Topic1"}},
    12345678
  };
  std::string tempJsonString = R"({"Action_t":"SUBSCRIBE_TOPIC","ParameterList":{"topicName":"Topic1"},"Timestamp":12345678})";
  
  T_Request resultRequest = tempParser.decode(tempJsonString);
  assert(resultRequest.Action_t == tempExpectedRequest.Action_t);
  assert(resultRequest.Timestamp == tempExpectedRequest.Timestamp); 
  assert(resultRequest.ParameterList == tempExpectedRequest.ParameterList);

}

int main() {
  TestEncode();
  TestDecode();

  std::cout << "All tests for class RequestParser passed" << std::endl;
  return 0;
}
