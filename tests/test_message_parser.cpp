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
#include "action_status_enum.h"

void TestEncodeObject() {
  MessageParser tempParser;

  // Test RequestType
  std::map<std::string, std::string> paramlist = {
    {"TestParameter", "TestParameterValue"}
  };
  RequestType request = RequestType(ACTION_ENUM::PUBLISH_TOPIC, paramlist, 12345678);

  std::string result = tempParser.encodeObject(request);
  
  assert(result == R"({"mAction":2,"mParameterList":{"TestParameter":"TestParameterValue"},"mTimestamp":12345678})");

  // Test ActionStatus
  ACTION_STATUS_ENUM actionStatus = ACTION_STATUS_ENUM::TOPIC_NON_EXISTENT;
  
  std::string actionStatusResult = tempParser.encodeObject(actionStatus);

  assert(actionStatusResult == R"({"ActionStatus":1})");
}

void TestDecodeObject() { 
  MessageParser tempParser;

  // Test RequestType
  RequestType tempExpectedRequestType = {
    ACTION_ENUM::PUBLISH_TOPIC,
    {{"TestParameter", "TestParameterValue"}},
    12345678
  };
  std::string tempRequestTypeString = R"({"mAction":2,"mParameterList":{"TestParameter":"TestParameterValue"},"mTimestamp":12345678})";

  RequestType resultResultType = tempParser.decodeObject<RequestType>(tempRequestTypeString);
  assert(resultResultType.mAction == tempExpectedRequestType.mAction);
  assert(resultResultType.mParameterList == tempExpectedRequestType.mParameterList);
  assert(resultResultType.mTimestamp == tempExpectedRequestType.mTimestamp);

  // Test ActionStatus
  ACTION_STATUS_ENUM tempExpectedActionStatus = ACTION_STATUS_ENUM::TOPIC_NON_EXISTENT;
  std::string tempActionStatusStirng = R"({"ActionStatus":1})";

  ACTION_STATUS_ENUM resultActionStatus = tempParser.decodeObject<ACTION_STATUS_ENUM>(tempActionStatusStirng);
  assert(resultActionStatus == ACTION_STATUS_ENUM::TOPIC_NON_EXISTENT);
}

int main() {
  TestEncodeObject();
  TestDecodeObject();

  std::cout << "All tests for class MessageParser passed" << std::endl;
}
