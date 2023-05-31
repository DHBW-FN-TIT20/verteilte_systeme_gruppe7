/**************************************************************************************************
 * @file    test_log_manager.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    31-May-2023
 * @brief   Unit tests for class LogManger
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "log_manager.cpp"
#include <iostream>
#include <cassert>
#include <cstdio>
#include <regex>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>

/**************************************************************************************************
 * Global variabels
 *************************************************************************************************/
const std::string TEMP_FILE_NAME = "tempUnitTestFile.txt";

/**************************************************************************************************
 * Test class
 *************************************************************************************************/
class TestLogManager : public LogManager {
  public:
    std::string getTimestampString(void) const {
      return LogManager::getTimestampString();
    }

    TestLogManager(const std::string& filename) : LogManager::LogManager(filename) {}
};

/**************************************************************************************************
 * Function prototypes
 *************************************************************************************************/
void TestConstructor(void);
void TestAddLogEntry(void);
void TestGetTimestampString(void);

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TestConstructor(void) {
  try {
    LogManager testLogManagerConstructor(TEMP_FILE_NAME);
  } catch (...) {
    assert(false && "Unexpected exception occurred");
  }

  assert(0U == std::remove(TEMP_FILE_NAME.c_str()));
}

void TestAddLogEntry(void) {
  std::string testLogMessage = "Test log message";
  std::time_t tempTimestamp;
  std::string tempTimestampString;
  try {
    LogManager testAddLogEntry(TEMP_FILE_NAME);
    testAddLogEntry.addLogEntry(testLogMessage);
    tempTimestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* timeinfo = std::localtime(&tempTimestamp);
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << timeinfo->tm_mday << "." << std::setw(2) << (timeinfo->tm_mon + 1U) << "." << (timeinfo->tm_year + 1900U) << " ";
    oss << std::setw(2) << timeinfo->tm_hour << ":" << std::setw(2) << timeinfo->tm_min << ":" << std::setw(2) << timeinfo->tm_sec << ": ";
    tempTimestampString = oss.str();
  } catch(...) {
    assert(false && "Unexpected exception occcurred");
  }

  std::string lineBuffer, tempLog;
  std::ifstream readFile(TEMP_FILE_NAME);

  if(readFile.is_open()) {
    while(std::getline(readFile, lineBuffer)) {
      tempLog += lineBuffer;
    }
    readFile.close();
  }

  std::string tempExpectedString = tempTimestampString + testLogMessage;
  assert(tempLog == tempExpectedString);
  assert(0U == std::remove(TEMP_FILE_NAME.c_str()));
}

void TestGetTimestampString(void) {
  TestLogManager testGetTimestampString(TEMP_FILE_NAME);
  std::string testTimestamp = testGetTimestampString.getTimestampString();
  std::regex tempTimestampPattern(R"(\d{2}\.\d{2}\.\d{4} \d{2}:\d{2}:\d{2}: )");
  assert(std::regex_match(testTimestamp, tempTimestampPattern));
  assert(0U == std::remove(TEMP_FILE_NAME.c_str()));
}

int main() {
  TestConstructor();
  TestAddLogEntry();
  TestGetTimestampString();

  std::cout << "All tests for class LogManager passed" << std::endl;
  return 0;
}