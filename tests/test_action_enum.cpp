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
  ACTION_ENUM test_subscribe_topic = ACTION_ENUM::SUBSCRIBE_TOPIC;
  assert(test_subscribe_topic.toString() == "SUBSCRIBE_TOPIC");

  ACTION_ENUM test_unsubscribe_topic = ACTION_ENUM::UNSUBSCRIBE_TOPIC;
  assert(test_unsubscribe_topic.toString() == "UNSUBSCRIBE_TOPIC");

  ACTION_ENUM test_publish_topic = ACTION_ENUM::PUBLISH_TOPIC;
  assert(test_publish_topic.toString() == "PUBLISH_TOPIC");

  ACTION_ENUM test_list_topics = ACTION_ENUM::LIST_TOPICS;
  assert(test_list_topics.toString() == "LIST_TOPICS");

  ACTION_ENUM test_get_topic_status = ACTION_ENUM::GET_TOPIC_STATUS;
  assert(test_get_topic_status.toString() == "GET_TOPIC_STATUS");

  ACTION_ENUM test_update_topic = ACTION_ENUM::UPDATE_TOPIC;
  assert(test_update_topic.toString() == "UPDATE_TOPIC");

  ACTION_ENUM test_error = static_cast<ACTION_ENUM::Action>(10);
  assert(test_error.toString() == "Error");
}

void TEST_conversionOperator() {
  ACTION_ENUM action = ACTION_ENUM::SUBSCRIBE_TOPIC;
  action = ACTION_ENUM::UNSUBSCRIBE_TOPIC;
  assert(action == ACTION_ENUM::UNSUBSCRIBE_TOPIC);
}

int main() {
  TEST_toString();
  TEST_conversionOperator();

  std::cout << "All tests for class ACTION_ENUM passed" << std::endl;
  return 0;
}

