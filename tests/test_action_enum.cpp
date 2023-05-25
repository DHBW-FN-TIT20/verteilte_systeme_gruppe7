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
#include "../inc/global/action_enum.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

 /*************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TEST_toString() {
  ACTION_ENUM action1(ACTION_ENUM::SUBSCRIBE_TOPIC);
  assert(action1.toString() == "SUBSCRIBE_TOPIC");

  ACTION_ENUM action2(ACTION_ENUM::UNSUBSCRIBE_TOPIC);
  assert(action2.toString() == "UNSUBSCRIBE_TOPIC");

  ACTION_ENUM action3(ACTION_ENUM::PUBLISH_TOPIC);
  assert(action3.toString() == "PUBLISH_TOPIC");

  ACTION_ENUM action4(ACTION_ENUM::LIST_TOPICS);
  assert(action4.toString() == "LIST_TOPICS");

  ACTION_ENUM action5(ACTION_ENUM::GET_TOPIC_STATUS);
  assert(action5.toString() == "GET_TOPIC_STATUS");

  ACTION_ENUM action6(ACTION_ENUM::UPDATE_TOPIC);
  assert(action6.toString() == "UPDATE_TOPIC");

  ACTION_ENUM actionStatus7(static_cast<ACTION_ENUM::Action>(10));
  assert(actionStatus7.toString() == "Error");
}

void TEST_conversionOperator() {
  ACTION_ENUM action(ACTION_ENUM::SUBSCRIBE_TOPIC);
  ACTION_ENUM::Action status = action;
  assert(status == ACTION_ENUM::SUBSCRIBE_TOPIC);
}

int main() {
  TEST_toString();
  TEST_conversionOperator();

  cout << "All tests passed" << endl;
  return 0;
}