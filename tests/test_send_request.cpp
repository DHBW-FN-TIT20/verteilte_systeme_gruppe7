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

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/
/* Test request with response */
void TestSendRequestNormal(void) {

}

/* Test request without response */
void TestSendRequestVoid(void) {

}

int main() {
  TestSendRequestNormal();
  TestSendRequestVoid();

  std::cout << "All tests for sendRequest functions passed" << std::endl;
  return 0;
}