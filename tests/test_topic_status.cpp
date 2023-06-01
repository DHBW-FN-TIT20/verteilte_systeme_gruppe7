/**
  *************************************************************************************************
  * @file    test_topic_status.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    01-June-2023
  * @brief   Unit tests for class ActionStatusType
  *************************************************************************************************
  */

 /**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "T_TopicStatus.h"
#include "action_status_type.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>

 /*************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TEST_toString() {
  int32_t tempTimestamp = 12345678;
  T_SubscriberList tempSubscriberList = {"subscriber1", "subscriber2", "subscriber3"};
  ActionStatusType tempActionStatus = ActionStatusType::STATUS_OK;
  
  T_TopicStatus testTopicStatus_t = {
    tempTimestamp,
    tempSubscriberList,
    tempActionStatus
  };
  assert(testTopicStatus_t.toString() == "Timestamp: 12345678; Subscriber: subscriber1, subscriber2, subscriber3; Action Status: STATUS_OK");
}


int main() {
  TEST_toString();

  std::cout << "All tests for struct T_TopicStatus passed" << std::endl;
  return 0;
}