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
#include "action_status_enum.h"
#include <iostream>
#include <cassert>

 /*************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TEST_toString() {
  ACTION_STATUS_ENUM testStatusOk = ACTION_STATUS_ENUM::STATUS_OK;
  assert(testStatusOk.toString() == "STATUS_OK");

  ACTION_STATUS_ENUM testTopicNonExistent = ACTION_STATUS_ENUM::TOPIC_NON_EXISTENT;
  assert(testTopicNonExistent.toString() == "TOPIC_NON_EXISTENT");

  ACTION_STATUS_ENUM testInvalidParameters = ACTION_STATUS_ENUM::INVALID_PARAMETERS;
  assert(testInvalidParameters.toString() == "INVALID_PARAMETERS");

  ACTION_STATUS_ENUM testInternalError = ACTION_STATUS_ENUM::INTERNAL_ERROR;
  assert(testInternalError.toString() == "INTERNAL_ERROR");

  ACTION_STATUS_ENUM testError = static_cast<ACTION_STATUS_ENUM::ActionStatus>(10);
  assert(testError.toString() == "Error");
}

void TEST_conversionOperator() {
  ACTION_STATUS_ENUM actionStatus = ACTION_STATUS_ENUM::STATUS_OK;
  actionStatus = ACTION_STATUS_ENUM::TOPIC_NON_EXISTENT;
  assert(actionStatus == ACTION_STATUS_ENUM::TOPIC_NON_EXISTENT);
}

int main() {
  TEST_toString();
  TEST_conversionOperator();

  std::cout << "All tests for class ACTION_STATUS_ENUM passed" << std::endl;
  return 0;
}