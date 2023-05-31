/**
 *************************************************************************************************
 * @file    test_log_manager.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    31-May-2023
 * @brief   Unit tests for class LogManger
 *************************************************************************************************
 */

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "log_manager.cpp"
#include <iostream>
#include <cassert>
#include <cstdio>
#include <regex>

/*************************************************************************************************
 * Test class
 *************************************************************************************************/
class TestLogManager : public LogManager {
  public:
    std::string getTimestampString(void) const {
      return LogManager::getTimestampString();
    }

    TestLogManager(const std::string& filename) : LogManager::LogManager(filename) {}
};

/*************************************************************************************************
 * Function prototypes
 *************************************************************************************************/
void TestConstructor(void);
void TestAddLogEntry(void);
void TestGetTimestampString(void);

/*************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TestConstructor(void) {
  std::string tempFileName = "tempUnitTestFile.txt";

  try {
    LogManager testLogManagerConstructor(tempFileName);
  } catch (...) {
    assert(false && "Unexpected exception occurred");
  }

  assert(0U == std::remove(tempFileName.c_str()));
}

void TestAddLogEntry(void) {

}

void TestGetTimestampString(void) {
  std::string tempFileName = "tempUnitTestFile.txt";
  TestLogManager testGetTimestampString(tempFileName);
  std::string testTimestamp = testGetTimestampString.getTimestampString();
  std::regex tempTimestampPattern(R"(\d{2}\.\d{2}\.\d{4} \d{2}:\d{2}:\d{2}: )");
  assert(std::regex_match(testTimestamp, tempTimestampPattern));
  assert(0U == std::remove(tempFileName.c_str()));
}

int main() {
  TestConstructor();
  TestAddLogEntry();
  TestGetTimestampString();

  std::cout << "All tests for class LogManager passed" << std::endl;
  return 0;
}