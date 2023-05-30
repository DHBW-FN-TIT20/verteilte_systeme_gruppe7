/**
  *************************************************************************************************
  * @file    test_request.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    30-May-2023
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
  RequestType testSetTimestampManually(ACTION_ENUM::SUBSCRIBE_TOPIC, {{"param1", "value1"}, {"param2", "value2"}}, static_cast<std::time_t>(1234567890));
  assert(testSetTimestampManually.mAction == ACTION_ENUM::SUBSCRIBE_TOPIC);
  std::map<std::string, std::string> tempParameterList = {{"param1", "value1"}, {"param2", "value2"}};
  assert(testSetTimestampManually.mParameterList == tempParameterList);
  assert(testSetTimestampManually.mTimestamp == static_cast<std::time_t>(1234567890));

  RequestType testDefaultTimestamp(ACTION_ENUM::SUBSCRIBE_TOPIC, {{"param1", "value1"}, {"param2", "value2"}});
  std::time_t testTimestamp = testDefaultTimestamp.getTimestamp();
  assert(testDefaultTimestamp.mAction == ACTION_ENUM::SUBSCRIBE_TOPIC);
  assert(testDefaultTimestamp.mParameterList == tempParameterList);
  assert(testDefaultTimestamp.mTimestamp == testTimestamp);
}

int main() {
  TestRequestType();

  std::cout << "All tests for class Request passed." << std::endl;
  return 0;
}