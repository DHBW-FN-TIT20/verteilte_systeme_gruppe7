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
  ACTION_STATUS_ENUM test_status_ok = ACTION_STATUS_ENUM::STATUS_OK;
  assert(test_status_ok.toString() == "STATUS_OK");

  ACTION_STATUS_ENUM test_topic_non_existent = ACTION_STATUS_ENUM::TOPIC_NON_EXISTENT;
  assert(test_topic_non_existent.toString() == "TOPIC_NON_EXISTENT");

  ACTION_STATUS_ENUM test_invalid_parameters = ACTION_STATUS_ENUM::INVALID_PARAMETERS;
  assert(test_invalid_parameters.toString() == "INVALID_PARAMETERS");

  ACTION_STATUS_ENUM test_internal_error = ACTION_STATUS_ENUM::INTERNAL_ERROR;
  assert(test_internal_error.toString() == "INTERNAL_ERROR");

  ACTION_STATUS_ENUM test_error = static_cast<ACTION_STATUS_ENUM::ActionStatus>(10);
  assert(test_error.toString() == "Error");
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