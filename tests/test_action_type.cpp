/**************************************************************************************************
  * @file    test_action_type.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    07-June-2023
  * @brief   Unit tests for class ActionType
  ************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "action_type.h"
#include <iostream>
#include <cassert>

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TestToString() {
  ActionType testSubscribeTopic = ActionType::SUBSCRIBE_TOPIC;
  assert(testSubscribeTopic.toString() == "SUBSCRIBE_TOPIC");

  ActionType testUnsubscribeTopic = ActionType::UNSUBSCRIBE_TOPIC;
  assert(testUnsubscribeTopic.toString() == "UNSUBSCRIBE_TOPIC");

  ActionType testPublishTopic = ActionType::PUBLISH_TOPIC;
  assert(testPublishTopic.toString() == "PUBLISH_TOPIC");

  ActionType testListTopic = ActionType::LIST_TOPICS;
  assert(testListTopic.toString() == "LIST_TOPICS");

  ActionType testGetTopicStatus = ActionType::GET_TOPIC_STATUS;
  assert(testGetTopicStatus.toString() == "GET_TOPIC_STATUS");

  ActionType testUpdateTopic = ActionType::UPDATE_TOPIC;
  assert(testUpdateTopic.toString() == "UPDATE_TOPIC");

  ActionType testError = static_cast<ActionType::Action>(10);
  assert(testError.toString() == "Error");
}

void TestConversionOperator() {
  ActionType action = ActionType::SUBSCRIBE_TOPIC;
  action = ActionType::UNSUBSCRIBE_TOPIC;
  assert(action == ActionType::UNSUBSCRIBE_TOPIC);
}

int main() {
  TestToString();
  TestConversionOperator();

  std::cout << "All tests for class ActionType passed" << std::endl;
  return 0;
}
