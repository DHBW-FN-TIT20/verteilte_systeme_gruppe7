/**************************************************************************************************
 * @file    test_message_parser.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    06-June-2023
 * @brief   
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <iostream>
#include <cassert>
#include <map>
#include <string>
#include "request_type.h"
#include "action_status_type.h"
#include "topic_status_type.h"
#include "parser/message_parser.hpp"

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TestEncodeObject() {
  MessageParser tempParser;

  // Test RequestType
  std::map<std::string, std::string> tempParamlist = {
    {"TestParameter", "TestParameterValue"}
  };
  RequestType request = RequestType(ActionType::PUBLISH_TOPIC, tempParamlist, 12345678);

  std::string result = tempParser.encodeObject(request);
  
  assert(result == R"({"mAction":2,"mParameterList":{"TestParameter":"TestParameterValue"},"mTimestamp":12345678})");

  // Test ActionStatus
  ActionStatusType tempActionStatus = ActionStatusType::TOPIC_NON_EXISTENT;
  
  std::string actionStatusResult = tempParser.encodeObject(tempActionStatus);

  assert(actionStatusResult == R"({"ActionStatus":1})");

  // Test TopicStatus
  T_TopicStatus tempTopicStatus;
  tempTopicStatus.Timestamp = 12345678;
  tempTopicStatus.SubscriberList = {{{"0.0.0.1", "1"}, nullptr}, {{"0.0.0.2", "2"}, nullptr}};

  std::string topicStatusResult = tempParser.encodeObject(tempTopicStatus);
  assert(topicStatusResult == R"({"SubscriberList_t":["0.0.0.1:1","0.0.0.2:2"],"Timestamp":12345678})");

  // Test TopicStringList
  std::vector<std::string> tempTopicList = {
    "topic-one", "topic-two"
  };

  std::string topicListResult = tempParser.encodeObject(tempTopicList);

  assert(topicListResult == R"(["topic-one","topic-two"])");
}

void TestDecodeObject() { 
  MessageParser tempParser;

  // Test RequestType
  RequestType tempExpectedRequestType = {
    ActionType::PUBLISH_TOPIC,
    {{"TestParameter", "TestParameterValue"}},
    12345678
  };
  std::string tempRequestTypeString = R"({"mAction":2,"mParameterList":{"TestParameter":"TestParameterValue"},"mTimestamp":12345678})";

  RequestType resultResultType = tempParser.decodeObject<RequestType>(tempRequestTypeString);
  assert(resultResultType.mAction == tempExpectedRequestType.mAction);
  assert(resultResultType.mParameterList == tempExpectedRequestType.mParameterList);
  assert(resultResultType.mTimestamp == tempExpectedRequestType.mTimestamp);

  // Test ActionStatus
  ActionStatusType tempExpectedActionStatus = ActionStatusType::TOPIC_NON_EXISTENT;
  std::string tempActionStatusStirng = R"({"ActionStatus":1})";

  ActionStatusType resultActionStatus = tempParser.decodeObject<ActionStatusType>(tempActionStatusStirng);
  assert(resultActionStatus == tempExpectedActionStatus);

  // Test TopicStatus
  T_TopicStatus tempExpectedTopicStatus;
  tempExpectedTopicStatus.Timestamp = 12345678;
  tempExpectedTopicStatus.SubscriberList = {StringToSubsciber("0.0.0.1:1"), StringToSubsciber("0.0.0.2:2")};
  std::string tempTopicStatusString = R"({"SubscriberList_t":["0.0.0.1:1","0.0.0.2:2"],"Timestamp":12345678})";

  T_TopicStatus resultTopicStatus = tempParser.decodeObject<T_TopicStatus>(tempTopicStatusString);
  assert(tempExpectedTopicStatus.Timestamp == resultTopicStatus.Timestamp);
  assert(tempExpectedTopicStatus.SubscriberList == resultTopicStatus.SubscriberList);

  // Test TopicStringList
  std::vector<std::string> tempExpectedTopicStringList = {
    "topic-one", "topic-two"
  };
  std::string tempTopicStringListString = R"(["topic-one", "topic-two"])";

  std::vector<std::string> resultTopicStringList = tempParser.decodeObject<std::vector<std::string>>(tempTopicStringListString);

  assert(resultTopicStringList == tempExpectedTopicStringList);
}

int main() {
  TestEncodeObject();
  TestDecodeObject();

  std::cout << "All tests for class MessageParser passed" << std::endl;
  return 0;
}
