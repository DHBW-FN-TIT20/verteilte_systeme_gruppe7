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
#include "request_type.h"
#include <iostream>
#include <cassert>

 /*************************************************************************************************
 * Unit tests
 *************************************************************************************************/
void TestEncode() {
  RequestParser tempParser;
  RequestType tempRequest = {
    ACTION_ENUM::SUBSCRIBE_TOPIC,
    {{"topicName", "Topic1"}},
    12345678
  };
  assert(tempParser.encode(tempRequest) == R"({"mAction":0,"mParameterList":{"topicName":"Topic1"},"mTimestamp":12345678})");
}

void TestDecode() {
  RequestParser tempParser;
  RequestType tempExpectedRequest = {
    ACTION_ENUM::SUBSCRIBE_TOPIC,
    {{"topicName", "Topic1"}},
    12345678
  };
  std::string tempJsonString = R"({"mAction":0,"mParameterList":{"topicName":"Topic1"},"mTimestamp":12345678})";
  
  RequestType resultRequest = tempParser.decode(tempJsonString);
  assert(resultRequest.mAction == tempExpectedRequest.mAction);
  assert(resultRequest.mTimestamp == tempExpectedRequest.mTimestamp); 
  assert(resultRequest.mParameterList == tempExpectedRequest.mParameterList);
}

int main() {
  TestEncode();
  TestDecode();

  std::cout << "All tests for class RequestParser passed" << std::endl;
  return 0;
}
