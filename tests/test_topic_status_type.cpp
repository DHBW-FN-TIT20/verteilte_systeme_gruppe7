/**************************************************************************************************
  * @file    test_topic_status_type.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    07-June-2023
  * @brief   Unit tests for T_TopicStatus
  ************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "topic_status_type.h"
#include "action_status_type.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TestToString() {
  int32_t tempTimestamp = 12345678;
  T_SubscriberList tempSubscriberList = {{{"0.0.0.1", "1"}, nullptr}, {{"0.0.0.2", "2"}, nullptr}, {{"0.0.0.3", "3"}, nullptr}};
  ActionStatusType tempActionStatus = ActionStatusType::STATUS_OK;
  
  T_TopicStatus testTopicStatus_t = {
    tempTimestamp,
    tempSubscriberList,
    tempActionStatus
  };
  assert(testTopicStatus_t.toString() == "Timestamp: 12345678; Subscriber: 0.0.0.1:1, 0.0.0.2:2, 0.0.0.3:3; Action Status: STATUS_OK");
}


int main() {
  TestToString();

  std::cout << "All tests for struct T_TopicStatus passed" << std::endl;
  return 0;
}
