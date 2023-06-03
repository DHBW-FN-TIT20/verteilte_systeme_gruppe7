/**************************************************************************************************
 * @file    test_message_parser.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    03-June-2023
 * @brief   
 **************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <iostream>
#include <map>
#include <string>
#include "request_type.h"
#include "message_parser.cpp"

void TestEncodeObject() {
  MessageParser tempParser;

  // Test RequestType
  std::map<std::string, std::string> paramlist = {
    {"TestParameter", "TestParameterValue"}
  };
  RequestType request = RequestType(ACTION_ENUM::PUBLISH_TOPIC, paramlist, 12345678);

  std::string result = tempParser.encodeObject(request);
  
  assert(result == R"({"mAction":2,"mParameterList":{"TestParameter":"TestParameterValue"},"mTimestamp":12345678})");
}

void TestDecodeObject() { 
  MessageParser tempParser;

  RequestType tempExpectedRequest = {
    ACTION_ENUM::PUBLISH_TOPIC,
    {{"TestParameter", "TestParameterValue"}},
    12345678
  };
  std::string tempObjectString = R"({"mAction":2,"mParameterList":{"TestParameter":"TestParameterValue"},"mTimestamp":12345678})";

  RequestType result = tempParser.decodeObject<RequestType>(tempObjectString);
  assert(result.mAction == tempExpectedRequest.mAction);
  assert(result.mParameterList == tempExpectedRequest.mParameterList);
  assert(result.mTimestamp == tempExpectedRequest.mTimestamp);
}

int main() {
  TestEncodeObject();
  TestDecodeObject();

  std::cout << "All tests for class MessageParser passed" << std::endl;
}
