/**************************************************************************************************
 * @file    test_endpoint_type.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    07-June-2023
 * @brief   Unit tests for struct T_Endpoint
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <iostream>
#include <cassert>
#include "endpoint_type.h"

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TestOperatorIsEqualTo(void) {
  T_Endpoint testOperatorIsEqualTo1 = {"127.0.0.1", "8080"};
  T_Endpoint testOperatorIsEqualTo2 = {"127.0.0.1", "8080"};
  T_Endpoint testOperatorIsEqualTo3 = {"0.0.0.0", "5000"};

  assert(testOperatorIsEqualTo1 == testOperatorIsEqualTo2);
  assert((testOperatorIsEqualTo1 == testOperatorIsEqualTo3) == false);
}

void TestOperatorNotEqualTo(void) {
  T_Endpoint testOperatorNotEqualTo1 = {"127.0.0.1", "8080"};
  T_Endpoint testOperatorNotEqualTo2 = {"127.0.0.1", "8080"};
  T_Endpoint testOperatorNotEqualTo3 = {"0.0.0.0", "5000"};

  assert(testOperatorNotEqualTo1 != testOperatorNotEqualTo3);
  assert((testOperatorNotEqualTo1 != testOperatorNotEqualTo2) == false);
}

void TestToString(void) {
  T_Endpoint testToString = {"127.0.0.1", "8080"};
  
  assert(testToString.toString() == "127.0.0.1:8080");
}

void TestStringToEndpoint(void) {
  std::string testStringToEndpoint = "127.0.0.1:8080";
  
  T_Endpoint convertedEndpoint = StringToEndpoint(testStringToEndpoint);
  std::string testAddress = convertedEndpoint.address;
  std::string testPort = convertedEndpoint.port;
  assert(testAddress == "127.0.0.1");
  assert(testPort == "8080");
}

void TestIsValid(void) {
  T_Endpoint testIsValidLowerEdge = {"0.0.0.0", "49152"};
  T_Endpoint testIsValidUpperEdge = {"255.255.255.255", "65535"};
  T_Endpoint testIsValidTooHighAddress = {"256.256.256.256", "1"};
  T_Endpoint testIsValidTooHighPort = {"1.1.1.1", "65536"};
  T_Endpoint testIsValidTooLongAddress = {"1.1.1.1.1", "1"};
  T_Endpoint testIsValidInvalidCharacters1 = {"a.b.c.d", "1"};
  T_Endpoint testIsValidInvalidCharacters2 = {"1.1.1.1", "a"};

  assert(testIsValidLowerEdge.isValid() == true);
  assert(testIsValidUpperEdge.isValid() == true);
  assert(testIsValidTooHighAddress.isValid() == false);
  assert(testIsValidTooHighPort.isValid() == false);
  assert(testIsValidTooLongAddress.isValid() == false);
  assert(testIsValidInvalidCharacters1.isValid() == false);
  assert(testIsValidInvalidCharacters2.isValid() == false);
}


int main() {
  TestOperatorIsEqualTo();
  TestOperatorNotEqualTo();
  TestToString();
  TestStringToEndpoint();
  TestIsValid();

  std::cout << "All tests for T_Endpoint passed" << std::endl;
  return 0;
}