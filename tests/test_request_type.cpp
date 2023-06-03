/**
  *************************************************************************************************
  * @file    test_request.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    01-June-2023
  * @brief   Unit tests for class Request 
  *************************************************************************************************
  */

 /**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "request_type.h"
#include <iostream>
#include <cassert>

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TestRequestType(void) {
  RequestType testSetTimestampManually(ActionType::SUBSCRIBE_TOPIC, {{"param1", "value1"}, {"param2", "value2"}}, static_cast<std::time_t>(1234567890));
  assert(testSetTimestampManually.mAction == ActionType::SUBSCRIBE_TOPIC);
  std::map<std::string, std::string> tempParameterList = {{"param1", "value1"}, {"param2", "value2"}};
  assert(testSetTimestampManually.mParameterList == tempParameterList);
  assert(testSetTimestampManually.mTimestamp == static_cast<std::time_t>(1234567890));

  RequestType testDefaultTimestamp(ActionType::SUBSCRIBE_TOPIC, {{"param1", "value1"}, {"param2", "value2"}});
  std::time_t testTimestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  assert(testDefaultTimestamp.mAction == ActionType::SUBSCRIBE_TOPIC);
  assert(testDefaultTimestamp.mParameterList == tempParameterList);
  assert(testDefaultTimestamp.mTimestamp == testTimestamp);
}

int main() {
  TestRequestType();

  std::cout << "All tests for class RequestType passed." << std::endl;
  return 0;
}