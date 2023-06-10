/**************************************************************************************************
 * @file    test_send_request.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   Unit tests for sendRequest functions.
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "send_request.hpp"
#include <iostream>
#include <cassert>
#include <string>

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/
void mockMessageHandler(std::string mockMessage) {} //callback function for tcp client (only definition needed)

void TestSplitAndRemoveNewline(void) {
  std::string inputString = "{element:1};{element:2}\n";
  std::vector<std::string> expectedVector = {"{element:1}", "{element:2}"};
  assert(splitAndRemoveNewline(inputString) == expectedVector);
}


int main() {
  TestSplitAndRemoveNewline();

  std::cout << "All tests for sendRequest functions passed" << std::endl;
  return 0;
}