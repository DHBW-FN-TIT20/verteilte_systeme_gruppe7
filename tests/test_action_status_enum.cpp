/**
  *************************************************************************************************
  * @file    test_action_enum.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    24-May-2023
  * @brief   Unit tests for class ACTION_STATUS_ENUM
  *************************************************************************************************
  */

 /**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "../inc/global/action_status_enum.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

 /*************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TEST_toString() {
  ACTION_STATUS_ENUM actionStatus1(ACTION_STATUS_ENUM::STATUS_OK);
  assert(actionStatus1.toString() == "STATUS_OK");

  ACTION_STATUS_ENUM actionStatus2(ACTION_STATUS_ENUM::TOPIC_NON_EXISTENT);
  assert(actionStatus2.toString() == "TOPIC_NON_EXISTENT");

  ACTION_STATUS_ENUM actionStatus3(ACTION_STATUS_ENUM::INVALID_PARAMETERS);
  assert(actionStatus3.toString() == "INVALID_PARAMETERS");

  ACTION_STATUS_ENUM actionStatus4(ACTION_STATUS_ENUM::INTERNAL_ERROR);
  assert(actionStatus4.toString() == "INTERNAL_ERROR");

  ACTION_STATUS_ENUM actionStatus5(static_cast<ACTION_STATUS_ENUM::ActionStatus>(10));
  assert(actionStatus5.toString() == "Error");
}

void TEST_conversionOperator() {
  ACTION_STATUS_ENUM actionStatus(ACTION_STATUS_ENUM::STATUS_OK);
  ACTION_STATUS_ENUM::ActionStatus status = actionStatus;
  assert(status == ACTION_STATUS_ENUM::STATUS_OK);
}

int main() {
  TEST_toString();
  TEST_conversionOperator();

  cout << "All tests passed" << endl;
  return 0;
}