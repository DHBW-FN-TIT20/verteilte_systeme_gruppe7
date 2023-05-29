/**
  *************************************************************************************************
  * @file    test_action_enum.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    24-May-2023
  * @brief   Unit tests for class ACTION_ENUM
  *************************************************************************************************
  */

 /**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "action_enum.h"
#include <iostream>
#include <cassert>

 /*************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TEST_toString() {
  ACTION_ENUM testSubscribeTopic = ACTION_ENUM::SUBSCRIBE_TOPIC;
  assert(testSubscribeTopic.toString() == "SUBSCRIBE_TOPIC");

  ACTION_ENUM testUnsubscribeTopic = ACTION_ENUM::UNSUBSCRIBE_TOPIC;
  assert(testUnsubscribeTopic.toString() == "UNSUBSCRIBE_TOPIC");

  ACTION_ENUM testPublishTopic = ACTION_ENUM::PUBLISH_TOPIC;
  assert(testPublishTopic.toString() == "PUBLISH_TOPIC");

  ACTION_ENUM testListTopic = ACTION_ENUM::LIST_TOPICS;
  assert(testListTopic.toString() == "LIST_TOPICS");

  ACTION_ENUM testGetTopicStatus = ACTION_ENUM::GET_TOPIC_STATUS;
  assert(testGetTopicStatus.toString() == "GET_TOPIC_STATUS");

  ACTION_ENUM testUpdateTopic = ACTION_ENUM::UPDATE_TOPIC;
  assert(testUpdateTopic.toString() == "UPDATE_TOPIC");

  ACTION_ENUM testError = static_cast<ACTION_ENUM::Action>(10);
  assert(testError.toString() == "Error");
}

void TEST_fromString() {
  std::string tempStringSubscribeTopic = "SUBSCRIBE_TOPIC";
  ACTION_ENUM testSubscribeTopic;
  testSubscribeTopic.fromString(tempStringSubscribeTopic);
  assert(testSubscribeTopic == 0U);

  std::string tempStringUnsubscribeTopic = "UNSUBSCRIBE_TOPIC";
  ACTION_ENUM testUnsubscribeTopic;
  testUnsubscribeTopic.fromString(tempStringUnsubscribeTopic);
  assert(testUnsubscribeTopic == 1U);

  std::string tempStringPublishTopic = "PUBLISH_TOPIC";
  ACTION_ENUM testPublishTopic;
  testPublishTopic.fromString(tempStringPublishTopic);
  assert(testPublishTopic == 2U);

  std::string tempStringListTopics = "LIST_TOPICS";
  ACTION_ENUM testListTopics;
  testListTopics.fromString(tempStringListTopics);
  assert(testListTopics == 3U);

  std::string tempStringGetTopicStatus = "GET_TOPIC_STATUS";
  ACTION_ENUM testGetTopicStatus;
  testGetTopicStatus.fromString(tempStringGetTopicStatus);
  assert(testGetTopicStatus == 4U);

  std::string tempStringUpdateTopic = "UPDATE_TOPIC";
  ACTION_ENUM testUpdateTopic;
  testUpdateTopic.fromString(tempStringUpdateTopic);
  assert(testUpdateTopic == 5U);
}

void TEST_conversionOperator() {
  ACTION_ENUM action = ACTION_ENUM::SUBSCRIBE_TOPIC;
  action = ACTION_ENUM::UNSUBSCRIBE_TOPIC;
  assert(action == ACTION_ENUM::UNSUBSCRIBE_TOPIC);
}

int main() {
  TEST_toString();
  TEST_fromString();
  TEST_conversionOperator();

  std::cout << "All tests for class ACTION_ENUM passed" << std::endl;
  return 0;
}

