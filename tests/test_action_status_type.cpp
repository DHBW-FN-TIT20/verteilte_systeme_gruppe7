/**************************************************************************************************
  * @file    test_action_status_type.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    07-June-2023
  * @brief   Unit tests for class ActionStatusType
  ************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "action_status_type.h"
#include <iostream>
#include <cassert>

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TestToString() {
  ActionStatusType testStatusOk = ActionStatusType::STATUS_OK;
  assert(testStatusOk.toString() == "STATUS_OK");

  ActionStatusType testTopicNonExistent = ActionStatusType::TOPIC_NON_EXISTENT;
  assert(testTopicNonExistent.toString() == "TOPIC_NON_EXISTENT");

  ActionStatusType testInvalidParameters = ActionStatusType::INVALID_PARAMETERS;
  assert(testInvalidParameters.toString() == "INVALID_PARAMETERS");

  ActionStatusType testInternalError = ActionStatusType::INTERNAL_ERROR;
  assert(testInternalError.toString() == "INTERNAL_ERROR");

  ActionStatusType testError = static_cast<ActionStatusType::ActionStatus>(10);
  assert(testError.toString() == "Error");
}

void TestConversionOperator() {
  ActionStatusType actionStatus = ActionStatusType::STATUS_OK;
  actionStatus = ActionStatusType::TOPIC_NON_EXISTENT;
  assert(actionStatus == ActionStatusType::TOPIC_NON_EXISTENT);
}

int main() {
  TestToString();
  TestConversionOperator();

  std::cout << "All tests for class ActionStatusType passed" << std::endl;
  return 0;
}
