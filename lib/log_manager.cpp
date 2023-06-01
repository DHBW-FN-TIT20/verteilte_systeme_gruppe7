/**************************************************************************************************
 * @file    log_manager.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    31-May-2023
 * @brief   Implementation for class LogManger
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "log_manager.h"

/**************************************************************************************************
 * Public - Class implementation
 *************************************************************************************************/

/* private member functions */
void LogManager::close(void) {
  if(mFile.is_open()) {
    mFile.close();
  }
}

std::string LogManager::getTimestampString(void) const {
  auto now = std::chrono::system_clock::now();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
  std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
  std::tm* timeinfo = std::localtime(&timestamp);
  std::ostringstream oss;

  oss << std::setfill('0') << std::setw(2) << timeinfo->tm_mday << "." << std::setw(2) << (timeinfo->tm_mon + 1U) << "." << (timeinfo->tm_year + 1900U) << " ";
  oss << std::setw(2) << timeinfo->tm_hour << ":" << std::setw(2) << timeinfo->tm_min << ":" << std::setw(2) << timeinfo->tm_sec << ":" << std::setw(3) << (milliseconds % 1000) << ": ";
  return oss.str();
}

/* public member functions */
LogManager::LogManager(const std::string& filename) : mFile(filename), mLogFileMutex() {
  if(!mFile) {
    throw::std::runtime_error("Error trying to open log file");
  }
}

LogManager::~LogManager() {
  close();
}

void LogManager::addLogEntry(const std::string& logMessage) {
  std::lock_guard<std::mutex> lock(mLogFileMutex);
  std::string timestamp = getTimestampString();
  mFile << timestamp << logMessage << std::endl;
}
